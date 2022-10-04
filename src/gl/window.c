#include <stdlib.h>
#include "gl/glad/glad.h"
#include <GLFW/glfw3.h>
#include <lua.h>
#include <honeysuckle.h>

struct window_data {
	lua_State *L;
	int framebuffer_size_callback;
};

struct window_data * create_window_data(lua_State *L)
{
	struct window_data *wdata = malloc(sizeof(struct window_data));
	if (wdata == NULL)
		return NULL;
	wdata->L = L;
	wdata->framebuffer_size_callback = LUA_NOREF;
	return wdata;
}

int window_create(lua_State *L);
int window_destroy(lua_State *L);
int window_make_context_current(lua_State *L);
int window_set_hint(lua_State *L);
int window_should_close(lua_State *L);
int window_poll_events(lua_State *L);
int window_swap_buffers(lua_State *L);
int window_set_framebuffer_size_callback(lua_State *L);
int window_get_time(lua_State *L);
int window_get_key(lua_State *L);


static const char *window_tname = "window";


void setup_window(lua_State *L, int honey_index)
{
	luaL_newmetatable(L, window_tname);
	lua_pop(L, 1);

	int hint_types = hs_create_table(L,
		hs_str_int("contextVersionMajor", GLFW_CONTEXT_VERSION_MAJOR),
		hs_str_int("contextVersionMinor", GLFW_CONTEXT_VERSION_MINOR),
		hs_str_int("openGlProfile", GLFW_OPENGL_PROFILE),
	);

	int profile_types = hs_create_table(L,
		hs_str_int("openGlCoreProfile", GLFW_OPENGL_CORE_PROFILE),
	);

	hs_create_table(L,
		hs_str_cfunc("create", window_create),
		hs_str_cfunc("destroy", window_destroy),
		hs_str_cfunc("makeContextCurrent", window_make_context_current),
		hs_str_cfunc("setHint", window_set_hint),
		hs_str_cfunc("shouldClose", window_should_close),
		hs_str_cfunc("pollEvents", window_poll_events),
		hs_str_cfunc("swapBuffers", window_swap_buffers),
		hs_str_cfunc("setFramebufferSizeCallback", window_set_framebuffer_size_callback),
		hs_str_cfunc("getTime", window_get_time),
		hs_str_cfunc("getKey", window_get_key),

		hs_str_tbl("hintType", hint_types),
		hs_str_tbl("profileType", profile_types),

		/* key states */
		hs_str_int("PRESS", GLFW_PRESS),
		hs_str_int("RELEASE", GLFW_RELEASE),

		/* key buttons */
		hs_str_int("KEY_ESCAPE", GLFW_KEY_ESCAPE),
	);
	lua_setfield(L, honey_index, "window");
}


static void framebuffer_size_callback_(GLFWwindow *win, int width, int height)
{
	struct window_data *wdata = glfwGetWindowUserPointer(win);
	if (wdata->framebuffer_size_callback != LUA_NOREF) {
		hs_rload(wdata->L, wdata->framebuffer_size_callback);
		lua_pushlightuserdata(wdata->L, win);
		lua_pushinteger(wdata->L, width);
		lua_pushinteger(wdata->L, height);
		hs_call(wdata->L, 3, 0);
	}
}

int window_create(lua_State *L)
{
	lua_Integer width, height;
	char *title;
	hs_parse_args(L, hs_int(width), hs_int(height), hs_str(title));

	GLFWwindow **win = lua_newuserdata(L, sizeof(GLFWwindow *));
	*win = glfwCreateWindow(width, height, title, NULL, NULL);
	if (*win == NULL)
		hs_throw_error(L, "failed to create window");
	
	struct window_data *wdata = create_window_data(L);
	glfwSetWindowUserPointer(*win, wdata);

	glfwSetFramebufferSizeCallback(*win, framebuffer_size_callback_);
	
	luaL_getmetatable(L, window_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int window_destroy(lua_State *L)
{
	GLFWwindow **win = luaL_checkudata(L, 1, window_tname);
	void *wdata = glfwGetWindowUserPointer(*win);
	if (wdata != NULL) {
		free(wdata);
		glfwSetWindowUserPointer(*win, NULL);
	}
	glfwDestroyWindow(*win);
	return 0;
}


int window_make_context_current(lua_State *L)
{
	GLFWwindow **win = luaL_checkudata(L, 1, window_tname);
	glfwMakeContextCurrent(*win);
	return 0;
}


int window_set_hint(lua_State *L)
{
	int hint = luaL_checkinteger(L, 1);
	int value = luaL_checkinteger(L, 2);
	glfwWindowHint(hint, value);
	return 0;
}


int window_should_close(lua_State *L)
{
	GLFWwindow **win = luaL_checkudata(L, 1, window_tname);
	lua_pushboolean(L, glfwWindowShouldClose(*win));
	return 1;
}


int window_poll_events(lua_State *L)
{
	glfwPollEvents();
	return 0;
}


int window_swap_buffers(lua_State *L)
{
	GLFWwindow **win = luaL_checkudata(L, 1, window_tname);
	glfwSwapBuffers(*win);
	return 0;
}


int window_set_framebuffer_size_callback(lua_State *L)
{
	GLFWwindow **win = luaL_checkudata(L, 1, window_tname);
	luaL_checktype(L, 2, LUA_TFUNCTION);
	int func = 2;

	struct window_data *wdata = glfwGetWindowUserPointer(*win);

	lua_pushvalue(L, func);
	wdata->framebuffer_size_callback = hs_rstore(L);
	return 0;
}


int window_get_time(lua_State *L)
{
	lua_pushnumber(L, glfwGetTime());
	return 1;
}


int window_get_key(lua_State *L)
{
	GLFWwindow **win = luaL_checkudata(L, 1, window_tname);
	int key = luaL_checkinteger(L, 2);
	lua_pushinteger(L, glfwGetKey(*win, key));
	return 1;
}
