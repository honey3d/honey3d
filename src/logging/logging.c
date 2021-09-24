#include <stdio.h>

#include "logging/logging.h"


const char * honey_log_level_str_(struct honey_log_info *info)
{
   switch(info->log_level) {
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
