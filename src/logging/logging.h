#ifndef HONEY_LOGGING_H
#define HONEY_LOGGING_H

struct honey_log_info {
   enum { DEBUG, INFO, WARN, ERROR, FATAL } log_level;
};

const char * honey_log_level_str_(struct honey_log_info *info);

#endif
