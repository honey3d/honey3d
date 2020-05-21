#include "include/texture.h"

enum honey_texture_result honey_texture_new(honey_texture* texture,
                                            char* texture_path,
                                            bool alpha_channel) {
  unsigned int texture_id;
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, channels;
  unsigned char* image_data = stbi_load(texture_path, &width, &height, &channels, 0);
  if (image_data == NULL) {
    fprintf(stderr, "ERROR: failed to load '%s'\n", texture_path);
    return TEXTURE_FAILED;
  }

  if (alpha_channel) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
  }
  else {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
  }

  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(image_data);

  (*texture).texture_id = texture_id;
  (*texture).width = width;
  (*texture).height = height;
  (*texture).channels = channels;

  return TEXTURE_OK;
}
