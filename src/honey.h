#ifndef HONEY_ENGINE_H
#define HONEY_ENGINE_H

/** @file honey.h
 * 
 * @brief Defines the basic loading and callback functions. 
*/

#include "common.h"

#include "cairo_bindings.h"
#include "glm_bindings.h"
#include "input.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "window.h"

/** @struct Helper struct to wrap command-line options. */
typedef struct {
    bool verbose;
    char* script_directory;
    char* logfile;
} honey_options;

/** @brief Print usage help for honey. */
void honey_print_help();

/** @brief Parse command-line options for honey.
 *
 * This function returns false if the -h option was passed, for simplicity's sake.
 *
 * @param[in] argc The number of arguments passed to honey.
 * @param[in] argv Argument string array.
 * @param[out] options Pointer to the honey_options struct to populate.
 *
 * @returns true if parsing was successful and execution should continue;
 * false otherwise.
 */
bool honey_parse_options(honey_options* options, int argc, char** argv);

/** @brief Initialize Honey and set up lua bindings.
 *
 * @param[out] L The lua state with honey configured.
 * @param[out] window The GLFW window configured by honey. 
 * Also accessible from lua as honey.window.glfw_window.
 *
 * @returns true on a success; false otherwise.
 */
bool honey_setup(lua_State** L);

/** @brief The main game loop.
 *
 * @param[in] L The lua state honey was initialized in.
 * @param[in] opts The honey_options struct previously populated by honey_parse_options().
 */
bool honey_run(lua_State* L, honey_options opts);

/** @brief Get a registry reference to a given honey callback.
 *
 * @param[in] L The lua state to find the reference in.
 * @param[in] callback Name of the callback to find.
 *
 * @returns Registry reference to the function if it exists;
 * LUA_NOREF otherwise.
 */
int honey_get_callback(lua_State* L, char* callback);

/** @brief Set the current render target.
 *
 * @param[in] framebuffer The framebuffer to target, or 0 to target the window's framebuffer.
 *
 * @returns Nothing.
 */
int honey_set_framebuffer(lua_State* L);

#endif
