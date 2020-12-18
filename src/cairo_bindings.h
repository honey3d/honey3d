#ifndef HONEY_CAIRO_H
#define HONEY_CAIRO_H

#include "common.h"

/* @file cairo_bindings.h
 * @brief Define some binding functions for creating and manipulating cairo surfaces,
 * as well as enabling turning them into OpenGL textures.
 */

extern int honey_cairo_mt_ref;

int honey_setup_cairo(lua_State* L);

int honey_cairo_new(lua_State* L);

int honey_cairo_update_texture(lua_State* L);

int honey_cairo_get_texture(lua_State* L);

int honey_cairo_destroy(lua_State* L);

/* drawing functions */

int honey_cairo_move_to(lua_State* L);

int honey_cairo_line_to(lua_State* L);

int honey_cairo_arc(lua_State* L);

int honey_cairo_stroke(lua_State* L);

int honey_cairo_set_color(lua_State* L);

int honey_cairo_set_line_width(lua_State* L);

#endif
