#include "../include/shader.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static honey_error read_file(char** destination, char* file_path) {
  FILE* f = fopen(file_path, "r");
  if (f == NULL) {
    honey_error_set_string1(file_path);
    return HONEY_FILE_READ_ERROR;
  }

  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  *destination = malloc(fsize + 1);
  if (*destination == NULL) {
    return HONEY_MEMORY_ALLOCATION_ERROR;
  }
  fread(*destination, 1, fsize, f);
  fclose(f);

  (*destination)[fsize] = 0;

  return HONEY_OK;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

honey_error honey_shader_load(honey_shader* shader,
                              char* vertex_shader_path,
                              char* fragment_shader_path) {
  /* load vertex shader code */
  char* vertex_shader_code;
  honey_error result = read_file(&vertex_shader_code,
                                 vertex_shader_path);
  if (result != HONEY_OK)
    return result;

  /* load fragment shader code */
  char* fragment_shader_code;
  result = read_file(&fragment_shader_code,
                     fragment_shader_path);
  if (result != HONEY_OK)
    return result;

  result = honey_shader_new(shader,
                            vertex_shader_code,
                            fragment_shader_code);

  if (result == HONEY_VERTEX_SHADER_COMPILATION_ERROR)
    honey_error_set_string2(vertex_shader_path);

  if (result == HONEY_FRAGMENT_SHADER_COMPILATION_ERROR)
    honey_error_set_string2(fragment_shader_path);

  free(vertex_shader_code);
  free(fragment_shader_code);

  return result;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

honey_error honey_shader_new(honey_shader* shader,
                             char* vertex_shader_code,
                             char* fragment_shader_code) {
    /* compile shaders */
  int success;
  char error[512];

  int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, ((const char**)&vertex_shader_code), NULL);
  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    honey_error_clear_strings();
    char compiler_error[HONEY_ERROR_DATA_STRING_LENGTH];
    glGetShaderInfoLog(vertex_shader, HONEY_ERROR_DATA_STRING_LENGTH, NULL, compiler_error);
    honey_error_set_string1(compiler_error);
    return HONEY_VERTEX_SHADER_COMPILATION_ERROR;
  }

  int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, ((const char**)&fragment_shader_code), NULL);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    honey_error_clear_strings();
    char compiler_error[HONEY_ERROR_DATA_STRING_LENGTH];
    glGetShaderInfoLog(fragment_shader, HONEY_ERROR_DATA_STRING_LENGTH, NULL, compiler_error);
    honey_error_set_string1(compiler_error);
    return HONEY_FRAGMENT_SHADER_COMPILATION_ERROR;
  }

  /* link shaders */
  *shader = glCreateProgram();
  glAttachShader(*shader, vertex_shader);
  glAttachShader(*shader, fragment_shader);
  glLinkProgram(*shader);
  glGetShaderiv(*shader, GL_LINK_STATUS, &success);
  if (!success) {
    honey_error_clear_strings();
    char compiler_error[HONEY_ERROR_DATA_STRING_LENGTH];
    glGetShaderInfoLog(vertex_shader, HONEY_ERROR_DATA_STRING_LENGTH, NULL, compiler_error);
    honey_error_set_string1(compiler_error);
    return HONEY_SHADER_LINK_ERROR;
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return HONEY_OK;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_shader_set_int(honey_shader shader,
                          char* int_name,
                          int value) {
  honey_shader_use(shader);
  unsigned int int_location = glGetUniformLocation(shader, int_name);
  glUniform1i(int_location, value);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_shader_set_float(honey_shader shader,
                            char* float_name,
                            float value) {
  honey_shader_use(shader);
  unsigned int float_location = glGetUniformLocation(shader, float_name);
  glUniform1f(float_location, value);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_shader_set_vec3(honey_shader shader,
                           char* vector_name,
                           vec3 value) {
  honey_shader_use(shader);
  unsigned int vector_location = glGetUniformLocation(shader, vector_name);
  glUniform3fv(vector_location, 1, (float*) value);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_shader_set_mat3(honey_shader shader,
                           char* matrix_name,
                           mat3 value) {
  glUseProgram(shader);
  unsigned int matrix_location = glGetUniformLocation(shader, matrix_name);
  glUniformMatrix3fv(matrix_location, 1, GL_FALSE, (float*) value);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_shader_set_mat4(honey_shader shader,
                           char* matrix_name,
                           mat4 value) {
  glUseProgram(shader);
  unsigned int matrix_location = glGetUniformLocation(shader, matrix_name);
  glUniformMatrix4fv(matrix_location, 1, GL_FALSE, (float*) value);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  
