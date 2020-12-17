#ifndef HONEY_TEXTURE_H
#define HONEY_TEXTURE_H

/** @file texture.h
 *
 *@brief Defines the honey_texture struct and associated functions. 
*/

#include "common.h"

#define HONEY_TEXTURE_DEFAULT_WIDTH 1024
#define HONEY_TEXTURE_DEFAULT_HEIGHT 1024
#define HONEY_TEXTURE_DEFAULT_CHANNELS 4
#define HONEY_TEXTURE_DEFAULT_TYPE HONEY_TEXTURE_TYPE_RGBA
#define HONEY_TEXTURE_DEFAULT_MIPMAPS false
#define HONEY_TEXTURE_DEFAULT_MIN_FILTER GL_LINEAR
#define HONEY_TEXTURE_DEFAULT_MAG_FILTER GL_LINEAR
#define HONEY_TEXTURE_DEFAULT_WRAP_S GL_REPEAT
#define HONEY_TEXTURE_DEFAULT_WRAP_T GL_REPEAT
#define HONEY_TEXTURE_DEFAULT_WRAP_R GL_REPEAT

#define HONEY_TEXTURE_TYPE_GREY GL_RED
#define HONEY_TEXTURE_TYPE_RGB GL_RGB
#define HONEY_TEXTURE_TYPE_RGBA GL_RGBA
#define HONEY_TEXTURE_TYPE_DEPTH GL_DEPTH_COMPONENT


extern int honey_texture_mt_ref;

enum honey_texture_result {
  TEXTURE_OK,
  TEXTURE_FAILED,
  TEXTURE_CHANNEL_ERROR,
  N_TEXTURE_RESULTS };

typedef struct {
    int width;
    int height;
    int channels;
    int type;
    bool mipmaps;
    int min_filter;
    int mag_filter;
    int wrap_s;
    int wrap_t;
    int wrap_r;
} honey_texture_params;

typedef struct {
    unsigned int id;
    honey_texture_params params;
} honey_texture;

/** @brief Place the honey.texture bindings as a table on the stack. */
void honey_setup_texture(lua_State* L);

int honey_lua_texture_new(lua_State* L);

/** @brief Generate a texture.
 *
 * @param[out] texture Pointer to the destination texture.
 * @param[in] data The data to populate the texture with, or NULL to leave it unpopulated.
 *
 * @returns Nothing.
 */
void honey_texture_generate(honey_texture* texture,
                            void* data);

/** @brief Set the parameters of a texture.
 *
 * This function takes the parameters given in a texture's `params` field
 * and applies them to it's OpenGL object. `honey_texture_generate` must be called
 * before using this function.
 *
 * @param[inout] texture The texture to configure.
 */
void honey_texture_configure(honey_texture* texture);

/** @brief Update the mipmaps of a texture.
 *
 * If a texture has params.mipmaps set to false, this function does nothing.
 *
 * @param[inout] texture The texture to generate new mipmaps for.
 *
 * @returns Nothing.
 */
void honey_texture_update_mipmaps(honey_texture* texture);

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
