#include <stdio.h>
#include <stdarg.h>
#include <lua.h>
#include "logging/logging.h"

int _honey_log_level = HONEY_WARN;

void honey_set_log_level(int level)
{
	_honey_log_level = level;
}

int log_fatal(lua_State *L)
{
    //validate arguments
    int count = lua_gettop(L);
    if (count == 0) {
        hs_throw_error(L, "no arguments provided");
    }
    if (!lua_isstring(L, 1)) {
        hs_throw_error(L, "first argument must be a string");
    }
    lua_getglobal(L, "string");
    if (lua_isnil(L, -1)) hs_throw_error(L, "'string' table is nil!");
    lua_getfield(L, -1, "format"); //pushed string.format (function) to the lua stack
    for (int i = 1; i <= count; i++) {
        lua_pushvalue(L, i);
    }
    lua_call(L, count, 1);
    const char *str = lua_tostring(L, -1); //getting result into a string
    honey_log(HONEY_FATAL, "[FATAL] %s\n", str);
    lua_pop(L, 2); //cleaned up stack
    return 0;
}

void honey_log(int level, const char *fmt, ...) {
  
	if (level > _honey_log_level) return;
	
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
}

  
