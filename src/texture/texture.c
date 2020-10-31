#include "texture.h"

static int honey_lua_texture_new(lua_State* L)
{
    honey_texture* texture = lua_newuserdata(L, sizeof(honey_texture));
    return 1;
}

static int honey_lua_texture_load(lua_State* L)
{
    honey_texture* texture;
    char* texture_path;
    bool use_alpha;
    honey_lua_parse_arguments(L, 3,
                              HONEY_USERDATA, &texture,
                              HONEY_STRING, &texture_path,
                              HONEY_BOOLEAN, &use_alpha);
    enum honey_texture_result result = honey_texture_load(texture, texture_path, use_alpha);
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

void honey_setup_texture(lua_State* L)
{
    honey_lua_element texture_elements[] = {
        { "new", HONEY_FUNCTION, { .function = honey_lua_texture_new } },
        { "load", HONEY_FUNCTION, { .function = honey_lua_texture_load } },
        { "use", HONEY_FUNCTION, { .function = honey_lua_texture_use } },
    };

    honey_lua_create_table(L, texture_elements, 3);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

enum honey_texture_result honey_texture_load(honey_texture* texture,
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
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

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_texture_use(honey_texture texture, int texture_unit) {
  glActiveTexture(GL_TEXTURE0 + texture_unit);
  glBindTexture(GL_TEXTURE_2D, texture.texture_id);
}
