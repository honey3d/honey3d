#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <honeysuckle.h>
#include "options/options.h"
#include "modules.h"


void print_load_error(lua_State *L, const char *script_file, int error_type);

int main(int argc, char **argv)
{
	/* parse command-line options */
	struct honey_options options;
	int result = parse_options(&options, argc, argv);
	if (result == EXIT_FAILURE) return 1;
	else if (result == EXIT_SUCCESS) return 0;

	/* set up lua state */
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	/* load honey bindings */
	lua_createtable(L, 0, 2);
	int honey_index = lua_gettop(L);
	#define X(module) setup_ ## module (L, honey_index);
	HONEY_MODULES
	#undef X
	lua_setglobal(L, "honey");

	/* load main script */
	int err = luaL_loadfile(L, options.script_file);
	if (err != 0) {
		print_load_error(L, options.script_file, err);
		lua_close(L);
		return 0;
	}

	/* run */
	err = hs_call(L, 0, 0);
	if (err != 0) {
		const char *err_str = lua_tostring(L, -1);
		printf("failed to run: \n%s\n", err_str);
	}

	/* clean up */
	lua_close(L);
	return 0;
}


void print_load_error(lua_State *L, const char *script_file, int error_type)
{
	switch(error_type) {
	case LUA_ERRFILE:
		printf("error: cannot open file '%s'\n", script_file);
		break;
	
	case LUA_ERRSYNTAX:
		printf("error: failed to compile file: %s\n", lua_tostring(L, -1));
		break;
	
	case LUA_ERRMEM:
		printf("error: memory error: %s\n", lua_tostring(L, -1));
		break;
	
	default:
		printf("error: an unknown error occured when trying to load file '%s'.\n", script_file);
		break;
	};
}
