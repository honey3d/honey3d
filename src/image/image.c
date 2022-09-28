#include <lua.h>
#include <honeysuckle.h>
#include <cairo/cairo.h>
/* assimp provides its own stb_image implementation */
/*#define STB_IMAGE_IMPLEMENTATION*/
#include "stb_image.h"
#include "image.h"


int load_image(lua_State *L);
int free_image(lua_State *L);

int surface_create(lua_State *L);
int surface_destroy(lua_State *L);
int surface_get_data(lua_State *L);
int context_create(lua_State *L);
int context_destroy(lua_State *L);
int context_select_font_face(lua_State *L);
int context_set_font_size(lua_State *L);
int context_show_text(lua_State *L);
int context_set_source_rgb(lua_State *L);
int context_move_to(lua_State *L);


void setup_image(lua_State *L, int honey_index)
{
	hs_create_table(L,
		/* basic images */
		hs_str_cfunc("load", load_image),
		hs_str_cfunc("destroy", free_image),

		/* cairo bindings */
		hs_str_cfunc("surface_create", surface_create),
		hs_str_cfunc("surface_destroy", surface_destroy),
		hs_str_cfunc("surface_get_data", surface_get_data),
		hs_str_cfunc("context_create", context_create),
		hs_str_cfunc("context_destroy", context_destroy),
		hs_str_cfunc("context_select_font_face", context_select_font_face),
		hs_str_cfunc("context_set_font_size", context_set_font_size),
		hs_str_cfunc("context_show_text", context_show_text),
		hs_str_cfunc("context_set_source_rgb", context_set_source_rgb),
		hs_str_cfunc("context_move_to", context_move_to),

		/* format enum */
		hs_str_int("FORMAT_ARGB32", CAIRO_FORMAT_ARGB32),


		/* font enums */
		hs_str_int("FONT_SLANT_NORMAL", CAIRO_FONT_SLANT_NORMAL),
		hs_str_int("FONT_WEIGHT_NORMAL", CAIRO_FONT_WEIGHT_NORMAL),
	);

	lua_setfield(L, honey_index, "image");
}


/* --===== basic images =====-- */

int load_image(lua_State *L)
{
	char *filename;
	lua_Integer requested_channels;
	hs_parse_args(L, hs_str(filename), hs_int(requested_channels));

	int width, height, channels;
	unsigned char *data = stbi_load(filename, &width, &height, &channels, requested_channels);

	if (data == NULL) hs_throw_error(L, "failed to load image '%s'", filename);
	
	lua_pushlightuserdata(L, data);
	lua_pushinteger(L, width);
	lua_pushinteger(L, height);
	lua_pushinteger(L, channels);
	return 4;
}


int free_image(lua_State *L)
{
	void *data;
	hs_parse_args(L, hs_light(data));
	stbi_image_free(data);
	return 0;
}


/* --===== cairo bindings =====-- */

int surface_create(lua_State *L)
{
	lua_Integer format, width, height;
	hs_parse_args(L, hs_int(format), hs_int(width), hs_int(height));

	cairo_surface_t *surface = cairo_image_surface_create(format, width, height);
	cairo_status_t status = cairo_surface_status(surface);
	if (status != CAIRO_STATUS_SUCCESS)
		hs_throw_error(L, "error creating cairo surface: %s", cairo_status_to_string(status));
	
	lua_pushlightuserdata(L, surface);
	return 1;
}


int surface_destroy(lua_State *L)
{
	void *surface_ptr;
	hs_parse_args(L, hs_light(surface_ptr));
	cairo_surface_t *surface = surface_ptr;

	cairo_surface_destroy(surface);
	return 0;
}


int surface_get_data(lua_State *L)
{
	void *surface_ptr;
	hs_parse_args(L, hs_light(surface_ptr));
	cairo_surface_t *surface = surface_ptr;

	unsigned char *data = cairo_image_surface_get_data(surface);
	lua_pushlightuserdata(L, data);
	return 1;
}


int context_create(lua_State *L)
{
	void *surface_ptr;
	hs_parse_args(L, hs_light(surface_ptr));
	cairo_surface_t *surface = surface_ptr;

	cairo_t *cr = cairo_create(surface);
	cairo_status_t status = cairo_status(cr);
	if (status != CAIRO_STATUS_SUCCESS)
		hs_throw_error(L, "error creating cairo context: %s", cairo_status_to_string(status));
	
	lua_pushlightuserdata(L, cr);
	return 1;
}


int context_destroy(lua_State *L)
{
	void *cr_ptr;
	hs_parse_args(L, hs_light(cr_ptr));
	cairo_t *cr = cr_ptr;

	cairo_destroy(cr);
	return 0;
}


int context_select_font_face(lua_State *L)
{
	void *cr_ptr;
	char *family;
	lua_Integer slant, weight;
	hs_parse_args(L, hs_light(cr_ptr), hs_str(family), hs_int(slant), hs_int(weight));
	cairo_t *cr = cr_ptr;

	cairo_select_font_face(cr, family, slant, weight);
	return 0;
}


int context_set_font_size(lua_State *L)
{
	void *cr_ptr;
	lua_Number size;
	hs_parse_args(L, hs_light(cr_ptr), hs_num(size));
	cairo_t *cr = cr_ptr;

	cairo_set_font_size(cr, size);
	return 0;
}


int context_show_text(lua_State *L)
{
	void *cr_ptr;
	char *str;
	hs_parse_args(L, hs_light(cr_ptr), hs_str(str));
	cairo_t *cr = cr_ptr;

	cairo_show_text(cr, str);
	return 0;
}


int context_set_source_rgb(lua_State *L)
{
	void *cr_ptr;
	lua_Number r, g, b;
	hs_parse_args(L, hs_light(cr_ptr), hs_num(r), hs_num(g), hs_num(b));
	cairo_t *cr = cr_ptr;

	cairo_set_source_rgb(cr, r, g, b);
	return 0;
}


int context_move_to(lua_State *L)
{
	void *cr_ptr;
	lua_Number x, y;
	hs_parse_args(L, hs_light(cr_ptr), hs_num(x), hs_num(y));
	cairo_t *cr = cr_ptr;

	cairo_move_to(cr, x, y);
	return 0;
}
