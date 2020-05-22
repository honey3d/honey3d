#ifndef HONEY_CAMERA_H
#define HONEY_CAMERA_H

/* @file camera.h
 *
 * @brief Define the basic honey_camera struct, associated functions,
 * and common camera variants.
 */

#include "common.h"

enum honey_camera_projection {
  HONEY_PERSPECTIVE,
  HONEY_ORTHOGRAPHIC,
};

typedef struct {
  vec3 position;
  vec3 angle; /* pitch, yaw, roll */
  vec3 look_direction;
  vec3 up;
  vec3 right;
  mat4 view;
  mat4 projection;
  enum honey_camera_projection projection_type;
  float aspect_ratio;
  float near, far;
  float fov;
  float ortho_left;
  float ortho_right;
  float ortho_top;
  float ortho_bottom;
} honey_camera;

/** @brief Create a new camera.
 *
 * @param[out] camera Pointer to the destination honey_camera.
 * @param[in] position The position of the camera.
 * @param[in] angle The Euler angles (pitch, yaw, roll) of the camera.
 * @param[in] projection The type of projection to use.
 * @param[in] projection_parameters The parameters to use for the projection matrix.
 * Use honey_perspective_parameters for a perspective projection and
 * honey_orthographic_parameters for an orthographic projection.
 */
void honey_camera_new(honey_camera* camera,
                      vec3 position,
                      vec3 angle,
                      enum honey_camera_projection projection_type,
                      float aspect_ratio,
                      float near, float far,
                      float fov,
                      float left, float right, float top, float bottom);

void honey_camera_new_perspective(honey_camera* camera,
                                  vec3 position,
                                  vec3 angle,
                                  float aspect_ratio,
                                  float near, float far,
                                  float fov);

void honey_camera_new_orthographic(honey_camera* camera,
                                   vec3 position,
                                   vec3 angle,
                                   float near, float far,
                                   float left, float right, float top, float bottom);

/** @brief (Re-)Calculate a camera's look_direction.
 *
 * @param[in] Pointer to the camera to re-calculate.
 */
void honey_camera_calculate_look_direction(honey_camera* camera);

void honey_camera_calculate_up(honey_camera* camera);
void honey_camera_calculate_right(honey_camera* camera);

/** @brief (Re-)Calculate a camera's view matrix. 
 *
 * This function need only be called when the camera has been moved in some way.
 *
 * @param[in] camera Pointer to the camera to re-calculate.
 */
void honey_camera_calculate_view(honey_camera* camera);

/** @brief (Re-)Calculate a camera's projection matrix.
 *
 * This function need only be called when the projection has changes in some way.
 * Most commonly, this would be changing the FOV.
 *
 * @param[in] camera Pointer to the camera to re-calculate.
 */
void honey_camera_calculate_projection(honey_camera* camera);

#endif
