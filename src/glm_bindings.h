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

#endif
