#ifndef HONEY_TEST_H
#define HONEY_TEST_H

#include "lily-test.h"

void suite_logging();

#define RUN_TESTS() \
	lily_run_suite(suite_logging);

#endif
