#include "gl/glad/glad.h"
#include <GLFW/glfw3.h>
#include <lua.h>
#include <honeysuckle.h>

int gl_set_viewport(lua_State *L);
int gl_draw_arrays(lua_State *L);
int gl_set_clear_color(lua_State *L);
int gl_clear(lua_State *L);

void setup_drawing(lua_State *L, int gl_index)
{
	int primitive_types = hs_create_table(L,
		hs_str_int("points", GL_POINTS),
		hs_str_int("lines", GL_LINES),
		hs_str_int("triangles", GL_TRIANGLES),
	);

	int buffer_masks = hs_create_table(L,
		hs_str_int("colorBuffer", GL_COLOR_BUFFER_BIT),
		hs_str_int("depthBuffer", GL_DEPTH_BUFFER_BIT),
		hs_str_int("stencilBuffer", GL_STENCIL_BUFFER_BIT),
	);

	hs_create_table(L,
		hs_str_cfunc("drawArrays", gl_draw_arrays),
		hs_str_cfunc("setClearColor", gl_set_clear_color),
		hs_str_cfunc("clear", gl_clear),
		hs_str_cfunc("setViewport", gl_set_viewport),

		hs_str_tbl("primitiveType", primitive_types),
		hs_str_tbl("bufferMask", buffer_masks),
	);

	lua_setfield(L, gl_index, "draw");
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


int gl_set_viewport(lua_State *L)
{
	lua_Integer x, y, w, h;
	hs_parse_args(L, hs_int(x), hs_int(y), hs_int(w), hs_int(h));
	glViewport(x, y, w, h);
	return 0;
}
