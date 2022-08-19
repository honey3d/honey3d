#include <stdlib.h>
#include "gl/glad/glad.h"
#include <GLFW/glfw3.h>
#include <lua.h>
#include <honeysuckle.h>

/* needs to be here because glad uses macros to define glBufferData */
#ifdef HONEY_TEST_H
#undef glBufferData
#define glBufferData mock_glBufferData_
#endif


int gl_init(lua_State *L);
int gl_terminate(lua_State *L);
int gl_create_buffer(lua_State *L);
int gl_bind_buffer(lua_State *L);
int gl_buffer_data(lua_State *L);


void setup_gl(lua_State *L, int honey_index)
{
	int buffer_binding_targets = hs_create_table(L,
		hs_str_int("arrayBuffer", GL_ARRAY_BUFFER),
	);

	hs_create_table(L,
		hs_str_cfunc("init", gl_init),
		hs_str_cfunc("terminate", gl_terminate),
		hs_str_cfunc("createBuffer", gl_create_buffer),
		hs_str_cfunc("bindBuffer", gl_bind_buffer),
		hs_str_tbl("bufferTarget", buffer_binding_targets),
		hs_str_cfunc("bufferData", gl_buffer_data),
	);
	lua_setfield(L, honey_index, "gl");
}


int gl_init(lua_State *L)
{
	if (!glfwInit()) {
		hs_throw_error(L, "failed to initialize GLFW");
	}
	return 0;
}


int gl_terminate(lua_State *L)
{
	glfwTerminate();
	return 0;
}


int gl_create_buffer(lua_State *L)
{
	int buf;
	glGenBuffers(1, &buf);
	lua_pushinteger(L, buf);
	return 1;
}


int gl_bind_buffer(lua_State *L)
{
	lua_Integer buf, target;
	hs_parse_args(L, hs_int(buf), hs_int(target));
	glBindBuffer(buf, target);
	return 0;
}


int gl_buffer_data(lua_State *L)
{
	lua_Integer target, usage;
	int table;
	hs_parse_args(L, hs_int(target), hs_tbl(table), hs_int(usage));

	/* build raw buffer */
	size_t len = lua_objlen(L, table);
	lua_Number *buf = malloc(len * sizeof(lua_Number));
	if (buf == NULL)
		hs_throw_error(L, "failed to allocate intermediary buffer");
	for (int i=0; i<len; i++) {
		lua_rawgeti(L, table, i+1);
		if (!lua_isnumber(L, -1)) {
			hs_throw_error(L, "all table items must be numbers (failed at index %d)", i);
		}
		buf[i] = lua_tonumber(L, -1);
		lua_pop(L, 1);
	}

	/* call */
	glBufferData(target, len*sizeof(lua_Number), buf, usage);
	free(buf);
	return 0;
}
