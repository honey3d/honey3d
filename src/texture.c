#include "texture.h"

int honey_texture_mt_ref = LUA_NOREF;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Texture parameter setup function declarations
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

static void setup_default_texture_params(honey_texture_params* params);
static void configure_params(lua_State* L, honey_texture_params* params);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Texture creation & destruction functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

static void setup_texture(lua_State* L, honey_texture** tex, bool use_params)
{
    honey_texture_params params;
    setup_default_texture_params(&params);
    if (use_params)
        configure_params(L, &params);
        
    honey_texture *texture = lua_newuserdata(L, sizeof(honey_texture));
    texture->params = params;
    *tex = texture;
        
    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_texture_mt_ref);
    lua_setmetatable(L, -2);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static int honey_lua_texture_new(lua_State* L)
{
    honey_texture* texture;
    int choice = honey_lua_parse_arguments(L, 2, 0, 1, HONEY_TABLE, NULL);
    setup_texture(L, &texture, choice == 1);

    honey_texture_generate(texture, NULL);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static int honey_lua_texture_load(lua_State* L)
{
    honey_texture* texture;
    char* texture_path;
    int choice = honey_lua_parse_arguments
        (L, 2,
         1, HONEY_STRING, &texture_path,
         2, HONEY_STRING, &texture_path, HONEY_TABLE, NULL);
    setup_texture(L, &texture, choice == 1);
    
    enum honey_texture_result result = honey_texture_load(texture, texture_path);
    if (result != TEXTURE_OK)
        honey_lua_throw_error(L, "failed to load '%s'",
                              texture_path);

    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static int honey_lua_texture_destroy(lua_State* L)
{
    honey_texture* texture;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &texture);
    glDeleteTextures(1, &(texture->id));
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static int honey_lua_texture_use(lua_State* L)
{
    honey_texture* texture;
    int texture_unit;
    honey_lua_parse_arguments(L, 1, 2,
                              HONEY_USERDATA, &texture,
                              HONEY_INTEGER, &texture_unit);
    honey_texture_use(*texture, texture_unit);
    return 0;
}

static int honey_lua_framebuffer_new(lua_State* L)
{
    honey_texture* draw, *depth;
    int width, height;
    honey_lua_parse_arguments(L, 1, 4,
			      HONEY_ANY, NULL,
			      HONEY_ANY, NULL,
                              HONEY_INTEGER, &width,
                              HONEY_INTEGER, &height);

    if (lua_isuserdata(L, 1))
        draw = lua_touserdata(L, 1);
    else
        draw = NULL;
    
    if (lua_isuserdata(L, 2))
        depth = lua_touserdata(L, 2);
    else
        depth = NULL;

    unsigned int framebuffer;
    honey_texture_framebuffer_object_new(&framebuffer,
                                         draw, depth,
                                         width, height);
    lua_pushinteger(L, framebuffer);
    return 1;
}

void honey_setup_texture(lua_State* L)
{
    honey_lua_create_table
        (L, 2,
         HONEY_TABLE, "__index", 1,
         HONEY_FUNCTION, "use", honey_lua_texture_use,

         HONEY_FUNCTION, "__gc", honey_lua_texture_destroy);
    honey_texture_mt_ref = luaL_ref(L, LUA_REGISTRYINDEX);
    
    honey_lua_create_table
        (L, 1,
         HONEY_FUNCTION, "load", honey_lua_texture_load);

    honey_lua_create_table
        (L, 1,
         HONEY_FUNCTION, "__call",  honey_lua_texture_new);
    lua_setmetatable(L, -2);

    lua_setfield(L, -2, "texture");
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Non-lua texture functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void honey_texture_generate(honey_texture* texture,
                            void* data)
{
    honey_texture_params params = texture->params;
    glGenTextures(1, &(texture->id));

    honey_texture_configure(texture);
    
    int type;
    switch(params.type) {
    case HONEY_TEXTURE_TYPE_GREY:
    case HONEY_TEXTURE_TYPE_RGB:
    case HONEY_TEXTURE_TYPE_RGBA:
        type = GL_UNSIGNED_BYTE;
        break;

    case HONEY_TEXTURE_TYPE_DEPTH:
        type = GL_FLOAT;
        break;

    default:
        // should never happen
        break;
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0,
                 params.type,
                 params.width, params.height, 0,
                 params.type,
                 type, data);

    honey_texture_update_mipmaps(texture);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_texture_configure(honey_texture* texture)
{
    honey_texture_params params = texture->params;
    glBindTexture(GL_TEXTURE_2D, texture->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.mag_filter);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, params.wrap_r);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_texture_update_mipmaps(honey_texture* texture)
{
    if (texture->params.mipmaps == false)
        return;

    glBindTexture(GL_TEXTURE_2D, texture->id);
    glGenerateMipmap(GL_TEXTURE_2D);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

enum honey_texture_result honey_texture_load(honey_texture* texture,
                                             char* texture_path)
{
    honey_texture_params *params = &(texture->params);
    int channels;

    unsigned char* image_data = stbi_load(texture_path,
                                          &(params->width),
                                          &(params->height),
                                          &channels, 0);
    if (image_data == NULL) {
        return TEXTURE_FAILED;
    }

    switch(channels) {
    case 1:
        params->type = HONEY_TEXTURE_TYPE_GREY;
        break;

    case 3:
        params->type = HONEY_TEXTURE_TYPE_RGB;
        break;

    case 4:
        params->type = HONEY_TEXTURE_TYPE_RGBA;
        break;

    default:
        return TEXTURE_CHANNEL_ERROR;
    }

    honey_texture_generate(texture, image_data);
    stbi_image_free(image_data);

    return TEXTURE_OK;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_texture_use(honey_texture texture, int texture_unit) {
  glActiveTexture(GL_TEXTURE0 + texture_unit);
  glBindTexture(GL_TEXTURE_2D, texture.id);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_texture_framebuffer_object_new(unsigned int* destination,
                                          honey_texture* draw,
                                          honey_texture* depth,
                                          int width, int height)
{
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glGenFramebuffers(1, destination);
    glBindFramebuffer(GL_FRAMEBUFFER, *destination);

    if (draw != NULL)
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, draw->id, 0);
    else {
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
    }

    if (depth != NULL)
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth->id, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("framebuffer is not complete!\n");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Texture parameter setup function definitions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

static void setup_default_texture_params(honey_texture_params* params)
{
    params->width = HONEY_TEXTURE_DEFAULT_WIDTH;
    params->height = HONEY_TEXTURE_DEFAULT_HEIGHT;
    params->channels = HONEY_TEXTURE_DEFAULT_CHANNELS;
    params->type = HONEY_TEXTURE_DEFAULT_TYPE;
    params->mipmaps = HONEY_TEXTURE_DEFAULT_MIPMAPS;
    params->min_filter = HONEY_TEXTURE_DEFAULT_MIN_FILTER;
    params->mag_filter = HONEY_TEXTURE_DEFAULT_MAG_FILTER;
    params->wrap_s = HONEY_TEXTURE_DEFAULT_WRAP_S;
    params->wrap_t = HONEY_TEXTURE_DEFAULT_WRAP_T;
    params->wrap_r = HONEY_TEXTURE_DEFAULT_WRAP_R;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


static void configure_width(lua_State* L, void* data)
{
    honey_texture_params* params = (honey_texture_params*) data;
    params->width = lua_tointeger(L, -1);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void configure_height(lua_State* L, void* data)
{
    honey_texture_params* params = (honey_texture_params*) data;
    params->height = lua_tointeger(L, -1);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void configure_type(lua_State* L, void* data)
{
    honey_texture_params* params = (honey_texture_params*) data;
    const char* type_string = lua_tostring(L, -1);
    if (strcmp(type_string, "grey") == 0) {
        params->type = HONEY_TEXTURE_TYPE_GREY;
        params->channels = 1;
    }
    else if (strcmp(type_string, "rgb") == 0) {
        params->type = HONEY_TEXTURE_TYPE_RGB;
        params->channels = 3;
    }
    else if (strcmp(type_string, "rgba") == 0) {
        params->type = HONEY_TEXTURE_TYPE_RGBA;
        params->channels = 4;
    }
    else if (strcmp(type_string, "depth") == 0) {
        params->type = HONEY_TEXTURE_TYPE_DEPTH;
        params->channels = 1;
    }
    else {
        honey_lua_throw_error
            (L, "unknown texture type: '%s'", type_string);
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void configure_mipmaps(lua_State* L, void* data)
{
    honey_texture_params* params = (honey_texture_params*) data;
    params->mipmaps = lua_toboolean(L, -1);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void configure_min_filter(lua_State* L, void* data)
{
    honey_texture_params* params = (honey_texture_params*) data;
    const char* str = lua_tostring(L, -1);

    if (strcmp(str, "nearest") == 0)
        params->min_filter = GL_NEAREST;
    else if (strcmp(str, "linear") == 0)
        params->min_filter = GL_LINEAR;
    else if (strcmp(str, "nearest-nearest") == 0)
        params->min_filter = GL_NEAREST_MIPMAP_NEAREST;
    else if (strcmp(str, "linear-nearest") == 0)
        params->min_filter = GL_LINEAR_MIPMAP_NEAREST;
    else if (strcmp(str, "nearest-linear") == 0)
        params->min_filter = GL_NEAREST_MIPMAP_LINEAR;
    else if (strcmp(str, "linear-linear") == 0)
        params->min_filter = GL_LINEAR_MIPMAP_LINEAR;
    else
        honey_lua_throw_error
            (L, "unknown minFilter type: '%s'", str);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void configure_mag_filter(lua_State* L, void* data)
{
    honey_texture_params* params = (honey_texture_params*) data;
    const char* str = lua_tostring(L, -1);

    if (strcmp(str, "nearest") == 0) {
        printf("MAG FILTER NEAREST\n");
        params->mag_filter = GL_NEAREST;
    }
    else if (strcmp(str, "linear") == 0)
        params->mag_filter = GL_LINEAR;
    else
        honey_lua_throw_error
            (L, "unknown magFilter type: '%s'", str);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void configure_wrap(lua_State* L, const char* string, int* wrap)
{
    if (strcmp(string, "clamp") == 0)
        *wrap = GL_CLAMP_TO_EDGE;
    else if (strcmp(string, "clamp-border") == 0)
        *wrap = GL_CLAMP_TO_BORDER;
    else if (strcmp(string, "repeat") == 0)
        *wrap = GL_REPEAT;
    else if (strcmp(string, "repeat-mirror") == 0)
        *wrap = GL_MIRRORED_REPEAT;
    else
        honey_lua_throw_error
            (L, "unknown wrapping type: '%s'", string);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void configure_wrap_s(lua_State* L, void* data)
{
    honey_texture_params* params = (honey_texture_params*) data;
    const char* str = lua_tostring(L, -1);
    configure_wrap(L, str, &(params->wrap_s));
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void configure_wrap_t(lua_State* L, void* data)
{
    honey_texture_params* params = (honey_texture_params*) data;
    const char* str = lua_tostring(L, -1);
    configure_wrap(L, str, &(params->wrap_t));
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void configure_wrap_r(lua_State* L, void* data)
{
    honey_texture_params* params = (honey_texture_params*) data;
    const char* str = lua_tostring(L, -1);
    configure_wrap(L, str, &(params->wrap_r));
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void configure_params(lua_State* L, honey_texture_params* params)
{
    honey_lua_parse_params
        (L, 8, 0,
         HONEY_INTEGER, "width", configure_width, params,
         HONEY_INTEGER, "height", configure_height, params,
         HONEY_STRING, "type", configure_type, params,
         HONEY_BOOLEAN, "mipmaps", configure_mipmaps, params,
         HONEY_STRING, "minFilter", configure_min_filter, params,
         HONEY_STRING, "magFilter", configure_mag_filter, params,
         HONEY_STRING, "sWrap", configure_wrap_s, params,
         HONEY_STRING, "tWrap", configure_wrap_t, params,
         HONEY_STRING, "rWrap", configure_wrap_r, params);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
