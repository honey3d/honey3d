#include "cglm_bindings.h"

void honey_setup_cglm(lua_State* L)
{
    honey_lua_element cglm_elements[] = {
        { "new_array_zero", HONEY_FUNC, { .function = honey_cglm_new_array_zero } },
        { "set_value", HONEY_FUNC, { .function = honey_cglm_array_set_value } },
        { "get_value", HONEY_FUNC, { .function = honey_cglm_array_get_value } },
    };

    honey_lua_create_table(L, cglm_elements, 3);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_new_array_zero(lua_State* L)
{
    if (!honey_lua_validate_types(L, 1, HONEY_INT))
        lua_error(L);

    int size = lua_tointeger(L, 1);
    
    float* array = lua_newuserdata(L, size*sizeof(float));
    memset(array, 0, size*sizeof(float));
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_array_set_value(lua_State* L)
{
    if (!honey_lua_validate_types(L, 3, HONEY_USERDATA, HONEY_INT, HONEY_NUM))
        lua_error(L);

    float* array = lua_touserdata(L, 1);
    int index = lua_tointeger(L, 2);
    float value = lua_tonumber(L, 3);

    array[index] = value;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_array_get_value(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_USERDATA, HONEY_INT))
        lua_error(L);

    float* array = lua_touserdata(L, 1);
    int index = lua_tointeger(L, 2);

    lua_pushnumber(L, array[index]);
    return 1;
}

