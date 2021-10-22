#include "minunit.h"
#include "test/mock_queue.h"
#include "mock_GLFW.h"

void glfwGetVersion(int *major, int *minor, int *rev)
{
   *major = mock_front(int);
   mock_pop();
   *minor = mock_front(int);
   mock_pop();
   *rev = mock_front(int);
   mock_pop();
}


int glfwInit()
{
   int result = mock_front(int);
   mock_pop();
   return result;
}


void glfwTerminate()
{
   mock_queue(bool, true);
}


int glfwGetError(const char **description)
{
   int error_code = mock_front(int);
   mock_pop();
   if (description != NULL) {
      *description = mock_front(const char *);
      mock_pop();
   }
   return error_code;
}
