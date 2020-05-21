/** @file Defines the honey_mesh struct and related basic mesh functions. 
*/

#ifndef HONEY_MESH_H
#define HONEY_MESH_H

#include "common.h"
#include "shader.h"

enum honey_mesh_result {
  MESH_OK,
  MEMORY_ERROR,
  BAD_VERTEX_DATA,
  BAD_INDEX_DATA,
  N_MESH_RESULTS };

typedef struct {
  float* vertices;
  unsigned int n_vertices;
  unsigned int* indices;
  unsigned int n_indices;
  unsigned int vertex_array, vertex_buffer, element_buffer;
} honey_mesh;

/** @brief Create a new mesh from vertex and index arrays.
 *
 * Note that this function creates copies of the vertex and index arrays, 
 * so you can deallocate those immediately.
 *
 * @param[out] mesh Pointer to the destination honey_mesh struct
 * @param[in] vertices Array of floats representing the vertices
 * @param[in] n_attributes The number of attributes per vertex
 * @param[in] attribute_sizes An array containing for each attribute how many floats it contains
 * @param[in] n_vertices The number of vertices (NOT the number of floats in the vertex array)
 * @param[in] indices Array of vertex indices
 * @param[in] n_indices The number of elements in the index array
 */
enum honey_mesh_result honey_mesh_new(honey_mesh* mesh,
                                      float* vertices,
                                      unsigned int n_vertices,
                                      unsigned int n_attributes,
                                      unsigned int* attribute_sizes,
                                      unsigned int* indices,
                                      unsigned int n_indices);

/** @brief Draw a mesh on screen.
 *
 * @param[in] mesh The mesh to draw
 * @param[in] shader The shader to use when drawing the mesh
 */
void honey_mesh_draw(honey_mesh mesh,
                     honey_shader shader);

/** @brief Delete a mesh.
 *
 * @param[in] mesh The mesh to delete
 */
void honey_mesh_delete(honey_mesh mesh);
  
#endif
