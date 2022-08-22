#include "gl/glad/glad.h"
#include <GLFW/glfw3.h>
#include <lua.h>
#include <honeysuckle.h>


int gl_texture_create(lua_State *L);
int gl_texture_bind(lua_State *L);
int gl_texture_image_2d(lua_State *L);
int gl_texture_generate_mipmaps(lua_State *L);
int gl_texture_set_active(lua_State *L);


void setup_texture(lua_State *L, int gl_index)
{
	int bind_targets = hs_create_table(L,
		hs_str_int("texture2d", GL_TEXTURE_2D),
	);

	int formats = hs_create_table(L,
		hs_str_int("rgb", GL_RGB),
		hs_str_int("rgba", GL_RGBA),
	);

	hs_create_table(L,
		hs_str_cfunc("create", gl_texture_create),
		hs_str_cfunc("bind", gl_texture_bind),
		hs_str_cfunc("bufferImage2d", gl_texture_image_2d),
		hs_str_cfunc("generateMipmaps", gl_texture_generate_mipmaps),
		hs_str_cfunc("setActiveUnit", gl_texture_set_active),

		hs_str_tbl("bindTarget", bind_targets),
		hs_str_tbl("format", formats),
	);

	lua_setfield(L, gl_index, "texture");
}


int gl_texture_create(lua_State *L)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	lua_pushinteger(L, texture);
	return 1;
}


int gl_texture_bind(lua_State *L)
{
	lua_Integer target, texture;
	hs_parse_args(L, hs_int(target), hs_int(texture));
	glBindTexture(target, texture);
	return 0;
}


int gl_texture_image_2d(lua_State *L)
{
	lua_Integer target, mipmap_level,
	            internal_format,
	            width, height,
	            format, type;
	void *data;
	hs_parse_args(L,
		hs_int(target), hs_int(mipmap_level),
		hs_int(internal_format),
		hs_int(width), hs_int(height),
		hs_int(format), hs_int(type),
		hs_light(data)
	);

	glTexImage2D(target, mipmap_level, internal_format, width, height, 0, format, type, data);
	return 0;
}


int gl_texture_generate_mipmaps(lua_State *L)
{
	lua_Integer target;
	hs_parse_args(L, hs_int(target));
	glGenerateMipmap(target);
	return 0;
}


int gl_texture_set_active(lua_State *L)
{
	lua_Integer unit;
	hs_parse_args(L, hs_int(unit));
	glActiveTexture(GL_TEXTURE0 + unit);
	return 0;
}
