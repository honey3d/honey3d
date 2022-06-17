#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "test/honey-test.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * include C file and declare mocks
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define vfprintf(file, fmt, vl) mock_vfprintf(file, fmt, vl)
void mock_vfprintf(FILE*, const char*, va_list vl);
#include "logging.c"
#undef vfprintf


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * define mock functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

MOCK(mock_vfprintf)(FILE *file, const char *fmt, va_list vl)
{
	/* to avoid basically just re-implementing printf parsing here,
	   i am limiting this function to be able to receive strings only */
	
	/* count format specifiers */
	char *ptr = strchr(fmt, '%');
	int n_args = 0;
	while (ptr != NULL) {
		n_args += 1;
		ptr = strchr(ptr+1, '%');
	}

	/* store arguments */
	struct lily_mock_arg_t args[] = {
		{ sizeof(FILE*), &file },
		{ sizeof(const char*), &fmt },
		{ sizeof(int), &n_args },
	};
	lily_mock_call(mock_vfprintf_data, args);

	/* store format arguments */
	lily_queue_t *queue = mock_vfprintf_data->values;
	for (int i=0; i<n_args; i++) {
		char *str = va_arg(vl, char*);
		lily_enqueue(queue, char*, str);
	}
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * declare tests and define suite
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void clean_mock(lily_mock_t **m)
{
	if (*m != NULL) {
		lily_mock_destroy(*m);
		*m = NULL;
	}
}

void level_fatal_log_fatal_succeeds();
void level_neg_log_fatal_fails();

void suite_logging()
{
	lily_run_test(level_neg_log_fatal_fails);
	lily_run_test(level_fatal_log_fatal_succeeds);

	CLEAN_MOCK(mock_vfprintf);
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * define tests
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void level_fatal_log_fatal_succeeds()
{
	USE_MOCK(mock_vfprintf);

	honey_set_log_level(HONEY_FATAL);
	honey_fatal("some message");
	lily_assert_int_equal(mock_vfprintf_data->n_calls, 1);

	FILE *file; const char *fmt; int n_strings;
	struct lily_mock_arg_t args[] = {
		{ sizeof(FILE*), &file },
		{ sizeof(const char*), &fmt },
		{ sizeof(int), &n_strings },
	};
	lily_get_call(mock_vfprintf_data, args, 0);

	lily_assert_ptr_equal(file, stderr);
	lily_assert_string_equal((char*) fmt, "[FATAL] some message");
	lily_assert_int_equal(n_strings, 0);
}


void level_neg_log_fatal_fails()
{
	USE_MOCK(mock_vfprintf);

	honey_set_log_level(-1);
	honey_fatal("some message");
	lily_assert_int_equal(mock_vfprintf_data->n_calls, 0);
}
