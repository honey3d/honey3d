#include <stdio.h>
#include <stdarg.h>
#include <lua.h>
#include <lauxlib.h>
#include "util/util.h"
#include "logging.h"

int _honey_log_level = HONEY_WARN;


#define LUA_LOG(level) \
int log_ ## level (lua_State *L) { \
	const char *msg = luaL_checkstring(L, 1); \
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
	struct honey_tbl_t log[] = {
		H_FUNC("fatal", log_fatal),
		H_FUNC("error", log_error),
		H_FUNC("warn", log_warn),
		H_FUNC("info", log_info),
		H_FUNC("debug", log_debug),
		H_FUNC("trace", log_trace),
		H_END
	};
	create_table(L, log);
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
