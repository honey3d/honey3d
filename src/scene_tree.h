#include "common.h"

/* @file Defines the basic scene tree nodes and functions to manipulate them. */

extern int honey_node_mt_ref;

void honey_setup_scene_tree(lua_State* L);

int honey_node_new(lua_State* L);

int honey_node_update_transform(lua_State* L);

int honey_node_update_cascade(lua_State* L);

int honey_node_draw_cascade(lua_State* L);

int honey_node_translate(lua_State* L);

int honey_node_rotate(lua_State* L);

int honey_node_scale(lua_State* L);


