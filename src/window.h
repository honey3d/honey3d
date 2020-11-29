/** @file */

#ifndef HONEY_WINDOW_H
#define HONEY_WINDOW_H

#include "common.h"

#define HONEY_WINDOW_DEFAULT_WIDTH 640
#define HONEY_WINDOW_DEFAULT_HEIGHT 480

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

/** @brief Bind a call back to the window resize.
 *
 * @param[in] callback The callback function to call on a window resize.
 *
 * @returns Nothing.
 */
int honey_window_resize_bind(lua_State* L);

/** @brief Unbind any callback that may be attached to the window resize.
 *
 * @returns Nothing.
 */
int honey_window_resize_unbind(lua_State* L);

/** @brief Bind a callback to the window changing focus.
 *
 * The supplied callback function should be of the form
 * function(boolean, data). The boolean is true if the window
 * is gaining focus, and false if it is losing focus. The data is 
 * just the data parameter passed to this function.
 *
 * @param callback The callback function to call on a window resize.
 * @param data Data to send to the callback.
 *
 * @returns Nothing.
 */
int honey_window_focus_bind(lua_State* L);

/** @brief Unbind any callback that may be attached to the window focus.
 *
 * @returns Nothing.
 */
int honey_window_focus_unbind(lua_State* L);

#endif
