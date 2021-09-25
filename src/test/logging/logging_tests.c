#include <stdio.h>
#include <stdlib.h>

#include "test/minunit.h"
#include "test/suites.h"

#include "logging/logging.h"


/* test declarations */

mu_test test_log_get_level();
mu_test test_log_set_defaults();
mu_test test_log_debug();
mu_test test_log_info();
mu_test test_log_warn();
mu_test test_log_error();
mu_test test_log_fatal();


/* main suite */

void honey_logging_tests()
{
   mu_run_test("get log level strings", test_log_get_level);
   mu_run_test("print debug message", test_log_debug);
   mu_run_test("print info message", test_log_info);
   mu_run_test("print warning message", test_log_warn);
   mu_run_test("print error message", test_log_error);
   mu_run_test("print fatal error message", test_log_fatal);
}


/* ~~~~~~~~ test definitions ~~~~~~~~ */

mu_test test_log_get_level()
{
   honey_log_set_level(DEBUG);
   mu_assert_equal(DEBUG, honey_log_get_level());
   mu_assert_streq("DEBUG", honey_log_level_str());

   honey_log_set_level(INFO);
   mu_assert_equal(INFO, honey_log_get_level());
   mu_assert_streq("INFO", honey_log_level_str());

   honey_log_set_level(WARN);
   mu_assert_equal(WARN, honey_log_get_level());
   mu_assert_streq("WARN", honey_log_level_str());

   honey_log_set_level(ERROR);
   mu_assert_equal(ERROR, honey_log_get_level());
   mu_assert_streq("ERROR", honey_log_level_str());

   honey_log_set_level(FATAL);
   mu_assert_equal(FATAL, honey_log_get_level());
   mu_assert_streq("FATAL", honey_log_level_str());

   return 0;
}


mu_test test_log_debug()
{
   FILE *stream;
   char *buffer;
   size_t len;

   stream = open_memstream(&buffer, &len);
   mu_assert_unequal(stream, NULL);

   honey_log_set_file(stream);
   mu_assert_equal(honey_log_get_file(), stream);
   
   honey_log_set_level(FATAL);
   mu_assert_equal(honey_log_get_level(), FATAL);

   honey_debug("hello, %s!", "world");
   fflush(stream);
   mu_assert_streq(buffer, "");

   honey_log_set_level(DEBUG);
   mu_assert_equal(honey_log_get_level(), DEBUG);
   
   honey_debug("hello, %s!", "world");
   fclose(stream);
   mu_assert_streq(buffer, "[DEBUG] hello, world!");
   free(buffer);

   return 0;
}


mu_test test_log_info()
{
   FILE *stream;
   char *buffer;
   size_t len;

   stream = open_memstream(&buffer, &len);
   mu_assert_unequal(stream, NULL);

   honey_log_set_file(stream);
   mu_assert_equal(honey_log_get_file(), stream);
   
   honey_log_set_level(FATAL);
   mu_assert_equal(honey_log_get_level(), FATAL);

   honey_info("hello, %s!", "world");
   fflush(stream);
   mu_assert_streq(buffer, "");

   honey_log_set_level(INFO);
   mu_assert_equal(honey_log_get_level(), INFO);
   
   honey_info("hello, %s!", "world");
   fclose(stream);
   mu_assert_streq(buffer, "[INFO]  hello, world!");
   free(buffer);

   return 0;
}


mu_test test_log_warn()
{
   FILE *stream;
   char *buffer;
   size_t len;

   stream = open_memstream(&buffer, &len);
   mu_assert_unequal(stream, NULL);

   honey_log_set_file(stream);
   mu_assert_equal(honey_log_get_file(), stream);
   
   honey_log_set_level(FATAL);
   mu_assert_equal(honey_log_get_level(), FATAL);

   honey_warn("hello, %s!", "world");
   fflush(stream);
   mu_assert_streq(buffer, "");

   honey_log_set_level(WARN);
   mu_assert_equal(honey_log_get_level(), WARN);
   
   honey_warn("hello, %s!", "world");
   fclose(stream);
   mu_assert_streq(buffer, "[WARN]  hello, world!");
   free(buffer);

   return 0;
}


mu_test test_log_error()
{
   FILE *stream;
   char *buffer;
   size_t len;

   stream = open_memstream(&buffer, &len);
   mu_assert_unequal(stream, NULL);

   honey_log_set_file(stream);
   mu_assert_equal(honey_log_get_file(), stream);
   
   honey_log_set_level(FATAL);
   mu_assert_equal(honey_log_get_level(), FATAL);

   honey_error("hello, %s!", "world");
   fflush(stream);
   mu_assert_streq(buffer, "");

   honey_log_set_level(ERROR);
   mu_assert_equal(honey_log_get_level(), ERROR);
   
   honey_error("hello, %s!", "world");
   fclose(stream);
   mu_assert_streq(buffer, "[ERROR] hello, world!");
   free(buffer);

   return 0;
}


mu_test test_log_fatal()
{
   FILE *stream;
   char *buffer;
   size_t len;

   stream = open_memstream(&buffer, &len);
   mu_assert_unequal(stream, NULL);

   honey_log_set_file(stream);
   mu_assert_equal(honey_log_get_file(), stream);
   
   honey_log_set_level(-1);
   mu_assert_equal(honey_log_get_level(), -1);

   honey_fatal("hello, %s!", "world");
   fflush(stream);
   // all error levels will print fatal messagesf
   mu_assert_streq(buffer, "[FATAL] hello, world!");

   honey_log_set_level(FATAL);
   mu_assert_equal(honey_log_get_level(), FATAL);
   
   honey_fatal("hello, %s!", "world");
   fclose(stream);
   mu_assert_streq(buffer, "[FATAL] hello, world![FATAL] hello, world!");
   free(buffer);

   return 0;
}
