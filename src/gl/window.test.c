#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <honeysuckle.h>
#include "test/honey-test.h"

int mock_glfwInit();
int mock_hs_throw_error(lua_State *L, const char *format_string, ...);
#define glfwInit mock_glfwInit
#define hs_throw_error mock_hs_throw_error
#include "gl/window.c"
#undef glfwInit
#undef hs_throw_error


lily_mock_t *mock_glfwInit_data = NULL;
int mock_glfwInit()
{
	lily_mock_call(mock_glfwInit_data, NULL);

	int result;
	mock_dequeue(mock_glfwInit, int, &result);
	return result;
}

lily_mock_t *mock_hs_throw_error_data = NULL;
int mock_hs_throw_error(lua_State *L, const char *format_string, ...)
{
	/* to avoid basically just re-implementing printf parsing here,
	   i am limiting this function to be able to receive strings only */
	
	/* count format specifiers */
	char *ptr = strchr(format_string, '%');
	int n_args = 0;
	while (ptr != NULL) {
		n_args += 1;
		ptr = strchr(ptr+1, '%');
	}

	/* store arguments */
	struct lily_mock_arg_t args[] = {
		{ sizeof(const char*), &format_string },
		{ sizeof(int), &n_args },
	};
	lily_mock_call(mock_hs_throw_error_data, args);

	/* store format arguments */
	va_list vl;
	va_start(vl, format_string);
	for (int i=0; i<n_args; i++) {
		char *str = va_arg(vl, char*);
		mock_enqueue(mock_hs_throw_error, char*, str);
	}
}


/* ~~~~~~~~ TESTS ~~~~~~~~ */
void gl_init_succeeds();
void gl_init_fail_glfwInit();

void suite_window()
{
	lily_run_test(gl_init_succeeds);
	lily_run_test(gl_init_fail_glfwInit);

	CLEAN_MOCK(mock_glfwInit);
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


void gl_init_succeeds()
{
	USE_MOCK(mock_glfwInit);
	USE_MOCK(mock_hs_throw_error);
	
	/* queue success */
	mock_enqueue(mock_glfwInit, int, GLFW_TRUE);
	gl_init(NULL);

	lily_assert_int_equal(mock_glfwInit_data->n_calls, 1);
	lily_assert_int_equal(mock_hs_throw_error_data->n_calls, 0);
}


void gl_init_fail_glfwInit()
{
	USE_MOCK(mock_glfwInit);
	USE_MOCK(mock_hs_throw_error);
	
	/* queue failure */
	mock_enqueue(mock_glfwInit, int, GLFW_FALSE);
	gl_init(NULL);

	lily_assert_int_equal(mock_glfwInit_data->n_calls, 1);
	lily_assert_int_equal(mock_hs_throw_error_data->n_calls, 1);

	const char *fmt; int argc;
	struct lily_mock_arg_t args[] = {
		{ sizeof(const char*), &fmt },
		{ sizeof(int), &argc },
	};
	lily_get_call(mock_hs_throw_error_data, args, 0);

	lily_assert_string_equal((char*) fmt, "failed to initialize GLFW");
}
