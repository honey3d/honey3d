#include "hs_tests.h"

static int testfunc(lua_State *L) { return 0; }

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * tests for hs_parse_overloaded
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#define PARSE_OVERLOADED				\
   bool b; lua_Integer i; int ti, fi, ni; lua_Number f;	\
   char *str; lua_CFunction fn; void *user, *light;	\
   int choice = hs_parse_overloaded			\
      (L,						\
       hs_overload(hs_bool(b)),				\
       hs_overload(hs_int(i)),				\
       hs_overload(hs_num(f)),				\
       hs_overload(hs_str(str)),			\
       hs_overload(hs_tbl(ti)),				\
       hs_overload(hs_func(fi)),			\
       hs_overload(hs_cfunc(fn)),			\
       hs_overload(hs_user(user)),			\
       hs_overload(hs_light(light)),			\
       hs_overload(hs_nil(ni)));

TEST(parse_bool_overloaded)
{
   lua_pushboolean(L, true);
   PARSE_OVERLOADED;
   mu_assert("boolean option was not chosen!", choice == 0);
   mu_assert("failed to properly parse boolean!", b);
   return 0;
}

TEST(parse_integer_overloaded)
{
   lua_pushinteger(L, 5);
   PARSE_OVERLOADED;
   mu_assert("integer option was not chosen!", choice == 1);
   mu_assert("failed to properly parse integer!", i == 5);
   return 0;
}

TEST(parse_number_overloaded)
{
   lua_pushnumber(L, 42.0f);
   PARSE_OVERLOADED;
   mu_assert("number option was not chosen!", choice == 2);
   mu_assert("failed to properly parse boolean!", f == 42.0f);
   return 0;
}

TEST(parse_string_overloaded)
{
   lua_pushstring(L, "hello, world!");
   PARSE_OVERLOADED;
   mu_assert("string option was not chosen!", choice == 3);
   mu_assert("failed to properly parse string!",
	     strcmp(str, "hello, world!") == 0);
   return 0;
}

TEST(parse_table_overloaded)
{
   lua_getglobal(L, "debug");
   int expected = lua_gettop(L);
   PARSE_OVERLOADED;
   mu_assert("table option was not chosen!", choice == 4);
   mu_assert("failed to properly parse table!", ti == expected);
   return 0;
}

TEST(parse_function_overloaded)
{
   luaL_loadstring(L, "print('hello, world!')");
   int expected = lua_gettop(L);
   PARSE_OVERLOADED;
   mu_assert("function option was not chosen!", choice == 5);
   mu_assert("failed to properly parse function!", fi == expected);
   return 0;
}

TEST(parse_cfunction_overloaded)
{
   lua_pushcfunction(L, testfunc);
   PARSE_OVERLOADED;
   mu_assert("C function option was not chosen!", choice == 6);
   mu_assert("failed to properly parse C function!", fn == testfunc);
   return 0;
}

TEST(parse_userdata_overloaded)
{
   void *userdata = lua_newuserdata(L, sizeof(char));
   PARSE_OVERLOADED;
   mu_assert("userdata option was not chosen!", choice == 7);
   mu_assert("failed to properly parse userdata!", user == userdata);
   return 0;
}

TEST(parse_lightuserdata_overloaded)
{
   int five = 5;
   lua_pushlightuserdata(L, &five);
   PARSE_OVERLOADED;
   mu_assert("light userdata option was not chosen!", choice == 8);
   mu_assert("failed to properly parse light userdata!", light == &five);
   return 0;
}

TEST(parse_nil_overloaded)
{
   lua_pushnil(L);
   int expected = lua_gettop(L);
   PARSE_OVERLOADED;
   mu_assert("nil option was not chosen!", choice == 9);
   mu_assert("failed to properly parse nil!", ni == expected);
   return 0;
}

TEST(parse_2_3_overload_0)
{
   lua_pushinteger(L, 69);
   lua_pushstring(L, "foo");
   lua_Integer i; char *str; void *data;
   int choice = hs_parse_overloaded
      (L,
       hs_overload(hs_int(i), hs_str(str)),
       hs_overload(hs_int(i), hs_str(str), hs_user(data)));

   mu_assert("incorrectly selected option other than 0!", choice == 0);
   mu_assert("failed to properly parse integer!", i == 69);
   mu_assert("failed to properly parse string!", strcmp(str, "foo") == 0);
   return 0;
}

TEST(parse_2_3_overload_1)
{
   lua_pushinteger(L, 69);
   lua_pushstring(L, "foo");
   void *userdata = lua_newuserdata(L, sizeof(char));
   lua_Integer i; char *str; void *data;
   int choice = hs_parse_overloaded
      (L,
       hs_overload(hs_int(i), hs_str(str)),
       hs_overload(hs_int(i), hs_str(str), hs_user(data)));

   mu_assert("incorrectly selected option other than 1!", choice == 1);
   mu_assert("failed to properly parse integer!", i == 69);
   mu_assert("failed to properly parse string!", strcmp(str, "foo") == 0);
   mu_assert("failed to properly parse userdata!", userdata == data);
   return 0;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * test suite
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void hs_parse_overloaded_tests()
{
   /* the commented tests below require more work to ensure that
    * they function correctly. Due to type ambiguities that are
    * useful in other contexts, overloads differing only in a
    * number/integer, function/cfunction, or userdata/lightuserdata
    * in the same position are not readily distinguishable from one
    * another.
    */
   
   printf("running hs_parse_overloaded() parsing tests...\n");
   mu_run_test("parse bool overloaded", parse_bool_overloaded);
   mu_run_test("parse integer overloaded", parse_integer_overloaded);
   // mu_run_test("parse number overloaded", parse_number_overloaded);
   mu_run_test("parse string overloaded", parse_string_overloaded);
   mu_run_test("parse table overloaded", parse_table_overloaded);
   mu_run_test("parse function overloaded", parse_function_overloaded);
   // mu_run_test("parse cfunction overloaded", parse_cfunction_overloaded);
   mu_run_test("parse userdata overloaded", parse_userdata_overloaded);
   // mu_run_test("parse lightuserdata overloaded", parse_lightuserdata_overloaded);
   mu_run_test("parse nil overloaded", parse_nil_overloaded);
   mu_run_test("parse 2/3 overload 0", parse_2_3_overload_0);
   mu_run_test("parse 2/3 overload 1", parse_2_3_overload_1);
}
