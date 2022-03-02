#ifndef HONEY_GL_H
#define HONEY_GL_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

struct honey_window {
   GLFWwindow * window;
   bool created;
   lua_State *L;
};

extern struct honey_window window;

void setup_window(lua_State *L, int tbl_index);

#endif
