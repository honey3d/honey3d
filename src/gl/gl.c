#include <stdlib.h>
#include <stdbool.h>
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
int glad_init(lua_State *L);
int gl_terminate(lua_State *L);
int gl_get_error(lua_State *L);

/* buffers */
int gl_create_buffer(lua_State *L);
int gl_bind_buffer(lua_State *L);
int gl_buffer_data(lua_State *L);

int gl_vertex_array_create(lua_State *L);
int gl_vertex_array_bind(lua_State *L);
int gl_vertex_attrib_pointer(lua_State *L);
int gl_vertex_array_enable_attrib(lua_State *L);

/* shaders */
int gl_create_shader(lua_State *L);
int gl_shader_set_source(lua_State *L);
int gl_shader_compile(lua_State *L);
int gl_shader_delete(lua_State *L);

int gl_program_create(lua_State *L);
int gl_program_attach_shader(lua_State *L);
int gl_program_link(lua_State *L);
int gl_program_use(lua_State *L);

/* drawing */
int gl_set_viewport(lua_State *L);
int gl_draw_arrays(lua_State *L);
int gl_set_clear_color(lua_State *L);
int gl_clear(lua_State *L);


void setup_gl(lua_State *L, int honey_index)
{
	int error_types = hs_create_table(L,
		hs_str_int("noError", GL_NO_ERROR),
		hs_str_int("invalidEnum", GL_INVALID_ENUM),
		hs_str_int("invalidValue", GL_INVALID_VALUE),
		hs_str_int("invalidOperation", GL_INVALID_OPERATION),
		hs_str_int("invalidFramebufferOperation", GL_INVALID_FRAMEBUFFER_OPERATION),
		hs_str_int("outOfMemory", GL_OUT_OF_MEMORY),
	);

	int buffer_binding_targets = hs_create_table(L,
		hs_str_int("arrayBuffer", GL_ARRAY_BUFFER),
	);

	int buffer_usage_patterns = hs_create_table(L,
		hs_str_int("streamDraw", GL_STREAM_DRAW),
		hs_str_int("staticDraw", GL_STATIC_DRAW),
		hs_str_int("dynamicDraw", GL_DYNAMIC_DRAW),
	);

	int shader_types = hs_create_table(L,
		hs_str_int("vertexShader", GL_VERTEX_SHADER),
		hs_str_int("fragmentShader", GL_FRAGMENT_SHADER),
	);

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
		hs_str_cfunc("init", gl_init),
		hs_str_cfunc("initGlad", glad_init),
		hs_str_cfunc("terminate", gl_terminate),
		hs_str_cfunc("getError", gl_get_error),

		hs_str_tbl("errorType", error_types),

		/* buffer */
		hs_str_cfunc("createBuffer", gl_create_buffer),
		hs_str_cfunc("bindBuffer", gl_bind_buffer),
		hs_str_cfunc("bufferData", gl_buffer_data),

		hs_str_cfunc("createVertexArray", gl_vertex_array_create),
		hs_str_cfunc("bindVertexArray", gl_vertex_array_bind),
		hs_str_cfunc("vertexAttribPointer", gl_vertex_attrib_pointer),
		hs_str_cfunc("vertexArrayEnableAttrib", gl_vertex_array_enable_attrib),

		hs_str_tbl("bufferTarget", buffer_binding_targets),
		hs_str_tbl("bufferUsage", buffer_usage_patterns),

		/* shader */
		hs_str_cfunc("createShader", gl_create_shader),
		hs_str_cfunc("setShaderSource", gl_shader_set_source),
		hs_str_cfunc("compileShader", gl_shader_compile),
		hs_str_cfunc("deleteShader", gl_shader_delete),

		hs_str_cfunc("createProgram", gl_program_create),
		hs_str_cfunc("programAttachShader", gl_program_attach_shader),
		hs_str_cfunc("linkProgram", gl_program_link),
		hs_str_cfunc("useProgram", gl_program_use),

		hs_str_tbl("shaderType", shader_types),

		/* drawing */
		hs_str_cfunc("drawArrays", gl_draw_arrays),
		hs_str_cfunc("setClearColor", gl_set_clear_color),
		hs_str_cfunc("clear", gl_clear),
		hs_str_cfunc("setViewport", gl_set_viewport),

		hs_str_tbl("primitiveType", primitive_types),
		hs_str_tbl("bufferMask", buffer_masks),
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


int glad_init(lua_State *L)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		hs_throw_error(L, "failed to initialize GLAD");
	}
}


int gl_terminate(lua_State *L)
{
	glfwTerminate();
	return 0;
}


int gl_get_error(lua_State *L)
{
	lua_pushinteger(L, glGetError());
	return 1;
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


int gl_buffer_data(lua_State *L)
{
	lua_Integer target, usage;
	int table;
	hs_parse_args(L, hs_int(target), hs_tbl(table), hs_int(usage));

	/* build raw buffer */
	size_t len = lua_objlen(L, table);
	float *buf = malloc(len * sizeof(float));
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
	glBufferData(target, len*sizeof(float), buf, usage);
	free(buf);
	return 0;
}


int gl_create_shader(lua_State *L)
{
	lua_Integer type;
	hs_parse_args(L, hs_int(type));
	lua_Integer shader = glCreateShader(type);
	lua_pushinteger(L, shader);
	return 1;
}


int gl_shader_set_source(lua_State *L)
{
	lua_Integer shader;
	char *code;
	hs_parse_args(L, hs_int(shader), hs_str(code));
	glShaderSource(shader, 1, &code, NULL);
	return 0;
}


int gl_shader_compile(lua_State *L)
{
	lua_Integer shader;
	hs_parse_args(L, hs_int(shader));
	glCompileShader(shader);
	int success; char log[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 1024, NULL, log);
		hs_throw_error(L, "shader compilation failed: %s", log);
	}
	return 0;
}


int gl_shader_delete(lua_State *L)
{
	lua_Integer shader;
	hs_parse_args(L, hs_int(shader));
	glDeleteShader(shader);
	return 0;
}


int gl_program_create(lua_State *L)
{
	lua_Integer program = glCreateProgram();
	lua_pushinteger(L, program);
	return 1;
}


int gl_program_attach_shader(lua_State *L)
{
	lua_Integer program, shader;
	hs_parse_args(L, hs_int(program), hs_int(shader)),
	glAttachShader(program, shader);
	return 0;
}


int gl_program_link(lua_State *L)
{
	lua_Integer program;
	hs_parse_args(L, hs_int(program));
	glLinkProgram(program);
	int success; char log[1024];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 1024, NULL, log);
		hs_throw_error(L, "shader linking failed: %s", log);
	}
	return 0;
}


int gl_program_use(lua_State *L)
{
	lua_Integer program;
	hs_parse_args(L, hs_int(program));
	glUseProgram(program);
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
