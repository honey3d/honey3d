#include "hs_tests.h"

static int testfunc(lua_State *L) { return 0; }

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * hs_parse_args typechecking tests
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

// typechecking macros
#define PARSE_TYPECHECK_TEST(name, type, macro)		\
   int name ## _testfunc(lua_State *L) {		\
      type test; hs_parse_args(L, macro(test));		\
      return 0;						\
   }							\
   TEST(name)

#define CHECK_FAIL_BOOL(name)						\
   lua_pushcfunction(L, name ## _testfunc); lua_pushboolean(L, true);	\
   mu_assert("incorrectly succeeded in parsing boolean!",		\
	     lua_pcall(L, 1, 0, 0) != 0);				\
   lua_pop(L, 1);

#define CHECK_FAIL_INT(name)						\
   lua_pushcfunction(L, name ## _testfunc); lua_pushinteger(L, 5);	\
   mu_assert("incorrectly succeeded in parsing integer!",		\
	     lua_pcall(L, 1, 0, 0) != 0);				\
   lua_pop(L, 1);

#define CHECK_FAIL_NUM(name)						\
   lua_pushcfunction(L, name ## _testfunc); lua_pushnumber(L, 42.0f);	\
   mu_assert("incorrectly succeeded in parsing number!",		\
	     lua_pcall(L, 1, 0, 0) != 0);				\
   lua_pop(L, 1);

#define CHECK_FAIL_STRING(name)						\
   lua_pushcfunction(L, name ## _testfunc); lua_pushstring(L, "hello!"); \
   mu_assert("incorrectly succeeded in parsing string!",		\
	     lua_pcall(L, 1, 0, 0) != 0);				\
   lua_pop(L, 1);

#define CHECK_FAIL_TABLE(name)						\
   lua_pushcfunction(L, name ## _testfunc); lua_getglobal(L, "debug");	\
   mu_assert("incorrectly succeeded in parsing table!",			\
	     lua_pcall(L, 1, 0, 0) != 0);				\
   lua_pop(L, 1);

#define CHECK_FAIL_FUNC(name)						\
   lua_pushcfunction(L, name ## _testfunc);				\
   luaL_loadstring(L, "print('hello, world!')");			\
   mu_assert("incorrectly succeeded in parsing function!",		\
	     lua_pcall(L, 1, 0, 0) != 0);				\
   lua_pop(L, 1);

#define CHECK_FAIL_CFUNC(name)						\
   lua_pushcfunction(L, name ## _testfunc); lua_pushvalue(L, -1);	\
   mu_assert("incorrectly succeeded in parsing C function!",		\
	     lua_pcall(L, 1, 0, 0) != 0);				\
   lua_pop(L, 1);

#define CHECK_FAIL_USER(name)						\
   lua_pushcfunction(L, name ## _testfunc); lua_newuserdata(L, sizeof(char)); \
   mu_assert("incorrectly succeeded in parsing userdata!",		\
	     lua_pcall(L, 1, 0, 0) != 0);				\
   lua_pop(L, 1);

#define CHECK_FAIL_LIGHT(name)						\
   int test_data = 5;							\
   lua_pushcfunction(L, name ## _testfunc); lua_pushlightuserdata(L, &test_data); \
   mu_assert("incorrectly succeeded in parsing light userdata!",	\
	     lua_pcall(L, 1, 0, 0) != 0);				\
   lua_pop(L, 1);

#define CHECK_FAIL_NIL(name)					\
   lua_pushcfunction(L, name ## _testfunc); lua_pushnil(L);	\
   mu_assert("incorrectly succeeded in parsing nil!",		\
	     lua_pcall(L, 1, 0, 0) != 0);			\
   lua_pop(L, 1);


PARSE_TYPECHECK_TEST(parse_bool_typecheck, bool, hs_bool)
{
   lua_pushcfunction(L, parse_bool_typecheck_testfunc);
   lua_pushboolean(L, true);
   mu_assert("typecheck for bool failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   CHECK_FAIL_INT(parse_bool_typecheck);
   CHECK_FAIL_NUM(parse_bool_typecheck);
   CHECK_FAIL_STRING(parse_bool_typecheck);
   CHECK_FAIL_TABLE(parse_bool_typecheck);
   CHECK_FAIL_FUNC(parse_bool_typecheck);
   CHECK_FAIL_CFUNC(parse_bool_typecheck);
   CHECK_FAIL_USER(parse_bool_typecheck);
   CHECK_FAIL_LIGHT(parse_bool_typecheck);
   CHECK_FAIL_NIL(parse_bool_typecheck);
   return 0;
}

PARSE_TYPECHECK_TEST(parse_int_typecheck, lua_Integer, hs_int)
{
   CHECK_FAIL_BOOL(parse_int_typecheck);

   lua_pushcfunction(L, parse_int_typecheck_testfunc);
   lua_pushinteger(L, 5);
   mu_assert("typecheck for int failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   // we would check for num, but in lua 5.1 there
   // isn't a separate integer type, so it would
   // still work
   CHECK_FAIL_STRING(parse_int_typecheck);
   CHECK_FAIL_TABLE(parse_int_typecheck);
   CHECK_FAIL_FUNC(parse_int_typecheck);
   CHECK_FAIL_CFUNC(parse_int_typecheck);
   CHECK_FAIL_USER(parse_int_typecheck);
   CHECK_FAIL_LIGHT(parse_int_typecheck);
   CHECK_FAIL_NIL(parse_int_typecheck);
   return 0;
}

PARSE_TYPECHECK_TEST(parse_num_typecheck, lua_Number, hs_num)
{
   CHECK_FAIL_BOOL(parse_num_typecheck);
   // we would check for int, but in lua 5.1 there
   // isn't a separate integer type, so it would
   // still work

   lua_pushcfunction(L, parse_int_typecheck_testfunc);
   lua_pushnumber(L, 42.0f);
   mu_assert("typecheck for number failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   CHECK_FAIL_STRING(parse_num_typecheck);
   CHECK_FAIL_TABLE(parse_num_typecheck);
   CHECK_FAIL_FUNC(parse_num_typecheck);
   CHECK_FAIL_CFUNC(parse_num_typecheck);
   CHECK_FAIL_USER(parse_num_typecheck);
   CHECK_FAIL_LIGHT(parse_num_typecheck);
   CHECK_FAIL_NIL(parse_num_typecheck);
   return 0;
}

PARSE_TYPECHECK_TEST(parse_string_typecheck, char *, hs_str)
{
   CHECK_FAIL_BOOL(parse_string_typecheck);
   CHECK_FAIL_INT(parse_string_typecheck);
   CHECK_FAIL_NUM(parse_string_typecheck);

   lua_pushcfunction(L, parse_string_typecheck_testfunc);
   lua_pushstring(L, "hello!");
   mu_assert("typecheck for string failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   CHECK_FAIL_TABLE(parse_string_typecheck);
   CHECK_FAIL_FUNC(parse_string_typecheck);
   CHECK_FAIL_CFUNC(parse_string_typecheck);
   CHECK_FAIL_USER(parse_string_typecheck);
   CHECK_FAIL_LIGHT(parse_string_typecheck);
   CHECK_FAIL_NIL(parse_string_typecheck);
   return 0;
}

PARSE_TYPECHECK_TEST(parse_table_typecheck, int, hs_tbl)
{
   CHECK_FAIL_BOOL(parse_table_typecheck);
   CHECK_FAIL_INT(parse_table_typecheck);
   CHECK_FAIL_NUM(parse_table_typecheck);
   CHECK_FAIL_STRING(parse_table_typecheck);

   lua_pushcfunction(L, parse_table_typecheck_testfunc);
   lua_getglobal(L, "debug");
   mu_assert("typecheck for table failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   CHECK_FAIL_FUNC(parse_table_typecheck);
   CHECK_FAIL_CFUNC(parse_table_typecheck);
   CHECK_FAIL_USER(parse_table_typecheck);
   CHECK_FAIL_LIGHT(parse_table_typecheck);
   CHECK_FAIL_NIL(parse_table_typecheck);
   return 0;
}

PARSE_TYPECHECK_TEST(parse_func_typecheck, int, hs_func)
{
   CHECK_FAIL_BOOL(parse_func_typecheck);
   CHECK_FAIL_INT(parse_func_typecheck);
   CHECK_FAIL_NUM(parse_func_typecheck);
   CHECK_FAIL_STRING(parse_func_typecheck);
   CHECK_FAIL_TABLE(parse_func_typecheck);

   lua_pushcfunction(L, parse_func_typecheck_testfunc);
   luaL_loadstring(L, "print('hello, world!')");
   mu_assert("typecheck for function failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   lua_pushcfunction(L, parse_func_typecheck_testfunc);
   lua_pushvalue(L, -1);
   mu_assert("typecheck for C function failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   CHECK_FAIL_USER(parse_func_typecheck);
   CHECK_FAIL_LIGHT(parse_func_typecheck);
   CHECK_FAIL_NIL(parse_func_typecheck);
   return 0;
}

PARSE_TYPECHECK_TEST(parse_cfunc_typecheck, lua_CFunction, hs_cfunc)
{
   CHECK_FAIL_BOOL(parse_cfunc_typecheck);
   CHECK_FAIL_INT(parse_cfunc_typecheck);
   CHECK_FAIL_NUM(parse_cfunc_typecheck);
   CHECK_FAIL_STRING(parse_cfunc_typecheck);
   CHECK_FAIL_TABLE(parse_cfunc_typecheck);
   CHECK_FAIL_FUNC(parse_cfunc_typecheck);

   lua_pushcfunction(L, parse_cfunc_typecheck_testfunc);
   lua_pushvalue(L, -1);
   mu_assert("typecheck for C function failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   CHECK_FAIL_USER(parse_cfunc_typecheck);
   CHECK_FAIL_LIGHT(parse_cfunc_typecheck);
   CHECK_FAIL_NIL(parse_cfunc_typecheck);
   return 0;
}

PARSE_TYPECHECK_TEST(parse_user_typecheck, void *, hs_user)
{
   CHECK_FAIL_BOOL(parse_user_typecheck);
   CHECK_FAIL_INT(parse_user_typecheck);
   CHECK_FAIL_NUM(parse_user_typecheck);
   CHECK_FAIL_STRING(parse_user_typecheck);
   CHECK_FAIL_TABLE(parse_user_typecheck);
   CHECK_FAIL_FUNC(parse_user_typecheck);
   CHECK_FAIL_CFUNC(parse_user_typecheck);

   lua_pushcfunction(L, parse_user_typecheck_testfunc);
   lua_newuserdata(L, sizeof(char));
   mu_assert("typecheck for userdata failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   lua_pushcfunction(L, parse_user_typecheck_testfunc);
   int testdata = 5; lua_pushlightuserdata(L, &testdata);
   mu_assert("typecheck for light userdata failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   CHECK_FAIL_NIL(parse_user_typecheck);
   return 0;
}

PARSE_TYPECHECK_TEST(parse_light_typecheck, void *, hs_light)
{
   CHECK_FAIL_BOOL(parse_light_typecheck);
   CHECK_FAIL_INT(parse_light_typecheck);
   CHECK_FAIL_NUM(parse_light_typecheck);
   CHECK_FAIL_STRING(parse_light_typecheck);
   CHECK_FAIL_TABLE(parse_light_typecheck);
   CHECK_FAIL_FUNC(parse_light_typecheck);
   CHECK_FAIL_CFUNC(parse_light_typecheck);
   CHECK_FAIL_USER(parse_light_typecheck);

   lua_pushcfunction(L, parse_light_typecheck_testfunc);
   int testdata = 5; lua_pushlightuserdata(L, &testdata);
   mu_assert("typecheck for light userdata failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   CHECK_FAIL_NIL(parse_light_typecheck);
   return 0;
}

PARSE_TYPECHECK_TEST(parse_nil_typecheck, int, hs_nil)
{
   CHECK_FAIL_BOOL(parse_nil_typecheck);
   CHECK_FAIL_INT(parse_nil_typecheck);
   CHECK_FAIL_NUM(parse_nil_typecheck);
   CHECK_FAIL_STRING(parse_nil_typecheck);
   CHECK_FAIL_TABLE(parse_nil_typecheck);
   CHECK_FAIL_FUNC(parse_nil_typecheck);
   CHECK_FAIL_CFUNC(parse_nil_typecheck);
   CHECK_FAIL_USER(parse_nil_typecheck);
   CHECK_FAIL_LIGHT(parse_nil_typecheck);

   lua_pushcfunction(L, parse_nil_typecheck_testfunc);
   lua_pushnil(L);
   mu_assert("typecheck for nil failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   return 0;
}

PARSE_TYPECHECK_TEST(parse_any_typecheck, int, hs_any)
{
   lua_pushcfunction(L, parse_bool_typecheck_testfunc);
   lua_pushboolean(L, true);
   mu_assert("typecheck for bool failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   lua_pushcfunction(L, parse_int_typecheck_testfunc);
   lua_pushinteger(L, 5);
   mu_assert("typecheck for int failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   lua_pushcfunction(L, parse_int_typecheck_testfunc);
   lua_pushnumber(L, 42.0f);
   mu_assert("typecheck for number failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   lua_pushcfunction(L, parse_string_typecheck_testfunc);
   lua_pushstring(L, "hello!");
   mu_assert("typecheck for string failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   lua_pushcfunction(L, parse_table_typecheck_testfunc);
   lua_getglobal(L, "debug");
   mu_assert("typecheck for table failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   lua_pushcfunction(L, parse_func_typecheck_testfunc);
   luaL_loadstring(L, "print('hello, world!')");
   mu_assert("typecheck for function failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   lua_pushcfunction(L, parse_cfunc_typecheck_testfunc);
   lua_pushvalue(L, -1);
   mu_assert("typecheck for C function failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   lua_pushcfunction(L, parse_user_typecheck_testfunc);
   lua_newuserdata(L, sizeof(char));
   mu_assert("typecheck for userdata failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   lua_pushcfunction(L, parse_user_typecheck_testfunc);
   int testdata = 5; lua_pushlightuserdata(L, &testdata);
   mu_assert("typecheck for light userdata failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   lua_pushcfunction(L, parse_nil_typecheck_testfunc);
   lua_pushnil(L);
   mu_assert("typecheck for nil failed!",
	     lua_pcall(L, 1, 0, 0) == 0);

   return 0;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * hs_parse_args parsing tests
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

TEST(parse_bool)
{
   lua_pushboolean(L, true);
   bool b = false;
   hs_parse_args(L, hs_bool(b));
   mu_assert("failed to properly parse boolean!", b);
   return 0;
}

TEST(parse_int)
{
   lua_pushinteger(L, 420);
   lua_Integer i = 0;
   hs_parse_args(L, hs_int(i));
   mu_assert("failed to properly parse integer!", i == 420);
   return 0;
}

TEST(parse_num)
{
   lua_pushnumber(L, 40.5f);
   lua_Number n = 0;
   hs_parse_args(L, hs_num(n));
   mu_assert("failed to properly parse number!", n == 40.5f);
   return 0;
}

TEST(parse_str)
{
   lua_pushstring(L, "hello, world!");
   char *s = "";
   hs_parse_args(L, hs_str(s));
   mu_assert("failed to properly parse string!",
	     strcmp(s, "hello, world!") == 0);
   return 0;
}

TEST(parse_tbl)
{
   lua_getglobal(L, "debug");
   int correct_index = lua_gettop(L);
   int tbl_index;
   hs_parse_args(L, hs_tbl(tbl_index));
   mu_assert("failed to properly parse table!", tbl_index == correct_index);
   return 0;
}

TEST(parse_func)
{
   lua_getglobal(L, "type");
   int correct_index = lua_gettop(L);
   int index = 0;
   hs_parse_args(L, hs_func(index));
   mu_assert("failed to properly parse function!", index == correct_index);
   return 0;
}

TEST(parse_cfunc)
{
   lua_pushcfunction(L, testfunc);
   lua_CFunction f;
   hs_parse_args(L, hs_cfunc(f));
   mu_assert("failed to properly parse C function!", f == testfunc);
   return 0;
}

int should_fail(lua_State *L)
{
   lua_CFunction f;
   hs_parse_args(L, hs_cfunc(f));
   return 0;
}

TEST(fail_parse_noncfunc)
{
   lua_pushcfunction(L, should_fail);
   luaL_loadstring(L, "print('hello, world!')");
   mu_assert("incorrectly parsed non-C function!",
	     lua_pcall(L, 1, 0, 0) != 0);
   return 0;
}

TEST(parse_userdata)
{
   void *userdata = lua_newuserdata(L, sizeof(char));
   void *parsed = NULL;
   hs_parse_args(L, hs_user(parsed));
   mu_assert("failed to properly parse userdata!",
	     parsed == userdata);
   return 0;
}

TEST(parse_lightuserdata)
{
   int five = 5;
   lua_pushlightuserdata(L, &five);

   void *data;
   hs_parse_args(L, hs_light(data));
   mu_assert("failed to properly parse light userdata!",
	     data == &five);
   return 0;
}

TEST(parse_nil)
{
   lua_pushnil(L);
   int correct_index = lua_gettop(L);
   int index = 0;
   hs_parse_args(L, hs_nil(index));
   mu_assert("failed to properly parse nil!",
	     index == correct_index);
   return 0;
}

TEST(parse_any)
{
   lua_pushnil(L);
   int correct_index = lua_gettop(L);
   int index = 0;
   hs_parse_args(L, hs_any(index));
   mu_assert("failed to properly parse [any]!",
	     index == correct_index);
   return 0;
}

TEST(parse_all)
{
   lua_pushboolean(L, true);
   lua_pushinteger(L, 420);
   lua_pushnumber(L, 40.5f);
   lua_pushstring(L, "hello, world!");
   lua_getglobal(L, "debug");
   int tbl_index = lua_gettop(L);
   lua_getglobal(L, "type");
   int func_index = lua_gettop(L);
   lua_pushcfunction(L, testfunc);
   void *userdata = lua_newuserdata(L, sizeof(char));
   int five = 5;
   lua_pushlightuserdata(L, &five);
   lua_pushnil(L);
   int nil_index = lua_gettop(L);
   lua_pushnil(L);
   int any_index = lua_gettop(L);

   bool b;
   lua_Integer i;
   lua_Number f;
   char *str;
   int i_tbl;
   int i_func;
   lua_CFunction fn;
   void *user;
   void *light;
   int i_nil;
   int i_any;
   hs_parse_args
      (L,
       hs_bool(b),
       hs_int(i),
       hs_num(f),
       hs_str(str),
       hs_tbl(i_tbl),
       hs_func(i_func),
       hs_cfunc(fn),
       hs_user(user),
       hs_light(light),
       hs_nil(i_nil),
       hs_any(i_any));

   mu_assert("failed to properly parse boolean!", b);
   mu_assert("failed to properly parse integer!", i == 420);
   mu_assert("failed to properly parse number!", f == 40.5f);
   mu_assert("failed to properly parse string!",
	     strcmp(str, "hello, world!") == 0);
   mu_assert("failed to properly parse table!", i_tbl == tbl_index);
   mu_assert("failed to properly parse function!", func_index == i_func);
   mu_assert("failed to properly parse C function!", fn == testfunc);
   mu_assert("failed to properly parse userdata!", user == userdata);
   mu_assert("failed to properly parse light userdata!", light == &five);
   mu_assert("failed to properly parse nil!", nil_index == i_nil);
   mu_assert("failed to properly parse [any]!", any_index == i_any);
   return 0;
}

TEST(parse_readme_example)
{
   lua_pushboolean(L, true);
   lua_pushinteger(L, 7);
   lua_getglobal(L, "debug");
   int expected = lua_gettop(L);
   lua_pushnumber(L, 3.1415f);
   lua_pushstring(L, "c: c: c:");
   void *userdata = lua_newuserdata(L, sizeof(char));

   bool b; lua_Integer i; int table_index;
   lua_Number f; char *str; void *user;
   hs_parse_args
      (L, hs_bool(b), hs_int(i), hs_tbl(table_index),
       hs_num(f), hs_str(str), hs_user(user));

   mu_assert("failed to properly parse boolean!", b);
   mu_assert("failed to properly parse integer!", i == 7);
   mu_assert("failed to properly parse table!", table_index == expected);
   mu_assert("failed to properly parse number!", f == 3.1415f);
   mu_assert("failed to properly parse string!", strcmp(str, "c: c: c:") == 0);
   mu_assert("failed to properly parse userdata!", user == userdata);
   return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * test suite
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void hs_parse_args_tests()
{
   printf("running hs_parse_args() tests...\n");
   mu_run_test("parse bool typecheck", parse_bool_typecheck);
   mu_run_test("parse int typecheck", parse_int_typecheck);
   mu_run_test("parse num typecheck", parse_num_typecheck);
   mu_run_test("parse string typecheck", parse_string_typecheck);
   mu_run_test("parse table typecheck", parse_table_typecheck);
   mu_run_test("parse func typecheck", parse_func_typecheck);
   mu_run_test("parse cfunc typecheck", parse_cfunc_typecheck);
   mu_run_test("parse user typecheck", parse_user_typecheck);
   mu_run_test("parse light typecheck", parse_light_typecheck);
   mu_run_test("parse nil typecheck", parse_nil_typecheck);
   mu_run_test("parse any typecheck", parse_any_typecheck);

   mu_run_test("parse bool", parse_bool);
   mu_run_test("parse int", parse_int);
   mu_run_test("parse num", parse_num);
   mu_run_test("parse str", parse_str);
   mu_run_test("parse tbl", parse_tbl);
   mu_run_test("parse func", parse_func);
   mu_run_test("parse cfunc", parse_cfunc);
   mu_run_test("fail parse noncfunc", fail_parse_noncfunc);
   mu_run_test("parse userdata", parse_userdata);
   mu_run_test("parse lightuserdata", parse_lightuserdata);
   mu_run_test("parse nil", parse_nil);
   mu_run_test("parse any", parse_any);
   mu_run_test("parse all", parse_all);
   mu_run_test("parse readme example", parse_readme_example);
}
