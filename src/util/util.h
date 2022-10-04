#ifndef HONEY_UTIL_H
#define HONEY_UTIL_H

#include <lua.h>

void setup_util(lua_State *L, int honey_tbl);
void append_table(lua_State *L, int tbl_a, int tbl_b);

#endif
