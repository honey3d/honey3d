#include <stdio.h>
#include <stdarg.h>

#include "logging/logging.h"


struct honey_log_info_t honey_log_info;


const char * honey_log_level_str()
{
   switch(honey_log_info.log_level) {
   case DEBUG:
      return "DEBUG";
      break;

   case INFO:
      return "INFO";
      break;

   case WARN:
      return "WARN";
      break;

   case ERROR:
      return "ERROR";
      break;

   case FATAL:
      return "FATAL";
      break;

   default:
      return NULL;
      break;
   }
}


void honey_debug(const char *fmt, ...)
{
   if (honey_log_info.log_level >= DEBUG) {
      va_list args;
      va_start(args, fmt);
      fprintf(honey_log_info.debug_out, "[DEBUG] ");
      vfprintf(honey_log_info.debug_out, fmt, args);
      va_end(args);
   }
}
