#ifndef HONEY_LOGGING_H
#define HONEY_LOGGING_H

#include <lua.h>

#define HONEY_FATAL 0
#define HONEY_ERROR 1
#define HONEY_WARN  2
#define HONEY_INFO  3
#define HONEY_DEBUG 4
#define HONEY_TRACE 5

extern int _honey_log_level;

void setup_logging(lua_State *L, int honey_tbl);

void honey_set_log_level(int level);
void honey_log(int level, const char *fmt, ...);

#define honey_log_fatal(...) honey_log(HONEY_FATAL, "[FATAL] "__VA_ARGS__)
#define honey_log_error(...) honey_log(HONEY_ERROR, "[ERROR] "__VA_ARGS__)
#define honey_log_warn(...)  honey_log(HONEY_WARN,  "[WARN] " __VA_ARGS__)
#define honey_log_info(...)  honey_log(HONEY_INFO,  "[INFO] " __VA_ARGS__)
#define honey_log_debug(...) honey_log(HONEY_DEBUG, "[DEBUG] "__VA_ARGS__)
#define honey_log_trace(...) honey_log(HONEY_TRACE, "[TRACE] "__VA_ARGS__)

#endif
