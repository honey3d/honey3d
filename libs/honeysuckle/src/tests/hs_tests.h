#pragma once

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "../honeysuckle.h"
#include "colors.h"

#define STR_IMPL(x) #x
#define STR(x) STR_IMPL(x)

#define mu_indent "   "

/* minunit testing macros modified from those at
   www.jera.com/techinfo/jtns/jtn002.html */
#define mu_assert(message, test) do {					\
	if (!(test)) return message					\
			 "\n" mu_indent MAGENTA " [" __FILE__ ":" STR(__LINE__) "]" RESET; \
    } while (0)
#define mu_assert_equal(a, b) mu_assert("'" #a "' is not equal to '" #b "'", (a) == (b))
#define mu_assert_not_equal(a, b) mu_assert("'" #a "' is equal to '" #b "'", (a) != (b))
#define mu_assert_str_equal(a, b)					\
    mu_assert("'" #a "' is not equal to '" #b "'", strcmp((a), (b)) == 0)
#define mu_assert_str_not_equal(a, b)					\
    mu_assert("'" #a "' is equal to '" #b "'", strcmp((a), (b)) != 0)

#define mu_run_test(name, test) do {                            \
	lua_State *L = luaL_newstate();                         \
	luaL_openlibs(L);                                       \
	const char *message = test(L);				\
	lua_close(L);                                           \
	tests_run++;                                            \
	if (message) {                                          \
	    printf(RED mu_indent "test '%s' failed:" RESET " %s\n", name, message);	\
	    tests_failed++;                                     \
	}                                                       \
    } while (0)
#define TEST(name) static const char* name(lua_State *L)
#define mu_run_suite(suite) do {					\
	tests_run_old = tests_run;					\
	suite();							\
	printf(mu_indent "ran %d tests\n", tests_run - tests_run_old);	\
    } while (0)

extern int tests_run, tests_run_old, tests_failed;

void hs_type_to_string_tests();
void hs_parse_args_tests();
void hs_parse_overloaded_tests();
void hs_create_table_tests();
void hs_create_enum_tests();
void hs_process_table_tests();
void hs_throw_error_tests();
void hs_traceback_tests();
void hs_call_tests();
void hs_call_args_tests();
void hs_pushstring_tests();
void hs_rxx_tests();
