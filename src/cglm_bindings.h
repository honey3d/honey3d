#ifndef HONEY_CGLM_BINDINGS_H
#define HONEY_CGLM_BINDINGS_H

/** @file cglm_bindings.h
 * @brief Lua bindings for CGLM functions. 
 */

#include "common.h"

/** @brief Push the honey cglm binding functions to the lua stack.
 *
 * @returns Nothing.
 */
void honey_setup_cglm(lua_State* L);

/** @brief Push a new float array to the lua stack.
 *
 * This function initializes the array to all zeros.
 *
 * @param[in] n The size of the floating-point array to create.
 *
 * @returns The vector so generated.
 */
int honey_cglm_new_array_zero(lua_State* L);

/** @brief Set an element of a float array.
 *
 * This function does NOT check if your index is out of bounds.
 * Use caution!
 *
 * @param[in] array The array to modify.
 * @param[in] index The index to set.
 * @param[in] value The value to set array[index] to.
 *
 * @returns Nothing.
 */
int honey_cglm_array_set_value(lua_State* L);

/** @brief Get an element of a vec3.
 *
 * This function does NOT check if your index is out of bounds.
 * Use caution!
 *
 * @param[in] array The array to inspect.
 * @param[in] index The index to get.
 *
 * @returns The value at array[index].
 */
int honey_cglm_array_get_value(lua_State* L);

/** @brief Create a copy of a floating point array.
 *
 * @param[in] array The array to copy.
 * @param[in] n The size of the array.
 *
 * @returns A copy of the array.
 */
int honey_cglm_array_copy(lua_State* L);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
 *
 * cglm vec3 functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/** @brief Compute the dot product of two vectors.
 *
 * @param[in] a Vector a.
 * @param[in] b Vector b.
 *
 * @returns dot(a,b).
 */
int honey_cglm_vec3_dot(lua_State* L);

/** @brief Compute the square of the norm of a vector.
 *
 * Use this if you are tempted to compute norm*norm;
 * it avoids the two calls to sqrt.
 *
 * @param[in] v The vector to compute norm^2 for.
 *
 * @returns norm(v)^2.
 */
int honey_cglm_vec3_norm2(lua_State* L);

/** @brief Compute the norm of a vector.
 *
 * @param[in] v The vector.
 *
 * @returns norm(v).
 */
int honey_cglm_vec3_norm(lua_State* L);

/** @brief Add two vectors together.
 *
 * @param[in] a The first vector.
 * @param[in] b The second vector.
 * @param[out] dest vec3 to fill with a + b.
 *
 * @returns Nothing.
 */
int honey_cglm_vec3_add(lua_State* L);

/** @brief Add a scalar to a vector.
 *
 * @param[in] a The scalar.
 * @param[in] v The vector.
 * @param[out] dest vec3 to fill with a + v
 *
 * @returns Nothing.
 */
int honey_cglm_vec3_adds(lua_State* L);

/** @param Component-wise multiply two vectors together.
 *
 * @param[in] a The first vector.
 * @param[in] b The second vector.
 * @param[out] dest vec3 to fill with [ a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w ]
 *
 * @returns Nothing.
 */
int honey_cglm_vec3_mul(lua_State* L);

/** @brief Multiply a vector by a scalar.
 *
 * @param[in] a The scalar.
 * @param[in] v The vector.
 * @param[out] dest vec3 to fill with a*v.
 *
 * @returns Nothing.
 */
int honey_cglm_vec3_muls(lua_State* L);

/** @brief Normalize a vector.
 *
 * @param[in,out] v The vector.
 *
 * @returns Nothing.
 */
int honey_cglm_vec3_normalize(lua_State* L);

/** @brief Compute the distance between two vectors.
 *
 * @param[in] a The first vector.
 * @param[in] b The second vector.
 *
 * @returns norm(a-b).
 */
int honey_cglm_vec3_distance(lua_State* L);

/** @brief Linearly interpolate between two values.
 *
 * @param[in] a The first vector.
 * @param[in] b The second vector.
 * @param[in] s A scalar.
 * @param[out] dest vec3 to fill with a + s*(b-s).
 *
 * @returns Nothing.
 */
int honey_cglm_vec3_lerp(lua_State* L);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * cglm vec4 functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/** @brief Compute the dot product of two vectors.
 *
 * @param[in] a Vector a.
 * @param[in] b Vector b.
 *
 * @returns dot(a,b).
 */
int honey_cglm_vec4_dot(lua_State* L);

