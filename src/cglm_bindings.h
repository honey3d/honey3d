#ifndef HONEY_CGLM_BINDINGS_H
#define HONEY_CGLM_BINDINGS_H

#include "common.h"

/** @brief Push the honey cglm binding functions to the lua stack.
 *
 * @returns Nothing.
 */
void honey_setup_cglm(lua_State* L);

/** @brief Push a new float array to the lua stack.
 *
 * This function initializes the array to all zeros.
 *
 * @param[in] n The size of the floating-point array to create.
 *
 * @returns The vector so generated.
 */
int honey_cglm_new_array_zero(lua_State* L);

/** @brief Set an element of a float array.
 *
 * This function does NOT check if your index is out of bounds.
 * Use caution!
 *
 * @param[in] array The array to modify.
 * @param[in] index The index to set.
 * @param[in] value The value to set array[index] to.
 *
 * @returns Nothing.
 */
int honey_cglm_array_set_value(lua_State* L);

/** @brief Get an element of a vec3.
 *
 * This function does NOT check if your index is out of bounds.
 * Use caution!
 *
 * @param[in] array The array to inspect.
 * @param[in] index The index to get.
 *
 * @returns The value at array[index].
 */
int honey_cglm_array_get_value(lua_State* L);

#endif
