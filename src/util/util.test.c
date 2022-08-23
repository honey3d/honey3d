#include <lua.h>
#include <lauxlib.h>
#include <honeysuckle.h>
#include "test/honey-test.h"


#include "util.c"


void test_append_table()
{
	lua_State *L = luaL_newstate();
	int a = hs_create_table(L,
		hs_str_int("one", 1),
		hs_str_int("two", 2),
	);
	int b = hs_create_table(L,
		hs_str_int("three", 3),
		hs_str_int("four", 4),
		hs_int_int(15, 2),
	);
	append_table(L, a, b);

	lua_getfield(L, a, "one");
	lily_assert_int_equal(lua_tointeger(L, -1), 1);
	
	lua_getfield(L, a, "two");
	lily_assert_int_equal(lua_tointeger(L, -1), 2);
	
	lua_getfield(L, a, "three");
	lily_assert_int_equal(lua_tointeger(L, -1), 3);

	lua_getfield(L, a, "four");
	lily_assert_int_equal(lua_tointeger(L, -1), 4);

	lua_pushinteger(L, 15);
	lua_gettable(L, a);
	lily_assert_int_equal(lua_tointeger(L, -1), 2);

	lua_close(L);
}


void suite_util()
{
	lily_run_test(test_append_table);
}