/** @brief Compute the square of the norm of a vector.
 *
 * Use this if you are tempted to compute norm*norm;
 * it avoids the two calls to sqrt.
 *
 * @param[in] v The vector to compute norm^2 for.
 *
 * @returns norm(v)^2.
 */
int honey_cglm_vec4_norm2(lua_State* L);

/** @brief Compute the norm of a vector.
 *
 * @param[in] v The vector.
 *
 * @returns norm(v).
 */
int honey_cglm_vec4_norm(lua_State* L);

/** @brief Add two vectors together.
 *
 * @param[in] a The first vector.
 * @param[in] b The second vector.
 * @param[out] dest vec4 to fill with a + b.
 *
 * @returns Nothing.
 */
int honey_cglm_vec4_add(lua_State* L);

/** @brief Add a scalar to a vector.
 *
 * @param[in] a The scalar.
 * @param[in] v The vector.
 * @param[out] dest vec4 to fill with a + v
 *
 * @returns Nothing.
 */
int honey_cglm_vec4_adds(lua_State* L);

/** @param Component-wise multiply two vectors together.
 *
 * @param[in] a The first vector.
 * @param[in] b The second vector.
 * @param[out] dest vec4 to fill with [ a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w ]
 *
 * @returns Nothing.
 */
int honey_cglm_vec4_mul(lua_State* L);

/** @brief Multiply a vector by a scalar.
 *
 * @param[in] a The scalar.
 * @param[in] v The vector.
 * @param[out] dest vec4 to fill with a*v.
 *
 * @returns Nothing.
 */
int honey_cglm_vec4_muls(lua_State* L);

/** @brief Normalize a vector.
 *
 * @param[in,out] v The vector.
 *
 * @returns Nothing.
 */
int honey_cglm_vec4_normalize(lua_State* L);

/** @brief Compute the distance between two vectors.
 *
 * @param[in] a The first vector.
 * @param[in] b The second vector.
 *
 * @returns norm(a-b).
 */
int honey_cglm_vec4_distance(lua_State* L);

/** @brief Linearly interpolate between two values.
 *
 * @param[in] a The first vector.
 * @param[in] b The second vector.
 * @param[in] s A scalar.
 * @param[out] dest vec4 to fill with a + s*(b-s).
 *
 * @returns Nothing.
 */
int honey_cglm_vec4_lerp(lua_State* L);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * cglm mat3 functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/** @brief Set a matrix to be the identity matrix.
 *
 * @param[out] matrix The matrix to set to the identity.
 *
 * @returns Nothing.
 */
int honey_cglm_mat3_identity(lua_State* L);

/** @brief Multiply two mat3s together.
 *
 * @param[in] A The first matrix.
 * @param[in] B The second matrix.
 * @param[out] dest mat3 to fill with A*B.
 *
 * @returns Nothing.
 */
int honey_cglm_mat3_mul(lua_State* L);

/** @brief Multiply a matrix by a scalar.
 *
 * @param[in] a The scalar.
 * @param[in,out] M The matrix.
 *
 * @returns Nothing.
 */
int honey_cglm_mat3_muls(lua_State* L);

/** @brief Multiply a matrix by a column vector.
 *
 * @param[in] M The matrix.
 * @param[in] v The column vector.
 * @param[out] dest Matrix to fill with M*v.
 *
 * @returns Nothing.
 */
int honey_cglm_mat3_mulv(lua_State* L);

/** @brief Transpose a matrix.
 *
 * @param[in,out] M The matrix to transpose.
 *
 * @returns Nothing.
 */
int honey_cglm_mat3_trans(lua_State* L);

/** @brief Get the determinant of a matrix.
 *
 * @param[in] M The matrix.
 *
 * @returns det(M).
 */
int honey_cglm_mat3_det(lua_State* L);

/** @brief Get the trace of a matrix.
 *
 * @param[in] M The matrix.
 *
 * @returns trace(M).
 */
int honey_cglm_mat3_trace(lua_State* L);

/** @brief Get the inverse of a matrix.
 *
 * @param[in] M The matrix to invert.
 * @param[out] dest Matrix to fill with inv(M).
 *
 * @returns Nothing.
 */
int honey_cglm_mat3_inv(lua_State* L);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * cglm mat4 functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/** @brief Set a matrix to be the identity matrix.
 *
 * @param[out] matrix The matrix to set to the identity.
 *
 * @returns Nothing.
 */
