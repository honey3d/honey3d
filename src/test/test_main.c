#include "minunit.h"
#include "suites.h"

int tests_run = 0;
int tests_failed = 0;

int main()
{
   printf("~~~~~~~~ running tests ~~~~~~~~\n\n");
   RUN_TESTS;
   printf("~~~~~~~~~ tests done ~~~~~~~~~~\n\n");

   mu_tests_finished();
}
