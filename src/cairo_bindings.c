#include "cairo_bindings.h"
#include "texture.h"

int honey_cairo_mt_ref = LUA_NOREF;

static const cairo_user_data_key_t TEXTURE_KEY;

int honey_setup_cairo(lua_State* L)
{
    honey_lua_create_table
        (L, 2,
         HONEY_TABLE, "__index", 8,
         HONEY_FUNCTION, "getTexture", honey_cairo_get_texture,
         HONEY_FUNCTION, "updateTexture", honey_cairo_update_texture,
         HONEY_FUNCTION, "moveTo", honey_cairo_move_to,
         HONEY_FUNCTION, "lineTo", honey_cairo_line_to,
	 HONEY_FUNCTION, "arc", honey_cairo_arc,
         HONEY_FUNCTION, "stroke", honey_cairo_stroke,
         HONEY_FUNCTION, "setColor", honey_cairo_set_color,
	 HONEY_FUNCTION, "setLineWidth", honey_cairo_set_line_width,

         HONEY_FUNCTION, "__gc", honey_cairo_destroy);
    honey_cairo_mt_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    lua_pushcfunction(L, honey_cairo_new);
    lua_setfield(L, -2, "cairo");
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

struct texture_ref {
    int ref;
    lua_State* L;
};

static void destroy_texture_ref(void* data)
{
    struct texture_ref* ref = data;
    luaL_unref(ref->L, LUA_REGISTRYINDEX, ref->ref);
    free(ref);
}

int honey_cairo_new(lua_State* L)
{
    int choice = honey_lua_parse_arguments(L, 2, 0, 1, HONEY_TABLE, NULL);

    lua_pushcfunction(L, honey_lua_texture_new);
    if (choice == 0)
        honey_lua_pcall(L, 0, 1);
    else {
        lua_pushvalue(L, 1);
        honey_lua_pcall(L, 1, 1);
    }

    /* configure texture swizzling ARGB -> RGBA */
    honey_texture* texture = lua_touserdata(L, -1);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_BLUE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_RED);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_RED);

    /* setup texture reference */
    struct texture_ref* ref = malloc(sizeof(struct texture_ref));
    if (ref == NULL)
        honey_lua_throw_error
            (L, "failed to allocate memory for texture handle!");
    
    ref->ref = luaL_ref(L, LUA_REGISTRYINDEX);
    ref->L = L;

    /* create cairo surface */
    cairo_surface_t* surface =
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                   texture->params.width,
                                   texture->params.height);
    
    cairo_status_t status = cairo_surface_status(surface);
    if (status != CAIRO_STATUS_SUCCESS)
        honey_lua_throw_error
            (L, "error creating cairo surface: %s", cairo_status_to_string(status));

    /* create cairo context */
    cairo_t** cr = lua_newuserdata(L, sizeof(cairo_t*));
    *cr = cairo_create(surface);
    status = cairo_status(*cr);
    if (status != CAIRO_STATUS_SUCCESS)
        honey_lua_throw_error
            (L, "error creating cairo context: %s", cairo_status_to_string(status));

    cairo_surface_destroy(surface);

    /* bind texture ref to context userdata */
    status = cairo_set_user_data(*cr,
                                 &TEXTURE_KEY,
                                 ref,
                                 destroy_texture_ref);
    if (status != CAIRO_STATUS_SUCCESS)
        honey_lua_throw_error
            (L, "error binding cairo texture: %s", cairo_status_to_string(status));

    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_cairo_mt_ref);
    lua_setmetatable(L, -2);

    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cairo_update_texture(lua_State* L)
{
    cairo_t** cr;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &cr);

    struct texture_ref *ref = cairo_get_user_data(*cr, &TEXTURE_KEY);
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref->ref);
    honey_texture* texture = lua_touserdata(L, -1);
    lua_pop(L, 1);

    cairo_surface_t* surface = cairo_get_target(*cr);

    glBindTexture(GL_TEXTURE_2D, texture->id);
    unsigned char* image_data = cairo_image_surface_get_data(surface);
    glTexSubImage2D(GL_TEXTURE_2D,
                    0, 0, 0,
                    texture->params.width,
                    texture->params.height,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    image_data);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cairo_get_texture(lua_State* L)
{
    cairo_t** cr;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &cr);

    struct texture_ref *ref = cairo_get_user_data(*cr, &TEXTURE_KEY);
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref->ref);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cairo_destroy(lua_State* L)
{
    cairo_t** cr;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &cr);

    struct texture_ref* ref = cairo_get_user_data(*cr, &TEXTURE_KEY);

    cairo_destroy(*cr);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Drawing functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int honey_cairo_move_to(lua_State* L)
{
    cairo_t** cr;
    float x, y;
    honey_lua_parse_arguments
        (L, 1, 3, HONEY_USERDATA, &cr, HONEY_NUMBER, &x, HONEY_NUMBER, &y);

    cairo_move_to(*cr, x, y);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cairo_line_to(lua_State* L)
{
    cairo_t** cr;
    float x, y;
    honey_lua_parse_arguments
        (L, 1, 3, HONEY_USERDATA, &cr, HONEY_NUMBER, &x, HONEY_NUMBER, &y);

    cairo_line_to(*cr, x, y);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cairo_arc(lua_State* L)
{
    cairo_t** cr;
    float cx, cy, radius, angle1, angle2;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 4,
	 HONEY_USERDATA, &cr,
	 HONEY_NUMBER, &cx, HONEY_NUMBER, &cy, HONEY_NUMBER, &radius,
	 6,
	 HONEY_USERDATA, &cr,
	 HONEY_NUMBER, &cx, HONEY_NUMBER, &cy, HONEY_NUMBER, &radius,
	 HONEY_NUMBER, &angle1, HONEY_NUMBER, &angle2);

    if (choice == 0) {
	angle1 = 0;
	angle2 = 6.2831;
    }

    cairo_arc(*cr, cx, cy, radius, angle1, angle2);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cairo_stroke(lua_State* L)
{
    cairo_t** cr;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &cr);

    cairo_stroke(*cr);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cairo_set_color(lua_State* L)
{
    cairo_t** cr;
    float r, g, b, a;
    int choice = honey_lua_parse_arguments
        (L, 2,
         4,
         HONEY_USERDATA, &cr,
         HONEY_NUMBER, &r, HONEY_NUMBER, &g, HONEY_NUMBER, &b,
         5,
         HONEY_USERDATA, &cr,
         HONEY_NUMBER, &r, HONEY_NUMBER, &g, HONEY_NUMBER, &b, HONEY_NUMBER, &a);

    if (choice == 0)
        cairo_set_source_rgb(*cr, r, g, b);
    else
        cairo_set_source_rgba(*cr, r, g, b, a);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_cairo_set_line_width(lua_State* L)
{
    cairo_t** cr;
    float width;
    honey_lua_parse_arguments(L, 1, 2, HONEY_USERDATA, &cr, HONEY_NUMBER, &width);

    cairo_set_line_width(*cr, width);
    return 0;
}
			      
