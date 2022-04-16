#include "hs_tests.h"

#define process()							\
   bool boolean = false;						\
   lua_Integer integer = 0;							\
   lua_Number number = 0;							\
   const char *string = "";						\
   hs_process_table(L, -1,						\
		    hs_process_bool("boolean", hs_pt_set_boolean, &boolean), \
		    hs_process_int("integer", hs_pt_set_integer, &integer), \
		    hs_process_num("number", hs_pt_set_number, &number), \
		    hs_process_str("string", hs_pt_set_string, &string));

#define test_set_boolean() do { mu_assert("failed to set boolean!", boolean == true); } while(0);
#define test_noset_boolean() do { mu_assert("incorrectly set boolean!", boolean == false); } while(0);
#define test_set_integer() do { mu_assert("failed to set integer!", integer == 14); } while(0);
#define test_noset_integer() do { mu_assert("incorrectly set integer!", integer == 0); } while(0);
#define test_set_number() do { mu_assert("failed to set number!", number == 44.66); } while(0);
#define test_noset_number() do { mu_assert("incorrectly set number!", number == 0); } while(0);
#define test_set_string() \
    do { mu_assert("failed to set string!", strcmp(string, "c: c: c:") == 0); } while(0);
#define test_noset_string() \
    do { mu_assert("incorrectly set string!", strcmp(string, "") == 0); } while(0);
    

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * tests for all 16 possible combinations of one table containing one
 * boolean, integer, number, and string key each.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */


