#include "shader.h"

void honey_setup_shader(lua_State* L)
{
    honey_lua_element shader_elements[] = {
        { "new", HONEY_FUNC, { .function = honey_shader_new } },
        { "use", HONEY_FUNC, { .function = honey_shader_use } },
        { "set_int", HONEY_FUNC, { .function = honey_shader_set_int } },
        { "set_float", HONEY_FUNC, { .function = honey_shader_set_float } },
        { "set_vec3", HONEY_FUNC, { .function = honey_shader_set_vec3 } },
        { "set_vec4", HONEY_FUNC, { .function = honey_shader_set_vec4 } },
        { "set_mat3", HONEY_FUNC, { .function = honey_shader_set_mat3 } },
        { "set_mat4", HONEY_FUNC, { .function = honey_shader_set_mat4 } },
        { "delete", HONEY_FUNC, { .function = honey_shader_delete } },
    };

    honey_lua_create_table(L, shader_elements, 9);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static bool compile_shader(int* shader,
                           const char* source,
                           int shader_type,
                           char* error_message,
                           size_t error_size)
{
    int success;
    
    *shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(*shader, 1, source, NULL);
    glCompileShader(*shader);
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(*shader, error_size, NULL, error_message);
        return false;
    }

    return true;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_new(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_STRING, HONEY_STRING))
        lua_error(L);

    const char* vertex_shader_source = lua_tostring(L, 1);
    const char* fragment_shader_source = lua_tostring(L, 2);
    
    char error[1024];

    int vertex_shader, fragment_shader;
    
    if (!compile_shader(&vertex_shader,
                        vertex_shader_source,
                        GL_VERTEX_SHADER,
                        error, 1024)) {
        lua_pushstring(L, error);
        lua_error(L);
    }

    if (!compile_shader(&fragment_shader,
                        fragment_shader_source,
                        GL_FRAGMENT_SHADER,
                        error, 1024)) {
        lua_pushstring(L, error);
        lua_error(L);
    }

    int shader = glCreateProgram();
    glAttachShader(shader, vertex_shader);
    glAttachShader(shader, fragment_shader);
    glLinkProgram(shader);

    int success;
    glGetShaderiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, error);
        lua_pushstring(L, error);
        lua_error(L);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    lua_pushinteger(L, shader);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_use(lua_State* L)
{
    if (!honey_lua_validate_types(L, 1, HONEY_INT))
        lua_error(L);

    int shader = lua_tointeger(L, 1);
    glUseProgram(shader);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_set_int(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_INT, HONEY_STRING, HONEY_INT))
        lua_error(L);

    int shader       = lua_tointeger(L, 1);
    const char* name = lua_tostring(L, 2);
    int value        = lua_tointeger(L, 3);

    glUseProgram(shader);
    unsigned int location = glGetUniformLocation(shader, name);
    glUniform1i(location, value);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_set_float(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_INT, HONEY_STRING, HONEY_NUM))
        lua_error(L);

    int shader       = lua_tointeger(L, 1);
    const char* name = lua_tostring(L, 2);
    float value      = lua_tonumber(L, 3);

    glUseProgram(shader);
    unsigned int location = glGetUniformLocation(shader, name);
    glUniform1f(location, value);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void get_array(lua_State* L,
                      unsigned int* location,
                      float** value)
{
    if (!honey_lua_validate_types(L, 2, HONEY_INT, HONEY_STRING, HONEY_USERDATA))
        lua_error(L);

    int shader       = lua_tointeger(L, 1);
    const char* name = lua_tostring(L, 2);
    *value           = lua_touserdata(L, 3);

    glUseProgram(shader);
    *location = glGetUniformLocation(shader, name);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_shader_set_vec3(lua_State* L)
{
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
    if (!honey_lua_validate_types(L, 1, HONEY_INT))
        lua_error(L);

    int shader = lua_tointeger(L, 1);

    glDeleteProgram(shader);
    return 0;
}
