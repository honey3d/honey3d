#include "hs_tests.h"

static int testfunc1(lua_State *L) { return 0; }
static int testfunc2(lua_State *L) { return 0; }

static void print_stack(lua_State *L)
{
   printf("stack: %d [", lua_gettop(L));
   for (int i=0; i<lua_gettop(L); i++) {
      printf(" %s, ", lua_typename(L, lua_type(L, i+1)));
   }
   printf("]\n");
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * tests for hs_create_table
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

TEST(table_correct_index)
{
   int top_old = lua_gettop(L);
   int index = hs_create_table(L);
   mu_assert("the stack is unchanged!", lua_gettop(L) != top_old);
   mu_assert("returned incorrect index!", index == lua_gettop(L));
   return 0;
}

#define load_key(index, value, pushf) do {		\
      pushf(L, value); lua_gettable(L, index);		\
      mu_assert("value at key '" #value "' is nil!",	\
		!lua_isnil(L, -1));			\
   } while(0)

#define loadkey_bool(index, value)		\
   load_key(index, value, lua_pushboolean)
#define loadkey_int(index, value)		\
   load_key(index, value, lua_pushinteger)
#define loadkey_num(index, value)		\
   load_key(index, value, lua_pushnumber)
#define loadkey_str(index, value)		\
   lua_getfield(L, index, value)
#define loadkey_tbl(index, value) do {				\
      lua_pushvalue(L, value); lua_gettable(L, index);		\
      mu_assert("value at table (index '" #value "') is nil!",	\
		!lua_isnil(L, -1));				\
   } while(0)
#define loadkey_func(index, value) do {					\
      lua_pushvalue(L, value); lua_gettable(L, index);			\
      mu_assert("value at function (index '" #value "') is nil!",	\
		!lua_isnil(L, -1));					\
   } while(0)
#define loadkey_cfunc(index, value)		\
   load_key(index, value, lua_pushcfunction)
#define loadkey_user(index, value) do {					\
      lua_pushvalue(L, value); lua_gettable(L, index);			\
      mu_assert("value at userdata (index '" #value "') is nil!",	\
		!lua_isnil(L, -1));					\
   } while(0)
#define loadkey_light(index, value)			\
   load_key(index, value, lua_pushlightuserdata)

#define check_value(is_type, typestring, type, conversion, comparison)	\
   do {									\
      mu_assert("value is not of type " typestring, is_type(L, -1));	\
      type value = conversion(L, -1); lua_pop(L, 1);			\
      mu_assert("test " #comparison " failed!", (comparison));		\
   } while(0)

#define checkval_bool(expected)						\
   check_value(lua_isboolean, "boolean", bool, lua_toboolean, value==expected)
#define checkval_int(expected)						\
   check_value(lua_isnumber, "integer", lua_Integer, lua_tointeger, value==expected)
#define checkval_num(expected)						\
   check_value(lua_isnumber, "number", lua_Number, lua_tonumber, value==expected)
#define checkval_str(expected)						\
   check_value(lua_isstring, "string", const char *, lua_tostring, strcmp(value, expected)==0)
#define checkval_tbl(expected)						\
   check_value(lua_istable, "table", const void *, lua_topointer, value==lua_topointer(L, expected))
#define checkval_func(expected)						\
   check_value(lua_isfunction, "function", const void *, lua_topointer, value==lua_topointer(L, expected))
#define checkval_cfunc(expected)					\
   check_value(lua_iscfunction, "C function", lua_CFunction, lua_tocfunction, value==expected)
#define checkval_user(expected)						\
   check_value(lua_isuserdata, "userdata", void *, lua_touserdata, value==lua_topointer(L, expected))
#define checkval_light(expected)					\
   check_value(lua_islightuserdata, "light userdata", void *, lua_touserdata, value==expected)

#define store(name)					\
   lua_pushvalue(L, -1);				\
   int name ## _ref = luaL_ref(L, LUA_REGISTRYINDEX);	\
   int name = lua_gettop(L);

#define load(name)					\
   lua_rawgeti(L, LUA_REGISTRYINDEX, name ## _ref);	\
   name = lua_gettop(L);


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * boolean keys
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

TEST(create_table_bool_bool)
{
   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_bool_bool(true, true), hs_bool_bool(false, true));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_bool(index, true);
   checkval_bool(true);
   loadkey_bool(index, false);
   checkval_bool(true);
   return 0;
}

TEST(create_table_bool_int)
{
   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_bool_int(true, 15), hs_bool_int(false, 25));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_bool(index, true);
   checkval_int(15);
   loadkey_bool(index, false);
   checkval_int(25);
   return 0;
}

TEST(create_table_bool_num)
{
   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_bool_num(true, 2.718), hs_bool_num(false, 1.618));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_bool(index, true);
   checkval_num(2.718);
   loadkey_bool(index, false);
   checkval_num(1.618);
   return 0;
}

TEST(create_table_bool_str)
{
   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_bool_str(true, "hello"), hs_bool_str(false, "world"));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_bool(index, true);
   checkval_str("hello");
   loadkey_bool(index, false);
   checkval_str("world");
   return 0;
}

