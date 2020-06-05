#ifndef HONEY_PRIMITIVES_H
#define HONEY_PRIMITIVES H

/** @file primitives.h
 *
 * @brief Define various common primitive objects.
 */

#include "common.h"
#include "mesh.h"

/** @brief Create a textured plane.
 *
 * This function creates a plane with vertex positions in attribute 0,
 * vertex normals in attribute 1, and UV coordinates in attribute 2.
 *
 * @param[out] mesh Pointer to the destination mesh
 * @param[in] width Desired width of the plane (x-axis)
 * @param[in] height Desired height of the plane (y-axis)
 *
 * @return 0 (HONEY_OK) on success, and an error code otherwise. 
 */
honey_result honey_mesh_new_textured_plane(honey_mesh* mesh,
                                           float width,
                                           float height);

/** @brief Create a cube.
 *
 * This function creates a cube with vertex positions in attribute 0.
 *
 * @param[out] mesh Pointer to the destination mesh
 * @param[in] width Desired width of the cube (x-axis)
 * @param[in] height Desired height of the cube (y-axis)
 * @param[in] depth Desired depth of the cube (z-axis)
 * 
 * @return Success or failure code
 */
honey_result honey_mesh_new_cube(honey_mesh* mesh,
                                 float width,
                                 float height,
                                 float depth);
/** @brief Create a textured cube.
 *
 * This function creates a cube with vertex positions in attribute 0,
 * and texture coordinates in attribute 1.
 *
 * @param[out] mesh Pointer to the destination mesh
 * @param[in] width Desired width of the cube (x-axis)
 * @param[in] height Desired height of the cube (y-axis)
 * @param[in] depth Desired depth of the cube (z-axis)
 * 
 * @return Success or failure code
 */
honey_result honey_mesh_new_textured_cube(honey_mesh* mesh,
                                          float width,
                                          float height,
                                          float depth);

#endif
