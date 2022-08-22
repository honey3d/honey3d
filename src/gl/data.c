#include <stdlib.h>
#include <stdbool.h>
#include "gl/glad/glad.h"
#include <GLFW/glfw3.h>
#include <lua.h>
#include <honeysuckle.h>
#include "gl.h"

int gl_create_buffer(lua_State *L);
int gl_bind_buffer(lua_State *L);
int gl_buffer_data(lua_State *L);

int gl_vertex_array_create(lua_State *L);
int gl_vertex_array_bind(lua_State *L);
int gl_vertex_attrib_pointer(lua_State *L);
int gl_vertex_array_enable_attrib(lua_State *L);


void setup_data(lua_State *L, int gl_index)
{
	int buffer_binding_targets = hs_create_table(L,
		hs_str_int("arrayBuffer", GL_ARRAY_BUFFER),
		hs_str_int("elementArrayBuffer", GL_ELEMENT_ARRAY_BUFFER),
	);

	int buffer_usage_patterns = hs_create_table(L,
		hs_str_int("streamDraw", GL_STREAM_DRAW),
		hs_str_int("staticDraw", GL_STATIC_DRAW),
		hs_str_int("dynamicDraw", GL_DYNAMIC_DRAW),
	);

	hs_create_table(L,
		hs_str_cfunc("createBuffer", gl_create_buffer),
		hs_str_cfunc("bindBuffer", gl_bind_buffer),
		hs_str_cfunc("bufferData", gl_buffer_data),

		hs_str_cfunc("createVertexArray", gl_vertex_array_create),
		hs_str_cfunc("bindVertexArray", gl_vertex_array_bind),
		hs_str_cfunc("vertexAttribPointer", gl_vertex_attrib_pointer),
		hs_str_cfunc("vertexArrayEnableAttrib", gl_vertex_array_enable_attrib),

		hs_str_tbl("bufferTarget", buffer_binding_targets),
		hs_str_tbl("bufferUsage", buffer_usage_patterns),
	);	

	lua_setfield(L, gl_index, "data");
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
	lua_Integer target, buf;
	hs_parse_args(L, hs_int(target), hs_int(buf));
	glBindBuffer(target, buf);
	return 0;
}


#define GET_BUFFER_TYPE(type, name, conversion) \
	void * get_buffer_ ## name (lua_State *L, size_t *sz, int tbl) { \
		size_t len = lua_objlen(L, tbl); \
		*sz = len * sizeof(type); \
		type *buf = malloc(*sz); \
		if (buf == NULL) \
			hs_throw_error(L, "failed to allocate intermediary buffer"); \
		for (int i=0; i<len; i++) { \
			lua_rawgeti(L, tbl, i+1); \
			if (!lua_isnumber(L, -1)) \
				hs_throw_error(L, "all elements must be numbers (failed at index %d)", i); \
			buf[i] = conversion(L, -1); \
			lua_pop(L, 1); \
		} \
		return buf; \
	}

GET_BUFFER_TYPE(unsigned int, uint, lua_tointeger)
GET_BUFFER_TYPE(int, int, lua_tointeger)
GET_BUFFER_TYPE(float, float, lua_tonumber)

int gl_buffer_data(lua_State *L)
{
	lua_Integer target, type, usage;
	int table;
	hs_parse_args(L, hs_int(target), hs_int(type), hs_tbl(table), hs_int(usage));

	/* build raw buffer */
	void *buf; size_t len;
	switch(type) {
	case GL_UNSIGNED_INT:
		buf = get_buffer_uint(L, &len, table);
		break;

	case GL_INT:
		buf = get_buffer_int(L, &len, table);
		break;

	case GL_FLOAT:
		buf = get_buffer_float(L, &len, table);
		break;

	default:
		hs_throw_error(L, "invalid type");
	}

	/* call */
	glBufferData(target, len, buf, usage);
	free(buf);
	return 0;
}


int gl_vertex_array_create(lua_State *L)
{
	int array;
	glGenVertexArrays(1, &array);
	lua_pushinteger(L, array);
	return 1;
}


int gl_vertex_array_bind(lua_State *L)
{
	lua_Integer array;
	hs_parse_args(L, hs_int(array));
	glBindVertexArray(array);
	return 0;
}


int gl_vertex_attrib_pointer(lua_State *L)
{
	lua_Integer index, size, stride, offset;
	bool normalized;
	hs_parse_args(L, hs_int(index), hs_int(size), hs_bool(normalized), hs_int(stride), hs_int(offset));
	glVertexAttribPointer(index, size, GL_FLOAT, 
	                      normalized, stride*sizeof(float), 
	                      (void*) (offset*sizeof(float)));
	return 0;
}


int gl_vertex_array_enable_attrib(lua_State *L)
{
	lua_Integer index;
	hs_parse_args(L, hs_int(index));
	glEnableVertexAttribArray(index);
	return 0;
}
