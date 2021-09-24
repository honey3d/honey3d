#ifndef HONEY_TESTS_SUITES
#define HONEY_TESTS_SUITES

#include "minunit.h"

void honey_logging_tests();

#define RUN_TESTS				\
   mu_run_suite(honey_logging_tests);

#endif
