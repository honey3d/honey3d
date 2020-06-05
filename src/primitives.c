#include "include/primitives.h"

honey_result honey_mesh_new_textured_plane(honey_mesh* mesh,
                                           float width,
                                           float height) {
  float x0 = 0;
  float y0 = 0;
  float x1 = width;
  float y1 = height;

  float vertices[] = {
    /* position        normal        uv */
    x0, y0, 0,         0, 0, 1,      0, 0,
    x1, y0, 0,         0, 0, 1,      1, 0,
    x0, y1, 0,         0, 0, 1,      0, 1,
    x1, y1, 0,         0, 0, 1,      1, 1 };

  unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3 };

  unsigned int attrib_sizes[] = { 3, 3, 2 };

  honey_result result = honey_mesh_new(mesh,
                                       vertices, 4,
                                       3, attrib_sizes,
                                       indices, 6);
  return result;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

honey_result honey_mesh_new_cube(honey_mesh* mesh,
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
    /* position        normal     tex coord */
    /* back face */
    x0, y0, z0,       0, 0, -1,
    x1, y0, z0,       0, 0, -1,
    x0, y1, z0,       0, 0, -1,
    x1, y1, z0,       0, 0, -1,

    /* front face */
    x0, y0, z1,       0, 0, 1, 
    x1, y0, z1,       0, 0, 1, 
    x0, y1, z1,       0, 0, 1, 
    x1, y1, z1,       0, 0, 1, 

    /* left face */
    x0, y0, z0,       -1, 0, 0,
    x0, y1, z0,       -1, 0, 0,
    x0, y0, z1,       -1, 0, 0,
    x0, y1, z1,       -1, 0, 0,

    /* right face */
    x1, y0, z0,        1, 0, 0,
    x1, y1, z0,        1, 0, 0,
    x1, y0, z1,        1, 0, 0,
    x1, y1, z1,        1, 0, 0,

    /* bottom face */
    x0, y0, z0,       0, -1, 0,
    x1, y0, z0,       0, -1, 0,
    x0, y0, z1,       0, -1, 0,
    x1, y0, z1,       0, -1, 0,
    
    /* top face */
    x0, y1, z0,       0,  1, 0,
    x1, y1, z0,       0,  1, 0,
    x0, y1, z1,       0,  1, 0,
    x1, y1, z1,       0,  1, 0 };

  unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3,
    4, 5, 6,
    5, 6, 7,
    8, 9, 10,
    9, 10, 11,
    12, 13, 14,
    13, 14, 15,
    16, 17, 18,
    17, 18, 19,
    20, 21, 22,
    21, 22, 23 };

  unsigned int attrib_sizes[] = { 3, 3 };

  honey_result result = honey_mesh_new(mesh,
                                       vertices, 24,
                                       2, attrib_sizes,
                                       indices, 36);

  return result;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

honey_result honey_mesh_new_textured_cube(honey_mesh* mesh,
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
    /* position        normal     tex coord */
    /* back face */
    x0, y0, z0,       0, 0, -1,     0, 0,
    x1, y0, z0,       0, 0, -1,     1, 0,
    x0, y1, z0,       0, 0, -1,     0, 1,
    x1, y1, z0,       0, 0, -1,     1, 1,

    /* front face */
    x0, y0, z1,       0, 0, 1,      0, 0,
    x1, y0, z1,       0, 0, 1,      1, 0,
    x0, y1, z1,       0, 0, 1,      0, 1,
    x1, y1, z1,       0, 0, 1,      1, 1,

    /* left face */
    x0, y0, z0,       -1, 0, 0,     0, 0,
    x0, y1, z0,       -1, 0, 0,     1, 0,
    x0, y0, z1,       -1, 0, 0,     0, 1,
    x0, y1, z1,       -1, 0, 0,     1, 1,

    /* right face */
    x1, y0, z0,        1, 0, 0,     0, 0,
    x1, y1, z0,        1, 0, 0,     1, 0,
    x1, y0, z1,        1, 0, 0,     0, 1,
    x1, y1, z1,        1, 0, 0,     1, 1,

    /* bottom face */
    x0, y0, z0,       0, -1, 0,     0, 0,
    x1, y0, z0,       0, -1, 0,     1, 0,
    x0, y0, z1,       0, -1, 0,     0, 1,
    x1, y0, z1,       0, -1, 0,     1, 1,
    
    /* top face */
    x0, y1, z0,       0,  1, 0,     0, 0,
    x1, y1, z0,       0,  1, 0,     1, 0,
    x0, y1, z1,       0,  1, 0,     0, 1,
    x1, y1, z1,       0,  1, 0,     1, 1 };

  unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3,
    4, 5, 6,
    5, 6, 7,
    8, 9, 10,
    9, 10, 11,
    12, 13, 14,
    13, 14, 15,
    16, 17, 18,
    17, 18, 19,
    20, 21, 22,
    21, 22, 23 };

  unsigned int attrib_sizes[] = { 3, 3, 2 };

  honey_result result;
  result = honey_mesh_new(mesh, vertices, 24,
                          3, attrib_sizes,
                          indices, 36);
  return result;
}
