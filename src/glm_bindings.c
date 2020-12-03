#include "glm_bindings.h"

int honey_glm_vec3_mt_ref = LUA_NOREF;
int honey_glm_vec4_mt_ref = LUA_NOREF;
int honey_glm_mat3_mt_ref = LUA_NOREF;
int honey_glm_mat4_mt_ref = LUA_NOREF;

int honey_glm_UNIT_X_ref = LUA_NOREF;
int honey_glm_UNIT_Y_ref = LUA_NOREF;
int honey_glm_UNIT_Z_ref = LUA_NOREF;

static void create_vec3(lua_State* L,
		 int x, int y, int z,
		 int* ref)
{
    lua_createtable(L, 3, 0);

    lua_pushnumber(L, x);
    lua_rawseti(L, -2, 1);

    lua_pushnumber(L, y);
    lua_rawseti(L, -2, 2);

    lua_pushnumber(L, z);
    lua_rawseti(L, -2, 3);

    lua_pushcfunction(L, honey_glm_new_vec3);
    lua_pushvalue(L, -2);
    honey_lua_pcall(L, 1, 1);

    *ref = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_pop(L, 1);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_setup_glm(lua_State* L)
{
    /* vec3 metatable */
    honey_lua_create_table
	(L, 3,
	 HONEY_TABLE, "__index", 24,
	 HONEY_FUNCTION, "get", honey_glm_array_vec_get,
	 HONEY_FUNCTION, "set", honey_glm_array_vec_set,
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
	 HONEY_FUNCTION, "muls", honey_glm_vec3_muls,
	 HONEY_FUNCTION, "scale", honey_glm_vec3_scale,
	 HONEY_FUNCTION, "scaleAs", honey_glm_vec3_scale_as,
	 HONEY_FUNCTION, "div", honey_glm_vec3_div,
	 HONEY_FUNCTION, "negate", honey_glm_vec3_negate,
	 HONEY_FUNCTION, "normalize", honey_glm_vec3_normalize,
	 HONEY_FUNCTION, "angleTo", honey_glm_vec3_angle,
	 HONEY_FUNCTION, "clamp", honey_glm_vec3_clamp,
	 HONEY_FUNCTION, "lerpTo", honey_glm_vec3_lerp,
	 
	 HONEY_FUNCTION, "__tostring", honey_glm_vector_to_string,
	 
	 HONEY_FUNCTION, "__gc", honey_glm_array_destroy);
    honey_glm_vec3_mt_ref = luaL_ref(L, LUA_REGISTRYINDEX);


    /* vec4 metatable */
    honey_lua_create_table
	(L, 3,
	 HONEY_TABLE, "__index", 20,
	 HONEY_FUNCTION, "get", honey_glm_array_vec_get,
	 HONEY_FUNCTION, "set", honey_glm_array_vec_set,
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

	 HONEY_FUNCTION, "__tostring", honey_glm_vector_to_string,
	 
	 HONEY_FUNCTION, "__gc", honey_glm_array_destroy);
    honey_glm_vec4_mt_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    /* mat3 metatable */
    honey_lua_create_table
	(L, 3,

	 HONEY_TABLE, "__index", 11,
	 HONEY_FUNCTION, "get", honey_glm_array_mat_get,
	 HONEY_FUNCTION, "set", honey_glm_array_mat_set,
	 HONEY_FUNCTION, "copyTo", honey_glm_mat3_copy,
	 HONEY_FUNCTION, "eye", honey_glm_mat3_eye,
	 HONEY_FUNCTION, "zero", honey_glm_mat3_zero,
	 HONEY_FUNCTION, "mul", honey_glm_mat3_mul,
	 HONEY_FUNCTION, "transpose", honey_glm_mat3_transpose,
	 HONEY_FUNCTION, "mulv", honey_glm_mat3_mulv,
	 HONEY_FUNCTION, "scale", honey_glm_mat3_scale,
	 HONEY_FUNCTION, "det", honey_glm_mat3_det,
	 HONEY_FUNCTION, "inv", honey_glm_mat3_inv,

	 HONEY_FUNCTION, "__tostring", honey_glm_matrix_to_string,

	 HONEY_FUNCTION, "__gc", honey_glm_array_destroy);
    honey_glm_mat3_mt_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    /* mat4 metatable */
    honey_lua_create_table
	(L, 3,

	 HONEY_TABLE, "__index", 25,
	 HONEY_FUNCTION, "get", honey_glm_array_mat_get,
	 HONEY_FUNCTION, "set", honey_glm_array_mat_set,
	 HONEY_FUNCTION, "copyTo", honey_glm_mat4_copy,
	 HONEY_FUNCTION, "eye", honey_glm_mat4_eye,
	 HONEY_FUNCTION, "zero", honey_glm_mat4_zero,
	 HONEY_FUNCTION, "mul", honey_glm_mat4_mul,
	 HONEY_FUNCTION, "transpose", honey_glm_mat4_transpose,
	 HONEY_FUNCTION, "mulv", honey_glm_mat4_mulv,
	 HONEY_FUNCTION, "scale", honey_glm_mat4_scale,
	 HONEY_FUNCTION, "det", honey_glm_mat4_det,
	 HONEY_FUNCTION, "inv", honey_glm_mat4_inv,
	 HONEY_FUNCTION, "basis", honey_glm_mat4_basis,
	 HONEY_FUNCTION, "translate", honey_glm_translate,
	 HONEY_FUNCTION, "translateX", honey_glm_translate_x,
	 HONEY_FUNCTION, "translateY", honey_glm_translate_y,
	 HONEY_FUNCTION, "translateZ", honey_glm_translate_z,
	 HONEY_FUNCTION, "scalev", honey_glm_scalev,
	 HONEY_FUNCTION, "rotateX", honey_glm_rotate_x,
	 HONEY_FUNCTION, "rotateY", honey_glm_rotate_y,
	 HONEY_FUNCTION, "rotateZ", honey_glm_rotate_z,
	 HONEY_FUNCTION, "rotate", honey_glm_rotate,
	 HONEY_FUNCTION, "perspective", honey_glm_perspective,
	 HONEY_FUNCTION, "perspectiveResize", honey_glm_perspective_resize,
	 HONEY_FUNCTION, "lookAt", honey_glm_lookat,
	 HONEY_FUNCTION, "look", honey_glm_look,

	 HONEY_FUNCTION, "__tostring", honey_glm_matrix_to_string,

	 HONEY_FUNCTION, "__gc", honey_glm_array_destroy);
    honey_glm_mat4_mt_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    create_vec3(L, 1, 0, 0, &honey_glm_UNIT_X_ref);
    create_vec3(L, 0, 1, 0, &honey_glm_UNIT_Y_ref);
    create_vec3(L, 0, 0, 1, &honey_glm_UNIT_Z_ref);
    
    /* glm table */
    honey_lua_create_table
	(L, 4,
	 HONEY_FUNCTION, "vec3", honey_glm_new_vec3,
	 HONEY_FUNCTION, "vec4", honey_glm_new_vec4,
	 HONEY_FUNCTION, "mat3", honey_glm_new_mat3,
	 HONEY_FUNCTION, "mat4", honey_glm_new_mat4);

    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_glm_UNIT_X_ref);
    lua_setfield(L, -2, "UNIT_X");

    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_glm_UNIT_Y_ref);
    lua_setfield(L, -2, "UNIT_Y");

    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_glm_UNIT_Z_ref);
    lua_setfield(L, -2, "UNIT_Z");
    
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
			    honey_glm_array_type type,
			    int choice)
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

    if (choice == 1) {
	size_t length = lua_objlen(L, 1);
	if (length != size)
	    honey_lua_throw_error
		(L, "initialization table must contain %d elements; got %d elements instead",
		 size, length);

	for (int i=0; i<size; i++) {
	    lua_rawgeti(L, 1, i+1);
	    if (!lua_isnumber(L, -1))
		honey_lua_throw_error(L, "initialization table must contain only numbers");
	    array->data[i] = lua_tonumber(L, -1);
	    lua_pop(L, 1);
	}
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static int glm_matrix_dim(honey_glm_array_type type)
{
    switch (type) {
    case MAT3:
	return 3;

    case MAT4:
	return 4;

    default:
	return 0;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_new_vec3(lua_State* L)
{
    int choice = honey_lua_parse_arguments(L, 2, 0, 1, HONEY_TABLE);

    honey_glm_array* vec3 = lua_newuserdata(L, sizeof(honey_glm_array));
    setup_new_array(L, vec3, VEC3, choice);

    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_glm_vec3_mt_ref);
    lua_setmetatable(L, -2);
    return 1;
}

int honey_glm_new_vec4(lua_State* L)
{
    int choice = honey_lua_parse_arguments(L, 2, 0, 1, HONEY_TABLE);
    honey_glm_array* vec4 = lua_newuserdata(L, sizeof(honey_glm_array));
    setup_new_array(L, vec4, VEC4, choice);
    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_glm_vec4_mt_ref);
    lua_setmetatable(L, -2);
    return 1;
}

int honey_glm_new_mat3(lua_State* L)
{
    int choice = honey_lua_parse_arguments(L, 2, 0, 1, HONEY_TABLE);
    honey_glm_array* mat3 = lua_newuserdata(L, sizeof(honey_glm_array));
    setup_new_array(L, mat3, MAT3, choice);
    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_glm_mat3_mt_ref);
    lua_setmetatable(L, -2);
    return 1;
}

