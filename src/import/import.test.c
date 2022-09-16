#include <lua.h>
#include <lauxlib.h>
#include <honeysuckle.h>
#include "test/honey-test.h"


#include "import.c"


void test_push_vector()
{
	lua_State *L = luaL_newstate();
	struct aiVector3D v;
	v.x = 1.5;
	v.y = 2.0;
	v.z = 3.6;

	push_vector(L, v);

	lily_assert_int_equal(lua_type(L, -1), LUA_TTABLE);

	lua_getfield(L, -1, "x");
	lily_assert_int_equal(lua_type(L, -1), LUA_TNUMBER);
	lily_assert_float_equal(lua_tonumber(L, -1), 1.5, 0.1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "y");
	lily_assert_int_equal(lua_type(L, -1), LUA_TNUMBER);
	lily_assert_float_equal(lua_tonumber(L, -1), 2.0, 0.1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "z");
	lily_assert_int_equal(lua_type(L, -1), LUA_TNUMBER);
	lily_assert_float_equal(lua_tonumber(L, -1), 3.6, 0.1);
	lua_pop(L, 1);

	lua_close(L);
}


void suite_import()
{
	lily_run_test(test_push_vector);
}
