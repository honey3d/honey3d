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
		/* add one to the index bc lua is 1-indexed */
		lua_pushinteger(L, face.mIndices[i]+1);
		lua_rawseti(L, tbl, i+1);
	}
}


void push_aistring(lua_State *L, struct aiString str)
{
	lua_pushstring(L, str.data);
}


void push_mesh(lua_State *L, struct aiMesh mesh)
{
	/* create mesh table */
	lua_createtable(L, 0, 1);
	int meshtbl = lua_gettop(L);

	int count = mesh.mNumVertices;
	int pop_count = 0;

	/* create tables */
	lua_createtable(L, count, 0);
	int vertices = lua_gettop(L);
	pop_count += 1;

	int normals = 0;
	if (mesh.mNormals != NULL) {
		lua_createtable(L, count, 0);
		normals = lua_gettop(L);
		pop_count += 1;
	}

	/* populate vertices */
	for (int i=0; i<count; i++) {
		/* positions */
		push_vector(L, mesh.mVertices[i]);
		lua_rawseti(L, vertices, i+1);

		/* normals */
		if (normals) {
			push_vector(L, mesh.mNormals[i]);
			lua_rawseti(L, normals, i+1);
		}
	}

	/* populate faces */
	int faces = 0;
	if (mesh.mNumFaces != 0) {
		lua_createtable(L, mesh.mNumFaces, 0);
		faces = lua_gettop(L);
		pop_count += 1;
		for (int i=0; i<mesh.mNumFaces; i++) {
			push_face(L, mesh.mFaces[i]);
			lua_rawseti(L, faces, i+1);
		}
	}

	/* assign values */
	lua_pushvalue(L, vertices);
	lua_setfield(L, meshtbl, "vertices");

	if (normals) {
		lua_pushvalue(L, normals);
		lua_setfield(L, meshtbl, "normals");
	}

	if (faces) {
		lua_pushvalue(L, faces);
		lua_setfield(L, meshtbl, "faces");
	}

	/* clean up */
	lua_pop(L, pop_count);
}
