#include <lua.h>
#include <honeysuckle.h>
#include <assimp/scene.h>
#include "import.h"


void push_vector(lua_State *L, struct aiVector3D vec)
{
	hs_create_table(L,
		hs_str_num("x", vec.x),
		hs_str_num("y", vec.y),
		hs_str_num("z", vec.z),
	);
}


void push_face(lua_State *L, struct aiFace face)
{
	lua_createtable(L, face.mNumIndices, 0);
	int tbl = lua_gettop(L);

	for (int i=0; i<face.mNumIndices; i++) {
		lua_pushinteger(L, face.mIndices[i]);
		lua_rawseti(L, tbl, i+1);
	}
}


void push_aistring(lua_State *L, struct aiString str)
{
	lua_pushstring(L, str.data);
}


void push_mesh(lua_State *L, struct aiMesh mesh)
{
	int count = mesh.mNumVertices;

	/* create tables */
	lua_createtable(L, count, 0);
	int vertices = lua_gettop(L);

	/* populate */
	for (int i=0; i<count; i++) {
		/* positions */
		push_vector(L, mesh.mVertices[i]);
		lua_rawseti(L, vertices, i+1);
	}

	/* create mesh table */
	lua_createtable(L, 0, 1);
	int meshtbl = lua_gettop(L);

	lua_pushvalue(L, vertices);
	lua_setfield(L, meshtbl, "vertices");

	/* clean up */
	lua_remove(L, vertices);
}
