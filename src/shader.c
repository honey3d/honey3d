#include "shader.h"

int honey_shader_mt_ref = LUA_NOREF;

void honey_setup_shader(lua_State* L)
{
    honey_lua_element shader_elements[] = {
        { "new", HONEY_FUNCTION, { .function = honey_shader_new } },
        { "use", HONEY_FUNCTION, { .function = honey_shader_use } },
        { "set_int", HONEY_FUNCTION, { .function = honey_shader_set_int } },
        { "set_float", HONEY_FUNCTION, { .function = honey_shader_set_float } },
        { "set_vec3", HONEY_FUNCTION, { .function = honey_shader_set_vec3 } },
        { "set_vec4", HONEY_FUNCTION, { .function = honey_shader_set_vec4 } },
        { "set_mat3", HONEY_FUNCTION, { .function = honey_shader_set_mat3 } },
        { "set_mat4", HONEY_FUNCTION, { .function = honey_shader_set_mat4 } },
        { "delete", HONEY_FUNCTION, { .function = honey_shader_delete } },
    };

    honey_lua_create_table(L, shader_elements, 9);
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
                   &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 1024, NULL, error);
	honey_lua_throw_error(L, "error compiling vertex shader: %s",
			      error);
    }

    int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1,
                   &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 1024, NULL, error);
	honey_lua_throw_error(L, "error compiling fragment shader: %s",
			      error);
    }

    int shader = glCreateProgram();
    glAttachShader(shader, vertex_shader);
    glAttachShader(shader, fragment_shader);
    glLinkProgram(shader);

    glGetShaderiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, error);
	honey_lua_throw_error(L, "error linking shader program: %s",
			      error);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    lua_pushinteger(L, shader);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_use(lua_State* L)
{
    int shader;
    honey_lua_parse_arguments
	(L, 1,
	 1, HONEY_INTEGER, &shader);
    
    glUseProgram(shader);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_set_int(lua_State* L)
{
    int shader, value;
    char* name;
    
    honey_lua_parse_arguments
	(L, 1,
	 3,
	 HONEY_INTEGER, &shader,
	 HONEY_STRING, &name,
	 HONEY_INTEGER, &value);

    glUseProgram(shader);
    unsigned int location = glGetUniformLocation(shader, name);
    glUniform1i(location, value);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_set_float(lua_State* L)
{
    int shader; char* name; float value;
    honey_lua_parse_arguments
	(L, 1, 3,
	 HONEY_INTEGER, &shader,
	 HONEY_STRING, &name,
	 HONEY_NUMBER, &value);
    
    glUseProgram(shader);
    unsigned int location = glGetUniformLocation(shader, name);
    glUniform1f(location, value);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_set_vec3(lua_State* L)
{
    int shader; char* name; float* array;
    honey_lua_parse_arguments
	(L, 1, 3,
	 HONEY_INTEGER, &shader,
	 HONEY_STRING, &name,
	 HONEY_USERDATA, &array);
			    
    
    unsigned int location;
    float* array;
    get_array(L, &location, &array);

    glUniform3fv(location, 1, array);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_set_vec4(lua_State* L)
{
    unsigned int location;
    float* array;
    get_array(L, &location, &array);

    glUniform4fv(location, 1, array);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_set_mat3(lua_State* L)
{
    unsigned int location;
    float* array;
    get_array(L, &location, &array);

    glUniformMatrix3fv(location, 1, GL_FALSE, array);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_set_mat4(lua_State* L)
{
    unsigned int location;
    float* array;
    get_array(L, &location, &array);

    glUniformMatrix4fv(location, 1, GL_FALSE, array);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_delete(lua_State* L)
{
    if (!honey_lua_validate_types(L, 1, HONEY_INTEGER))
        lua_error(L);

    int shader = lua_tointeger(L, 1);

    glDeleteProgram(shader);
    return 0;
}
