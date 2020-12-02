#ifndef HONEY_GLM_BINDINGS_H
#define HONEY_GLM_BINDINGS_H

/** @file glm_bindings.h
 * @brief Lua bindings for GLM functions. 
 */

#include "common.h"

extern int honey_glm_vec3_mt_ref;
extern int honey_glm_vec4_mt_ref;
extern int honey_glm_mat3_mt_ref;
extern int honey_glm_mat4_mt_ref;

extern honey_glm_array UNIT_X;
extern honey_glm_array UNIT_Y;
extern honey_glm_array UNIT_Z;

/** @brief Push the honey glm binding functions to the lua stack.
 *
 * @returns Nothing.
 */
void honey_setup_glm(lua_State* L);

int honey_glm_new_vec3(lua_State* L);

int honey_glm_new_vec4(lua_State* L);

int honey_glm_new_mat3(lua_State* L);

int honey_glm_new_mat4(lua_State* L);

int honey_glm_array_vec_get(lua_State* L);

int honey_glm_array_vec_set(lua_State* L);

int honey_glm_array_mat_get(lua_State* L);

int honey_glm_array_mat_set(lua_State* L);

int honey_glm_vector_to_string(lua_State* L);

int honey_glm_matrix_to_string(lua_State* L);

int honey_glm_array_destroy(lua_State* L);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Vec3 Functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int honey_glm_vec3_copy(lua_State* L);

int honey_glm_vec3_zero(lua_State* L);

int honey_glm_vec3_eye(lua_State* L);

int honey_glm_vec3_dot(lua_State* L);

int honey_glm_vec3_cross(lua_State* L);
			     
int honey_glm_vec3_crossn(lua_State* L);
			     
int honey_glm_vec3_norm2(lua_State* L);
			     
int honey_glm_vec3_norm(lua_State* L);
			     
int honey_glm_vec3_add(lua_State* L);
			     
int honey_glm_vec3_adds(lua_State* L);
			     
int honey_glm_vec3_sub(lua_State* L);
			     
int honey_glm_vec3_subs(lua_State* L);

int honey_glm_vec3_mul(lua_State* L);
			     
int honey_glm_vec3_scale(lua_State* L);
			     
int honey_glm_vec3_scale_as(lua_State* L);
			     
int honey_glm_vec3_div(lua_State* L);
			     
int honey_glm_vec3_negate(lua_State* L);
			     
int honey_glm_vec3_normalize(lua_State* L);
			     
int honey_glm_vec3_angle(lua_State* L);
			     
int honey_glm_vec3_clamp(lua_State* L);
			     
int honey_glm_vec3_lerp(lua_State* L);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Vec4 Functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int honey_glm_vec4_copy(lua_State* L);

int honey_glm_vec4_zero(lua_State* L);

int honey_glm_vec4_eye(lua_State* L);

int honey_glm_vec4_dot(lua_State* L);

int honey_glm_vec4_norm2(lua_State* L);
			     
int honey_glm_vec4_norm(lua_State* L);
			     
int honey_glm_vec4_add(lua_State* L);
			     
int honey_glm_vec4_adds(lua_State* L);
			     
int honey_glm_vec4_sub(lua_State* L);
			     
int honey_glm_vec4_subs(lua_State* L);

int honey_glm_vec4_mul(lua_State* L);
			     
int honey_glm_vec4_scale(lua_State* L);
			     
int honey_glm_vec4_scale_as(lua_State* L);
			     
int honey_glm_vec4_div(lua_State* L);
			     
int honey_glm_vec4_negate(lua_State* L);
			     
int honey_glm_vec4_normalize(lua_State* L);
			     
int honey_glm_vec4_clamp(lua_State* L);
			     
int honey_glm_vec4_lerp(lua_State* L);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Mat3 Functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int honey_glm_mat3_copy(lua_State* L);

int honey_glm_mat3_eye(lua_State* L);

int honey_glm_mat3_zero(lua_State* L);

int honey_glm_mat3_mul(lua_State* L);

int honey_glm_mat3_transpose(lua_State* L);

int honey_glm_mat3_mulv(lua_State* L);

int honey_glm_mat3_scale(lua_State* L);

int honey_glm_mat3_det(lua_State* L);

int honey_glm_mat3_inv(lua_State* L);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Mat4 Functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int honey_glm_mat4_copy(lua_State* L);

int honey_glm_mat4_eye(lua_State* L);

int honey_glm_mat4_zero(lua_State* L);

int honey_glm_mat4_mul(lua_State* L);

int honey_glm_mat4_transpose(lua_State* L);

int honey_glm_mat4_mulv(lua_State* L);

int honey_glm_mat4_scale(lua_State* L);

int honey_glm_mat4_det(lua_State* L);

int honey_glm_mat4_inv(lua_State* L);

int honey_glm_translate(lua_State* L);

int honey_glm_translate_x(lua_State* L);

int honey_glm_translate_y(lua_State* L);

int honey_glm_translate_z(lua_State* L);

int honey_glm_scalev(lua_State* L);

int honey_glm_rotate_x(lua_State* L);

int honey_glm_rotate_y(lua_State* L);

int honey_glm_rotate_z(lua_State* L);

int honey_glm_rotate(lua_State* L);

int honey_glm_perspective(lua_State* L);

int honey_glm_perspective_resize(lua_State* L);

int honey_glm_lookat(lua_State* L);

int honey_glm_look(lua_State* L);

#endif