int honey_cglm_mat4_identity(lua_State* L);

/** @brief Get the upper left of a matrix as a mat3.
 *
 * @param[in] matrix The matrix to extract.
 * @param[out] dest The 3x3 matrix to fill.
 *
 * @returns Nothing.
 */
int honey_cglm_mat4_pick3(lua_State* L);

/** @brief Multiply two mat4s together.
 *
 * @param[in] A The first matrix.
 * @param[in] B The second matrix.
 * @param[out] dest mat4 to fill with A*B.
 *
 * @returns Nothing.
 */
int honey_cglm_mat4_mul(lua_State* L);

/** @brief Multiply a matrix by a scalar.
 *
 * @param[in] a The scalar.
 * @param[in,out] M The matrix.
 *
 * @returns Nothing.
 */
int honey_cglm_mat4_muls(lua_State* L);

/** @brief Multiply a matrix by a column vector.
 *
 * @param[in] M The matrix.
 * @param[in] v The column vector.
 * @param[out] dest Matrix to fill with M*v.
 *
 * @returns Nothing.
 */
int honey_cglm_mat4_mulv(lua_State* L);

/** @brief Transpose a matrix.
 *
 * @param[in,out] M The matrix to transpose.
 *
 * @returns Nothing.
 */
int honey_cglm_mat4_trans(lua_State* L);

/** @brief Get the determinant of a matrix.
 *
 * @param[in] M The matrix.
 *
 * @returns det(M).
 */
int honey_cglm_mat4_det(lua_State* L);

/** @brief Get the trace of a matrix.
 *
 * @param[in] M The matrix.
 *
 * @returns trace(M).
 */
int honey_cglm_mat4_trace(lua_State* L);

/** @brief Get the inverse of a matrix.
 *
 * This is the precise version; use honey_cglm_mat4_inv_fast
 * for a faster but less precise version.
 *
 * @param[in] M The matrix to invert.
 * @param[out] dest Matrix to fill with inv(M).
 *
 * @returns Nothing.
 */
int honey_cglm_mat4_inv(lua_State* L);

/** @brief Get the inverse of a matrix.
 *
 * This is the fast version; use honey_cglm_mat4_inv
 * for a slower but more precise version.
 *
 * @param[in] M The matrix to invert.
 * @param[out] dest Matrix to fill with inv(M).
 *
 * @returns Nothing.
 */
int honey_cglm_mat4_inv_fast(lua_State* L);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * cglm 3d affine transforms
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/** @brief Translate a matrix by a vector.
 *
 * This function modifies the matrix in place.
 *
 * @param[in,out] matrix The mat4 to translate.
 * @param[in] vector The vec3 to translate by.
 *
 * @returns Nothing.
 */
int honey_cglm_translate(lua_State* L);

/** @brief Scale a matrix by a vector.
 *
 * @param[in,out] matrix The mat4 to scale.
 * @param[in] vector The vec3 to scale by.
 *
 * @returns Nothing.
 */
int honey_cglm_scale(lua_State* L);

/** @brief Rotate a matrix about a given axis.
 *
 * @param[in,out] matrix The mat4 to rotate.
 * @param[in] center The vec3 center of rotation.
 * @param[in] axis The vec3 axis of rotation.
 * @param[in] angle The angle to rotate by.
 *
 * @returns Nothing.
 */
int honey_cglm_rotate(lua_State* L);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * cglm camera matrix functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/** @brief Put perspective projection matrix into float array.
 *
 * @param[out] matrix The mat4 to populate.
 * @param[in] fov The FOV for the camera.
 * @param[in] aspect The aspect ratio to use with the camera.
 * @param[in] near Distance to the near clipping plane.
 * @param[in] far Distance to the far clipping plane.
 *
 * @returns Nothing.
 */
int honey_cglm_perspective(lua_State* L);

/** @brief Put an orthographic projection matrix into float array.
 *
 * @param[out] matrix The mat4 to populate.
 * @param[in] a The first vector of the AABB bounding box.
 * @param[in] b The second vector of the AABB bounding box.
 *
 * @returns Nothing.
 */
int honey_cglm_orthographic(lua_State* L);

/** @brief Compute the view matrix.
 *
 * @param[in] position The camera's vec3 position.
 * @param[in] direction The vec3 direction the camera is facing.
 * @param[in] up The camera's vec3 up vector.
 * @param[out] dest The view matrix destination.
 *
 * @returns Nothing.
 */
int honey_cglm_look(lua_State* L);


#endif
