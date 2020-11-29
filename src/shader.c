#include "shader.h"

int honey_shader_mt_ref = LUA_NOREF;

void honey_setup_shader(lua_State* L)
{
    honey_lua_create_table
	(L, 2,
	 HONEY_TABLE, "__index", 7,

	 /* honey.shader.prototype */
	 HONEY_FUNCTION, "use",       honey_shader_use,
	 HONEY_FUNCTION, "set_int",   honey_shader_set_int,
	 HONEY_FUNCTION, "set_float", honey_shader_set_float,
	 HONEY_FUNCTION, "set_vec3",  honey_shader_set_vec3,
	 HONEY_FUNCTION, "set_vec4",  honey_shader_set_vec4,
	 HONEY_FUNCTION, "set_mat3",  honey_shader_set_mat3,
	 HONEY_FUNCTION, "set_mat4",  honey_shader_set_mat4,

	 HONEY_FUNCTION, "__gc", honey_shader_delete);

    honey_shader_mt_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    lua_pushcfunction(L, honey_shader_new);
    lua_setfield(L, -2, "shader");
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_new(lua_State* L)
{
    char* vertex_shader_source, *fragment_shader_source;
    honey_lua_parse_arguments
	(L, 1,
	 2, HONEY_STRING, &vertex_shader_source, HONEY_STRING, &fragment_shader_source);

    int success;
    char error[1024];

    int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1,
                   (const char* const*) &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 1024, NULL, error);
	honey_lua_throw_error(L, "error compiling vertex shader: %s",
			      error);
    }

    int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1,
                   (const char* const*) &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 1024, NULL, error);
	honey_lua_throw_error(L, "error compiling fragment shader: %s",
			      error);
    }

    int program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glGetShaderiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(program, 1024, NULL, error);
	honey_lua_throw_error(L, "error linking shader program: %s",
			      error);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    int* shader = lua_newuserdata(L, sizeof(int));
    *shader = program;

    if (honey_shader_mt_ref == LUA_NOREF ||
	honey_shader_mt_ref == LUA_REFNIL)
	honey_lua_throw_error
	    (L, "cannot create shader as there is no shader metatable set up.");

    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_shader_mt_ref);
    lua_setmetatable(L, -2);
    
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_use(lua_State* L)
{
    int *shader;
    honey_lua_parse_arguments
	(L, 1,
	 1, HONEY_USERDATA, &shader);
    
    glUseProgram(*shader);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_set_int(lua_State* L)
{
    int *shader, value;
    char* name;
    
    honey_lua_parse_arguments
	(L, 1,
	 3,
	 HONEY_USERDATA, &shader,
	 HONEY_STRING, &name,
	 HONEY_INTEGER, &value);

    glUseProgram(*shader);
    unsigned int location = glGetUniformLocation(*shader, name);
    glUniform1i(location, value);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_set_float(lua_State* L)
{
    int *shader; char* name; float value;
    honey_lua_parse_arguments
	(L, 1, 3,
	 HONEY_USERDATA, &shader,
	 HONEY_STRING, &name,
	 HONEY_NUMBER, &value);
    
    glUseProgram(*shader);
    unsigned int location = glGetUniformLocation(*shader, name);
    glUniform1f(location, value);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_set_vec3(lua_State* L)
{
    int *shader; char* name; honey_glm_array* array;
    honey_lua_parse_arguments
	(L, 1, 3,
	 HONEY_USERDATA, &shader,
	 HONEY_STRING, &name,
	 HONEY_USERDATA, &array);

    if (array->type != VEC3)
	honey_lua_throw_error(L,
			      "expected glm array of type VEC3 (%d), but got %d instead",
			      VEC3,
			      array->type);

    glUseProgram(*shader);
    unsigned int location = glGetUniformLocation(*shader, name);
    glUniform3fv(location, 1, array->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_set_vec4(lua_State* L)
{
    int *shader; char* name; honey_glm_array* array;
    honey_lua_parse_arguments
	(L, 1, 3,
	 HONEY_USERDATA, &shader,
	 HONEY_STRING, &name,
	 HONEY_USERDATA, &array);

    if (array->type != VEC4)
	honey_lua_throw_error(L,
			      "expected glm array of type VEC4 (%d), but got %d instead",
			      VEC4,
			      array->type);
    
    glUseProgram(*shader);
    unsigned int location = glGetUniformLocation(*shader, name);
    glUniform4fv(location, 1, array->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_set_mat3(lua_State* L)
{
    int *shader; char* name; honey_glm_array* array;
    honey_lua_parse_arguments
	(L, 1, 3,
	 HONEY_USERDATA, &shader,
	 HONEY_STRING, &name,
	 HONEY_USERDATA, &array);
			    

    if (array->type != MAT3)
	honey_lua_throw_error(L,
			      "expected glm array of type MAT3 (%d), but got %d instead",
			      MAT3,
			      array->type);
    
    glUseProgram(*shader);
    unsigned int location = glGetUniformLocation(*shader, name);
    glUniformMatrix3fv(location, 1, GL_FALSE, array->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_set_mat4(lua_State* L)
{
    int *shader; char* name; honey_glm_array* array;
    honey_lua_parse_arguments
	(L, 1, 3,
	 HONEY_USERDATA, &shader,
	 HONEY_STRING, &name,
	 HONEY_USERDATA, &array);


    if (array->type != MAT4)
	honey_lua_throw_error(L,
			      "expected glm array of type MAT4 (%d), but got %d instead",
			      MAT4,
			      array->type);

    glUseProgram(*shader);
    unsigned int location = glGetUniformLocation(*shader, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, array->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_delete(lua_State* L)
{
    int *shader;
    honey_lua_parse_arguments
	(L, 1, 1, HONEY_USERDATA, &shader);

    glDeleteProgram(*shader);
    return 0;
}
