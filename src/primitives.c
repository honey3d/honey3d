#include "include/primitives.h"

enum honey_mesh_result honey_mesh_new_cube(honey_mesh* mesh,
                                           float width,
                                           float height,
                                           float depth) {
  float x0 = 0;
  float y0 = 0;
  float z0 = 0;

  float x1 = width;
  float y1 = height;
  float z1 = depth;

  float vertices[] = {
    x0, y0, z0,
    x1, y0, z0,
    x0, y1, z0,
    x1, y1, z0,
    x0, y0, z1,
    x1, y0, z1,
    x0, y1, z1,
    x1, y1, z1 };

  unsigned int indices[] = { 0, 1, 2,
                             1, 2, 3,
                             4, 5, 6,
                             5, 6, 7,
                             0, 2, 4,
                             2, 4, 6,
                             1, 3, 5,
                             3, 5, 7,
                             2, 3, 6,
                             3, 6, 7,
                             0, 1, 4,
                             1, 4, 5 };

  unsigned int attrib_sizes[] = { 3 };

  enum honey_mesh_result result = honey_mesh_new(mesh,
                                                 vertices,
                                                 8, 1, attrib_sizes,
                                                 indices, 36);

  return result;
}


