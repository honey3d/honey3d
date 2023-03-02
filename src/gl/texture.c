#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <lua.h>
#include <honeysuckle.h>
#include "util/util.h"


int gl_texture_create(lua_State *L);
int gl_texture_bind(lua_State *L);
int gl_texture_image_2d(lua_State *L);
int gl_texture_generate_mipmaps(lua_State *L);
int gl_texture_set_active(lua_State *L);
int gl_tex_parameter_i(lua_State *L);


void setup_texture(lua_State *L, int gl_index)
{
	int tbl = hs_create_table(L,
		/* functions */
		hs_str_cfunc("GenTextures", gl_texture_create),
		hs_str_cfunc("BindTexture", gl_texture_bind),
		hs_str_cfunc("TexImage2D", gl_texture_image_2d),
		hs_str_cfunc("GenerateMipmap", gl_texture_generate_mipmaps),
		hs_str_cfunc("ActiveTexture", gl_texture_set_active),
		hs_str_cfunc("TexParameteri", gl_tex_parameter_i),

		/******** enums ********/
		/* texture binding targets */
		hs_str_int("TEXTURE_2D", GL_TEXTURE_2D),

		/* texture data formats */
		hs_str_int("RGB", GL_RGB),
		hs_str_int("RGBA", GL_RGBA),

		/* texture parameters */
		hs_str_int("TEXTURE_WRAP_S", GL_TEXTURE_WRAP_S),
		hs_str_int("TEXTURE_WRAP_T", GL_TEXTURE_WRAP_T),
		hs_str_int("TEXTURE_MIN_FILTER", GL_TEXTURE_MIN_FILTER),
		hs_str_int("TEXTURE_MAG_FILTER", GL_TEXTURE_MAG_FILTER),
		hs_str_int("TEXTURE_SWIZZLE_R", GL_TEXTURE_SWIZZLE_R),
		hs_str_int("TEXTURE_SWIZZLE_G", GL_TEXTURE_SWIZZLE_G),
		hs_str_int("TEXTURE_SWIZZLE_B", GL_TEXTURE_SWIZZLE_B),
		hs_str_int("TEXTURE_SWIZZLE_A", GL_TEXTURE_SWIZZLE_A),

		/* wrapping types */
		hs_str_int("REPEAT", GL_REPEAT),

		/* filter types */
		hs_str_int("NEAREST", GL_NEAREST),
		hs_str_int("LINEAR", GL_LINEAR),

		/* swizzle targets */
		hs_str_int("RED", GL_RED),
		hs_str_int("GREEN", GL_GREEN),
		hs_str_int("BLUE", GL_BLUE),
		hs_str_int("ALPHA", GL_ALPHA),
		hs_str_int("ZERO", GL_ZERO),
		hs_str_int("ONE", GL_ONE),
	);

	append_table(L, gl_index, tbl);
	lua_pop(L, 1);
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


int gl_tex_parameter_i(lua_State *L)
{
	lua_Integer target, pname, param;
	hs_parse_args(L, hs_int(target), hs_int(pname), hs_int(param));
	glTexParameteri(target, pname, param);
	return 0;
}
