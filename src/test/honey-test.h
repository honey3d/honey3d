#ifndef HONEY_TEST_H
#define HONEY_TEST_H

#include "lily-test.h"

#define MOCK(name) \
	lily_mock_t * name ## _data = NULL; \
	void name

#define mock_enqueue(name, type, data) \
	lily_enqueue(name ## _data->values, type, data)

#define mock_dequeue(name, type, data) \
	lily_dequeue(name ## _data->values, type, data)

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
void suite_gl();
void suite_window();
void suite_util();

#define RUN_TESTS() \
	lily_run_suite(suite_logging); \
	lily_run_suite(suite_gl); \
	lily_run_suite(suite_window); \
	lily_run_suite(suite_util); \

#endif
