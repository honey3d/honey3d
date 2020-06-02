#ifndef HONEY_MODEL_H
#define HONEY_MODEL_H

#include "common.h"
#include "mesh.h"
#include "shader.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#define HONEY_MODEL_MAX_MESHES 32

typedef struct {
  mat4 model_matrix;
  honey_mesh meshes[HONEY_MODEL_MAX_MESHES];
  unsigned int n_meshes;
} honey_model;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/** @brief Load a model.
 *
 * @param[out] model Pointer to the destination honey_model struct.
 * @param[in] path Path of the model to be loaded.
 */
honey_error honey_model_load(honey_model* model, char* path);
void honey_model_draw(honey_model* model, honey_shader shader);
void honey_model_delete(honey_model* model);

#endif
