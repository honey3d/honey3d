#include "../include/common.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_error_clear_strings() {
  memset(honey_error_data.string1, 0, HONEY_ERROR_DATA_STRING_LENGTH);
  memset(honey_error_data.string2, 0, HONEY_ERROR_DATA_STRING_LENGTH);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_error_set_string1(char* string) {
  size_t n_bytes = strlen(string) + 1;
  if (n_bytes > HONEY_ERROR_DATA_STRING_LENGTH)
    n_bytes = HONEY_ERROR_DATA_STRING_LENGTH;
  memcpy(honey_error_data.string1, string, n_bytes);
  honey_error_data.string1[HONEY_ERROR_DATA_STRING_LENGTH-1] = 0;
}

void honey_error_set_string2(char* string) {
  size_t n_bytes = strlen(string) + 1;
  if (n_bytes > HONEY_ERROR_DATA_STRING_LENGTH)
    n_bytes = HONEY_ERROR_DATA_STRING_LENGTH;
  memcpy(honey_error_data.string2, string, n_bytes);
  honey_error_data.string2[HONEY_ERROR_DATA_STRING_LENGTH-1] = 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_human_readable_error(char* error_string, honey_error error) {
  size_t string_size = sizeof(char)*3*HONEY_ERROR_DATA_STRING_LENGTH;
    
  switch(error) {
  case HONEY_OK:
    snprintf(error_string, string_size, "[honey] OK");
    break;

  case HONEY_MEMORY_ALLOCATION_ERROR:
    snprintf(error_string, string_size, "[honey] ERROR: failed to allocate memory");
    break;

  case HONEY_FILE_READ_ERROR:
    if (honey_error_data.string1 != NULL) {
      snprintf(error_string,
               string_size,
               "[honey] ERROR: failed to read file '%s'",
               honey_error_data.string1);
    } else {
      snprintf(error_string, string_size, "[honey] ERROR: failed to read file");
    }
    break;

  case HONEY_VERTEX_SHADER_COMPILATION_ERROR:
    if (honey_error_data.string1 != NULL) {
      if (honey_error_data.string2 != NULL) {
        snprintf(error_string,
                 string_size,
                 "[honey] ERROR: failed to compile vertex shader '%s'\n"
                 "[honey] GLSL compiler output:\n%s\n",
                 honey_error_data.string2,
                 honey_error_data.string1);
      } else {
        snprintf(error_string,
                 string_size,
                 "[honey] ERROR: failed to compile vertex shader\n"
                 "[honey] GLSL compiler output:\n%s\n",
                 honey_error_data.string1);
      }
    } else {
      snprintf(error_string,
               string_size,
               "[honey] ERROR: failed to compile vertex shader.");
    }
    break;


  case HONEY_FRAGMENT_SHADER_COMPILATION_ERROR:
    if (honey_error_data.string1 != NULL) {
      if (honey_error_data.string2 != NULL) {
        snprintf(error_string,
                 string_size,
                 "[honey] ERROR: failed to compile fragment shader '%s'\n"
                 "[honey] GLSL compiler output:\n%s\n",
                 honey_error_data.string2,
                 honey_error_data.string1);
      } else {
        snprintf(error_string,
                 string_size,
                 "[honey] ERROR: failed to compile fragment shader\n"
                 "[honey] GLSL compiler output:\n%s\n",
                 honey_error_data.string1);
      }
    } else {
      snprintf(error_string,
               string_size,
               "[honey] ERROR: failed to compile fragment shader.");
    }
    break;
        
  case HONEY_SHADER_LINK_ERROR:
    break;
    
  case HONEY_MESH_BAD_VERTEX_DATA:
    break;
    
  case HONEY_MESH_BAD_INDEX_DATA:
    break;

  case HONEY_MODEL_LOAD_ERROR:
    snprintf(error_string,
             string_size,
             "[honey] ERROR: model '%s' contains errors",
             honey_error_data.string1);
    break;

  default:
    break;
  }
}
    

    
    
    
    
    
