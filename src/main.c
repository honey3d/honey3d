#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <honeysuckle.h>
#include "audio/audio.h"
#include "gl/gl.h"
#include "glm/glm.h"
#include "image/image.h"
#include "import/import.h"
#include "logging/logging.h"
#include "options/options.h"


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
	setup_audio(L, honey_index);
	setup_gl(L, honey_index);
	setup_glm(L, honey_index);
	setup_image(L, honey_index);
	setup_import(L, honey_index);
	setup_logging(L, honey_index);
	setup_window(L, honey_index);
	lua_setglobal(L, "honey");

	/* load main script */
	int err = luaL_loadfile(L, options.script_file);
	if (err != 0) {
		printf("cannot open file '%s'\n", options.script_file);
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
