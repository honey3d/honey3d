#ifndef HONEY_CGLM_BINDINGS_H
#define HONEY_CGLM_BINDINGS_H

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

/** @brief Dot product of a and b.
 *
 * @param[in] a Vector a.
 * @param[in] b Vector b.
 *
 * @returns The result of dot(a, b)
 */
int honey_cglm_vec3_dot(lua_State* L);

/** @brief Cross product of a and b.
 *
 * @param[in] a Vector a.
 * @param[in] b Vector b.
 *
 * @returns vec3 of cross(a, b).
 */
int honey_cglm_vec3_cross(lua_State* L);

/** @brief Compute the square of the norm of a vector.
 *
 * This function is useful if you want norm*norm
 * because it avoids the overhead of two sqrt calls.
 *
 * @param a Vector a.
 *
 * @returns The square of norm(a).
 */
int honey_cglm_vec3_square_norm(lua_State* L);

/** @brief Compute the L2 norm of a vector.
 *
 * @param a Vector a.
 *
 * @returns The norm(a).
 */
int honey_cglm_vec3_norm(lua_State* L);

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
 *
 * @returns a + b
 */
int honey_cglm_vec4_add(lua_State* L);

/** @brief Add a scalar to a vector.
 *
 * @param[in] a The scalar.
 * @param[in] v The vector.
 *
 * @returns a + v.
 */
int honey_cglm_vec4_adds(lua_State* L);

/** @param Component-wise multiply two vectors together.
 *
 * @param a The first vector.
 * @param b The second vector.
 *
 * @returns [ a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w ]
 */
int honey_cglm_vec4_mul(lua_State* L);

/** @brief Multiply a vector by a scalar.
 *
 * @param a The scalar.
 * @param v The vector.
 *
 * @returns a*v.
 */
int honey_cglm_vec4_muls(lua_State* L);

/** @brief Normalize a vector.
 *
 * @param[inout] v The vector.
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
 * @param a The first vector.
 * @param b The second vector.
 * @param s A scalar.
 *
 * @returns a + s*(b-s)
 */
int honey_cglm_vec4_lerp(lua_State* L);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * cglm mat4 functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/** @brief Set a matrix to be the identity matrix.
 *
 * @param matrix The matrix to set to the identity.
 *
 * @returns Nothing.
 */
int honey_cglm_mat4_identity(lua_State* L);

/** @brief Get the upper left of a matrix as a mat3.
 *
 * @param matrix The matrix to extract.
 *
 * @returns A new matrix containing the upper left 3x3 section of matrix.
 */
int honey_cglm_mat4_pick3(lua_State* L);

/** @brief Multiply two mat4s together.
 *
 * @param A The first matrix.
 * @param B The second matrix.
 *
 * @returns A*B.
 */
int honey_cglm_mat4_mul(lua_State* L);

/** @brief Multiply a matrix by a scalar.
 *
 * @param[in] a The scalar.
 * @param[in] M The matrix.
 *
 * @returns Matrix containing a*M.
 */
int honey_cglm_mat4_muls(lua_State* L);

/** @brief Multiply a matrix by a column vector.
 *
 * @param[in] M The matrix.
 * @param[in] v The column vector.
 *
 * @returns Matrix containing M*v.
 */
int honey_cglm_mat4_mulv(lua_State* L);

/** @brief Transpose a matrix.
 *
 * @param[inout] M The matrix to transpose.
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
 *
 * @returns inv(M).
 */
int honey_cglm_mat4_inv(lua_State* L);

/** @brief Get the inverse of a matrix.
 *
 * This is the fast version; use honey_cglm_mat4_inv
 * for a slower but more precise version.
 *
 * @param[in] M The matrix to invert.
 *
 * @returns inv(M).
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
 * @param[inout] matrix The mat4 to translate.
 * @param[in] vector The vec3 to translate by.
 *
 * @returns Nothing.
 */
int honey_cglm_translate(lua_State* L);

/** @brief Scale a matrix by a vector.
 *
 * @param[inout] matrix The mat4 to scale.
 * @param[in] vector The vec3 to scale by.
 *
 * @returns Nothing.
 */
int honey_cglm_scale(lua_State* L);

/** @brief Rotate a matrix about a given axis.
 *
 * @param[inout] matrix The mat4 to rotate.
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

#endif
