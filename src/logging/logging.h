#ifndef HONEY_LOGGING_H
#define HONEY_LOGGING_H

#include <stdio.h>


struct honey_log_info {
   enum { FATAL, ERROR, WARN, INFO, DEBUG } log_level;
   FILE *debug_out;
   FILE *info_out;
   FILE *warn_out;
   FILE *error_out;
   FILE *fatal_out;
};

const char * honey_log_level_str_(struct honey_log_info *info);

#define honey_log_(info, required_level, prefix, ...) do {	\
      if (info.log_level >= required_level) {			\
	 fprintf(info.debug_out, prefix " " __VA_ARGS__);	\
      }								\
   } while(0)

#define honey_debug_(info, ...)				\
   honey_log_(info, DEBUG, "[DEBUG]", __VA_ARGS__)
   

#endif
