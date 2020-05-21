#include "include/shader.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static char* read_file(char* file_path) {
  FILE* f = fopen(file_path, "r");
  if (f == NULL) {
    return NULL;
  }

  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  char* file_string = malloc(fsize + 1);
  if (file_string == NULL) {
    return NULL;
  }
  fread(file_string, 1, fsize, f);
  fclose(f);

  file_string[fsize] = 0;

  return file_string;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

enum honey_shader_result honey_shader_load(honey_shader* shader,
                                           char* vertex_shader_path,
                                           char* fragment_shader_path) {
  enum honey_shader_result result;

  /* load vertex shader code */
  char* vertex_shader_code = read_file(vertex_shader_path);

  /* load fragment shader code */
  char* fragment_shader_code = read_file(fragment_shader_path);

  /* compile shaders */
  int success;
  char error[512];

  int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, ((const char**)&vertex_shader_code), NULL);
  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, NULL, error);
    printf("Failed to compile vertex shader: %s\n", error);
    result = VERTEX_SHADER_FAILED;
    return result;
  }

  int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, ((const char**)&fragment_shader_code), NULL);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, NULL, error);
    printf("Failed to compile fragment shader: %s\n", error);
    result = FRAGMENT_SHADER_FAILED;
    return result;
  }

  /* link shaders */
  *shader = glCreateProgram();
  glAttachShader(*shader, vertex_shader);
  glAttachShader(*shader, fragment_shader);
  glLinkProgram(*shader);
  glGetShaderiv(*shader, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(*shader, 512, NULL, error);
    printf("Failed to link shaders: %s\n", error);
    result = SHADER_LINK_FAILED;
    return result;
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  free(vertex_shader_code);
  free(fragment_shader_code);

  result = SHADER_OK;
  
  return result;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_shader_set_int(honey_shader shader,
                          char* int_name,
                          int number) {
  honey_shader_use(shader);
  unsigned int int_location = glGetUniformLocation(shader, int_name);
  glUniform1i(int_location, number);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_shader_set_mat4(honey_shader shader,
                           char* matrix_name,
                           float* matrix) {
  glUseProgram(shader);
  unsigned int matrix_location = glGetUniformLocation(shader, matrix_name);
  glUniformMatrix4fv(matrix_location, 1, GL_FALSE, matrix);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  
