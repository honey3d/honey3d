#include "hs_tests.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * RUN TESTS
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int tests_run = 0;
int tests_run_old = 0;
int tests_failed = 0;

int main()
{
    printf("================ start tests ================\n\n");

    mu_run_suite(hs_type_to_string_tests);
    mu_run_suite(hs_parse_args_tests);
    mu_run_suite(hs_parse_overloaded_tests);
    mu_run_suite(hs_create_table_tests);
    //mu_run_suite(hs_create_enum_tests);
    mu_run_suite(hs_process_table_tests);
    mu_run_suite(hs_throw_error_tests);
    
    mu_run_suite(hs_pushstring_tests);
		
    printf("\n=============== tests finished ===============\n\n");

    const char *color = tests_failed == 0 ? GREEN : RED;
    printf("%sran %d tests, %d failed\n" RESET, color, tests_run, tests_failed);
    return tests_failed;
}
