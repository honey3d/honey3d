#include <stdio.h>
#include "logging/logging.h"

int _honey_log_level = HONEY_WARN;

void honey_set_log_level(int level)
{
	_honey_log_level = level;
}


void honey_log(int level, const char *fmt, ...) {
	//if (level > _honey_log_level) return;

	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
}
