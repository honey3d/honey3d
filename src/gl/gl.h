#ifndef HONEY_GL_H
#define HONEY_GL_H

#include <lua.h>

void setup_gl(lua_State *L, int honey_index);
void setup_shader(lua_State *L, int gl_index);
void setup_window(lua_State *L, int honey_index);

#endif