TEST(create_table_bool_tbl)
{
   int oldtop = lua_gettop(L);

   lua_newtable(L);
   store(value1);
   lua_newtable(L);
   store(value2);

   int index = hs_create_table
      (L, hs_bool_tbl(true, value1), hs_bool_tbl(false, value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(value1);
   load(value2);

   loadkey_bool(index, true);
   checkval_tbl(value1);
   loadkey_bool(index, false);
   checkval_tbl(value2);
   return 0;
}

TEST(create_table_bool_func)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('hello')");
   store(value1);
   luaL_loadstring(L, "print('hello')");
   store(value2);

   int index = hs_create_table
      (L, hs_bool_func(true, value1), hs_bool_func(false, value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(value1);
   load(value2);

   loadkey_bool(index, true);
   checkval_func(value1);
   loadkey_bool(index, false);
   checkval_func(value2);
   return 0;
}

TEST(create_table_bool_cfunc)
{

   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_bool_cfunc(true, testfunc1), hs_bool_cfunc(false, testfunc2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_bool(index, true);
   checkval_cfunc(testfunc1);
   loadkey_bool(index, false);
   checkval_cfunc(testfunc2);
   return 0;
}


TEST(create_table_bool_user)
{
   int oldtop = lua_gettop(L);

   lua_newuserdata(L, sizeof(char));
   store(user1);
   lua_newuserdata(L, sizeof(char));
   store(user2);

   int index = hs_create_table
      (L, hs_bool_user(true, user1), hs_bool_user(false, user2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(user1);
   load(user2);

   loadkey_bool(index, true);
   checkval_user(user1);
   loadkey_bool(index, false);
   checkval_user(user2);
   return 0;
}

TEST(create_table_bool_light)
{
   int a1 = 5;
   void *light1 = (void *) &a1;
   int a2 = 6;
   void *light2 = (void *) &a2;

   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_bool_light(true, light1), hs_bool_light(false, light2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_bool(index, true);
   checkval_light(light1);
   loadkey_bool(index, false);
   checkval_light(light2);
   return 0;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * integer keys
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

TEST(create_table_int_bool)
{
   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_int_bool(15, true), hs_int_bool(25, true));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_int(index, 15);
   checkval_bool(true);
   loadkey_int(index, 25);
   checkval_bool(true);
   return 0;
}

TEST(create_table_int_int)
{
   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_int_int(15, 15), hs_int_int(25, 25));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_int(index, 15);
   checkval_int(15);
   loadkey_int(index, 25);
   checkval_int(25);
   return 0;
}

TEST(create_table_int_num)
{
   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_int_num(15, 2.718), hs_int_num(25, 1.618));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_int(index, 15);
   checkval_num(2.718);
   loadkey_int(index, 25);
   checkval_num(1.618);
   return 0;
}

TEST(create_table_int_str)
{
   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_int_str(15, "hello"), hs_int_str(25, "world"));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_int(index, 15);
   checkval_str("hello");
   loadkey_int(index, 25);
   checkval_str("world");
   return 0;
}

TEST(create_table_int_tbl)
{
   int oldtop = lua_gettop(L);

   lua_newtable(L);
   store(value1);
   lua_newtable(L);
   store(value2);

   int index = hs_create_table
      (L, hs_int_tbl(15, value1), hs_int_tbl(25, value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(value1);
   load(value2);

   loadkey_int(index, 15);
   checkval_tbl(value1);
   loadkey_int(index, 25);
   checkval_tbl(value2);
   return 0;
}

TEST(create_table_int_func)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('hello')");
   store(value1);
   luaL_loadstring(L, "print('hello')");
   store(value2);

   int index = hs_create_table
      (L, hs_int_func(15, value1), hs_int_func(25, value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(value1);
   load(value2);

   loadkey_int(index, 15);
   checkval_func(value1);
   loadkey_int(index, 25);
   checkval_func(value2);
   return 0;
}

TEST(create_table_int_cfunc)
{

   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_int_cfunc(15, testfunc1), hs_int_cfunc(25, testfunc2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_int(index, 15);
   checkval_cfunc(testfunc1);
   loadkey_int(index, 25);
   checkval_cfunc(testfunc2);
   return 0;
}


TEST(create_table_int_user)
{
   int oldtop = lua_gettop(L);

   lua_newuserdata(L, sizeof(char));
   store(user1);
   lua_newuserdata(L, sizeof(char));
   store(user2);

   int index = hs_create_table
      (L, hs_int_user(15, user1), hs_int_user(25, user2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(user1);
   load(user2);

   loadkey_int(index, 15);
   checkval_user(user1);
   loadkey_int(index, 25);
   checkval_user(user2);
   return 0;
}

TEST(create_table_int_light)
{
   int a1 = 5;
   void *light1 = (void *) &a1;
   int a2 = 6;
   void *light2 = (void *) &a2;

   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_int_light(15, light1), hs_int_light(25, light2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_int(index, 15);
   checkval_light(light1);
   loadkey_int(index, 25);
   checkval_light(light2);
   return 0;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * number keys
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

TEST(create_table_num_bool)
{
   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_num_bool(43.3f, true), hs_num_bool(23.56f, false));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_num(index, 43.3f);
   checkval_bool(true);
   loadkey_num(index, 23.56f);
   checkval_bool(false);
   return 0;
}

TEST(create_table_num_int)
{
   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_num_int(43.3f, 15), hs_num_int(23.56f, 25));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_num(index, 43.3f);
   checkval_int(15);
   loadkey_num(index, 23.56f);
   checkval_int(25);
   return 0;
}

TEST(create_table_num_num)
{
   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_num_num(43.3f, 2.718), hs_num_num(23.56f, 1.618));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_num(index, 43.3f);
   checkval_num(2.718);
   loadkey_num(index, 23.56f);
   checkval_num(1.618);
   return 0;
}

TEST(create_table_num_str)
{
   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_num_str(43.3f, "hello"), hs_num_str(23.56f, "world"));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_num(index, 43.3f);
   checkval_str("hello");
   loadkey_num(index, 23.56f);
   checkval_str("world");
   return 0;
}

TEST(create_table_num_tbl)
{
   int oldtop = lua_gettop(L);

   lua_newtable(L);
   store(value1);
   lua_newtable(L);
   store(value2);

   int index = hs_create_table
      (L, hs_num_tbl(43.3f, value1), hs_num_tbl(23.56f, value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(value1);
   load(value2);

   loadkey_num(index, 43.3f);
   checkval_tbl(value1);
   loadkey_num(index, 23.56f);
   checkval_tbl(value2);
   return 0;
}

TEST(create_table_num_func)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('hello')");
   store(value1);
   luaL_loadstring(L, "print('hello')");
   store(value2);

   int index = hs_create_table
      (L, hs_num_func(43.3f, value1), hs_num_func(23.56f, value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(value1);
   load(value2);

   loadkey_num(index, 43.3f);
   checkval_func(value1);
   loadkey_num(index, 23.56f);
   checkval_func(value2);
   return 0;
}

TEST(create_table_num_cfunc)
{

   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_num_cfunc(43.3f, testfunc1), hs_num_cfunc(23.56f, testfunc2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_num(index, 43.3f);
   checkval_cfunc(testfunc1);
   loadkey_num(index, 23.56f);
   checkval_cfunc(testfunc2);
   return 0;
}


TEST(create_table_num_user)
{
   int oldtop = lua_gettop(L);

   lua_newuserdata(L, sizeof(char));
   store(user1);
   lua_newuserdata(L, sizeof(char));
   store(user2);

   int index = hs_create_table
      (L, hs_num_user(43.3f, user1), hs_num_user(23.56f, user2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(user1);
   load(user2);

   loadkey_num(index, 43.3f);
   checkval_user(user1);
   loadkey_num(index, 23.56f);
   checkval_user(user2);
   return 0;
}

TEST(create_table_num_light)
{
   int a1 = 5;
   void *light1 = (void *) &a1;
   int a2 = 6;
   void *light2 = (void *) &a2;

   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_num_light(43.3f, light1), hs_num_light(23.56f, light2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_num(index, 43.3f);
   checkval_light(light1);
   loadkey_num(index, 23.56f);
   checkval_light(light2);
   return 0;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * string keys
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

TEST(create_table_str_bool)
{
   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_str_bool("c:", true), hs_str_bool(":)", true));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_str(index, "c:");
   checkval_bool(true);
   loadkey_str(index, ":)");
   checkval_bool(true);
   return 0;
}

TEST(create_table_str_int)
{
   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_str_int("c:", 15), hs_str_int(":)", 25));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_str(index, "c:");
   checkval_int(15);
   loadkey_str(index, ":)");
   checkval_int(25);
   return 0;
}

TEST(create_table_str_num)
{
   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_str_num("c:", 2.718), hs_str_num(":)", 1.618));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_str(index, "c:");
   checkval_num(2.718);
   loadkey_str(index, ":)");
   checkval_num(1.618);
   return 0;
}

TEST(create_table_str_str)
{
   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_str_str("c:", "hello"), hs_str_str(":)", "world"));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_str(index, "c:");
   checkval_str("hello");
   loadkey_str(index, ":)");
   checkval_str("world");
   return 0;
}

TEST(create_table_str_tbl)
{
   int oldtop = lua_gettop(L);

   lua_newtable(L);
   store(value1);
   lua_newtable(L);
   store(value2);

   int index = hs_create_table
      (L, hs_str_tbl("c:", value1), hs_str_tbl(":)", value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(value1);
   load(value2);

   loadkey_str(index, "c:");
   checkval_tbl(value1);
   loadkey_str(index, ":)");
   checkval_tbl(value2);
   return 0;
}

TEST(create_table_str_func)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('hello')");
   store(value1);
   luaL_loadstring(L, "print('hello')");
   store(value2);

   int index = hs_create_table
      (L, hs_str_func("c:", value1), hs_str_func(":)", value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(value1);
   load(value2);

   loadkey_str(index, "c:");
   checkval_func(value1);
   loadkey_str(index, ":)");
   checkval_func(value2);
   return 0;
}

TEST(create_table_str_cfunc)
{

   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_str_cfunc("c:", testfunc1), hs_str_cfunc(":)", testfunc2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_str(index, "c:");
   checkval_cfunc(testfunc1);
   loadkey_str(index, ":)");
   checkval_cfunc(testfunc2);
   return 0;
}


TEST(create_table_str_user)
{
   int oldtop = lua_gettop(L);

   lua_newuserdata(L, sizeof(char));
   store(user1);
   lua_newuserdata(L, sizeof(char));
   store(user2);

   int index = hs_create_table
      (L, hs_str_user("c:", user1), hs_str_user(":)", user2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(user1);
   load(user2);

   loadkey_str(index, "c:");
   checkval_user(user1);
   loadkey_str(index, ":)");
   checkval_user(user2);
   return 0;
}

TEST(create_table_str_light)
{
   int a1 = 5;
   void *light1 = (void *) &a1;
   int a2 = 6;
   void *light2 = (void *) &a2;

   int oldtop = lua_gettop(L);
   int index = hs_create_table
      (L, hs_str_light("c:", light1), hs_str_light(":)", light2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_str(index, "c:");
   checkval_light(light1);
   loadkey_str(index, ":)");
   checkval_light(light2);
   return 0;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * table keys
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

TEST(create_table_tbl_bool)
{
   int oldtop = lua_gettop(L);

   lua_newtable(L);
   store(tbl1);
   lua_newtable(L);
   store(tbl2);

   int index = hs_create_table
      (L, hs_tbl_bool(tbl1, true), hs_tbl_bool(tbl2, false));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(tbl1);
   load(tbl2);

   loadkey_tbl(index, tbl1);
   checkval_bool(true);
   loadkey_tbl(index, tbl2);
   checkval_bool(false);
   return 0;
}

TEST(create_table_tbl_int)
{
   int oldtop = lua_gettop(L);

   lua_newtable(L);
   store(tbl1);
   lua_newtable(L);
   store(tbl2);

   int index = hs_create_table
      (L, hs_tbl_int(tbl1, 15), hs_tbl_int(tbl2, 25));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(tbl1);
   load(tbl2);

   loadkey_tbl(index, tbl1);
   checkval_int(15);
   loadkey_tbl(index, tbl2);
   checkval_int(25);
   return 0;
}

TEST(create_table_tbl_num)
{
   int oldtop = lua_gettop(L);

   lua_newtable(L);
   store(tbl1);
   lua_newtable(L);
   store(tbl2);

   int index = hs_create_table
      (L, hs_tbl_num(tbl1, 2.718), hs_tbl_num(tbl2, 1.618));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(tbl1);
   load(tbl2);

   loadkey_tbl(index, tbl1);
   checkval_num(2.718);
   loadkey_tbl(index, tbl2);
   checkval_num(1.618);
   return 0;
}

TEST(create_table_tbl_str)
{
   int oldtop = lua_gettop(L);

   lua_newtable(L);
   store(tbl1);
   lua_newtable(L);
   store(tbl2);

   int index = hs_create_table
      (L, hs_tbl_str(tbl1, "hello"), hs_tbl_str(tbl2, "world"));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(tbl1);
   load(tbl2);

   loadkey_tbl(index, tbl1);
   checkval_str("hello");
   loadkey_tbl(index, tbl2);
   checkval_str("world");
   return 0;
}

TEST(create_table_tbl_tbl)
{
   int oldtop = lua_gettop(L);

   lua_newtable(L);
   store(tbl1);
   lua_newtable(L);
   store(tbl2);


   lua_newtable(L);
   store(value1);
   lua_newtable(L);
   store(value2);

   int index = hs_create_table
      (L, hs_tbl_tbl(tbl1, value1), hs_tbl_tbl(tbl2, value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(tbl1);
   load(tbl2);

   load(value1);
   load(value2);

   loadkey_tbl(index, tbl1);
   checkval_tbl(value1);
   loadkey_tbl(index, tbl2);
   checkval_tbl(value2);
   return 0;
}

TEST(create_table_tbl_func)
{
   int oldtop = lua_gettop(L);

   lua_newtable(L);
   store(tbl1);
   lua_newtable(L);
   store(tbl2);


   luaL_loadstring(L, "print('hello')");
   store(value1);
   luaL_loadstring(L, "print('hello')");
   store(value2);

   int index = hs_create_table
      (L, hs_tbl_func(tbl1, value1), hs_tbl_func(tbl2, value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(tbl1);
   load(tbl2);

   load(value1);
   load(value2);

   loadkey_tbl(index, tbl1);
   checkval_func(value1);
   loadkey_tbl(index, tbl2);
   checkval_func(value2);
   return 0;
}

TEST(create_table_tbl_cfunc)
{

   int oldtop = lua_gettop(L);

   lua_newtable(L);
   store(tbl1);
   lua_newtable(L);
   store(tbl2);

   int index = hs_create_table
      (L, hs_tbl_cfunc(tbl1, testfunc1), hs_tbl_cfunc(tbl2, testfunc2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(tbl1);
   load(tbl2);

   loadkey_tbl(index, tbl1);
   checkval_cfunc(testfunc1);
   loadkey_tbl(index, tbl2);
   checkval_cfunc(testfunc2);
   return 0;
}


TEST(create_table_tbl_user)
{
   int oldtop = lua_gettop(L);

   lua_newtable(L);
   store(tbl1);
   lua_newtable(L);
   store(tbl2);


   lua_newuserdata(L, sizeof(char));
   store(user1);
   lua_newuserdata(L, sizeof(char));
   store(user2);

   int index = hs_create_table
      (L, hs_tbl_user(tbl1, user1), hs_tbl_user(tbl2, user2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(tbl1);
   load(tbl2);

   load(user1);
   load(user2);

   loadkey_tbl(index, tbl1);
   checkval_user(user1);
   loadkey_tbl(index, tbl2);
   checkval_user(user2);
   return 0;
}

TEST(create_table_tbl_light)
{
   int a1 = 5;
   void *light1 = (void *) &a1;
   int a2 = 6;
   void *light2 = (void *) &a2;

   int oldtop = lua_gettop(L);

   lua_newtable(L);
   store(tbl1);
   lua_newtable(L);
   store(tbl2);

   int index = hs_create_table
      (L, hs_tbl_light(tbl1, light1), hs_tbl_light(tbl2, light2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(tbl1);
   load(tbl2);

   loadkey_tbl(index, tbl1);
   checkval_light(light1);
   loadkey_tbl(index, tbl2);
   checkval_light(light2);
   return 0;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * function keys
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

TEST(create_table_func_bool)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(func1);
   luaL_loadstring(L, "print('')");
   store(func2);

   int index = hs_create_table
      (L, hs_func_bool(func1, true), hs_func_bool(func2, false));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(func1);
   load(func2);

   loadkey_func(index, func1);
   checkval_bool(true);
   loadkey_func(index, func2);
   checkval_bool(false);
   return 0;
}

TEST(create_table_func_int)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(func1);
   luaL_loadstring(L, "print('')");
   store(func2);

   int index = hs_create_table
      (L, hs_func_int(func1, 15), hs_func_int(func2, 25));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(func1);
   load(func2);

   loadkey_func(index, func1);
   checkval_int(15);
   loadkey_func(index, func2);
   checkval_int(25);
   return 0;
}

TEST(create_table_func_num)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(func1);
   luaL_loadstring(L, "print('')");
   store(func2);

   int index = hs_create_table
      (L, hs_func_num(func1, 2.718), hs_func_num(func2, 1.618));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(func1);
   load(func2);

   loadkey_func(index, func1);
   checkval_num(2.718);
   loadkey_func(index, func2);
   checkval_num(1.618);
   return 0;
}

TEST(create_table_func_str)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(func1);
   luaL_loadstring(L, "print('')");
   store(func2);

   int index = hs_create_table
      (L, hs_func_str(func1, "hello"), hs_func_str(func2, "world"));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(func1);
   load(func2);

   loadkey_func(index, func1);
   checkval_str("hello");
   loadkey_func(index, func2);
   checkval_str("world");
   return 0;
}

TEST(create_table_func_tbl)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(func1);
   luaL_loadstring(L, "print('')");
   store(func2);


   lua_newtable(L);
   store(value1);
   lua_newtable(L);
   store(value2);

   int index = hs_create_table
      (L, hs_func_tbl(func1, value1), hs_func_tbl(func2, value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(func1);
   load(func2);

   load(value1);
   load(value2);

   loadkey_func(index, func1);
   checkval_tbl(value1);
   loadkey_func(index, func2);
   checkval_tbl(value2);
   return 0;
}

TEST(create_table_func_func)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(func1);
   luaL_loadstring(L, "print('')");
   store(func2);


   luaL_loadstring(L, "print('hello')");
   store(value1);
   luaL_loadstring(L, "print('hello')");
   store(value2);

   int index = hs_create_table
      (L, hs_func_func(func1, value1), hs_func_func(func2, value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(func1);
   load(func2);

   load(value1);
   load(value2);

   loadkey_func(index, func1);
   checkval_func(value1);
   loadkey_func(index, func2);
   checkval_func(value2);
   return 0;
}

TEST(create_table_func_cfunc)
{

   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(func1);
   luaL_loadstring(L, "print('')");
   store(func2);

   int index = hs_create_table
      (L, hs_func_cfunc(func1, testfunc1), hs_func_cfunc(func2, testfunc2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(func1);
   load(func2);

   loadkey_func(index, func1);
   checkval_cfunc(testfunc1);
   loadkey_func(index, func2);
   checkval_cfunc(testfunc2);
   return 0;
}


TEST(create_table_func_user)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(func1);
   luaL_loadstring(L, "print('')");
   store(func2);


   lua_newuserdata(L, sizeof(char));
   store(user1);
   lua_newuserdata(L, sizeof(char));
   store(user2);

   int index = hs_create_table
      (L, hs_func_user(func1, user1), hs_func_user(func2, user2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(func1);
   load(func2);

   load(user1);
   load(user2);

   loadkey_func(index, func1);
   checkval_user(user1);
   loadkey_func(index, func2);
   checkval_user(user2);
   return 0;
}

TEST(create_table_func_light)
{
   int a1 = 5;
   void *light1 = (void *) &a1;
   int a2 = 6;
   void *light2 = (void *) &a2;

   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(func1);
   luaL_loadstring(L, "print('')");
   store(func2);

   int index = hs_create_table
      (L, hs_func_light(func1, light1), hs_func_light(func2, light2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(func1);
   load(func2);

   loadkey_func(index, func1);
   checkval_light(light1);
   loadkey_func(index, func2);
   checkval_light(light2);
   return 0;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * C function keys
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/* todo */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * userdata keys
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

TEST(create_table_user_bool)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(user1);
   luaL_loadstring(L, "print('')");
   store(user2);

   int index = hs_create_table
      (L, hs_user_bool(user1, true), hs_user_bool(user2, false));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(user1);
   load(user2);

   loadkey_user(index, user1);
   checkval_bool(true);
   loadkey_user(index, user2);
   checkval_bool(false);
   return 0;
}

TEST(create_table_user_int)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(user1);
   luaL_loadstring(L, "print('')");
   store(user2);

   int index = hs_create_table
      (L, hs_user_int(user1, 15), hs_user_int(user2, 25));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(user1);
   load(user2);

   loadkey_user(index, user1);
   checkval_int(15);
   loadkey_user(index, user2);
   checkval_int(25);
   return 0;
}

TEST(create_table_user_num)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(user1);
   luaL_loadstring(L, "print('')");
   store(user2);

   int index = hs_create_table
      (L, hs_user_num(user1, 2.718), hs_user_num(user2, 1.618));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(user1);
   load(user2);

   loadkey_user(index, user1);
   checkval_num(2.718);
   loadkey_user(index, user2);
   checkval_num(1.618);
   return 0;
}

TEST(create_table_user_str)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(user1);
   luaL_loadstring(L, "print('')");
   store(user2);

   int index = hs_create_table
      (L, hs_user_str(user1, "hello"), hs_user_str(user2, "world"));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(user1);
   load(user2);

   loadkey_user(index, user1);
   checkval_str("hello");
   loadkey_user(index, user2);
   checkval_str("world");
   return 0;
}

TEST(create_table_user_tbl)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(user1);
   luaL_loadstring(L, "print('')");
   store(user2);


   lua_newtable(L);
   store(value1);
   lua_newtable(L);
   store(value2);

   int index = hs_create_table
      (L, hs_user_tbl(user1, value1), hs_user_tbl(user2, value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(user1);
   load(user2);

   load(value1);
   load(value2);

   loadkey_user(index, user1);
   checkval_tbl(value1);
   loadkey_user(index, user2);
   checkval_tbl(value2);
   return 0;
}

TEST(create_table_user_func)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(user1);
   luaL_loadstring(L, "print('')");
   store(user2);


   luaL_loadstring(L, "print('hello')");
   store(value1);
   luaL_loadstring(L, "print('hello')");
   store(value2);

   int index = hs_create_table
      (L, hs_user_func(user1, value1), hs_user_func(user2, value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(user1);
   load(user2);

   load(value1);
   load(value2);

   loadkey_user(index, user1);
   checkval_func(value1);
   loadkey_user(index, user2);
   checkval_func(value2);
   return 0;
}

TEST(create_table_user_cfunc)
{

   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(user1);
   luaL_loadstring(L, "print('')");
   store(user2);

   int index = hs_create_table
      (L, hs_user_cfunc(user1, testfunc1), hs_user_cfunc(user2, testfunc2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(user1);
   load(user2);

   loadkey_user(index, user1);
   checkval_cfunc(testfunc1);
   loadkey_user(index, user2);
   checkval_cfunc(testfunc2);
   return 0;
}


TEST(create_table_user_user)
{
   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(user1);
   luaL_loadstring(L, "print('')");
   store(user2);


   lua_newuserdata(L, sizeof(char));
   store(value1);
   lua_newuserdata(L, sizeof(char));
   store(value2);

   int index = hs_create_table
      (L, hs_user_user(user1, value1), hs_user_user(user2, value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(user1);
   load(user2);

   load(value1);
   load(value2);

   loadkey_user(index, user1);
   checkval_user(value1);
   loadkey_user(index, user2);
   checkval_user(value2);
   return 0;
}

TEST(create_table_user_light)
{
   int a1 = 5;
   void *light1 = (void *) &a1;
   int a2 = 6;
   void *light2 = (void *) &a2;

   int oldtop = lua_gettop(L);

   luaL_loadstring(L, "print('')");
   store(user1);
   luaL_loadstring(L, "print('')");
   store(user2);

   int index = hs_create_table
      (L, hs_user_light(user1, light1), hs_user_light(user2, light2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(user1);
   load(user2);

   loadkey_user(index, user1);
   checkval_light(light1);
   loadkey_user(index, user2);
   checkval_light(light2);
   return 0;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * light userdata keys
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

TEST(create_table_light_bool)
{
   int oldtop = lua_gettop(L);

   int l1 = 5;
   int l2 = 6;
   void *light1 = (void *) &l1;
   void *light2 = (void *) &l2;

   int index = hs_create_table
      (L, hs_light_bool(light1, true), hs_light_bool(light2, true));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_light(index, light1);
   checkval_bool(true);
   loadkey_light(index, light2);
   checkval_bool(true);
   return 0;
}

TEST(create_table_light_int)
{
   int oldtop = lua_gettop(L);

   int l1 = 5;
   int l2 = 6;
   void *light1 = (void *) &l1;
   void *light2 = (void *) &l2;

   int index = hs_create_table
      (L, hs_light_int(light1, 15), hs_light_int(light2, 25));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_light(index, light1);
   checkval_int(15);
   loadkey_light(index, light2);
   checkval_int(25);
   return 0;
}

TEST(create_table_light_num)
{
   int oldtop = lua_gettop(L);

   int l1 = 5;
   int l2 = 6;
   void *light1 = (void *) &l1;
   void *light2 = (void *) &l2;

   int index = hs_create_table
      (L, hs_light_num(light1, 2.718), hs_light_num(light2, 1.618));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_light(index, light1);
   checkval_num(2.718);
   loadkey_light(index, light2);
   checkval_num(1.618);
   return 0;
}

TEST(create_table_light_str)
{
   int oldtop = lua_gettop(L);

   int l1 = 5;
   int l2 = 6;
   void *light1 = (void *) &l1;
   void *light2 = (void *) &l2;

   int index = hs_create_table
      (L, hs_light_str(light1, "hello"), hs_light_str(light2, "world"));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_light(index, light1);
   checkval_str("hello");
   loadkey_light(index, light2);
   checkval_str("world");
   return 0;
}

TEST(create_table_light_tbl)
{
   int oldtop = lua_gettop(L);

   int l1 = 5;
   int l2 = 6;
   void *light1 = (void *) &l1;
   void *light2 = (void *) &l2;

   lua_newtable(L);
   store(value1);
   lua_newtable(L);
   store(value2);

   int index = hs_create_table
      (L, hs_light_tbl(light1, value1), hs_light_tbl(light2, value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(value1);
   load(value2);

   loadkey_light(index, light1);
   checkval_tbl(value1);
   loadkey_light(index, light2);
   checkval_tbl(value2);
   return 0;
}

TEST(create_table_light_func)
{
   int oldtop = lua_gettop(L);

   int l1 = 5;
   int l2 = 6;
   void *light1 = (void *) &l1;
   void *light2 = (void *) &l2;

   luaL_loadstring(L, "print('hello')");
   store(value1);
   luaL_loadstring(L, "print('hello')");
   store(value2);

   int index = hs_create_table
      (L, hs_light_func(light1, value1), hs_light_func(light2, value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(value1);
   load(value2);

   loadkey_light(index, light1);
   checkval_func(value1);
   loadkey_light(index, light2);
   checkval_func(value2);
   return 0;
}

TEST(create_table_light_cfunc)
{

   int oldtop = lua_gettop(L);

   int l1 = 5;
   int l2 = 6;
   void *light1 = (void *) &l1;
   void *light2 = (void *) &l2;

   int index = hs_create_table
      (L, hs_light_cfunc(light1, testfunc1), hs_light_cfunc(light2, testfunc2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_light(index, light1);
   checkval_cfunc(testfunc1);
   loadkey_light(index, light2);
   checkval_cfunc(testfunc2);
   return 0;
}


TEST(create_table_light_user)
{
   int oldtop = lua_gettop(L);

   int l1 = 5;
   int l2 = 6;
   void *light1 = (void *) &l1;
   void *light2 = (void *) &l2;

   lua_newuserdata(L, sizeof(char));
   store(user1);
   lua_newuserdata(L, sizeof(char));
   store(user2);

   int index = hs_create_table
      (L, hs_light_user(light1, user1), hs_light_user(light2, user2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   load(user1);
   load(user2);

   loadkey_light(index, light1);
   checkval_user(user1);
   loadkey_light(index, light2);
   checkval_user(user2);
   return 0;
}

TEST(create_table_light_light)
{
   int oldtop = lua_gettop(L);

   int l1 = 5;
   int l2 = 6;
   void *light1 = (void *) &l1;
   void *light2 = (void *) &l2;

   int a1 = 5;
   void *value1 = (void *) &a1;
   int a2 = 6;
   void *value2 = (void *) &a2;

   int index = hs_create_table
      (L, hs_light_light(light1, value1), hs_light_light(light2, value2));
   mu_assert_equal(oldtop + 1, lua_gettop(L));
   mu_assert_equal(index, lua_gettop(L));
   mu_assert_equal(lua_type(L, index), LUA_TTABLE);

   loadkey_light(index, light1);
   checkval_light(value1);
   loadkey_light(index, light2);
   checkval_light(value2);
   return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * nested tables
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

TEST(create_nested_table)
{
   int index = hs_create_table
      (L,
       hs_str_tbl("sub1", hs_create_table(L, hs_str_int("five", 5))),
       hs_str_tbl("sub2", hs_create_table(L, hs_str_int("six", 6)))
       );

   mu_assert_equal(lua_gettop(L), 1);


   lua_getfield(L, index, "sub1");
   mu_assert("'sub1' is not a table!", lua_istable(L, -1));
   lua_getfield(L, -1, "five");
   mu_assert("'sub1.five' is not a number!", lua_isnumber(L, -1));
   mu_assert_equal(lua_tointeger(L, -1), 5);

   lua_pop(L, 2);

   lua_getfield(L, index, "sub2");
   mu_assert("'sub2' is not a table!", lua_istable(L, -1));
   lua_getfield(L, -1, "six");
   mu_assert("'sub2.six' is not a number!", lua_isnumber(L, -1));
   mu_assert_equal(lua_tointeger(L, -1), 6);

   return 0;
}

TEST(create_tree)
{
   /*
    * { 0={ 0={ 0=0, 1=1},
    *       1={ 0=0, 1=1},
    *     },
    *   1={ 0={ 0=0, 1=1},
    *       1={ 0=0, 1=1},
    *     },
    * }
    */
   int index = hs_create_table
      (L,
       hs_int_tbl(0,
		  hs_create_table
		  (L,
		   hs_int_tbl(0,
			      hs_create_table
			      (L,
			       hs_int_int(0, 0),
			       hs_int_int(1, 1)
			       )),
		   hs_int_tbl(1,
			      hs_create_table
			      (L,
			       hs_int_int(0, 0),
			       hs_int_int(1, 1)
			       )),
		   )),
       hs_int_tbl(1,
		  hs_create_table
		  (L,
		   hs_int_tbl(0,
			      hs_create_table
			      (L,
			       hs_int_int(0, 0),
			       hs_int_int(1, 1)
			       )),
		   hs_int_tbl(1,
			      hs_create_table
			      (L,
			       hs_int_int(0, 0),
			       hs_int_int(1, 1)
			       )),
		   ))
       );

   mu_assert_equal(lua_gettop(L), 1);

   lua_rawgeti(L, index, 0);
   mu_assert("tbl[0] is not a table!", lua_istable(L, -1));
   lua_rawgeti(L, -1, 0);
   mu_assert("tbl[0][0] is not a table!", lua_istable(L, -1));
   lua_rawgeti(L, -1, 0);
   mu_assert("tbl[0][0][0] is not a number!", lua_isnumber(L, -1));
   lua_pop(L, 3);

   lua_rawgeti(L, index, 0);
   mu_assert("tbl[0] is not a table!", lua_istable(L, -1));
   lua_rawgeti(L, -1, 0);
   mu_assert("tbl[0][0] is not a table!", lua_istable(L, -1));
   lua_rawgeti(L, -1, 1);
   mu_assert("tbl[0][0][1] is not a number!", lua_isnumber(L, -1));
   lua_pop(L, 3);

   lua_rawgeti(L, index, 0);
   mu_assert("tbl[0] is not a table!", lua_istable(L, -1));
   lua_rawgeti(L, -1, 1);
   mu_assert("tbl[0][1] is not a table!", lua_istable(L, -1));
   lua_rawgeti(L, -1, 0);
   mu_assert("tbl[0][1][0] is not a number!", lua_isnumber(L, -1));
   lua_pop(L, 3);

   lua_rawgeti(L, index, 0);
   mu_assert("tbl[0] is not a table!", lua_istable(L, -1));
   lua_rawgeti(L, -1, 1);
   mu_assert("tbl[0][1] is not a table!", lua_istable(L, -1));
   lua_rawgeti(L, -1, 1);
   mu_assert("tbl[0][1][1] is not a number!", lua_isnumber(L, -1));
   lua_pop(L, 3);

   lua_rawgeti(L, index, 1);
   mu_assert("tbl[1] is not a table!", lua_istable(L, -1));
   lua_rawgeti(L, -1, 0);
   mu_assert("tbl[1][0] is not a table!", lua_istable(L, -1));
   lua_rawgeti(L, -1, 0);
   mu_assert("tbl[1][0][0] is not a number!", lua_isnumber(L, -1));
   lua_pop(L, 3);

   lua_rawgeti(L, index, 1);
   mu_assert("tbl[1] is not a table!", lua_istable(L, -1));
   lua_rawgeti(L, -1, 0);
   mu_assert("tbl[1][0] is not a table!", lua_istable(L, -1));
   lua_rawgeti(L, -1, 1);
   mu_assert("tbl[1][0][1] is not a number!", lua_isnumber(L, -1));
   lua_pop(L, 3);

   lua_rawgeti(L, index, 1);
   mu_assert("tbl[1] is not a table!", lua_istable(L, -1));
   lua_rawgeti(L, -1, 1);
   mu_assert("tbl[1][1] is not a table!", lua_istable(L, -1));
   lua_rawgeti(L, -1, 0);
   mu_assert("tbl[1][1][0] is not a number!", lua_isnumber(L, -1));
   lua_pop(L, 3);

   lua_rawgeti(L, index, 1);
   mu_assert("tbl[1] is not a table!", lua_istable(L, -1));
   lua_rawgeti(L, -1, 1);
   mu_assert("tbl[1][1] is not a table!", lua_istable(L, -1));
   lua_rawgeti(L, -1, 1);
   mu_assert("tbl[1][1][1] is not a number!", lua_isnumber(L, -1));
   lua_pop(L, 3);

   return 0;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * test suite
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void hs_create_table_tests()
{
   printf("running hs_create_table() tests...\n");

   mu_run_test("return correct stack index", table_correct_index);

   /* boolean keys */
   mu_run_test("create table with boolean keys and boolean values",
	       create_table_bool_bool);
   mu_run_test("create table with boolean keys and integer values", \
	       create_table_bool_int);
   mu_run_test("create table with boolean keys and number values", \
	       create_table_bool_num);
   mu_run_test("create table with boolean keys and string values", \
	       create_table_bool_str);
   mu_run_test("create table with boolean keys and table values",	\
	       create_table_bool_tbl);
   mu_run_test("create table with boolean keys and function values", \
	       create_table_bool_func);
   mu_run_test("create table with boolean keys and C function values", \
	       create_table_bool_cfunc);
   mu_run_test("create table with boolean keys and userdata values", \
	       create_table_bool_user);
   mu_run_test("create table with boolean keys and light userdata values",		\
	       create_table_bool_light);

   /* integer keys */
   mu_run_test("create table with integer keys and boolean values",
	       create_table_int_bool);
   mu_run_test("create table with integer keys and integer values", \
	       create_table_int_int);
   mu_run_test("create table with integer keys and number values", \
	       create_table_int_num);
   mu_run_test("create table with integer keys and string values", \
	       create_table_int_str);
   mu_run_test("create table with integer keys and table values",	\
	       create_table_int_tbl);
   mu_run_test("create table with integer keys and function values", \
	       create_table_int_func);
   mu_run_test("create table with integer keys and C function values", \
	       create_table_int_cfunc);
   mu_run_test("create table with integer keys and userdata values", \
	       create_table_int_user);
   mu_run_test("create table with integer keys and light userdata values",		\
	       create_table_int_light);

   /* number keys */
   mu_run_test("create table with number keys and boolean values",
	       create_table_num_bool);
   mu_run_test("create table with number keys and integer values", \
	       create_table_num_int);
   mu_run_test("create table with number keys and number values", \
	       create_table_num_num);
   mu_run_test("create table with number keys and string values", \
	       create_table_num_str);
   mu_run_test("create table with number keys and table values",	\
	       create_table_num_tbl);
   mu_run_test("create table with number keys and function values", \
	       create_table_num_func);
   mu_run_test("create table with number keys and C function values", \
	       create_table_num_cfunc);
   mu_run_test("create table with number keys and userdata values", \
	       create_table_num_user);
   mu_run_test("create table with number keys and light userdata values",		\
	       create_table_num_light);

   /* string keys */
   mu_run_test("create table with string keys and boolean values",
	       create_table_str_bool);
   mu_run_test("create table with string keys and integer values", \
	       create_table_str_int);
   mu_run_test("create table with string keys and number values", \
	       create_table_str_num);
   mu_run_test("create table with string keys and string values", \
	       create_table_str_str);
   mu_run_test("create table with string keys and table values",	\
	       create_table_str_tbl);
   mu_run_test("create table with string keys and function values", \
	       create_table_str_func);
   mu_run_test("create table with string keys and C function values", \
	       create_table_str_cfunc);
   mu_run_test("create table with string keys and userdata values", \
	       create_table_str_user);
   mu_run_test("create table with string keys and light userdata values",		\
	       create_table_str_light);

   /* table keys */
   mu_run_test("create table with table keys and boolean values",
	       create_table_tbl_bool);
   mu_run_test("create table with table keys and integer values", \
	       create_table_tbl_int);
   mu_run_test("create table with table keys and number values", \
	       create_table_tbl_num);
   mu_run_test("create table with table keys and string values", \
	       create_table_tbl_str);
   mu_run_test("create table with table keys and table values",	\
	       create_table_tbl_tbl);
   mu_run_test("create table with table keys and function values", \
	       create_table_tbl_func);
   mu_run_test("create table with table keys and C function values", \
	       create_table_tbl_cfunc);
   mu_run_test("create table with table keys and userdata values", \
	       create_table_tbl_user);
   mu_run_test("create table with table keys and light userdata values",		\
	       create_table_tbl_light);

   /* function keys */
   mu_run_test("create table with function keys and boolean values",
	       create_table_func_bool);
   mu_run_test("create table with function keys and integer values", \
	       create_table_func_int);
   mu_run_test("create table with function keys and number values", \
	       create_table_func_num);
   mu_run_test("create table with function keys and string values", \
	       create_table_func_str);
   mu_run_test("create table with function keys and table values",	\
	       create_table_func_tbl);
   mu_run_test("create table with function keys and function values", \
	       create_table_func_func);
   mu_run_test("create table with function keys and C function values", \
	       create_table_func_cfunc);
   mu_run_test("create table with function keys and userdata values", \
	       create_table_func_user);
   mu_run_test("create table with function keys and light userdata values",		\
	       create_table_func_light);

   /* C function keys /
   mu_run_test("create table with C function keys and boolean values",
	       create_table_cfunc_bool);
   mu_run_test("create table with C function keys and integer values", \
	       create_table_cfunc_int);
   mu_run_test("create table with C function keys and number values", \
	       create_table_cfunc_num);
   mu_run_test("create table with C function keys and string values", \
	       create_table_cfunc_str);
   mu_run_test("create table with C function keys and table values",	\
	       create_table_cfunc_tbl);
   mu_run_test("create table with C function keys and function values", \
	       create_table_cfunc_func);
   mu_run_test("create table with C function keys and C function values", \
	       create_table_cfunc_cfunc);
   mu_run_test("create table with C function keys and userdata values", \
	       create_table_cfunc_user);
   mu_run_test("create table with C function keys and light userdata values",		\
	       create_table_cfunc_light);

   /* userdata keys */
   mu_run_test("create table with userdata keys and boolean values",
	       create_table_user_bool);
   mu_run_test("create table with userdata keys and integer values", \
	       create_table_user_int);
   mu_run_test("create table with userdata keys and number values", \
	       create_table_user_num);
   mu_run_test("create table with userdata keys and string values", \
	       create_table_user_str);
   mu_run_test("create table with userdata keys and table values",	\
	       create_table_user_tbl);
   mu_run_test("create table with userdata keys and function values", \
	       create_table_user_func);
   mu_run_test("create table with userdata keys and C function values", \
	       create_table_user_cfunc);
   mu_run_test("create table with userdata keys and userdata values", \
	       create_table_user_user);
   mu_run_test("create table with userdata keys and light userdata values",		\
	       create_table_user_light);

   /* light userdata keys */
   mu_run_test("create table with light userdata keys and boolean values",
	       create_table_light_bool);
   mu_run_test("create table with light userdata keys and integer values", \
	       create_table_light_int);
   mu_run_test("create table with light userdata keys and number values", \
	       create_table_light_num);
   mu_run_test("create table with light userdata keys and string values", \
	       create_table_light_str);
   mu_run_test("create table with light userdata keys and table values",	\
	       create_table_light_tbl);
   mu_run_test("create table with light userdata keys and function values", \
	       create_table_light_func);
   mu_run_test("create table with light userdata keys and C function values", \
	       create_table_light_cfunc);
   mu_run_test("create table with light userdata keys and userdata values", \
	       create_table_light_user);
   mu_run_test("create table with light userdata keys and light userdata values",		\
	       create_table_light_light);

   mu_run_test("create nested tables", create_nested_table);
   mu_run_test("create tree of nested tables", create_tree);
}
