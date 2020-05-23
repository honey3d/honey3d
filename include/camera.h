#ifndef HONEY_CAMERA_H
#define HONEY_CAMERA_H

/** @file camera.h
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
 * The full camera creation function. Most of the time, you will probably use either
 * honey_camera_new_perspective() or honey_camera_new_projection() instead.
 *
 * @param[out] camera Pointer to the destination honey_camera.
 * @param[in] position The position of the camera.
 * @param[in] angle The Euler angles (pitch, yaw, roll) of the camera.
 * @param[in] projection_type The type of projection to use.
 * @param[in] aspect_ratio The aspect ratio of the camera. Set to zero if using orthographic projection.
 * @param[in] near The distance of the near plane.
 * @param[in] far The distance of the far plane.
 * @param[in] fov The field of view. Set to zero if using orthographic projection.
 * @param[in] left The leftmost distance. Set to zero if using perspective projection.
 * @param[in] right The rightmost distance. Set to zero if using perspective projection.
 * @param[in] top The uppermost distance. Set to zero if using perspective projection.
 * @param[in] bottom The lowest distance. Set to zero if using perspective projection.
 */
void honey_camera_new(honey_camera* camera,
                      vec3 position,
                      vec3 angle,
                      enum honey_camera_projection projection_type,
                      float aspect_ratio,
                      float near, float far,
                      float fov,
                      float left, float right, float top, float bottom);

/** @brief Create a camera with a perspective projection matrix.
 *
 * @param[out] camera Pointer to the destination honey_camera.
 * @param[in] position The position of the camera.
 * @param[in] angle The Euler angles (pitch, yaw, roll) of the camera.
 * @param[in] aspect_ratio The aspect ratio of the camera.
 * @param[in] near The distance of the near plane.
 * @param[in] far The distance of the far plane.
 * @param[in] fov The field of view. 
 */
void honey_camera_new_perspective(honey_camera* camera,
                                  vec3 position,
                                  vec3 angle,
                                  float aspect_ratio,
                                  float near, float far,
                                  float fov);

/** @brief Create a camera with an orthographic projection matrix.
 *
 * @param[out] camera Pointer to the destination honey_camera.
 * @param[in] position The position of the camera.
 * @param[in] angle The Euler angles (pitch, yaw, roll) of the camera.
 * @param[in] near The distance of the near plane.
 * @param[in] far The distance of the far plane.
 * @param[in] left The leftmost distance.
 * @param[in] right The rightmost distance.
 * @param[in] top The uppermost distance.
 * @param[in] bottom The lowest distance.
 */
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

/** @brief (Re-)Calculate a camera's up vector.
 *
 * @param[in] Pointer to the camera to re-calculate.
 */
void honey_camera_calculate_up(honey_camera* camera);

/** @brief (Re-)Calculate a camera's right vector.
 *
 * @param[in] Pointer to the camera to re-calculate.
 */
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
