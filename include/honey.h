#ifndef HONEY_ENGINE_H
#define HONEY_ENGINE_H

/** @file honey.h
 * 
 * @brief Defines the basic loading and callback functions. 
*/

#include "camera.h"
#include "common.h"
#include "mesh.h"
#include "primitives.h"
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

/** @brief Set the main update function.
 *
 * @param[in] update_callback The function to call every loop
 */
void honey_set_update_callback(void (*update_callback)(float));

/** @brief Set the main draw function
 *
 * @param[in] draw_callback The function to call every draw cycle
 */
void honey_set_draw_callback(void (*draw_callback)());

/** @brief The main game loop.
 *
 * @param[in] window The window the game is running in, created with honey_setup()
 */
void honey_run(honey_window window);

#define honey_set_resize_callback glfwSetFramebufferSizeCallback
#define honey_set_mouse_move_callback glfwSetCursorPosCallback

#define honey_quit glfwTerminate

#endif
