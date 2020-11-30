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

/** @brief Push the honey glm binding functions to the lua stack.
 *
 * @returns Nothing.
 */
void honey_setup_glm(lua_State* L);

int honey_glm_new_vec3(lua_State* L);

int honey_glm_new_vec4(lua_State* L);

int honey_glm_new_mat3(lua_State* L);

int honey_glm_new_mat4(lua_State* L);

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

#endif
