#include "gl/glad/glad.h"
#include <GLFW/glfw3.h>
#include <lua.h>
#include <honeysuckle.h>
#include "util/util.h"

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
int gl_uniform_1f(lua_State *L);
int gl_uniform_3f(lua_State *L);
int gl_uniform_4f(lua_State *L);

int gl_uniform_matrix_4fv(lua_State *L);


void setup_shader(lua_State *L, int gl_index)
{
	int tbl = hs_create_table(L,
		/* functions */
		hs_str_cfunc("CreateShader", gl_create_shader),
		hs_str_cfunc("ShaderSource", gl_shader_set_source),
		hs_str_cfunc("CompileShader", gl_shader_compile),
		hs_str_cfunc("DeleteShader", gl_shader_delete),

		hs_str_cfunc("CreateProgram", gl_program_create),
		hs_str_cfunc("AttachShader", gl_program_attach_shader),
		hs_str_cfunc("LinkProgram", gl_program_link),
		hs_str_cfunc("UseProgram", gl_program_use),

		hs_str_cfunc("GetUniformLocation", gl_uniform_get_location),
		hs_str_cfunc("Uniform1i", gl_uniform_1i),
		hs_str_cfunc("Uniform1f", gl_uniform_1i),
		hs_str_cfunc("Uniform3f", gl_uniform_1i),
		hs_str_cfunc("Uniform4f", gl_uniform_4f),

		hs_str_cfunc("UniformMatrix4fv", gl_uniform_matrix_4fv),

		/******** enums ********/
		/* shader types */
		hs_str_int("VERTEX_SHADER", GL_VERTEX_SHADER),
		hs_str_int("FRAGMENT_SHADER", GL_FRAGMENT_SHADER),
	);

	append_table(L, gl_index, tbl);
	lua_pop(L, 1);
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
	glShaderSource(shader, 1, (const GLchar * const*)&code, NULL);
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


int gl_uniform_1f(lua_State *L)
{
	int location = luaL_checkinteger(L, 1);
	double value = luaL_checknumber(L, 2);
	glUniform1f(location, value);
	return 0;
}


int gl_uniform_3f(lua_State *L)
{
	int location = luaL_checkinteger(L, 1);
	double v0 = luaL_checknumber(L, 2);
	double v1 = luaL_checknumber(L, 3);
	double v2 = luaL_checknumber(L, 4);
	glUniform3f(location, v0, v1, v2);
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


int gl_uniform_matrix_4fv(lua_State *L)
{
	lua_Integer location;
	bool transpose;
	void *ptr;
	hs_parse_args(L, hs_int(location), hs_bool(transpose), hs_user(ptr));

	float *value = ptr;
	glUniformMatrix4fv(location, 1, transpose, value);
	return 0;
}
