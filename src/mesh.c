#include "include/mesh.h"

enum honey_mesh_result honey_mesh_new(honey_mesh* mesh,
                                      float* vertices,
                                      unsigned int n_vertices,
                                      unsigned int n_attributes,
                                      unsigned int* attribute_sizes,
                                      unsigned int* indices,
                                      unsigned int n_indices) {
  if (vertices == NULL || n_vertices == 0) {
    return BAD_VERTEX_DATA;
  }
  if (indices == NULL || n_indices == 0) {
    return BAD_INDEX_DATA;
  }

  unsigned int vertex_size = 0;
  for (int i=0; i<n_attributes; i++) {
    vertex_size += attribute_sizes[i];
  }

  (*mesh).vertices = malloc(vertex_size*n_vertices * sizeof(float));
  if ((*mesh).vertices == NULL) {
    return MEMORY_ERROR;
  }
  memcpy((*mesh).vertices, vertices, vertex_size*n_vertices*sizeof(float));

  (*mesh).indices = malloc(n_indices * sizeof(unsigned int));
  if ((*mesh).indices == NULL) {
    return MEMORY_ERROR;
  }
  memcpy((*mesh).indices, indices, n_indices * sizeof(unsigned int));

  (*mesh).n_vertices = n_vertices;
  (*mesh).n_indices  = n_indices;

  glGenVertexArrays(1, &((*mesh).vertex_array));
  glGenBuffers(1, &((*mesh).vertex_buffer));
  glGenBuffers(1, &((*mesh).element_buffer));

  glBindVertexArray((*mesh).vertex_array);

  glBindBuffer(GL_ARRAY_BUFFER, (*mesh).vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, vertex_size*n_vertices*sizeof(float), (*mesh).vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*mesh).element_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_indices * sizeof(unsigned int), (*mesh).indices, GL_STATIC_DRAW);

  /* set up vertex attributes */
  unsigned int offset = 0;
  for (int i=0; i<n_attributes; i++) {
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i,
                          attribute_sizes[i],
                          GL_FLOAT,
                          GL_FALSE,
                          vertex_size*sizeof(float),
                          (void*) (offset*sizeof(float)));
    offset += attribute_sizes[i];
  }
  
  glBindVertexArray(0);

  return MESH_OK;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_mesh_draw(honey_mesh mesh, honey_shader shader) {
  honey_shader_use(shader);
  
  glBindVertexArray(mesh.vertex_array);
  glDrawElements(GL_TRIANGLES, mesh.n_indices, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_mesh_delete(honey_mesh mesh) {
  free(mesh.vertices);
  free(mesh.indices);

  glDeleteVertexArrays(1, &(mesh.vertex_array));
  glDeleteBuffers(1, &(mesh.vertex_buffer));
  glDeleteBuffers(1, &(mesh.element_buffer));
}
