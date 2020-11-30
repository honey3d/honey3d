#include "glm_bindings.h"

int honey_glm_vec3_mt_ref = LUA_NOREF;
int honey_glm_vec4_mt_ref = LUA_NOREF;
int honey_glm_mat3_mt_ref = LUA_NOREF;
int honey_glm_mat4_mt_ref = LUA_NOREF;

void honey_setup_glm(lua_State* L)
{
    /* vec3 metatable */
    honey_lua_create_table
	(L, 2,
	 HONEY_TABLE, "__index", 21,
	 HONEY_FUNCTION, "copyTo", honey_glm_vec3_copy,
	 HONEY_FUNCTION, "zero", honey_glm_vec3_zero,
	 HONEY_FUNCTION, "eye", honey_glm_vec3_eye,
	 HONEY_FUNCTION, "dot", honey_glm_vec3_dot,
	 HONEY_FUNCTION, "cross", honey_glm_vec3_cross,
	 HONEY_FUNCTION, "crossn", honey_glm_vec3_crossn,
	 HONEY_FUNCTION, "norm2", honey_glm_vec3_norm2,
	 HONEY_FUNCTION, "norm", honey_glm_vec3_norm,
	 HONEY_FUNCTION, "add", honey_glm_vec3_add,
	 HONEY_FUNCTION, "adds", honey_glm_vec3_adds,
	 HONEY_FUNCTION, "sub", honey_glm_vec3_sub,
	 HONEY_FUNCTION, "subs", honey_glm_vec3_subs,
	 HONEY_FUNCTION, "mul", honey_glm_vec3_mul,
	 HONEY_FUNCTION, "scale", honey_glm_vec3_scale,
	 HONEY_FUNCTION, "scaleAs", honey_glm_vec3_scale_as,
	 HONEY_FUNCTION, "div", honey_glm_vec3_div,
	 HONEY_FUNCTION, "negate", honey_glm_vec3_negate,
	 HONEY_FUNCTION, "normalize", honey_glm_vec3_normalize,
	 HONEY_FUNCTION, "angleTo", honey_glm_vec3_angle,
	 HONEY_FUNCTION, "clamp", honey_glm_vec3_clamp,
	 HONEY_FUNCTION, "lerpTo", honey_glm_vec3_lerp,
	 
	 
	 HONEY_FUNCTION, "__gc", honey_glm_array_destroy);
    honey_glm_vec3_mt_ref = luaL_ref(L, LUA_REGISTRYINDEX);


    /* vec4 metatable */
    honey_lua_create_table
	(L, 2,
	 HONEY_TABLE, "__index", 18,
	 HONEY_FUNCTION, "copyTo", honey_glm_vec4_copy,
	 HONEY_FUNCTION, "zero", honey_glm_vec4_zero,
	 HONEY_FUNCTION, "eye", honey_glm_vec4_eye,
	 HONEY_FUNCTION, "dot", honey_glm_vec4_dot,
	 HONEY_FUNCTION, "norm2", honey_glm_vec4_norm2,
	 HONEY_FUNCTION, "norm", honey_glm_vec4_norm,
	 HONEY_FUNCTION, "add", honey_glm_vec4_add,
	 HONEY_FUNCTION, "adds", honey_glm_vec4_adds,
	 HONEY_FUNCTION, "sub", honey_glm_vec4_sub,
	 HONEY_FUNCTION, "subs", honey_glm_vec4_subs,
	 HONEY_FUNCTION, "mul", honey_glm_vec4_mul,
	 HONEY_FUNCTION, "scale", honey_glm_vec4_scale,
	 HONEY_FUNCTION, "scaleAs", honey_glm_vec4_scale_as,
	 HONEY_FUNCTION, "div", honey_glm_vec4_div,
	 HONEY_FUNCTION, "negate", honey_glm_vec4_negate,
	 HONEY_FUNCTION, "normalize", honey_glm_vec4_normalize,
	 HONEY_FUNCTION, "clamp", honey_glm_vec4_clamp,
	 HONEY_FUNCTION, "lerpTo", honey_glm_vec4_lerp,
	 
	 
	 HONEY_FUNCTION, "__gc", honey_glm_array_destroy);
    honey_glm_vec4_mt_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    /* mat3 metatable */
    honey_lua_create_table
	(L, 2,

	 HONEY_TABLE, "__index", 9,
	 HONEY_FUNCTION, "copyTo", honey_glm_mat3_copy,
	 HONEY_FUNCTION, "eye", honey_glm_mat3_eye,
	 HONEY_FUNCTION, "zero", honey_glm_mat3_zero,
	 HONEY_FUNCTION, "mul", honey_glm_mat3_mul,
	 HONEY_FUNCTION, "transpose", honey_glm_mat3_transpose,
	 HONEY_FUNCTION, "mulv", honey_glm_mat3_mulv,
	 HONEY_FUNCTION, "scale", honey_glm_mat3_scale,
	 HONEY_FUNCTION, "det", honey_glm_mat3_det,
	 HONEY_FUNCTION, "inv", honey_glm_mat3_inv,

	 HONEY_FUNCTION, "__gc", honey_glm_array_destroy);
    honey_glm_mat3_mt_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    /* mat4 metatable */
    honey_lua_create_table
	(L, 2,

	 HONEY_TABLE, "__index", 16,
	 HONEY_FUNCTION, "copy", honey_glm_mat4_copy,
	 HONEY_FUNCTION, "eye", honey_glm_mat4_eye,
	 HONEY_FUNCTION, "zero", honey_glm_mat4_zero,
	 HONEY_FUNCTION, "mul", honey_glm_mat4_mul,
	 HONEY_FUNCTION, "transpose", honey_glm_mat4_transpose,
	 HONEY_FUNCTION, "mulv", honey_glm_mat4_mulv,
	 HONEY_FUNCTION, "scale", honey_glm_mat4_scale,
	 HONEY_FUNCTION, "det", honey_glm_mat4_det,
	 HONEY_FUNCTION, "inv", honey_glm_mat4_inv,
	 HONEY_FUNCTION, "translateX", honey_glm_translate_x,
	 HONEY_FUNCTION, "translateY", honey_glm_translate_y,
	 HONEY_FUNCTION, "translateZ", honey_glm_translate_z,
	 HONEY_FUNCTION, "scalev", honey_glm_scalev,
	 HONEY_FUNCTION, "rotateX", honey_glm_rotate_x,
	 HONEY_FUNCTION, "rotateY", honey_glm_rotate_y,
	 HONEY_FUNCTION, "rotateZ", honey_glm_rotate_z,
	 HONEY_FUNCTION, "rotate", honey_glm_rotate,

	 HONEY_FUNCTION, "__gc", honey_glm_array_destroy);
    honey_glm_mat4_mt_ref = luaL_ref(L, LUA_REGISTRYINDEX);
    
    /* glm table */
    honey_lua_create_table
	(L, 4,
	 HONEY_FUNCTION, "vec3", honey_glm_new_vec3,
	 HONEY_FUNCTION, "vec4", honey_glm_new_vec4,
	 HONEY_FUNCTION, "mat3", honey_glm_new_mat3,
	 HONEY_FUNCTION, "mat4", honey_glm_new_mat4);
    lua_setfield(L, -2, "glm");
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * GLM Array Basic Functions
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

int honey_glm_new_vec3(lua_State* L)
{
    honey_glm_array* vec3 = lua_newuserdata(L, sizeof(honey_glm_array));
    setup_new_array(L, vec3, VEC3);
    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_glm_vec3_mt_ref);
    lua_setmetatable(L, -2);
    return 1;
}

int honey_glm_new_vec4(lua_State* L)
{
    honey_glm_array* vec4 = lua_newuserdata(L, sizeof(honey_glm_array));
    setup_new_array(L, vec4, VEC4);
    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_glm_vec4_mt_ref);
    lua_setmetatable(L, -2);
    return 1;
}

int honey_glm_new_mat3(lua_State* L)
{
    honey_glm_array* mat3 = lua_newuserdata(L, sizeof(honey_glm_array));
    setup_new_array(L, mat3, MAT3);
    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_glm_mat3_mt_ref);
    lua_setmetatable(L, -2);
    return 1;
}

int honey_glm_new_mat4(lua_State* L)
{
    honey_glm_array* mat4 = lua_newuserdata(L, sizeof(honey_glm_array));
    setup_new_array(L, mat4, MAT4);
    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_glm_mat4_mt_ref);
    lua_setmetatable(L, -2);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_array_destroy(lua_State* L)
{
    honey_glm_array* array;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &array);
    free(array->data);
    return 0;
}
