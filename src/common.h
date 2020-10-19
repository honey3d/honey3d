#ifndef HONEY_COMMON_H
#define HONEY_COMMON_H

// standard c libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// POSIX options
#include <unistd.h>

// lua interpreter
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

// glad
#include "glad/glad.h"
#include <GLFW/glfw3.h>

// c opengl mathematics function
#include <cglm/cglm.h>
#include <cglm/call.h>

// assimp
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// stb image
#include "stb_image/stb_image.h"

typedef GLFWwindow* honey_window;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef enum {
  /* generic results */
  HONEY_OK,
  HONEY_MEMORY_ALLOCATION_ERROR,
  HONEY_FILE_READ_ERROR,

  /* shader errors */
  HONEY_VERTEX_SHADER_COMPILATION_ERROR,
  HONEY_FRAGMENT_SHADER_COMPILATION_ERROR,
  HONEY_SHADER_LINK_ERROR,

  /* mesh errors */
  HONEY_MESH_BAD_VERTEX_DATA,
  HONEY_MESH_BAD_INDEX_DATA,

  /* model errors */
  HONEY_MODEL_LOAD_ERROR,
  
  HONEY_N_ERRORS
} honey_result;

#define HONEY_ERROR_DATA_STRING_LENGTH 4096

static struct {
  char string1[HONEY_ERROR_DATA_STRING_LENGTH];
  char string2[HONEY_ERROR_DATA_STRING_LENGTH];
} honey_error_data;

void honey_error_clear_strings();
void honey_error_set_string1(char* string);
void honey_error_set_string2(char* string);

/** @brief Generate a human-readable error message.
 *
 * @param[out] error_string A string with at least 3*HONEY_ERROR_DATA_STRING_LENGTH characters to store the result
 * @param[in] error The error to generate a message for
 */
void honey_human_readable_error(char* error_string, honey_result error);

#endif
