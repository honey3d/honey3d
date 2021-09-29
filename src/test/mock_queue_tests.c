#include "test/minunit.h"
#include "test/mock_queue.h"

mu_test mock_queue_int();
mu_test mock_queue_int_seq();
mu_test mock_queue_pop_multi();
mu_test mock_queue_clean_finish();


void mock_queue_tests()
{
   mock_queue_init();
   mu_run_test("push and pop integer to mock queue", mock_queue_int);
   mu_run_test("push and pop integer sequence", mock_queue_int_seq);
   mu_run_test("pop multiple times with empty queue", mock_queue_pop_multi);
   mu_run_test("clean up mock queue", mock_queue_clean_finish);
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

mu_test mock_queue_int()
{
   mock_queue(int, 5);
   mu_assert_unequal(mock_queue_len(), 0);
   mu_assert_equal(mock_front(int), 5);

   mock_pop();

   mu_assert_equal(mock_queue_len(), 0);

   return 0;
}


mu_test mock_queue_int_seq()
{
   mock_queue(int, 2);
   mock_queue(int, 1);
   mock_queue(int, 3);
   mock_queue(int, 4);

   mu_assert_unequal(mock_queue_len(), 0);
   mu_assert_equal(mock_queue_len(), 4);
   mu_assert_equal(mock_front(int), 2);

   mock_pop();

   mu_assert_unequal(mock_queue_len(), 0);
   mu_assert_equal(mock_queue_len(), 3);
   mu_assert_equal(mock_front(int), 1);

   mock_pop();

   mu_assert_unequal(mock_queue_len(), 0);
   mu_assert_equal(mock_queue_len(), 2);
   mu_assert_equal(mock_front(int), 3);

   mock_pop();

   mu_assert_unequal(mock_queue_len(), 0);
   mu_assert_equal(mock_queue_len(), 1);
   mu_assert_equal(mock_front(int), 4);

   mock_pop();

   mu_assert_equal(mock_queue_len(), 0);

   return 0;
}


mu_test mock_queue_pop_multi()
{
   mu_assert_equal(mock_queue_len(), 0);

   mock_pop();
   mock_pop();
   mock_pop();

   mu_assert_equal(mock_queue_len(), 0);
   return 0;
}


mu_test mock_queue_clean_finish()
{
   mu_assert_equal(mock_queue_len(), 0);

   mock_queue(int, 5);
   mock_queue(int, 5);
   mock_queue(int, 5);

   mu_assert_equal(mock_queue_len(), 3);

   mock_queue_cleanup();

   mu_assert_equal(mock_queue_len(), 0);

   return 0;
}
