#ifndef HONEY_UTIL_H
#define HONEY_UTIL_H

#include <lua.h>


struct honey_tbl_t {
	const char *key;
	int type;
	union {
		lua_Integer integer;
		lua_CFunction function;
	} value;
};

#define H_INT(k, v)  { .key=k, .type=LUA_TNUMBER, .value.integer=v }
#define H_ENUM(v)    { .key=#v, .type=LUA_TNUMBER, .value.integer=v }
#define H_FUNC(k, v) { .key=k, .type=LUA_TFUNCTION, .value.function=v }
#define H_END { .key=NULL, .type=LUA_TNIL, .value.integer=0 }


void setup_util(lua_State *L, int honey_tbl);
void create_table(lua_State *L, struct honey_tbl_t *tbl);
void append_table(lua_State *L, int tbl_a, int tbl_b);

#endif
