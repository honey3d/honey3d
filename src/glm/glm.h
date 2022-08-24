#ifndef HONEY_GLM_H
#define HONEY_GLM_H

#include <lua.h>

void setup_glm(lua_State *L, int honey_index);
void setup_vec3(lua_State *L, int glm_tbl);
void setup_mat4(lua_State *L, int glm_tbl);
void setup_transform(lua_State *L, int glm_tbl);
void setup_camera(lua_State *L, int glm_tbl);

void array_get(lua_State *L, int max, float *array, int index);
void array_set(lua_State *L, int max, float *array, int index, float value);

#endif
