/** @file */

#ifndef HONEY_WINDOW_H
#define HONEY_WINDOW_H

#include "../common.h"

#define HONEY_WINDOW_DEFAULT_WIDTH 640
#define HONEY_WINDOW_DEFAULT_HEIGHT 480

typedef struct {
    honey_window window;
    int width;
    int height;
    bool fullscreen;
} honey_window_information;

extern int honey_window_info_ref;

/** @brief Push the various honey.window table to the stack.
 *
 * @param[in] L The lua state to push to
 * @param[in] window The window created by honey_setup()
 *
 * @returns Nothing.
 */
bool honey_setup_window(lua_State* L);

/** @brief Set whether or not the window is fullscreen.
 *
 * Lua parameters:
 * @param[in] fullscreen Boolean set to true if the window is to be fullscreen and false otherwise.
 *
 * @returns Nothing.
 */
int honey_window_set_fullscreen(lua_State* L);

/** @brief Set the title of the window.
 *
 * @param[in] title String containing the desired window title.
 *
 * @returns Nothing.
 */
int honey_window_set_title(lua_State* L);

/** @brief Get the current size of the window.
 *
 * @returns width, height numbers representing the window size in pixels.
 */
int honey_window_get_size(lua_State* L);

/** @brief Set the current size of the window.
 *
 * @param[in] width Integer of the desired width in pixels.
 * @param[in] height Integer of the desired height in pixels.
 *
 * @returns Nothing.
 */
int honey_window_set_size(lua_State* L);

#endif
