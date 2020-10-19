#ifndef HONEY_LIGHT_H
#define HONEY_LIGHT_H

#include "../common.h"

#define HONEY_MAX_LIGHT_NAME_LENGTH 64

typedef struct {
  vec3 position;
  vec3 color;

  float constant;
  float linear;
  float quadratic;
} honey_point_light;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef struct {
  vec3 direction;
  vec3 color;
} honey_directional_light;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_point_light_new(honey_point_light* light,
                           float x, float y, float z,
                           float r, float g, float b,
                           float constant,
                           float linear,
                           float quadratic);

#endif
