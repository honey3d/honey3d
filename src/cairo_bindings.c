#include "cairo_bindings.h"
#include "texture.h"

int honey_cairo_mt_ref = LUA_NOREF;

int honey_setup_cairo(lua_State* L)
{
    honey_lua_create_table
        (L, 2,
         HONEY_TABLE, "__index", 1,
         HONEY_FUNCTION, "getTexture", honey_cairo_get_texture,

         HONEY_FUNCTION, "__gc", honey_cairo_destroy);
    honey_cairo_mt_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    lua_pushcfunction(L, honey_cairo_new);
    lua_setfield(L, -2, "cairo");
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cairo_new(lua_State* L)
{
    int width, height;
    honey_lua_parse_arguments(L, 1, 2, HONEY_INTEGER, &width, HONEY_INTEGER, &height);

    cairo_surface_t** surface = lua_newuserdata(L, sizeof(cairo_surface_t*));
    *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);

    cairo_status_t status = cairo_surface_status(*surface);
    if (status != CAIRO_STATUS_SUCCESS)
        honey_lua_throw_error
            (L, "libcairo error: %s", cairo_status_to_string(status));

    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_cairo_mt_ref);
    lua_setmetatable(L, -2);

    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cairo_get_texture(lua_State* L)
{
    /* todo
    cairo_surface_t** surface;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &surface);

    unsigned char* data = cairo_image_surface_get_data(*surface);
    honey_texture* texture = lua_newuserdata(L, sizeof(honey_texture));

    glGenTextures(1, &(texture->id));
    glBindTexture(GL_TEXTURE_2D, texture->id);
    */
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cairo_destroy(lua_State* L)
{
    cairo_surface_t** surface;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &surface);

    cairo_surface_destroy(*surface);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
