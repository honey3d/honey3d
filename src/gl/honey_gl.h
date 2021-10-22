#ifndef HONEY_GL_H
#define HONEY_GL_H

#include <stdbool.h>

#ifdef UNIT_TEST
#include "test/mock/mock_GLFW.h"
#else
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#endif

extern int honey_gl_window_ref;

bool honey_gl_setup();


#endif
