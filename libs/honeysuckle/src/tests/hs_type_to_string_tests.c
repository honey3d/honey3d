#include "hs_tests.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * tests for hs_type_to_string
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

TEST(hs_bool_to_string)
{
    mu_assert("HS_BOOL does not result in 'boolean'!",
	      strcmp(hs_type_to_string(HS_BOOL), "boolean") == 0);
    return 0;
}

TEST(hs_int_to_string)
{
    mu_assert("HS_INT does not result in 'integer'!",
	      strcmp(hs_type_to_string(HS_INT), "integer") == 0);
    return 0;
}

TEST(hs_num_to_string)
{
    mu_assert("HS_NUM does not result in 'number'!",
	      strcmp(hs_type_to_string(HS_NUM), "number") == 0);
    return 0;
}

TEST(hs_str_to_string)
{
    mu_assert("HS_STR does not result in 'string'!",
	      strcmp(hs_type_to_string(HS_STR), "string") == 0);
    return 0;
}

TEST(hs_tbl_to_string)
{
    mu_assert("HS_TBL does not result in 'table'!",
	      strcmp(hs_type_to_string(HS_TBL), "table") == 0);
    return 0;
}

TEST(hs_func_to_string)
{
    mu_assert("HS_FUNC does not result in 'function'!",
	      strcmp(hs_type_to_string(HS_FUNC), "function") == 0);
    return 0;
}

TEST(hs_cfunc_to_string)
{
    mu_assert("HS_CFUNC does not result in 'C function'!",
	      strcmp(hs_type_to_string(HS_CFUNC), "C function") == 0);
    return 0;
}

TEST(hs_user_to_string)
{
    mu_assert("HS_USER does not result in 'userdata'!",
	      strcmp(hs_type_to_string(HS_USER), "userdata") == 0);
    return 0;
}

TEST(hs_light_to_string)
{
    mu_assert("HS_LIGHT does not result in 'light userdata'!",
	      strcmp(hs_type_to_string(HS_LIGHT), "light userdata") == 0);
    return 0;
}

TEST(hs_nil_to_string)
{
    mu_assert("HS_NIL does not result in 'nil'!",
	      strcmp(hs_type_to_string(HS_NIL), "nil") == 0);
    return 0;
}

TEST(hs_any_to_string)
{
    mu_assert("HS_ANY does not result in 'any'!",
	      strcmp(hs_type_to_string(HS_ANY), "any") == 0);
    return 0;
}


void hs_type_to_string_tests()
{
    printf("running hs_type_to_string() tests...\n");
    mu_run_test("bool to string", hs_bool_to_string);
    mu_run_test("int to string", hs_int_to_string);
    mu_run_test("num to string", hs_num_to_string);
    mu_run_test("str to string", hs_str_to_string);
    mu_run_test("tbl to string", hs_tbl_to_string);
    mu_run_test("func to string", hs_func_to_string);
    mu_run_test("cfunc to string", hs_cfunc_to_string);
    mu_run_test("user to string", hs_user_to_string);
    mu_run_test("light to string", hs_light_to_string);
    mu_run_test("nil to string", hs_nil_to_string);
    mu_run_test("any to string", hs_any_to_string);
}
