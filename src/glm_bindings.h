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

typedef enum { VEC3,
	       VEC4,
	       MAT3,
	       MAT4
} honey_glm_array_type;

typedef struct {
  honey_glm_array_type type;
  unsigned int size;
  float* data;
} honey_glm_array;

/** @brief Push the honey glm binding functions to the lua stack.
 *
 * @returns Nothing.
 */
void honey_setup_glm(lua_State* L);

#endif
