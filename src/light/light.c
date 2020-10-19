#include "light.h"

void honey_point_light_new(honey_point_light* light,
                           float x, float y, float z,
                           float r, float g, float b,
                           float constant,
                           float linear,
                           float quadratic) {
  light->position[0] = x;
  light->position[1] = y;
  light->position[2] = z;
  
  light->color[0] = r;
  light->color[1] = g;
  light->color[2] = b;

  light->constant = constant;
  light->linear = linear;
  light->quadratic = quadratic;
}
