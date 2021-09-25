#ifndef HONEY_LOGGING_H
#define HONEY_LOGGING_H

#include <stdio.h>

enum honey_log_level_t
   { FATAL, ERROR, WARN, INFO, DEBUG };

struct honey_log_info_t {
   enum honey_log_level_t log_level;
   FILE *log_file;
};

extern struct honey_log_info_t honey_log_info;

const char * honey_log_level_str();


void honey_log_set_level(enum honey_log_level_t level);
enum honey_log_level_t honey_log_get_level();

void honey_log_set_file(FILE *file);
FILE * honey_log_get_file();

void honey_log(enum honey_log_level_t required_level,
	       const char *prefix,
	       const char *fmt, ...);

#define honey_debug(...) honey_log(DEBUG, "[DEBUG]", __VA_ARGS__)
#define honey_info(...)  honey_log(INFO, "[INFO]", __VA_ARGS__)

#endif
