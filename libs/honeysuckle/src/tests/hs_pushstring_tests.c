#include "hs_tests.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * tests for hs_pushstring
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

TEST(push_noformat)
{
    hs_pushstring(L, "a string");
    mu_assert("no string at top of stack!", lua_isstring(L, -1));
    const char *string = lua_tostring(L, -1);
    mu_assert("string != 'a string'", strcmp(string, "a string") == 0);
    return 0;
}

TEST(push_formatint)
{
    hs_pushstring(L, "%d is 5", 5);
    mu_assert("no string at top of stack!", lua_isstring(L, -1));
    const char *string = lua_tostring(L, -1);
    mu_assert("string != '5 is 5'", strcmp(string, "5 is 5") == 0);
    return 0;
}

TEST(push_formatstring)
{
    hs_pushstring(L, "%s is 'hello'", "hello");
    mu_assert("no string at top of stack!", lua_isstring(L, -1));
    const char *string = lua_tostring(L, -1);
    mu_assert("string != 'hello is 'hello''",
	      strcmp(string, "hello is 'hello'") == 0);
    return 0;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * test suite
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void hs_pushstring_tests()
{
    printf("running hs_pushstring() tests...\n");
    mu_run_test("hs_pushstring (no printf formatting)", push_noformat);
    mu_run_test("hs_pushstring (integer formatting)", push_formatint);
    mu_run_test("hs_pushstring (string formatting)", push_formatstring);
}
