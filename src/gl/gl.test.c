#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <honeysuckle.h>
#include "test/honey-test.h"


int mock_glfwInit_(void);
int mock_hs_throw_error_(lua_State *L, const char *str);
void mock_glfwTerminate_();

#define glfwInit mock_glfwInit_
#define hs_throw_error mock_hs_throw_error_
#define glfwTerminate mock_glfwTerminate_
#include "gl/gl.c"
#undef glfwTerminate
#undef hs_throw_error
#undef glfwInit


lily_mock_t *mock_glfwInit = NULL;
int mock_glfwInit_()
{
	struct lily_mock_arg_t args[] = {};
	lily_mock_store_call(mock_glfwInit, args);

	int result;
	lily_get_value(mock_glfwInit, int, &result);
	return result;
}


lily_mock_t *mock_hs_throw_error = NULL;
int mock_hs_throw_error_(lua_State *L, const char *str)
{
	struct lily_mock_arg_t args[] = {
		{ sizeof(const char *), &str }
	};
	lily_mock_store_call(mock_hs_throw_error, args);

	lua_pushstring(L, "some error");
	lua_error(L);

	return 0;
}


lily_mock_t *mock_glfwTerminate = NULL;
void mock_glfwTerminate_()
{
	struct lily_mock_arg_t args[] = {};
	lily_mock_store_call(mock_glfwTerminate, args);
}


/* ~~~~~~~~ suite ~~~~~~~~ */

void gl_init_succeeds()
{
	lily_mock_use(&mock_glfwInit);
	lily_mock_use(&mock_hs_throw_error);

	lua_State *L = luaL_newstate();
	lily_store_value(mock_glfwInit, int, 1);
	lua_pushcfunction(L, gl_init);
	int err = lua_pcall(L, 0, 0, 0);
	lua_close(L);

	lily_assert_int_equal(err, 0);
	lily_assert_int_equal(mock_glfwInit->n_calls, 1);
	lily_assert_int_equal(mock_hs_throw_error->n_calls, 0);
}


void gl_init_fails()
{
	lily_mock_use(&mock_glfwInit);
	lily_mock_use(&mock_hs_throw_error);

	lua_State *L = luaL_newstate();
	lily_store_value(mock_glfwInit, int, 0);
	lua_pushcfunction(L, gl_init);
	int err = lua_pcall(L, 0, 0, 0);
	lua_close(L);

	lily_assert_int_equal(err, LUA_ERRRUN);
	lily_assert_int_equal(mock_hs_throw_error->n_calls, 1);
}


void gl_terminate_works()
{
	lily_mock_use(&mock_glfwTerminate);

	lua_State *L = luaL_newstate();
	lua_pushcfunction(L, gl_terminate);
	int err = lua_pcall(L, 0, 0, 0);
	lua_close(L);

	lily_assert_int_equal(err, 0);
	lily_assert_int_equal(mock_glfwTerminate->n_calls, 1);
}


void suite_gl()
{
	lily_run_test(gl_init_succeeds);
	lily_run_test(gl_init_fails);
	lily_run_test(gl_terminate_works);

	lily_mock_destroy(mock_glfwInit);
	lily_mock_destroy(mock_hs_throw_error);
	lily_mock_destroy(mock_glfwTerminate);
}
