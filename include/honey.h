#ifndef HONEY_ENGINE_H
#define HONEY_ENGINE_H

/** @file Defines the basic loading and callback functions. */
#include "common.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

typedef GLFWwindow* honey_window;

/** @brief Initialize Honey.
 *
 * @param[in] screen_width The desired width of the screen in pixels
 * @param[in] screen_height The desired height of the screen in pixels
 * @param[in] window_title Title to use for the window.
 */
honey_window honey_setup(int screen_width, int screen_height, char* window_title);

static void (*honey_update_callback)(float dt);
static void (*honey_draw_callback)();
static float honey_draw_dt = 0.16;

void honey_set_update_callback(void (*update_callback)(float));
void honey_set_draw_callback(void (*draw_callback)());
void honey_set_fps(unsigned int);

void honey_run(honey_window window);

#define honey_set_resize_callback glfwSetFramebufferSizeCallback
#define honey_set_mouse_move_callback glfwSetCursorPosCallback

#define honey_quit glfwTerminate

#endif
