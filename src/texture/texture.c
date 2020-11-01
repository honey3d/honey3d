#include "texture.h"

static int honey_lua_texture_new(lua_State* L)
{
    honey_texture* texture = lua_newuserdata(L, sizeof(honey_texture));
    return 1;
}

static int honey_lua_texture_create(lua_State* L)
{
    honey_texture* texture;
    int width, height;
    char* type;
    honey_lua_parse_arguments(L, 4,
                              HONEY_USERDATA, &texture,
                              HONEY_STRING, &type,
                              HONEY_INTEGER, &width,
                              HONEY_INTEGER, &height);

    if (strcmp(type, "greyscale") == 0)
        honey_texture_new_greyscale(texture, width, height, NULL);
    else if (strcmp(type, "rgb") == 0)
        honey_texture_new_rgb(texture, width, height, NULL);
    else if (strcmp(type, "rgba") == 0)
        honey_texture_new_rgba(texture, width, height, NULL);
    else if (strcmp(type, "depth") == 0)
        honey_texture_new_depth(texture, width, height, NULL);
    else {
        char* error;
        honey_format_string(&error,
                            "unknown texture type '%s'",
                            type);
        lua_pushstring(L, error);
        free(error);
        lua_error(L);
    }
    return 0;
}

static int honey_lua_texture_load(lua_State* L)
{
    honey_texture* texture;
    char* texture_path;
    honey_lua_parse_arguments(L, 3,
                              HONEY_USERDATA, &texture,
                              HONEY_STRING, &texture_path);
    enum honey_texture_result result = honey_texture_load(texture, texture_path);
    if (result != TEXTURE_OK) {
        char* error;
        honey_format_string(&error,
                            "failed to load '%s'",
                            texture_path);
        lua_pushstring(L, error);
        free(error);
        lua_error(L);
    }

    return 0;
}

static int honey_lua_texture_use(lua_State* L)
{
    honey_texture* texture;
    int texture_unit;
    honey_lua_parse_arguments(L, 2,
                              HONEY_USERDATA, &texture,
                              HONEY_INTEGER, &texture_unit);
    honey_texture_use(*texture, texture_unit);
    return 0;
}

static int honey_lua_framebuffer_new(lua_State* L)
{
    honey_texture* draw, *depth;
    if (lua_isuserdata(L, 1))
        draw = lua_touserdata(L, 1);
    else
        draw = NULL;
    
    if (lua_isuserdata(L, 2))
        depth = lua_touserdata(L, 2);
    else
        depth = NULL;

    int width, height;
    honey_lua_parse_arguments(L, 4, HONEY_ANY, HONEY_ANY,
                              HONEY_INTEGER, &width,
                              HONEY_INTEGER, &height);

    unsigned int framebuffer;
    honey_texture_framebuffer_object_new(&framebuffer,
                                         draw, depth,
                                         width, height);
    lua_pushinteger(L, framebuffer);
    return 1;
}

void honey_setup_texture(lua_State* L)
{
    honey_lua_element texture_elements[] = {
        { "new", HONEY_FUNCTION, { .function = honey_lua_texture_new } },
        { "new_framebuffer", HONEY_FUNCTION, { .function = honey_lua_framebuffer_new } },
        { "create", HONEY_FUNCTION, { .function = honey_lua_texture_create } },
        { "load", HONEY_FUNCTION, { .function = honey_lua_texture_load } },
        { "use", HONEY_FUNCTION, { .function = honey_lua_texture_use } },
    };

    honey_lua_create_table(L, texture_elements, 5);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void generate_texture(honey_texture* texture,
                             int width, int height,
                             int format, int type,
                             void* data)
{
    unsigned int texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0,
                 format,
                 width, height, 0,
                 format,
                 type, data);

    texture->id = texture_id;
    texture->width = width;
    texture->height = height;

    switch(format) {
    case GL_RED:
        texture->type = GREY;
        texture->channels = 1;
        break;

    case GL_RGB:
        texture->type = RGB;
        texture->channels = 3;
        break;

    case GL_RGBA:
        texture->type = RGBA;
        texture->channels = 4;
        break;

    case GL_DEPTH_COMPONENT:
        texture->type = DEPTH;
        texture->channels = 1;
        break;

    default:
        break;
    }
    
    return HONEY_OK;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_texture_new_greyscale(honey_texture* texture,
                                 int height, int width,
                                 unsigned char* data)
{
    generate_texture(texture, width, height, GL_RED, GL_UNSIGNED_BYTE, data);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_texture_new_rgb(honey_texture* texture,
                           int height, int width,
                           unsigned char* data)
{
    generate_texture(texture, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_texture_new_rgba(honey_texture* texture,
                            int height, int width,
                            unsigned char* data)
{
    generate_texture(texture, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_texture_new_depth(honey_texture* texture,
                             int height, int width,
                             float* data)
{
    generate_texture(texture, width, height, GL_DEPTH_COMPONENT, GL_FLOAT, data);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

enum honey_texture_result honey_texture_load(honey_texture* texture,
                                             char* texture_path)
{
    int width, height, channels;
    unsigned char* image_data = stbi_load(texture_path, &width, &height, &channels, 0);
    if (image_data == NULL) {
        return TEXTURE_FAILED;
    }

    switch(channels) {
    case 1:
        honey_texture_new_greyscale(texture, width, height, image_data);
        break;

    case 3:
        honey_texture_new_rgb(texture, width, height, image_data);
        break;

    case 4:
        honey_texture_new_rgba(texture, width, height, image_data);
        break;

    default:
        return TEXTURE_CHANNEL_ERROR;
    }

    glGenerateMipmap(GL_TEXTURE_2D);
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
