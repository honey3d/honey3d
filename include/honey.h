#ifndef HONEY_ENGINE_H
#define HONEY_ENGINE_H

#include "common.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

typedef GLFWwindow* honey_window;

honey_window honey_setup(int screen_width, int screen_height, char* window_title);

#define honey_set_resize_callback glfwSetFramebufferSizeCallback
#define honey_set_mouse_move_callback glfwSetCursorPosCallback

#define honey_quit glfwTerminate

#endif
