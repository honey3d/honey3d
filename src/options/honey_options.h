#ifndef HONEY_OPTIONS_H
#define HONEY_OPTIONS_H

#include "logging/logging.h"

struct honey_options {
   const char *main_script;
   enum honey_log_level_t log_level;
   int display_help;
};

int parse_options(struct honey_options *opts, int argc, char **argv);

#endif
