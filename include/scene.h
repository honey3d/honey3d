#ifndef HONEY_SCENE_H
#define HONEY_SCENE_H

#include "common.h"
#include "light.h"
#include "model.h"
#include "texture.h"

#define HONEY_SCENE_MAX_POINT_LIGHTS 8
#define HONEY_SCENE_MAX_DIRECTIONAL_LIGHTS 8
#define HONEY_SCENE_MAX_MODELS 8
#define HONEY_SCENE_MAX_TEXTURES 8

typedef struct {
  honey_point_light point_lights[HONEY_SCENE_MAX_POINT_LIGHTS];
  unsigned int n_point_lights;
  
  honey_directional_light directional_lights[HONEY_SCENE_MAX_DIRECTIONAL_LIGHTS];
  unsigned int n_directional_lights;
  
  honey_mode models[HONEY_SCENE_MAX_MODELS];
  unsigned int n_models;
} honey_scene;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#endif
