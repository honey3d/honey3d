#ifndef HONEY_TESTS_SUITES
#define HONEY_TESTS_SUITES

#include "minunit.h"

void mock_queue_tests();
void honey_logging_tests();
void honey_gl_tests();

#define RUN_TESTS				\
   mu_run_suite(honey_logging_tests);		\
   mu_run_suite(mock_queue_tests);		\
   mu_run_suite(honey_gl_tests);

#endif
