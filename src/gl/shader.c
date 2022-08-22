#include "gl/glad/glad.h"
#include <GLFW/glfw3.h>
#include <lua.h>
#include <honeysuckle.h>

int gl_create_shader(lua_State *L);
int gl_shader_set_source(lua_State *L);
int gl_shader_compile(lua_State *L);
int gl_shader_delete(lua_State *L);

int gl_program_create(lua_State *L);
int gl_program_attach_shader(lua_State *L);
int gl_program_link(lua_State *L);
int gl_program_use(lua_State *L);

int gl_uniform_get_location(lua_State *L);
int gl_uniform_1i(lua_State *L);
int gl_uniform_4f(lua_State *L);


void setup_shader(lua_State *L, int gl_index)
{
	int shader_types = hs_create_table(L,
		hs_str_int("vertexShader", GL_VERTEX_SHADER),
		hs_str_int("fragmentShader", GL_FRAGMENT_SHADER),
	);

	hs_create_table(L,
		hs_str_cfunc("create", gl_create_shader),
		hs_str_cfunc("setSource", gl_shader_set_source),
		hs_str_cfunc("compile", gl_shader_compile),
		hs_str_cfunc("delete", gl_shader_delete),

		hs_str_cfunc("createProgram", gl_program_create),
		hs_str_cfunc("attachShader", gl_program_attach_shader),
		hs_str_cfunc("link", gl_program_link),
		hs_str_cfunc("use", gl_program_use),

		hs_str_cfunc("getUniformLocation", gl_uniform_get_location),
		hs_str_cfunc("uniform1i", gl_uniform_1i),
		hs_str_cfunc("uniform4f", gl_uniform_4f),

		hs_str_tbl("type", shader_types),
	);

	lua_setfield(L, gl_index, "shader");
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


int gl_uniform_get_location(lua_State *L)
{
	lua_Integer program;
	char *name;
	hs_parse_args(L, hs_int(program), hs_str(name));
	int location = glGetUniformLocation(program, (const GLchar*)name);
	lua_pushinteger(L, location);
	return 1;
}


int gl_uniform_1i(lua_State *L)
{
	lua_Integer location, v0;
	hs_parse_args(L, hs_int(location), hs_int(v0));
	glUniform1i(location, v0);
	return 0;
}


int gl_uniform_4f(lua_State *L)
{
	lua_Integer location;
	lua_Number v0, v1, v2, v3;
	hs_parse_args(L, hs_int(location), hs_num(v0), hs_num(v1), hs_num(v2), hs_num(v3));
	glUniform4f(location, v0, v1, v2, v3);
	return 0;
}
