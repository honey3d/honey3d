#include "test/minunit.h"
#include "test/suites.h"

#include "logging/logging.h"


/* test declarations */

mu_test test_log_get_level();


/* main suite */

void honey_logging_tests()
{
   mu_run_test("get log level strings", test_log_get_level);
}


/* test definitions */

mu_test test_log_get_level()
{
   struct honey_log_info info;

   info.log_level = DEBUG;
   mu_assert_streq("DEBUG", honey_log_level_str_(&info));

   info.log_level = INFO;
   mu_assert_streq("INFO", honey_log_level_str_(&info));

   info.log_level = WARN;
   mu_assert_streq("WARN", honey_log_level_str_(&info));

   info.log_level = ERROR;
   mu_assert_streq("ERROR", honey_log_level_str_(&info));

   info.log_level = FATAL;
   mu_assert_streq("FATAL", honey_log_level_str_(&info));

   return 0;
}
