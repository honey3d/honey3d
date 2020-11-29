#include "camera.h"

void honey_camera_new(honey_camera* camera,
                      vec3 position,
                      vec3 angle,
                      enum honey_camera_projection projection_type,
                      float aspect_ratio,
                      float near, float far,
                      float fov,
                      float left, float right, float top, float bottom) {
  glm_vec3_copy(position, camera->position);
  glm_vec3_copy(angle, camera->angle);

  camera->projection_type = projection_type;

  camera->aspect_ratio = aspect_ratio;
  camera->near = near;
  camera->far = far;
  
  if (projection_type == HONEY_PERSPECTIVE) {
    camera->fov = fov;
  }
  else if (projection_type == HONEY_ORTHOGRAPHIC) {
    camera->ortho_left = left;
    camera->ortho_right = right;
    camera->ortho_top = top;
    camera->ortho_bottom = bottom;
  }

  honey_camera_calculate_view(camera);
  honey_camera_calculate_projection(camera);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_camera_new_perspective(honey_camera* camera,
                                  vec3 position,
                                  vec3 angle,
                                  float aspect_ratio,
                                  float near, float far,
                                  float fov) {
  honey_camera_new(camera,
                   position, angle,
                   HONEY_PERSPECTIVE,
                   aspect_ratio, near, far, fov,
                   0, 0, 0, 0);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_camera_new_orthographic(honey_camera* camera,
                                   vec3 position,
                                   vec3 angle,
                                   float near, float far,
                                   float left, float right, float top, float bottom) {
  honey_camera_new(camera,
                   position, angle,
                   HONEY_ORTHOGRAPHIC,
                   0,
                   near, far,
                   0,
                   left, right, top, bottom);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_camera_calculate_look_direction(honey_camera* camera) {
  float pitch = camera->angle[0];
  float yaw = camera->angle[1];

  float x = cos(pitch) * cos(yaw);
  float y = sin(pitch);
  float z = cos(pitch) * sin(yaw);

  camera->look_direction[0] = x;
  camera->look_direction[1] = y;
  camera->look_direction[2] = z;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_camera_calculate_up(honey_camera* camera) {
 float pitch = camera->angle[0];
 float yaw = camera->angle[1];
 float roll = camera->angle[2];

 camera->up[0] = 0;
 camera->up[1] = 1;
 camera->up[2] = 0;

 mat3 rot3;
 mat4 rot4;
 glm_mat4_identity(rot4);
 glm_rotate(rot4, roll, camera->look_direction);
 glm_mat4_pick3(rot4, rot3);

 glm_mat3_mulv(rot3, camera->up, camera->up);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_camera_calculate_right(honey_camera* camera) {
  glm_vec3_cross(camera->up, camera->look_direction, camera->right);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_camera_calculate_view(honey_camera* camera) {
  honey_camera_calculate_look_direction(camera);
  honey_camera_calculate_up(camera);
  honey_camera_calculate_right(camera);

  glm_look(camera->position, camera->look_direction, camera->up, camera->view);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_camera_calculate_projection(honey_camera* camera) {
  if (camera->projection_type == HONEY_PERSPECTIVE) {
    glm_mat4_identity(camera->projection);
    glm_perspective(camera->fov,
                    camera->aspect_ratio,
                    camera->near,
                    camera->far,
                    camera->projection);
  }
  else if (camera->projection_type == HONEY_ORTHOGRAPHIC) {
    glm_mat4_identity(camera->projection);
    glm_ortho(camera->ortho_left,
              camera->ortho_right,
              camera->ortho_bottom,
              camera->ortho_top,
              camera->near,
              camera->far,
              camera->projection);
  }
}
