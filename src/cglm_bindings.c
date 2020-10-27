#include "cglm_bindings.h"

void honey_setup_cglm(lua_State* L)
{
    honey_lua_element vec3_elements[] = {
        { "dot",         HONEY_FUNCTION, { .function = honey_cglm_vec3_dot } },
        { "cross",       HONEY_FUNCTION, { .function = honey_cglm_vec3_cross } },
        { "square_norm", HONEY_FUNCTION, { .function = honey_cglm_vec3_square_norm } },
        { "norm",        HONEY_FUNCTION, { .function = honey_cglm_vec3_norm } },
    };

    honey_lua_element vec4_elements[] = {
        { "dot",       HONEY_FUNCTION, { .function = honey_cglm_vec4_dot } },
        { "norm2",     HONEY_FUNCTION, { .function = honey_cglm_vec4_norm2 } },
        { "norm",      HONEY_FUNCTION, { .function = honey_cglm_vec4_norm } },
        { "add",       HONEY_FUNCTION, { .function = honey_cglm_vec4_add } },
        { "adds",      HONEY_FUNCTION, { .function = honey_cglm_vec4_adds } },
        { "mul",       HONEY_FUNCTION, { .function = honey_cglm_vec4_mul } },
        { "muls",      HONEY_FUNCTION, { .function = honey_cglm_vec4_muls } },
        { "normalize", HONEY_FUNCTION, { .function = honey_cglm_vec4_normalize } },
        { "distance",  HONEY_FUNCTION, { .function = honey_cglm_vec4_distance } },
        { "lerp",      HONEY_FUNCTION, { .function = honey_cglm_vec4_lerp } },
    };

    honey_lua_element mat4_elements[] = {
        { "identity", HONEY_FUNCTION, { .function = honey_cglm_mat4_identity } },
        { "pick3",    HONEY_FUNCTION, { .function = honey_cglm_mat4_pick3 } },
        { "mul",      HONEY_FUNCTION, { .function = honey_cglm_mat4_mul } },
        { "muls",     HONEY_FUNCTION, { .function = honey_cglm_mat4_muls } },
        { "mulv",     HONEY_FUNCTION, { .function = honey_cglm_mat4_mulv } },
        { "trans",    HONEY_FUNCTION, { .function = honey_cglm_mat4_trans } },
        { "det",      HONEY_FUNCTION, { .function = honey_cglm_mat4_det } },
        { "trace",    HONEY_FUNCTION, { .function = honey_cglm_mat4_trace } },
        { "inv",      HONEY_FUNCTION, { .function = honey_cglm_mat4_inv } },
        { "inv_fast", HONEY_FUNCTION, { .function = honey_cglm_mat4_inv_fast } },
    };

    honey_lua_element affine_elements[] = {
        { "translate", HONEY_FUNCTION, { .function = honey_cglm_translate } },
        { "scale",     HONEY_FUNCTION, { .function = honey_cglm_scale } },
        { "rotate",    HONEY_FUNCTION, { .function = honey_cglm_rotate } },
    };

    honey_lua_element camera_elements[] = {
        { "perspective",  HONEY_FUNCTION, { .function = honey_cglm_perspective } },
        { "orthographic", HONEY_FUNCTION, { .function = honey_cglm_orthographic } },
    };
    
    honey_lua_element cglm_elements[] = {
        { "new_array_zero", HONEY_FUNCTION, { .function = honey_cglm_new_array_zero } },
        { "set_value",      HONEY_FUNCTION, { .function = honey_cglm_array_set_value } },
        { "get_value",      HONEY_FUNCTION, { .function = honey_cglm_array_get_value } },
        { "copy_array",     HONEY_FUNCTION, { .function = honey_cglm_array_copy } },
        { "vec3",           HONEY_TABLE, { .table = { 4, vec3_elements } } },
        { "vec4",           HONEY_TABLE, { .table = { 10, vec4_elements } } },
        { "mat4",           HONEY_TABLE, { .table = { 10, mat4_elements } } },
        { "affine",         HONEY_TABLE, { .table = { 3, affine_elements } } },
        { "camera",         HONEY_TABLE, { .table = { 2, camera_elements } } },
    };

    honey_lua_create_table(L, cglm_elements, 9);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_new_array_zero(lua_State* L)
{
    if (!honey_lua_validate_types(L, 1, HONEY_INTEGER))
        lua_error(L);

    int size = lua_tointeger(L, 1);
    
    float* array = lua_newuserdata(L, size*sizeof(float));
    memset(array, 0, size*sizeof(float));
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_array_set_value(lua_State* L)
{
    if (!honey_lua_validate_types(L, 3, HONEY_USERDATA, HONEY_INTEGER, HONEY_NUMBER))
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
    if (!honey_lua_validate_types(L, 2, HONEY_USERDATA, HONEY_INTEGER))
        lua_error(L);

    float* array = lua_touserdata(L, 1);
    int index = lua_tointeger(L, 2);

    lua_pushnumber(L, array[index]);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_array_copy(lua_State* L) {
    if (!honey_lua_validate_types(L, 2, HONEY_USERDATA, HONEY_INTEGER))
        lua_error(L);

    float* array = lua_touserdata(L, 1);
    int n = lua_tointeger(L, 2);

    float* copy = lua_newuserdata(L, n*sizeof(float));
    memcpy(copy, array, n*sizeof(float));
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
 *
 * cglm vec3 functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int honey_cglm_vec3_dot(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_USERDATA, HONEY_USERDATA))
        lua_error(L);

    float* a = lua_touserdata(L, 1);
    float* b = lua_touserdata(L, 2);

    float c = glm_vec3_dot(a, b);
    lua_pushnumber(L, c);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_vec3_cross(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_USERDATA, HONEY_USERDATA))
        lua_error(L);

    float* a = lua_touserdata(L, 1);
    float* b = lua_touserdata(L, 2);

    float* c = lua_newuserdata(L, 3*sizeof(float));

    glm_vec3_cross(a, b, c);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_vec3_square_norm(lua_State* L)
{
    if (!honey_lua_validate_types(L, 1, HONEY_USERDATA))
        lua_error(L);

    float* a = lua_touserdata(L, 1);

    float n2 = glm_vec3_norm2(a);
    lua_pushnumber(L, n2);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_vec3_norm(lua_State* L)
{
    if (!honey_lua_validate_types(L, 1, HONEY_USERDATA))
        lua_error(L);

    float* a = lua_touserdata(L, 1);

    float n = glm_vec3_norm(a);
    lua_pushnumber(L, n);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * cglm vec4 functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int honey_cglm_vec4_dot(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_USERDATA, HONEY_USERDATA))
        lua_error(L);

    float* a = lua_touserdata(L, 1);
    float* b = lua_touserdata(L, 2);

    float dot = glm_vec4_dot(a, b);
    lua_pushnumber(L, dot);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_vec4_norm2(lua_State* L)
{
    if (!honey_lua_validate_types(L, 1, HONEY_USERDATA))
        lua_error(L);

    float* v = lua_touserdata(L, 1);

    float norm2 = glm_vec4_norm2(v);

    lua_pushnumber(L, norm2);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_vec4_norm(lua_State* L)
{
    if (!honey_lua_validate_types(L, 1, HONEY_USERDATA))
        lua_error(L);

    float* v = lua_touserdata(L, 1);

    float norm = glm_vec4_norm(v);

    lua_pushnumber(L, norm);
    return 1;
}    

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_vec4_add(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_USERDATA, HONEY_USERDATA))
        lua_error(L);

    float* a = lua_touserdata(L, 1);
    float* b = lua_touserdata(L, 2);

    float* dest = lua_newuserdata(L, 4*sizeof(float));

    glm_vec4_add(a, b, dest);

    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_vec4_adds(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_NUMBER, HONEY_USERDATA))
        lua_error(L);

    float a = lua_tonumber(L, 1);
    float* v = lua_touserdata(L, 2);

    float* dest = lua_newuserdata(L, 4*sizeof(float));

    glm_vec4_adds(v, a, dest);

    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_vec4_mul(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_USERDATA, HONEY_USERDATA))
        lua_error(L);

    float* a = lua_touserdata(L, 1);
    float* b = lua_touserdata(L, 2);

    float* dest = lua_newuserdata(L, 4*sizeof(float));

    glm_vec4_mul(a, b, dest);

    return 1;
}    

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_vec4_muls(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_NUMBER, HONEY_USERDATA))
        lua_error(L);

    float a = lua_tonumber(L, 1);
    float* v = lua_touserdata(L, 2);

    float* dest = lua_newuserdata(L, 4*sizeof(float));

    glm_vec4_scale(v, a, dest);

    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_vec4_normalize(lua_State* L)
{
    if (!honey_lua_validate_types(L, 1, HONEY_USERDATA))
        lua_error(L);

    float* v = lua_touserdata(L, 1);

    glm_vec4_normalize(v);

    return 0;
}    

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_vec4_distance(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_USERDATA, HONEY_USERDATA))
        lua_error(L);

    float* a = lua_touserdata(L, 1);
    float* b = lua_touserdata(L, 2);

    float distance = glm_vec4_distance(a, b);
    lua_pushnumber(L, distance);

    return 1;
}    

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_vec4_lerp(lua_State* L)
{
    if (!honey_lua_validate_types(L, 3, HONEY_USERDATA, HONEY_USERDATA, HONEY_NUMBER))
        lua_error(L);

    float* a = lua_touserdata(L, 1);
    float* b = lua_touserdata(L, 2);
    float s = lua_tonumber(L, 3);

    float* dest = lua_newuserdata(L, 4*sizeof(float));

    glm_vec4_lerp(a, b, s, dest);

    return 1;
}    

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * cglm mat4 functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int honey_cglm_mat4_identity(lua_State* L)
{
    if (!honey_lua_validate_types(L, 1, HONEY_USERDATA))
        lua_error(L);

    float* matrix = lua_touserdata(L, 1);
    glm_mat4_identity(matrix);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_mat4_pick3(lua_State* L)
{
    if (!honey_lua_validate_types(L, 1, HONEY_USERDATA))
        lua_error(L);

    float* matrix = lua_touserdata(L, 1);

    float* dest = lua_newuserdata(L, 9*sizeof(float));
    glm_mat4_pick3(matrix, dest);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_mat4_mul(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_USERDATA))
        lua_error(L);

    float* A = lua_touserdata(L, 1);
    float* B = lua_touserdata(L, 2);

    float* dest = lua_newuserdata(L, 16*sizeof(float));

    glm_mat4_mul(A, B, dest);

    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_mat4_muls(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_NUMBER, HONEY_USERDATA))
        lua_error(L);

    float a = lua_tonumber(L, 1);
    float* M = lua_touserdata(L, 2);

    float* dest = lua_newuserdata(L, 16*sizeof(float));
    glm_mat4_scale(M, a);

    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_mat4_mulv(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_USERDATA))
        lua_error(L);

    float* M = lua_touserdata(L, 1);
    float* v = lua_touserdata(L, 2);

    float* dest = lua_newuserdata(L, 4*sizeof(float));

    glm_mat4_mulv(M, v, dest);

    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_mat4_trans(lua_State* L)
{
    if (!honey_lua_validate_types(L, 1, HONEY_USERDATA))
        lua_error(L);

    float* M = lua_touserdata(L, 1);

    glm_mat4_transpose(M);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_mat4_det(lua_State* L)
{
    if (!honey_lua_validate_types(L, 1, HONEY_USERDATA))
        lua_error(L);

    float* M = lua_touserdata(L, 1);

    float det = glm_mat4_det(M);
    lua_pushnumber(L, det);

    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_mat4_trace(lua_State* L)
{
    if (!honey_lua_validate_types(L, 1, HONEY_USERDATA))
        lua_error(L);

    float* M = lua_touserdata(L, 1);

    float trace = glm_mat4_trace(M);
    lua_pushnumber(L, trace);

    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_mat4_inv(lua_State* L)
{
        if (!honey_lua_validate_types(L, 1, HONEY_USERDATA))
        lua_error(L);

    float* M = lua_touserdata(L, 1);

    float* dest = lua_newuserdata(L, 16*sizeof(float));

    glm_mat4_inv(M, dest);

    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_mat4_inv_fast(lua_State* L)
{
        if (!honey_lua_validate_types(L, 1, HONEY_USERDATA))
        lua_error(L);

    float* M = lua_touserdata(L, 1);

    float* dest = lua_newuserdata(L, 16*sizeof(float));

    glm_mat4_inv_fast(M, dest);

    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * cglm 3d affine transforms
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int honey_cglm_translate(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_USERDATA, HONEY_USERDATA))
        lua_error(L);

    float* matrix = lua_touserdata(L, 1);
    float* vector = lua_touserdata(L, 2);

    glm_translate(matrix, vector);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_scale(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_USERDATA, HONEY_USERDATA))
        lua_error(L);

    float* matrix = lua_touserdata(L, 1);
    float* vector = lua_touserdata(L, 2);

    glm_scale(matrix, vector);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_rotate(lua_State* L) {
    if (!honey_lua_validate_types(L, 4,
                                  HONEY_USERDATA, HONEY_USERDATA,
                                  HONEY_USERDATA, HONEY_NUMBER))
        lua_error(L);

    float* matrix = lua_touserdata(L, 1);
    float* center = lua_touserdata(L, 2);
    float* axis   = lua_touserdata(L, 3);
    float angle   = lua_tonumber(L, 4);

    glm_rotate_at(matrix, center, angle, axis);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * cglm camera matrix functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int honey_cglm_perspective(lua_State* L)
{
    if (!honey_lua_validate_types(L, 5,
                                  HONEY_USERDATA,
                                  HONEY_NUMBER, HONEY_NUMBER,
                                  HONEY_NUMBER, HONEY_NUMBER))
        lua_error(L);

    float* matrix = lua_touserdata(L, 1);
    float fov     = lua_tonumber(L, 2);
    float aspect  = lua_tonumber(L, 3);
    float near    = lua_tonumber(L, 4);
    float far     = lua_tonumber(L, 5);

    glm_perspective(fov, aspect, near, far, matrix);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cglm_orthographic(lua_State* L)
{
    if (!honey_lua_validate_types(L, 5,
                                  HONEY_USERDATA,
                                  HONEY_USERDATA,
                                  HONEY_USERDATA))
                                  
        lua_error(L);

    float* matrix = lua_touserdata(L, 1);
    float* a = lua_touserdata(L, 2);
    float* b = lua_touserdata(L, 3);

    float* box[] = { a, b };
    
    glm_ortho_aabb(box, matrix);
    return 0;
}
