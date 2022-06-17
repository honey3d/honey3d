#ifndef HONEY_TEST_H
#define HONEY_TEST_H

#include "lily-test.h"

#define MOCK(name) \
	lily_mock_t * name ## _data = NULL; \
	void name

#define CLEAN_MOCK(name) \
	do { \
		if (name ## _data != NULL) { \
			lily_mock_destroy(name ## _data); \
			name ## _data = NULL; \
		} \
	} while(0)

#define USE_MOCK(name) \
	do { \
		CLEAN_MOCK(name); \
		name ## _data = lily_mock_create(); \
	} while(0)


void suite_logging();

#define RUN_TESTS() \
	lily_run_suite(suite_logging);

#endif
