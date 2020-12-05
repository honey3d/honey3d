#ifndef HONEY_TEXTURE_H
#define HONEY_TEXTURE_H

/** @file texture.h
 *
 *@brief Defines the honey_texture struct and associated functions. 
*/

#include "common.h"

extern int honey_texture_mt_ref;

enum honey_texture_result {
  TEXTURE_OK,
  TEXTURE_FAILED,
  TEXTURE_CHANNEL_ERROR,
  N_TEXTURE_RESULTS };

typedef struct {
    unsigned int id;
    enum {
        GREY,
        RGB,
        RGBA,
        DEPTH
    } type;
    int width;
    int height;
    int channels;
} honey_texture;

/** @brief Place the honey.texture bindings as a table on the stack. */
void honey_setup_texture(lua_State* L);

/** @brief Create a greyscale texture.
 *
 * @param[out] texture Pointer to the destination texture.
 * @param[in] width The width in pixels of the texture to create.
 * @param[in] height The height in pixels of the texture to create.
 * @param[in] data The data to populate the texture with, or NULL to leave it unpopulated.
 *
 * @returns Nothing.
 */
void honey_texture_new_greyscale(honey_texture* texture,
                                 int width, int height,
                                 unsigned char* data);

/** @brief Create an RGB texture.
 *
 * @param[out] texture Pointer to the destination texture.
 * @param[in] width The width in pixels of the texture to create.
 * @param[in] height The height in pixels of the texture to create.
 * @param[in] data The data to populate the texture with, or NULL to leave it unpopulated.
 *
 * @returns Nothing.
 */
void honey_texture_new_rgb(honey_texture* texture,
                           int width, int height,
                           unsigned char* data);

/** @brief Create an RGBA texture.
 *
 * @param[out] texture Pointer to the destination texture.
 * @param[in] width The width in pixels of the texture to create.
 * @param[in] height The height in pixels of the texture to create.
 * @param[in] data The data to populate the texture with, or NULL to leave it unpopulated.
 *
 * @returns Nothing.
 */
void honey_texture_new_rgba(honey_texture* texture,
                            int width, int height,
                            unsigned char* data);

/** @brief Create a depth texture.
 *
 * @param[out] texture Pointer to the destination texture.
 * @param[in] width The width in pixels of the texture to create.
 * @param[in] height The height in pixels of the texture to create.
 * @param[in] data The data to populate the texture with, or NULL to leave it unpopulated.
 *
 * @returns Nothing.
 */
void honey_texture_new_depth(honey_texture* texture,
                             int width, int height,
                             float* data);

/** @brief Load a texture from disk.
 *
 * @param[out] texture Pointer to the destination texture
 * @param[in] texture_path Path to the location of the texture
 * @param[in] alpha_channel Set to true if the target image contains an alpha channel
 *
 * @return Success or failure type
 */
enum honey_texture_result honey_texture_load(honey_texture* texture,
                                             char* texture_path);

/** @brief Load a texture into a texture unit.
 *
 * @param[in] texture The texture to use
 * @param[in] texture_unit The texture unit to put the texture in
 */
void honey_texture_use(honey_texture texture, int texture_unit);

/** @brief Create a framebuffer object.
 *
 * You must specify at least one of draw and depth; otherwise, the framebuffer will
 * be incomplete and fail.
 *
 * @param[out] destination Pointer to store the resulting OpenGL handle in.
 * @param[in] draw Pointer to a texture to draw to.
 * @param[in] depth Pointer to a depth texture.
 * @param[in] width The width in pixels of the FBO.
 * @param[in] height The height in pixels of the FBO.
 *
 * @returns Nothing.
 */
void honey_texture_framebuffer_object_new(unsigned int* destination,
                                          honey_texture* draw,
                                          honey_texture* depth,
                                          int width, int height);

#endif
