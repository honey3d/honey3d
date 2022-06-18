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
void glfw_window_hints_table();
void tointeger_parses_bool();
void tointeger_parses_int();
void tointeger_fails_other();

void suite_window()
{
	lily_run_test(gl_init_succeeds);
	lily_run_test(gl_init_fail_glfwInit);
	lily_run_test(glfw_window_hints_table);
	lily_run_test(tointeger_parses_bool);
	lily_run_test(tointeger_parses_int);
	lily_run_test(tointeger_fails_other);

	CLEAN_MOCK(mock_glfwInit);
	CLEAN_MOCK(mock_hs_throw_error);
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


int get_int(lua_State *L, int table_index, const char *key)
{
	lua_getfield(L, table_index, key);
	lily_assert_msg(lua_isnumber(L, -1), LILY_LOCATION, "key %s is not a number", key);
	int n = lua_tointeger(L, -1);
	lua_pop(L, 1);
	return n;
}

#define CHECK_VALUE(str, num) \
	do { \
		int value = get_int(L, 1, str); \
		lily_assert_int_equal(value, num); \
	} while(0)

void glfw_window_hints_table()
{
	lua_State *L = luaL_newstate();

	lily_assert_int_equal(lua_gettop(L), 0);
	create_glfw_window_hints_table(L);
	lily_assert_int_equal(lua_gettop(L), 2);
	lily_assert_true(lua_istable(L, 1));

	/* window hints */
	lily_assert_int_equal(
		get_int(L, 1, "resizable"),
		GLFW_RESIZABLE
	);

	lily_assert_int_equal(
		get_int(L, 1, "visible"),
		GLFW_VISIBLE
	);

	lily_assert_int_equal(
		get_int(L, 1, "decorated"),
		GLFW_DECORATED
	);

	lily_assert_int_equal(
		get_int(L, 1, "focused"),
		GLFW_FOCUSED
	);

	lily_assert_int_equal(
		get_int(L, 1, "autoIconify"),
		GLFW_AUTO_ICONIFY
	);

	lily_assert_int_equal(
		get_int(L, 1, "floating"),
		GLFW_FLOATING
	);

	lily_assert_int_equal(
		get_int(L, 1, "maximized"),
		GLFW_MAXIMIZED
	);

	lily_assert_int_equal(
		get_int(L, 1, "centerCursor"),
		GLFW_CENTER_CURSOR
	);

	lily_assert_int_equal(
		get_int(L, 1, "transparentFramebuffer"),
		GLFW_TRANSPARENT_FRAMEBUFFER
	);

	lily_assert_int_equal(
		get_int(L, 1, "focusOnShow"),
		GLFW_FOCUS_ON_SHOW
	);

	lily_assert_int_equal(
		get_int(L, 1, "scaleToMonitor"),
		GLFW_SCALE_TO_MONITOR
	);


	/* framebuffer hints */
	/* (don't expose accumulation or auxiliary buffer hints) */
	lily_assert_int_equal(
			get_int(L, 1, "redBits"),
		GLFW_RED_BITS
	);

	lily_assert_int_equal(
		get_int(L, 1, "greenBits"),
		GLFW_GREEN_BITS
	);

	lily_assert_int_equal(
		get_int(L, 1, "blueBits"),
		GLFW_BLUE_BITS
	);

	lily_assert_int_equal(
		get_int(L, 1, "alphaBits"),
		GLFW_ALPHA_BITS
	);

	lily_assert_int_equal(
		get_int(L, 1, "depthBits"),
		GLFW_DEPTH_BITS
	);

	lily_assert_int_equal(
		get_int(L, 1, "stereoscopic"),
		GLFW_STEREO
	);

	lily_assert_int_equal(
		get_int(L, 1, "samples"),
		GLFW_SAMPLES
	);

	lily_assert_int_equal(
		get_int(L, 1, "srgbCapable"),
		GLFW_SRGB_CAPABLE 
	);

	lily_assert_int_equal(
		get_int(L, 1, "doubleBuffer"),
		GLFW_DOUBLEBUFFER
	);


	/* monitor & context hints */
	lily_assert_int_equal(
		get_int(L, 1, "refreshRate"),
		GLFW_REFRESH_RATE 
	);

	lily_assert_int_equal(
		get_int(L, 1, "clientApi"),
		GLFW_CLIENT_API 
	);

	lily_assert_int_equal(
		get_int(L, 1, "contextCreationApi"),
		GLFW_CONTEXT_CREATION_API 
	);

	lily_assert_int_equal(
		get_int(L, 1, "contextVersionMajor"),
		GLFW_CONTEXT_VERSION_MAJOR 
	);

	lily_assert_int_equal(
		get_int(L, 1, "contextVersionMinor"),
		GLFW_CONTEXT_VERSION_MINOR 
	);

	lily_assert_int_equal(
		get_int(L, 1, "forwardCompatible"),
		GLFW_OPENGL_FORWARD_COMPAT 
	);

	lily_assert_int_equal(
		get_int(L, 1, "debugContext"),
		GLFW_OPENGL_DEBUG_CONTEXT 
	);

	lily_assert_int_equal(
		get_int(L, 1, "profile"),
		GLFW_OPENGL_PROFILE 
	);

	lily_assert_int_equal(
		get_int(L, 1, "contextRobustness"),
		GLFW_CONTEXT_ROBUSTNESS 
	);

	lily_assert_int_equal(
		get_int(L, 1, "contextReleaseBehavior"),
		GLFW_CONTEXT_RELEASE_BEHAVIOR 
	);

	lily_assert_int_equal(
		get_int(L, 1, "noError"),
		GLFW_CONTEXT_NO_ERROR
	);


	/* special hint values */

	lily_assert_int_equal(
		get_int(L, 2, "dontCare"),
		GLFW_DONT_CARE
	);

	/* client api */
	lily_assert_int_equal(
		get_int(L, 2, "glApi"),
		GLFW_OPENGL_API
	);

	lily_assert_int_equal(
		get_int(L, 2, "glesApi"),
		GLFW_OPENGL_ES_API
	);

	lily_assert_int_equal(
		get_int(L, 2, "noApi"),
		GLFW_NO_API
	);

	/* context api */
	lily_assert_int_equal(
		get_int(L, 2, "nativeApi"),
		GLFW_NATIVE_CONTEXT_API
	);

	lily_assert_int_equal(
		get_int(L, 2, "eglApi"),
		GLFW_EGL_CONTEXT_API 
	);

	lily_assert_int_equal(
		get_int(L, 2, "osMesaApi"),
		GLFW_OSMESA_CONTEXT_API
	);

	/* robustness */
	lily_assert_int_equal(
		get_int(L, 2, "noRobustness"),
		GLFW_NO_ROBUSTNESS
	);

	lily_assert_int_equal(
		get_int(L, 2, "noResetNotification"),
		GLFW_NO_RESET_NOTIFICATION 
	);

	lily_assert_int_equal(
		get_int(L, 2, "loseContextOnReset"),
		GLFW_LOSE_CONTEXT_ON_RESET
	);

	/* release */
	lily_assert_int_equal(
		get_int(L, 2, "anyBehavior"),
		GLFW_ANY_RELEASE_BEHAVIOR
	);

	lily_assert_int_equal(
		get_int(L, 2, "flush"),
		GLFW_RELEASE_BEHAVIOR_FLUSH 
	);

	lily_assert_int_equal(
		get_int(L, 2, "none"),
		GLFW_RELEASE_BEHAVIOR_NONE
	);

	/* profile */
	lily_assert_int_equal(
		get_int(L, 2, "anyProfile"),
		GLFW_OPENGL_ANY_PROFILE
	);

	lily_assert_int_equal(
		get_int(L, 2, "compatabilityProfile"),
		GLFW_OPENGL_COMPAT_PROFILE
	);

	lily_assert_int_equal(
		get_int(L, 2, "coreProfile"),
		GLFW_OPENGL_CORE_PROFILE
	);

	lua_close(L);
}


void tointeger_parses_bool()
{
	USE_MOCK(mock_hs_throw_error);
	lua_State *L = luaL_newstate();

	lua_pushboolean(L, 0);
	lily_assert_false(lua_toboolean(L, -1));
	lily_assert_int_equal(tointeger(L, -1), 0);

	lua_pushboolean(L, 1);
	lily_assert_true(lua_toboolean(L, -1));
	lily_assert_int_equal(tointeger(L, -1), 1);

	lua_close(L);
}


void tointeger_parses_int()
{
	USE_MOCK(mock_hs_throw_error);
	lua_State *L = luaL_newstate();
	
	lua_pushinteger(L, 234);
	lua_pushinteger(L, 55555);

	lily_assert_int_equal(tointeger(L, -2), 234);
	lily_assert_int_equal(tointeger(L, -1), 55555);

	lua_close(L);
}


void tointeger_fails_other()
{
	USE_MOCK(mock_hs_throw_error);
	lua_State *L = luaL_newstate();

	lua_pushstring(L, "hey there babe");
	tointeger(L, -1);
	lily_assert_int_equal(mock_hs_throw_error_data->n_calls, 1);
}
