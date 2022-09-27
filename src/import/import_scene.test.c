#include <lua.h>
#include <lauxlib.h>
#include <assimp/scene.h>
#include "test/lily-test.h"
#include "import.test.h"


void mock_push_mesh(lua_State *L, struct aiMesh *mesh)
{
	lua_pushlightuserdata(L, mesh);
}

void mock_push_node(lua_State *L, struct aiNode *node)
{
	lua_pushlightuserdata(L, node);
}

#define TEST_IMPORT_SCENE

#define push_mesh mock_push_mesh
#define push_node mock_push_node
#include "import.c"
#undef push_mesh
#undef push_node


void test_push_scene()
{
	lua_State *L = luaL_newstate();

	struct aiScene scene;
	const int num_meshes = 8;
	struct aiMesh m[num_meshes];
	struct aiMesh *meshes[num_meshes];
	for (int i=0; i<num_meshes; i++) {
		meshes[i] = m + i;
	}
	
	scene.mMeshes = meshes;
	scene.mNumMeshes = num_meshes;

	struct aiNode root;
	scene.mRootNode = &root;

	/* push */
	int top = lua_gettop(L);
	push_scene(L, &scene);

	lily_assert_int_equal(lua_gettop(L) - top, 1);
	lily_assert_int_equal(lua_type(L, -1), LUA_TTABLE);
	int scenetbl = lua_gettop(L);

	lua_getfield(L, scenetbl, "meshes");
	lily_assert_int_equal(lua_objlen(L, -1), num_meshes);
	int meshtbl = lua_gettop(L);

	for (int i=0; i<num_meshes; i++) {
		lua_rawgeti(L, meshtbl, i+1);
		lily_assert_ptr_equal(lua_touserdata(L, -1), m+i);
		lua_pop(L, 1);
	}
	lua_pop(L, 1);

	lua_getfield(L, scenetbl, "rootNode");
	lily_assert_int_equal(lua_type(L, -1), LUA_TLIGHTUSERDATA);
	lily_assert_ptr_equal(lua_touserdata(L, -1), &root);
	lua_pop(L, 2);

	lua_close(L);
}
