#include <assimp/scene.h>
#include <lua.h>
#include <lauxlib.h>
#include <honeysuckle.h>
#include "test/lily-test.h"
#include "import.test.h"


#include "import.c"


#define MESH_COUNT 13
void test_push_node()
{
	lua_State *L = luaL_newstate();

	int meshes[MESH_COUNT];
	for (int i=0; i<MESH_COUNT; i++)
		meshes[i] = i;
	
	/* first layer node */
	struct aiNode root;
	root.mParent = NULL;
	root.mMeshes = meshes;
	root.mNumMeshes = 3;

	/* second layer nodes */
	struct aiNode nodeA, nodeB;
	struct aiNode *root_children[] = { &nodeA, &nodeB };
	root.mChildren = root_children;
	root.mNumChildren = 2;

	nodeA.mMeshes = meshes + 3;
	nodeA.mNumMeshes = 2;
	nodeA.mChildren = NULL;
	
	nodeB.mMeshes = meshes + 5;
	nodeB.mNumMeshes = 2;
	nodeB.mChildren = NULL;

	/* third layer nodes */
	struct aiNode nodeC;
	struct aiNode *a_children[] = { &nodeC };
	nodeA.mChildren = a_children;
	nodeC.mMeshes = meshes + 7;
	nodeC.mNumMeshes = 1;
	nodeC.mChildren = NULL;

	/* push */
	int top = lua_gettop(L);
	push_node(L, &root);

	/* check */
	lily_assert_int_equal(top+1, lua_gettop(L));
	lily_assert_int_equal(lua_type(L, -1), LUA_TTABLE);

	int nodetbl = lua_gettop(L);

	/* check meshes */
	lua_getfield(L, nodetbl, "meshes");
	lily_assert_int_equal(lua_type(L, -1), LUA_TTABLE);

	lua_rawgeti(L, -1, 1);
	lily_assert_int_equal(lua_type(L, -1), LUA_TNUMBER);
	lily_assert_int_equal(lua_tointeger(L, -1), 1);
	lua_pop(L, 1);

	lua_rawgeti(L, -1, 2);
	lily_assert_int_equal(lua_type(L, -1), LUA_TNUMBER);
	lily_assert_int_equal(lua_tointeger(L, -1), 2);
	lua_pop(L, 1);

	lua_rawgeti(L, -1, 3);
	lily_assert_int_equal(lua_type(L, -1), LUA_TNUMBER);
	lily_assert_int_equal(lua_tointeger(L, -1), 3);
	lua_pop(L, 1);

	/* check children */
	lua_getfield(L, nodetbl, "children");
	lily_assert_int_equal(lua_objlen(L, -1), 2);
	int childrentbl = lua_gettop(L);
	lily_assert_int_equal(lua_type(L, -1), LUA_TTABLE);

	lua_rawgeti(L, childrentbl, 1);
	lily_assert_int_equal(lua_type(L, -1), LUA_TTABLE);
	int atbl = lua_gettop(L);
	lua_getfield(L, atbl, "meshes");
	lily_assert_int_equal(lua_type(L, -1), LUA_TTABLE);

	lua_rawgeti(L, -1, 1);
	lily_assert_int_equal(lua_type(L, -1), LUA_TNUMBER);
	lily_assert_int_equal(lua_tointeger(L, -1), 4);
	lua_pop(L, 1);

	lua_rawgeti(L, -1, 2);
	lily_assert_int_equal(lua_type(L, -1), LUA_TNUMBER);
	lily_assert_int_equal(lua_tointeger(L, -1), 5);
	lua_pop(L, 2);

	lua_rawgeti(L, childrentbl, 2);
	lily_assert_int_equal(lua_type(L, -1), LUA_TTABLE);
	int btbl = lua_gettop(L);
	lua_getfield(L, btbl, "meshes");
	lily_assert_int_equal(lua_type(L, -1), LUA_TTABLE);

	lua_rawgeti(L, -1, 1);
	lily_assert_int_equal(lua_type(L, -1), LUA_TNUMBER);
	lily_assert_int_equal(lua_tointeger(L, -1), 6);
	lua_pop(L, 1);

	lua_rawgeti(L, -1, 2);
	lily_assert_int_equal(lua_type(L, -1), LUA_TNUMBER);
	lily_assert_int_equal(lua_tointeger(L, -1), 7);
	lua_pop(L, 2);

	lua_getfield(L, btbl, "children");
	lily_assert_int_equal(lua_type(L, -1), LUA_TNIL);
	lua_pop(L, 1);

	/* check layer 3 */
	lua_getfield(L, atbl, "children");
	childrentbl = lua_gettop(L);
	lily_assert_int_equal(lua_type(L, -1), LUA_TTABLE);
	lily_assert_int_equal(lua_objlen(L, -1), 1);

	lua_rawgeti(L, childrentbl, 1);
	lily_assert_int_equal(lua_type(L, -1), LUA_TTABLE);
	int ctbl = lua_gettop(L);
	lua_getfield(L, ctbl, "meshes");
	lily_assert_int_equal(lua_type(L, -1), LUA_TTABLE);
	lily_assert_int_equal(lua_objlen(L, -1), 1);
	lua_rawgeti(L, -1, 1);
	lily_assert_int_equal(lua_type(L, -1), LUA_TNUMBER);
	lily_assert_int_equal(lua_tointeger(L, -1), 8);

	lua_close(L);
}
