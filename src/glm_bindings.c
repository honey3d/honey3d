#include "glm_bindings.h"

int honey_glm_vec3_mt_ref = LUA_NOREF;
int honey_glm_vec4_mt_ref = LUA_NOREF;
int honey_glm_mat3_mt_ref = LUA_NOREF;
int honey_glm_mat4_mt_ref = LUA_NOREF;

void honey_setup_glm(lua_State* L)
{
    honey_lua_create_table(L, NULL, 0);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * GLM Array Setup Functions
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

static void setup_new_array(lua_State* L,
			    honey_glm_array* array,
			    honey_glm_array_type type)
{
    unsigned int size;
    switch(type) {
    case VEC3:
	size = 3;
	break;

    case VEC4:
	size = 4;
	break;

    case MAT3:
	size = 9;
	break;

    case MAT4:
	size = 16;
	break;

    default:
	honey_lua_throw_error(L,
			      "unknown array type: %d",
			      type);
	break;
    }

    array->type = type;
    array->size = size;
    array->data = calloc(size, sizeof(float));
    if (array->data == NULL)
	honey_lua_throw_error(L,
			      "failed to allocate memory for array of type %d",
			      type);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static int honey_glm_new_vec3(lua_State* L)
{
    honey_glm_array* vec3 = lua_newuserdata(L, sizeof(honey_glm_array));
    setup_new_array(L, vec3, VEC3);
    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_glm_vec3_mt_ref);
    lua_setmetatable(L, -2);
    return 1;
}

static int honey_glm_new_vec4(lua_State* L)
{
    honey_glm_array* vec4 = lua_newuserdata(L, sizeof(honey_glm_array));
    setup_new_array(L, vec4, VEC4);
    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_glm_vec4_mt_ref);
    lua_setmetatable(L, -2);
    return 1;
}

static int honey_glm_new_mat3(lua_State* L)
{
    honey_glm_array* mat3 = lua_newuserdata(L, sizeof(honey_glm_array));
    setup_new_array(L, mat3, MAT3);
    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_glm_mat3_mt_ref);
    lua_setmetatable(L, -2);
    return 1;
}

static int honey_glm_new_mat4(lua_State* L)
{
    honey_glm_array* mat4 = lua_newuserdata(L, sizeof(honey_glm_array));
    setup_new_array(L, mat4, MAT4);
    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_glm_mat4_mt_ref);
    lua_setmetatable(L, -2);
    return 1;
}
