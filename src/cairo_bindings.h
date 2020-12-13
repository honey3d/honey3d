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

int honey_cairo_get_texture(lua_State* L);

int honey_cairo_destroy(lua_State* L);

#endif
