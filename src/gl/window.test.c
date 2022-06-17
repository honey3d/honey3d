#include <lua.h>
#include <lauxlib.h>
#include "test/honey-test.h"

int mock_glfwInit();
#define glfwInit mock_glfwInit
#include "gl/window.c"
#undef glfwInit


lily_mock_t *mock_glfwInit_data = NULL;
int mock_glfwInit()
{
	lily_mock_call(mock_glfwInit_data, NULL);

	int result;
	lily_dequeue(mock_glfwInit_data->values, int, &result);
	return result;
}


void gl_init_succeeds();

void suite_window()
{
	lily_run_test(gl_init_succeeds);

	CLEAN_MOCK(mock_glfwInit);
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


void gl_init_succeeds()
{
	USE_MOCK(mock_glfwInit);
	lua_State *L = luaL_newstate();
	
	lua_pushcfunction(L, gl_init);
	int error = lua_pcall(L, 0, 0, 0);

	lily_assert_int_equal(error, 0);
	lily_assert_int_equal(mock_glfwInit_data->n_calls, 1);
}
