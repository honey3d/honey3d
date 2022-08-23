#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <honeysuckle.h>
#include "test/honey-test.h"


int mock_glfwInit_(void);
int mock_hs_throw_error_(lua_State *L, const char *str, ...);
void mock_glfwTerminate_();
void mock_glBufferData_(int, size_t, const void *, int);

#define DUMMY_FUNCTION(...)

#define glfwInit mock_glfwInit_
#define hs_throw_error mock_hs_throw_error_
#define glfwTerminate mock_glfwTerminate_
#define setup_shader DUMMY_FUNCTION
#define setup_drawing DUMMY_FUNCTION
#define setup_texture DUMMY_FUNCTION
#include "gl/gl.c"
#include "gl/data.c"
#undef glBufferData
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
int mock_hs_throw_error_(lua_State *L, const char *str, ...)
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


lily_mock_t *mock_glBufferData = NULL;
void mock_glBufferData_(int target, size_t size, const void *data, int usage)
{
	struct lily_mock_arg_t args[] = {
		{ sizeof(int), &target },
		{ sizeof(size_t), &size },
		{ sizeof(int), &usage }
	};
	lily_mock_store_call(mock_glBufferData, args);

	int use_ints; lily_get_value(mock_glBufferData, int, &use_ints);

	if (use_ints) {
		size_t count = size/sizeof(int);
		int *numbers = data;
		for (int i=0; i<count; i++) {
			lily_store_value(mock_glBufferData, int, numbers[i]);
		}
	}
	else {
		size_t count = size/sizeof(float);
		float *numbers = data;
		for (int i=0; i<count; i++) {
			lily_store_value(mock_glBufferData, float, numbers[i]);
		}
	}
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


void gl_buffer_float_works()
{
	lily_mock_use(&mock_hs_throw_error);
	lily_mock_use(&mock_glBufferData);
	lily_store_value(mock_glBufferData, int, 0); // use floats

	lua_State *L = luaL_newstate();
	lua_pushcfunction(L, gl_buffer_data);
	lua_pushinteger(L, GL_ARRAY_BUFFER);
	lua_pushinteger(L, GL_FLOAT);
	hs_create_table(L,
		hs_int_num(1, 22),
		hs_int_num(2, 33),
		hs_int_num(3, 44),
	);
	lua_pushinteger(L, GL_STATIC_DRAW);
	int err = hs_call(L, 4, 0);
	lua_close(L);

	lily_assert_int_equal(err, 0);
	lily_assert_int_equal(mock_glBufferData->n_calls, 1);
	int target; size_t size; int usage;
	struct lily_mock_arg_t args[] = {
		{ sizeof(int), &target },
		{ sizeof(size_t), &size },
		{ sizeof(int), &usage }
	};
	lily_mock_get_call(mock_glBufferData, args, 0);
	lily_assert_int_equal(target, GL_ARRAY_BUFFER);
	lily_assert_int_equal(size, 3*sizeof(float));
	lily_assert_int_equal(usage, GL_STATIC_DRAW);

	float n;
	lily_get_value(mock_glBufferData, float, &n);
	lily_assert_float_equal(n, 22, 0.1);
	lily_get_value(mock_glBufferData, float, &n);
	lily_assert_float_equal(n, 33, 0.1);
	lily_get_value(mock_glBufferData, float, &n);
	lily_assert_float_equal(n, 44, 0.1);
}


void gl_buffer_int_works()
{
	lily_mock_use(&mock_hs_throw_error);
	lily_mock_use(&mock_glBufferData);
	lily_store_value(mock_glBufferData, int, 1); // use ints

	lua_State *L = luaL_newstate();
	lua_pushcfunction(L, gl_buffer_data);
	lua_pushinteger(L, GL_ARRAY_BUFFER);
	lua_pushinteger(L, GL_INT);
	hs_create_table(L,
		hs_int_num(1, 22),
		hs_int_num(2, 33),
		hs_int_num(3, 44),
	);
	lua_pushinteger(L, GL_STATIC_DRAW);
	int err = hs_call(L, 4, 0);
	lua_close(L);

	lily_assert_int_equal(err, 0);
	lily_assert_int_equal(mock_glBufferData->n_calls, 1);
	int target; size_t size; int usage;
	struct lily_mock_arg_t args[] = {
		{ sizeof(int), &target },
		{ sizeof(size_t), &size },
		{ sizeof(int), &usage }
	};
	lily_mock_get_call(mock_glBufferData, args, 0);
	lily_assert_int_equal(target, GL_ARRAY_BUFFER);
	lily_assert_int_equal(size, 3*sizeof(float));
	lily_assert_int_equal(usage, GL_STATIC_DRAW);

	int n;
	lily_get_value(mock_glBufferData, int, &n);
	lily_assert_int_equal(n, 22);
	lily_get_value(mock_glBufferData, int, &n);
	lily_assert_int_equal(n, 33);
	lily_get_value(mock_glBufferData, int, &n);
	lily_assert_int_equal(n, 44);
}

void suite_gl()
{
	lily_run_test(gl_init_succeeds);
	lily_run_test(gl_init_fails);
	lily_run_test(gl_terminate_works);
	lily_run_test(gl_buffer_float_works);
	lily_run_test(gl_buffer_int_works);

	lily_mock_destroy(mock_glfwInit);
	lily_mock_destroy(mock_hs_throw_error);
	lily_mock_destroy(mock_glfwTerminate);
	lily_mock_destroy(mock_glBufferData);
}
