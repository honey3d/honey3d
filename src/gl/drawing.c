#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <lua.h>
#include <honeysuckle.h>
#include "util/util.h"

int gl_set_viewport(lua_State *L);
int gl_draw_arrays(lua_State *L);
int gl_draw_elements(lua_State *L);
int gl_set_clear_color(lua_State *L);
int gl_clear(lua_State *L);
int gl_gen_framebuffers(lua_State *L);
int gl_bind_framebuffer(lua_State *L);
int gl_framebuffer_texture_2d(lua_State *L);

void setup_drawing(lua_State *L, int gl_index)
{
	int tbl = hs_create_table(L,
		/* functions */
		hs_str_cfunc("DrawArrays", gl_draw_arrays),
		hs_str_cfunc("DrawElements", gl_draw_elements),
		hs_str_cfunc("ClearColor", gl_set_clear_color),
		hs_str_cfunc("Clear", gl_clear),
		hs_str_cfunc("Viewport", gl_set_viewport),

		/******** enums ********/
		/* rendering primitives */
		hs_str_int("POINTS", GL_POINTS),
		hs_str_int("LINES", GL_LINES),
		hs_str_int("TRIANGLES", GL_TRIANGLES),

		/* clear bitmasks */
		hs_str_int("COLOR_BUFFER_BIT", GL_COLOR_BUFFER_BIT),
		hs_str_int("DEPTH_BUFFER_BIT", GL_DEPTH_BUFFER_BIT),
		hs_str_int("STENCIL_BUFFER_BIT", GL_STENCIL_BUFFER_BIT),
	);

	append_table(L, gl_index, tbl);
	lua_pop(L, 1);
}

int gl_set_clear_color(lua_State *L)
{
	lua_Number r, g, b, a;
	hs_parse_args(L, hs_num(r), hs_num(g), hs_num(b), hs_num(a));
	glClearColor(r, g, b, a);
	return 0;
}


int gl_clear(lua_State *L)
{
	lua_Integer mask;
	hs_parse_args(L, hs_int(mask));
	glClear(mask);
	return 0;
}


int gl_draw_arrays(lua_State *L)
{
	lua_Integer mode, first, count;
	hs_parse_args(L, hs_int(mode), hs_int(first), hs_int(count));
	glDrawArrays(mode, first, count);
	return 0;
}


int gl_draw_elements(lua_State *L)
{
	lua_Integer mode, count, type, offset;
	hs_parse_args(L, hs_int(mode), hs_int(count), hs_int(type), hs_int(offset));
	glDrawElements(mode, count, type, (const void*)offset);
	return 0;
}


int gl_set_viewport(lua_State *L)
{
	lua_Integer x, y, w, h;
	hs_parse_args(L, hs_int(x), hs_int(y), hs_int(w), hs_int(h));
	glViewport(x, y, w, h);
	return 0;
}


int gl_gen_framebuffers(lua_State *L)
{
	int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	lua_pushinteger(L, framebuffer);
	return 1;
}


int gl_bind_framebuffer(lua_State *L)
{
	int target = luaL_checkinteger(L, 1);
	int framebuffer = luaL_checkinteger(L, 2);
	glBindFramebuffer(target, framebuffer);
	return 0;
}


int gl_framebuffer_texture_2d(lua_State *L)
{
	int target = luaL_checkinteger(L, 1);
	int attachment = luaL_checkinteger(L, 2);
	int textarget = luaL_checkinteger(L, 3);
	int texture = luaL_checkinteger(L, 4);
	int level = luaL_checkinteger(L, 5);

	glFramebufferTexture2D(target, attachment, textarget, texture, level);
	return 0;
}
