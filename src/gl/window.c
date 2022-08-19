#include "gl/glad/glad.h"
#include <GLFW/glfw3.h>
#include <lua.h>
#include <honeysuckle.h>


int window_create(lua_State *L);
int window_destroy(lua_State *L);
int window_should_close(lua_State *L);
int window_poll_events(lua_State *L);


void setup_window(lua_State *L, int honey_index)
{
	hs_create_table(L,
		hs_str_cfunc("create", window_create),
		hs_str_cfunc("destroy", window_destroy),
		hs_str_cfunc("shouldClose", window_should_close),
		hs_str_cfunc("pollEvents", window_poll_events)
	);
	lua_setfield(L, honey_index, "window");
}


int window_create(lua_State *L)
{
	lua_Integer width, height;
	char *title;
	hs_parse_args(L, hs_int(width), hs_int(height), hs_str(title));

	GLFWwindow *win = glfwCreateWindow(width, height, title, NULL, NULL);
	if (win == NULL)
		hs_throw_error(L, "failed to create window");
	lua_pushlightuserdata(L, win);
	return 1;
}


int window_destroy(lua_State *L)
{
	void *ptr;
	hs_parse_args(L, hs_light(ptr));
	GLFWwindow *win = ptr;
	glfwDestroyWindow(win);
	return 0;
}


int window_should_close(lua_State *L)
{
	void *ptr;
	hs_parse_args(L, hs_light(ptr));
	GLFWwindow *win = ptr;
	lua_pushboolean(L, glfwWindowShouldClose(win));
	return 1;
}


int window_poll_events(lua_State *L)
{
	glfwPollEvents();
	return 0;
}