TEST(process_none)
{
    lua_createtable(L, 0, 0);

    process();

    test_noset_boolean();
    test_noset_integer();
    test_noset_number();
    test_noset_string();

    return 0;
}
TEST(process_bool)
{
    lua_createtable(L, 0, 0);
    lua_pushboolean(L, true);
    lua_setfield(L, -2, "boolean");

    process();

    test_set_boolean();
    test_noset_integer();
    test_noset_number();
    test_noset_string();
    
    return 0;
}
TEST(process_int)
{
    lua_createtable(L, 0, 0);

    lua_pushinteger(L, 14);
    lua_setfield(L, -2, "integer");

    process();

    test_noset_boolean();
    test_set_integer();
    test_noset_number();
    test_noset_string();
    
    return 0;
}
TEST(process_bool_int)
{
    lua_createtable(L, 0, 0);
    lua_pushboolean(L, true);
    lua_setfield(L, -2, "boolean");

    lua_pushinteger(L, 14);
    lua_setfield(L, -2, "integer");

    process();

    test_set_boolean();
    test_set_integer();
    test_noset_number();
    test_noset_string();
    
    return 0;
}
TEST(process_number)
{
    lua_createtable(L, 0, 0);
    lua_pushnumber(L, 44.66);
    lua_setfield(L, -2, "number");

    process();

    test_noset_boolean();
    test_noset_integer();
    test_set_number();
    test_noset_string();
    
    return 0;
}
TEST(process_bool_number)
{
    lua_createtable(L, 0, 0);
    lua_pushboolean(L, true);
    lua_setfield(L, -2, "boolean");

    lua_pushnumber(L, 44.66);
    lua_setfield(L, -2, "number");

    process();

    test_set_boolean();
    test_noset_integer();
    test_set_number();
    test_noset_string();
    
    return 0;
}
TEST(process_int_number)
{
    lua_createtable(L, 0, 0);

    lua_pushinteger(L, 14);
    lua_setfield(L, -2, "integer");

    lua_pushnumber(L, 44.66);
    lua_setfield(L, -2, "number");

    process();

    test_noset_boolean();
    test_set_integer();
    test_set_number();
    test_noset_string();
    
    return 0;
}
TEST(process_bool_int_number)
{
    lua_createtable(L, 0, 0);
    lua_pushboolean(L, true);
    lua_setfield(L, -2, "boolean");

    lua_pushinteger(L, 14);
    lua_setfield(L, -2, "integer");

    lua_pushnumber(L, 44.66);
    lua_setfield(L, -2, "number");

    process();

    test_set_boolean();
    test_set_integer();
    test_set_number();
    test_noset_string();
    
    return 0;
}
TEST(process_string)
{
    lua_createtable(L, 0, 0);

    lua_pushstring(L, "c: c: c:");
    lua_setfield(L, -2, "string");

    process();

    test_noset_boolean();
    test_noset_integer();
    test_noset_number();
    test_set_string();

    return 0;
}
TEST(process_bool_string)
{
    lua_createtable(L, 0, 0);
    lua_pushboolean(L, true);
    lua_setfield(L, -2, "boolean");

    lua_pushstring(L, "c: c: c:");
    lua_setfield(L, -2, "string");

    process();

    test_set_boolean();
    test_noset_integer();
    test_noset_number();
    test_set_string();
    
    return 0;
}
TEST(process_int_string)
{
    lua_createtable(L, 0, 0);

    lua_pushinteger(L, 14);
    lua_setfield(L, -2, "integer");

    lua_pushstring(L, "c: c: c:");
    lua_setfield(L, -2, "string");

    process();

    test_noset_boolean();
    test_set_integer();
    test_noset_number();
    test_set_string();
    
    return 0;
}
TEST(process_bool_int_string)
{
    lua_createtable(L, 0, 0);
    lua_pushboolean(L, true);
    lua_setfield(L, -2, "boolean");

    lua_pushinteger(L, 14);
    lua_setfield(L, -2, "integer");

    lua_pushstring(L, "c: c: c:");
    lua_setfield(L, -2, "string");

    process();

    test_set_boolean();
    test_set_integer();
    test_noset_number();
    test_set_string();
    
    return 0;
}
TEST(process_number_string)
{
    lua_createtable(L, 0, 0);
    lua_pushnumber(L, 44.66);
    lua_setfield(L, -2, "number");

    lua_pushstring(L, "c: c: c:");
    lua_setfield(L, -2, "string");

    process();

    test_noset_boolean();
    test_noset_integer();
    test_set_number();
    test_set_string();
    
    return 0;
}
TEST(process_bool_number_string)
{
    lua_createtable(L, 0, 0);
    lua_pushboolean(L, true);
    lua_setfield(L, -2, "boolean");

    lua_pushnumber(L, 44.66);
    lua_setfield(L, -2, "number");

    lua_pushstring(L, "c: c: c:");
    lua_setfield(L, -2, "string");

    process();

    test_set_boolean();
    test_noset_integer();
    test_set_number();
    test_set_string();
    
    return 0;
}
TEST(process_int_number_string)
{
    lua_createtable(L, 0, 0);

    lua_pushinteger(L, 14);
    lua_setfield(L, -2, "integer");

    lua_pushnumber(L, 44.66);
    lua_setfield(L, -2, "number");

    lua_pushstring(L, "c: c: c:");
    lua_setfield(L, -2, "string");

    process();

    test_noset_boolean();
    test_set_integer();
    test_set_number();
    test_set_string();
    
    return 0;
}
TEST(process_all)
{
    lua_createtable(L, 0, 0);
    lua_pushboolean(L, true);
    lua_setfield(L, -2, "boolean");

    lua_pushinteger(L, 14);
    lua_setfield(L, -2, "integer");

    lua_pushnumber(L, 44.66);
    lua_setfield(L, -2, "number");

    lua_pushstring(L, "c: c: c:");
    lua_setfield(L, -2, "string");

    process();

    test_set_boolean();
    test_set_integer();
    test_set_number();
    test_set_string();
    
    return 0;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * tests for four keys of the same type
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

TEST(process_four_bools)
{
    lua_createtable(L, 0, 4);

    lua_pushboolean(L, true);
    lua_setfield(L, -2, "b1");

    lua_pushboolean(L, false);
    lua_setfield(L, -2, "b2");

    lua_pushboolean(L, false);
    lua_setfield(L, -2, "b3");

    lua_pushboolean(L, true);
    lua_setfield(L, -2, "b4");

    bool b1 = false;
    bool b2 = true;
    bool b3 = true;
    bool b4 = false;
    
    hs_process_table(L, -1,
		     hs_process_bool("b1", hs_pt_set_boolean, &b1),
		     hs_process_bool("b2", hs_pt_set_boolean, &b2),
		     hs_process_bool("b3", hs_pt_set_boolean, &b3),
		     hs_process_bool("b4", hs_pt_set_boolean, &b4),
		     );

    mu_assert("b1 was not correctly set!", b1 == true);
    mu_assert("b2 was not correctly set!", b2 == false);
    mu_assert("b3 was not correctly set!", b3 == false);
    mu_assert("b4 was not correctly set!", b4 == true);
    return 0;
}
TEST(process_four_ints)
{
    lua_createtable(L, 0, 4);

    lua_pushinteger(L, 2);
    lua_setfield(L, -2, "j1");

    lua_pushinteger(L, 1);
    lua_setfield(L, -2, "j2");

    lua_pushinteger(L, 3);
    lua_setfield(L, -2, "j3");

    lua_pushinteger(L, 4);
    lua_setfield(L, -2, "j4");

    lua_Integer j1 = 0;
    lua_Integer j2 = 0;
    lua_Integer j3 = 0;
    lua_Integer j4 = 0;
    
    hs_process_table(L, -1,
		     hs_process_int("j1", hs_pt_set_integer, &j1),
		     hs_process_int("j2", hs_pt_set_integer, &j2),
		     hs_process_int("j3", hs_pt_set_integer, &j3),
		     hs_process_int("j4", hs_pt_set_integer, &j4));

    mu_assert("j1 was not correctly set!", j1 == 2);
    mu_assert("j2 was not correctly set!", j2 == 1);
    mu_assert("j3 was not correctly set!", j3 == 3);
    mu_assert("j4 was not correctly set!", j4 == 4);
    return 0;
}
TEST(process_four_numbers)
{
    lua_createtable(L, 0, 4);
    
    lua_pushnumber(L, 3.141);
    lua_setfield(L, -2, "n1");

    lua_pushnumber(L, 2.718);
    lua_setfield(L, -2, "n2");

    lua_pushnumber(L, 1.618);
    lua_setfield(L, -2, "n3");

    lua_pushnumber(L, 4.669);
    lua_setfield(L, -2, "n4");

    lua_Number n1 = 0;
    lua_Number n2 = 0;
    lua_Number n3 = 0;
    lua_Number n4 = 0;
 
    hs_process_table(L, -1,
		     hs_process_num("n1", hs_pt_set_number, &n1),
		     hs_process_num("n2", hs_pt_set_number, &n2),
		     hs_process_num("n3", hs_pt_set_number, &n3),
		     hs_process_num("n4", hs_pt_set_number, &n4));
		     
    mu_assert("n1 was not correctly set!", n1 == 3.141);
    mu_assert("n2 was not correctly set!", n2 == 2.718);
    mu_assert("n3 was not correctly set!", n3 == 1.618);
    mu_assert("n4 was not correctly set!", n4 == 4.669);
    return 0;
}
TEST(process_four_strings)
{
    lua_createtable(L, 0, 4);

    lua_pushstring(L, "When meditation is mastered, The mind is unwavering like the Flame of a lamp in a windless place." );
    lua_setfield(L, -2, "s1");

    lua_pushstring(L, "In the still mind, In the depths of meditation, The Self reveals itself.");
    lua_setfield(L, -2, "s2");

    lua_pushstring(L, "Beholding the Self By means of the Self, An aspirant knows the Joy and peace of complete fulfillment.");
    lua_setfield(L, -2, "s3");

    lua_pushstring(L, "Having attained that Abiding joy beyond the senses, Revealed in the stilled mind, He never swerves from the eternal truth.");
    lua_setfield(L, -2, "s4");

    const char *s1 = "";
    const char *s2 = "";
    const char *s3 = "";
    const char *s4 = "";
    
    hs_process_table(L, -1,
		     hs_process_str("s1", hs_pt_set_string, &s1),
		     hs_process_str("s2", hs_pt_set_string, &s2),
		     hs_process_str("s3", hs_pt_set_string, &s3),
		     hs_process_str("s4", hs_pt_set_string, &s4));
		     
    mu_assert("s1 was not correctly set!",
	      strcmp(s1, "When meditation is mastered, The mind is unwavering like the Flame of a lamp in a windless place.") == 0);
    mu_assert("s2 was not correctly set!",
	      strcmp(s2, "In the still mind, In the depths of meditation, The Self reveals itself.") == 0);
    mu_assert("s3 was not correctly set!",
	      strcmp(s3, "Beholding the Self By means of the Self, An aspirant knows the Joy and peace of complete fulfillment.") == 0);
    mu_assert("s4 was not correctly set!",
	      strcmp(s4, "Having attained that Abiding joy beyond the senses, Revealed in the stilled mind, He never swerves from the eternal truth.") == 0);
    return 0;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * test suite
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

void hs_process_table_tests()
{
    printf("running hs_process_table() tests...\n");
    
    mu_run_test("process empty table", process_none);
    mu_run_test("process boolean only", process_bool);
    mu_run_test("process integer only", process_int);
    mu_run_test("process boolean and integer", process_bool_int);
    mu_run_test("process number only", process_number);
    mu_run_test("process boolean and number", process_bool_number);
    mu_run_test("process integer and number", process_int_number);
    mu_run_test("process boolean, integer, and number", process_bool_int_number);
    
    mu_run_test("process string only", process_string);
    mu_run_test("process boolean and string", process_bool_string);
    mu_run_test("process integer and string", process_int_string);
    mu_run_test("process boolean, integer, and string", process_bool_int_string);
    mu_run_test("process number and string", process_number_string);
    mu_run_test("process boolean, number, and string", process_bool_number_string);
    mu_run_test("process integer,  number, and string", process_int_number_string);
    mu_run_test("process basic types", process_all);

    mu_run_test("process four booleans", process_four_bools);
    mu_run_test("process four integers", process_four_ints);
    mu_run_test("process four numbers", process_four_numbers);
    mu_run_test("process four strings", process_four_strings);
}
