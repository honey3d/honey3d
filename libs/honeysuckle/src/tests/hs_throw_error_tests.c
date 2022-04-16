#include "hs_tests.h"

char err_string[32] = "";

int set_err_string(lua_State *L)
{
    if (lua_isstring(L, -1))
	strcpy(err_string, lua_tostring(L, -1));
    return 0;
}


#define HS_ERROR_TEST(name, error_body, expectation)		\
    int name ## _errfunc(lua_State *L) error_body;		\
    TEST(name) {						\
	lua_pushcfunction(L, set_err_string);			\
	int pos = lua_gettop(L);				\
	lua_pushcfunction(L, name ## _errfunc);			\
	int result = lua_pcall(L, 0, 0, pos);			\
	mu_assert_equal(result, LUA_ERRRUN);			\
	mu_assert_str_not_equal(err_string, "");		\
	mu_assert_str_equal(err_string, expectation);	\
	return 0;						\
    }    


HS_ERROR_TEST(hs_throw_error_constant, {
	hs_throw_error(L, "a constant error");
	return 0;
    }, "a constant error");


HS_ERROR_TEST(hs_throw_error_format, {
	hs_throw_error(L, "%s number %d", "error", 10);
	return 0;
    }, "error number 10");


HS_ERROR_TEST(hs_throw_error_long, {
	hs_throw_error(L, "%s is a %s is a %s",
		       "a very, very, very long string",
		       "a very, very, very long string",
		       "a very, very, very long string");
	return 0;
    }, "a very, very, very long string is a a very, very, very long string is a a very, very, very long string");


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void hs_throw_error_tests()
{
    printf("running hs_throw_error() tests...\n");

    mu_run_test("throw constant error string", hs_throw_error_constant);
    mu_run_test("throw error with format string", hs_throw_error_format);
    mu_run_test("throw error with very long string", hs_throw_error_long);
}
