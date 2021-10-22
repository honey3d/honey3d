#include "test/minunit.h"
#include "test/mock_queue.h"

#include "gl/honey_gl.h"

mu_test honey_gl_do_setup();


void honey_gl_tests()
{
   mu_run_test("setup OpenGL", honey_gl_do_setup);
}


mu_test honey_gl_do_setup()
{
}
