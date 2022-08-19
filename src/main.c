#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <honeysuckle.h>
#include "gl/gl.h"


int main(int argc, char **argv)
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	lua_createtable(L, 0, 2);
	int honey_index = lua_gettop(L);
	setup_gl(L, honey_index);
	setup_window(L, honey_index);
	lua_setglobal(L, "honey");

	int err = luaL_loadfile(L, "honey.lua");
	if (err != 0) {
		printf("cannot open file!\n");
		lua_close(L);
		return 0;
	}
	err = hs_call(L, 0, 0);
	if (err != 0) {
		const char *err_str = lua_tostring(L, -1);
		printf("failed to run: %s\n", err_str);
	}
	lua_close(L);
	return 0;
}
