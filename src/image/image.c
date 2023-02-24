#include <lua.h>
#include <lauxlib.h>
/* nanovg provides its own stb_image implementation */
/*#define STB_IMAGE_IMPLEMENTATION*/
#include "stb_image.h"
#include "util/util.h"
#include "image.h"


int empty(lua_State *L);
int load_image(lua_State *L);
int free_image(lua_State *L);


void setup_image(lua_State *L, int honey_index)
{
	struct honey_tbl_t image[] = {
		/* basic images */
		H_FUNC("null", empty),
		H_FUNC("load", load_image),
		H_FUNC("destroy", free_image),
		H_END
	};
	create_table(L, image);
	lua_setfield(L, honey_index, "image");
}


/* --===== basic images =====-- */

int empty(lua_State *L)
{
	lua_pushlightuserdata(L, NULL);
	return 1;
}


int load_image(lua_State *L)
{
	const char *filename = luaL_checkstring(L, 1);
	int requested_channels = luaL_checkinteger(L, 2);

	int width, height, channels;
	unsigned char *data = stbi_load(filename, &width, &height, &channels, requested_channels);

	if (data == NULL) {
		return luaL_error(L, "failed to load image '%s'", filename);
	}
	
	lua_pushlightuserdata(L, data);
	lua_pushinteger(L, width);
	lua_pushinteger(L, height);
	lua_pushinteger(L, channels);
	return 4;
}


int free_image(lua_State *L)
{
	void *data = lua_touserdata(L, 1);
	if (data == NULL) {
		return luaL_typerror(L, 1, "userdata");
	}
	stbi_image_free(data);
	return 0;
}
