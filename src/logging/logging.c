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


void honey_log_set_level(enum honey_log_level_t level)
{
   honey_log_info.log_level = level;
}


enum honey_log_level_t honey_log_get_level()
{
   return honey_log_info.log_level;
}


void honey_log_set_file(FILE* file)
{
   honey_log_info.log_file = file;
}


FILE * honey_log_get_file()
{
   return honey_log_info.log_file;
}


void honey_log(enum honey_log_level_t required_level,
	       const char *prefix,
	       const char *fmt, ...)
{
   if (honey_log_info.log_file == NULL)
      return;
   
   if (honey_log_info.log_level >= required_level) {
      va_list args;
      va_start(args, fmt);
      fprintf(honey_log_info.log_file, prefix);
      vfprintf(honey_log_info.log_file, fmt, args);
      va_end(args);
   }
}
