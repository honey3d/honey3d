/** @file shader.h
 * 
 * @brief Functions to create, manipulate, and destroy GLSL shaders. 
 */

#ifndef HONEY_SHADER_H
#define HONEY_SHADER_H

#include "common.h"

enum honey_shader_result {
  SHADER_OK,
  VERTEX_SHADER_NOT_FOUND,
  VERTEX_SHADER_TOO_LARGE,
  VERTEX_SHADER_FAILED,
  FRAGMENT_SHADER_NOT_FOUND,
  FRAGMENT_SHADER_TOO_LARGE,
  FRAGMENT_SHADER_FAILED,
  SHADER_LINK_FAILED,
  N_SHADER_STATES };

typedef int honey_shader;

/** @brief Load a shader.
 *
 * @param[out] shader Pointer to the shader destination
 *
 * @param[in] vertex_shader_path The path to the vertex shader source code
 * @param[in] fragment_shader_path The path to the fragment shader source code
 * 
 * @return The result of the shader load.
 */
enum honey_shader_result honey_shader_load(honey_shader* shader,
                                           char* vertex_shader_path,
                                           char* fragment_shader_path);

/** @brief Set an integer uniform.
 *
 * @param[in] shader The shader to which the uniform belongs
 * @param[in] int_name The name of the integer uniform
 * @param[in] value The value of the integer uniform
 */
void honey_shader_set_int(honey_shader shader,
                          char* int_name,
                          int value);

/** @brief Set a float uniform.
 *
 * @param[in] shader The shader to which the uniform belongs
 * @param[in] float_name The name of the float uniform
 * @param[in] value The value of the float uniform
 */
void honey_shader_set_float(honey_shader shader,
                            char* float_name,
                            float value);

/** @brief Set a vec3 uniform.
 * @param[in] shader The shader to which the uniform belongs
 * @param[in] vector_name The name of the vec3 uniform
 * @param[in] value The value of the vector uniform
 */
void honey_shader_set_vec3(honey_shader shader,
                           char* vector_name,
                           vec3 value);


/** @brief Set a mat3 uniform.
 *
 * @param[in] shader The shader to which the uniform belongs
 * @param[in] matrix_name The name of the matrix uniform
 * @param[in] value The value of the matrix uniform
 */
void honey_shader_set_mat3(honey_shader shader,
                           char* matrix_name,
                           mat3 value);

/** @brief Set a mat4 uniform.
 *
 * @param[in] shader The shader to which the uniform belongs
 * @param[in] matrix_name The name of the matrix uniform
 * @param[in] value The value of the matrix uniform
 */
void honey_shader_set_mat4(honey_shader shader,
                           char* matrix_name,
                           mat4 value);

/** @brief Use a shader.
 */
#define honey_shader_use glUseProgram

/** @brief delete a shader.
 */
#define honey_shader_delete glDeleteProgram

#endif
