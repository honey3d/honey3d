#include <lua.h>

void append_table(lua_State *L, int tbl_a, int tbl_b)
{
	lua_pushnil(L);
	while(lua_next(L, tbl_b) != 0) {
		lua_pushvalue(L, -2); // key
		lua_pushvalue(L, -2); // value
		lua_settable(L, tbl_a);
		lua_pop(L, 1);
	}
}
