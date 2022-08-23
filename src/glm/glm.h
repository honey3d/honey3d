#ifndef HONEY_GLM_H
#define HONEY_GLM_H

#include <lua.h>

void setup_glm(lua_State *L, int honey_index);
void setup_mat4(lua_State *L, int glm_index);
void setup_transform(lua_State *L, int glm_index);

#endif
