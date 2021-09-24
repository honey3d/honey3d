#ifndef HONEY_LOGGING_H
#define HONEY_LOGGING_H

#include <stdio.h>


struct honey_log_info_t {
   enum { FATAL, ERROR, WARN, INFO, DEBUG } log_level;
   FILE *debug_out;
   FILE *info_out;
   FILE *warn_out;
   FILE *error_out;
   FILE *fatal_out;
};

extern struct honey_log_info_t honey_log_info;

const char * honey_log_level_str();

void honey_debug(const char *fmt, ...);
void honey_info(const char *fmt, ...);
void honey_warn(const char *fmt, ...);
void honey_error(const char *fmt, ...);
void honey_fatal(const char *fmt, ...);

#endif
