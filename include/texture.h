#ifndef HONEY_TEXTURE_H
#define HONEY_TEXTURE_H

/** @file texture.h
 *
 *@brief Defines the honey_texture struct and associated functions. 
*/

#include "common.h"

enum honey_texture_result {
  TEXTURE_OK,
  TEXTURE_FAILED,
  N_TEXTURE_RESULTS };

typedef struct {
  unsigned int texture_id;
  int width;
  int height;
  int channels;
} honey_texture;

/** @brief Load a texture from disk.
 *
 * @param[out] texture Pointer to the destination texture
 * @param[in] texture_path Path to the location of the texture
 * @param[in] alpha_channel Set to true if the target image contains an alpha channel
 *
 * @return Success or failure type
 */
enum honey_texture_result honey_texture_new(honey_texture* texture,
                                            char* texture_path,
                                            bool alpha_channel);

#endif
