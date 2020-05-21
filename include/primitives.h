#ifndef HONEY_PRIMITIVES_H
#define HONEY_PRIMITIVES H

/** @file Define various common primitive objects.
 */

#include "common.h"
#include "mesh.h"

/** @brief Create a cube.
 *
 * @param[out] mesh Pointer to the destination mesh
 * @param[in] width Desired width of the cube (x-axis)
 * @param[in] height Desired height of the cube (y-axis)
 * @param[in] depth Desired depth of the cube (z-axis)
 * 
 * @return Success or failure code
 */
enum honey_mesh_result honey_mesh_new_cube(honey_mesh* mesh,
                                           float width,
                                           float height,
                                           float depth);

#endif
