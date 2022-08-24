#include <stdio.h>
#include <stdarg.h>
#include <lua.h>
#include <honeysuckle.h>
#include "logging/logging.h"

int _honey_log_level = HONEY_WARN;


#define LUA_LOG(level) \
int log_ ## level (lua_State *L) { \
	char *msg; \
	hs_parse_args(L, hs_str(msg)); \
	honey_log_ ## level ("%s\n", msg); \
	return 0; \
}


LUA_LOG(fatal);
LUA_LOG(error);
LUA_LOG(warn);
LUA_LOG(info);
LUA_LOG(debug);
LUA_LOG(trace);


void setup_logging(lua_State *L, int honey_tbl)
{
	hs_create_table(L,
		hs_str_cfunc("fatal", log_fatal),
		hs_str_cfunc("error", log_error),
		hs_str_cfunc("warn", log_warn),
		hs_str_cfunc("info", log_info),
		hs_str_cfunc("debug", log_debug),
		hs_str_cfunc("trace", log_trace),
	);

	lua_setfield(L, honey_tbl, "log");
}


void honey_set_log_level(int level)
{
	_honey_log_level = level;
}


void honey_log(int level, const char *fmt, ...) {
  
	if (level > _honey_log_level) return;
	
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
}
