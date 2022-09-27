#include <lua.h>
#include <honeysuckle.h>
/* assimp provides its own stb_image implementation */
/*#define STB_IMAGE_IMPLEMENTATION*/
#include "stb_image.h"
#include "image.h"

int load_image(lua_State *L)
{
	char *filename;
	lua_Integer requested_channels;
	hs_parse_args(L, hs_str(filename), hs_int(requested_channels));

	int width, height, channels;
	unsigned char *data = stbi_load(filename, &width, &height, &channels, requested_channels);

	if (data == NULL) hs_throw_error(L, "failed to load image '%s'", filename);
	
	lua_pushlightuserdata(L, data);
	lua_pushinteger(L, width);
	lua_pushinteger(L, height);
	lua_pushinteger(L, channels);
	return 4;
}


int free_image(lua_State *L)
{
	void *data;
	hs_parse_args(L, hs_light(data));
	stbi_image_free(data);
	return 0;
}


void setup_image(lua_State *L, int honey_index)
{
	hs_create_table(L,
		hs_str_cfunc("load", load_image),
		hs_str_cfunc("destroy", free_image),
	);

	lua_setfield(L, honey_index, "image");
}
