#include <stdio.h>
#include <stdlib.h>

#include "test/minunit.h"
#include "test/suites.h"

#include "logging/logging.h"


/* test declarations */

mu_test test_log_get_level();
mu_test test_log_set_defaults();
mu_test test_log_debug();


/* main suite */

void honey_logging_tests()
{
   mu_run_test("get log level strings", test_log_get_level);
   mu_run_test("print debug message", test_log_debug);
}


/* ~~~~~~~~ test definitions ~~~~~~~~ */

mu_test test_log_get_level()
{
   honey_log_info.log_level = DEBUG;
   mu_assert_streq("DEBUG", honey_log_level_str());

   honey_log_info.log_level = INFO;
   mu_assert_streq("INFO", honey_log_level_str());

   honey_log_info.log_level = WARN;
   mu_assert_streq("WARN", honey_log_level_str());

   honey_log_info.log_level = ERROR;
   mu_assert_streq("ERROR", honey_log_level_str());

   honey_log_info.log_level = FATAL;
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

   honey_log_info.debug_out = stream;
   honey_log_info.log_level = FATAL;

   honey_debug("hello, %s!", "world");
   fflush(stream);
   mu_assert_streq(buffer, "");

   honey_log_info.log_level = DEBUG;
   honey_debug("hello, %s!", "world");
   fclose(stream);
   mu_assert_streq(buffer, "[DEBUG] hello, world!");
   free(buffer);

   return 0;
}
