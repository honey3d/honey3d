#ifndef HONEY_LOGGING_H
#define HONEY_LOGGING_H

#include <stdio.h>


struct honey_log_info {
   enum { DEBUG, INFO, WARN, ERROR, FATAL } log_level;
   FILE *debug_out;
   FILE *info_out;
   FILE *warn_out;
   FILE *error_out;
   FILE *fatal_out;
};

const char * honey_log_level_str_(struct honey_log_info *info);

#define honey_debug_(info, ...) \
   fprintf(info.debug_out, "[DEBUG] " __VA_ARGS__)
   

#endif
