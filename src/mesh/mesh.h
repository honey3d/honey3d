#ifndef HONEY_MESH_H
#define HONEY_MESH_H

/** @file mesh.h
 *
 * @brief Defines the honey_mesh struct and related basic mesh functions. 
*/



#include "../common.h"
#include "../shader/shader.h"

typedef struct {
    unsigned int n_vertices, n_indices;
    unsigned int vertex_array, vertex_buffer, element_buffer;
} honey_mesh;

/** @brief Create a new mesh from vertex and index arrays.
 *
 * This function copies the data, so you can safely permit vertices and
 * indices to be garbage collected after calling it.
 *
 * @param[in] vertices Userdata array containing the vertices.
 * @param[in] indices Userdata array defining the mesh faces.
 * @param[in] attributes Lua table containing the attribute sizes.
 * @param[in] n_vertices Integer number of vertices.
 * @param[in] n_indices Integer number of indices.
 *
 * @returns Userdata containing the mesh's OpenGL handles.
 */
int honey_mesh_new(lua_State* L);

/** @brief Draw a mesh on screen.
 *
 * @param[in] mesh The mesh to draw
 * @param[in] shader The shader to use when drawing the mesh
 */
int honey_mesh_draw(lua_State* L);

/** @brief Delete a mesh.
 *
 * @param[in] mesh The mesh to delete
 */
int honey_mesh_delete(lua_State* L);
  
#endif