int honey_glm_new_mat4(lua_State* L)
{
    int choice = honey_lua_parse_arguments(L, 2, 0, 1, HONEY_TABLE);
    honey_glm_array* mat4 = lua_newuserdata(L, sizeof(honey_glm_array));
    setup_new_array(L, mat4, MAT4, choice);
    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_glm_mat4_mt_ref);
    lua_setmetatable(L, -2);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_array_vec_get(lua_State* L)
{
    honey_glm_array* self;
    int index;
    honey_lua_parse_arguments
	(L, 1, 2, HONEY_USERDATA, &self, HONEY_INTEGER, &index);

    if (index < 0 || index >= self->size)
	honey_lua_throw_error(L, "index %d is out of range", index);

    lua_pushnumber(L, self->data[index]);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_array_vec_set(lua_State* L)
{
    honey_glm_array* self;
    int index;
    float value;
    honey_lua_parse_arguments
	(L, 1, 3, HONEY_USERDATA, &self, HONEY_INTEGER, &index, HONEY_NUMBER, &value);

    if (index < 0 || index >= self->size)
	honey_lua_throw_error(L, "index %d is out of range", index);

    self->data[index] = value;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_array_mat_set(lua_State* L)
{
    honey_glm_array* self;
    int column, row;
    float value;
    honey_lua_parse_arguments
	(L, 1, 4,
	 HONEY_USERDATA, &self,
	 HONEY_INTEGER, &row,
	 HONEY_INTEGER, &column,
	 HONEY_NUMBER, &value);

    int dim = glm_matrix_dim(self->type);

    int index = (row - 1) + dim * (column - 1);
    self->data[index] = value;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_array_mat_get(lua_State* L)
{
    honey_glm_array* self;
    int column, row;
    float value;
    honey_lua_parse_arguments
	(L, 1, 3,
	 HONEY_USERDATA, &self,
	 HONEY_INTEGER, &row,
	 HONEY_INTEGER, &column);

    int dim = glm_matrix_dim(self->type);

    int index = (row - 1) + dim * (column - 1);
    lua_pushnumber(L, self->data[index]);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vector_to_string(lua_State* L)
{
    honey_glm_array* self;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &self);
    
    char string[256];
    string[0] = '['; string[1] = ' '; string[2] = 0;
    int index = 2;
    for (int i=0; i<self->size; i++) {
	index += snprintf(string + index, 256-index, "%7.3f ", self->data[i]);
	if (i != self->size-1) {
	    string[index] = ' ';
	    index++;
	}
    }

    snprintf(string + index, 256-index, "]");
    
    lua_pushstring(L, string);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_matrix_to_string(lua_State* L)
{
    honey_glm_array* self;
    int column, row;
    float value;
    honey_lua_parse_arguments
	(L, 1, 1, HONEY_USERDATA, &self);

    int dim = glm_matrix_dim(self->type);

    char string[512];
    string[0] = 0;
    int index = 0;

    for (int row=0; row<dim; row++) {
	if (row == 0)
	    index += snprintf(string+index, 512-index, "/ ");
	else if (row == dim-1)
	    index += snprintf(string+index, 512-index, "\\ ");
	else
	    index += snprintf(string+index, 512-index, "| ");
	for (int col=0; col<dim; col++)
	    index += snprintf(string+index, 512-index, "%7.3f ", self->data[row + dim*col]);
	if (row == 0)
	    index += snprintf(string+index, 512-index, "\\\n");
	else if (row == dim-1)
	    index += snprintf(string+index, 512-index, "/\n");
	else
	    index += snprintf(string+index, 512-index, "|\n");
    }

    lua_pushstring(L, string);
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
