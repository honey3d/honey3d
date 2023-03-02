#include <stdlib.h>
#include <glad/glad.h>
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
int window_set_should_close(lua_State *L);
int window_poll_events(lua_State *L);
int window_swap_buffers(lua_State *L);
int window_set_framebuffer_size_callback(lua_State *L);
int window_get_time(lua_State *L);
int window_get_key(lua_State *L);
int window_get_cursor_pos(lua_State *L);
int window_set_input_mode(lua_State *L);


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

	struct hs_tbl_entry tbl[] = {
		hs_str_cfunc("create", window_create),
		hs_str_cfunc("destroy", window_destroy),
		hs_str_cfunc("makeContextCurrent", window_make_context_current),
		hs_str_cfunc("setHint", window_set_hint),
		hs_str_cfunc("shouldClose", window_should_close),
		hs_str_cfunc("setShouldClose", window_set_should_close),
		hs_str_cfunc("pollEvents", window_poll_events),
		hs_str_cfunc("swapBuffers", window_swap_buffers),
		hs_str_cfunc("setFramebufferSizeCallback", window_set_framebuffer_size_callback),
		hs_str_cfunc("getTime", window_get_time),
		hs_str_cfunc("getKey", window_get_key),
		hs_str_cfunc("getCursorPos", window_get_cursor_pos),
		hs_str_cfunc("setInputMode", window_set_input_mode),

		hs_str_tbl("hintType", hint_types),
		hs_str_tbl("profileType", profile_types),

		/* input modes */
		hs_str_int("CURSOR", GLFW_CURSOR),

		/* cursor modes */
		hs_str_int("CURSOR_NORMAL", GLFW_CURSOR_NORMAL),
		hs_str_int("CURSOR_HIDDEN", GLFW_CURSOR_HIDDEN),
		hs_str_int("CURSOR_DISABLED", GLFW_CURSOR_DISABLED),

		/* key states */
		hs_str_int("PRESS", GLFW_PRESS),
		hs_str_int("RELEASE", GLFW_RELEASE),

		/* key buttons */
		hs_str_int("KEY_UNKNOWN", GLFW_KEY_UNKNOWN),
		hs_str_int("KEY_SPACE", GLFW_KEY_SPACE),
		hs_str_int("KEY_APOSTROPHE", GLFW_KEY_APOSTROPHE),
		hs_str_int("KEY_COMMA", GLFW_KEY_COMMA),
		hs_str_int("KEY_MINUS", GLFW_KEY_MINUS),
		hs_str_int("KEY_PERIOD", GLFW_KEY_PERIOD),
		hs_str_int("KEY_SLASH", GLFW_KEY_SLASH),
		hs_str_int("KEY_0", GLFW_KEY_0),
		hs_str_int("KEY_1", GLFW_KEY_1),
		hs_str_int("KEY_2", GLFW_KEY_2),
		hs_str_int("KEY_3", GLFW_KEY_3),
		hs_str_int("KEY_4", GLFW_KEY_4),
		hs_str_int("KEY_5", GLFW_KEY_5),
		hs_str_int("KEY_6", GLFW_KEY_6),
		hs_str_int("KEY_7", GLFW_KEY_7),
		hs_str_int("KEY_8", GLFW_KEY_8),
		hs_str_int("KEY_9", GLFW_KEY_9),
		hs_str_int("KEY_SEMICOLON", GLFW_KEY_SEMICOLON),
		hs_str_int("KEY_EQUAL", GLFW_KEY_EQUAL),
		hs_str_int("KEY_A", GLFW_KEY_A),
		hs_str_int("KEY_B", GLFW_KEY_B),
		hs_str_int("KEY_C", GLFW_KEY_C),
		hs_str_int("KEY_D", GLFW_KEY_D),
		hs_str_int("KEY_E", GLFW_KEY_E),
		hs_str_int("KEY_F", GLFW_KEY_F),
		hs_str_int("KEY_G", GLFW_KEY_G),
		hs_str_int("KEY_H", GLFW_KEY_H),
		hs_str_int("KEY_I", GLFW_KEY_I),
		hs_str_int("KEY_J", GLFW_KEY_J),
		hs_str_int("KEY_K", GLFW_KEY_K),
		hs_str_int("KEY_L", GLFW_KEY_L),
		hs_str_int("KEY_M", GLFW_KEY_M),
		hs_str_int("KEY_N", GLFW_KEY_N),
		hs_str_int("KEY_O", GLFW_KEY_O),
		hs_str_int("KEY_P", GLFW_KEY_P),
		hs_str_int("KEY_Q", GLFW_KEY_Q),
		hs_str_int("KEY_R", GLFW_KEY_R),
		hs_str_int("KEY_S", GLFW_KEY_S),
		hs_str_int("KEY_T", GLFW_KEY_T),
		hs_str_int("KEY_U", GLFW_KEY_U),
		hs_str_int("KEY_V", GLFW_KEY_V),
		hs_str_int("KEY_W", GLFW_KEY_W),
		hs_str_int("KEY_X", GLFW_KEY_X),
		hs_str_int("KEY_Y", GLFW_KEY_Y),
		hs_str_int("KEY_Z", GLFW_KEY_Z),
		hs_str_int("KEY_LEFT_BRACKET", GLFW_KEY_LEFT_BRACKET),
		hs_str_int("KEY_BACKSLASH", GLFW_KEY_BACKSLASH),
		hs_str_int("KEY_RIGHT_BRACKET", GLFW_KEY_RIGHT_BRACKET),
		hs_str_int("KEY_GRAVE_ACCENT", GLFW_KEY_GRAVE_ACCENT),
		hs_str_int("KEY_WORLD_1", GLFW_KEY_WORLD_1),
		hs_str_int("KEY_WORLD_2", GLFW_KEY_WORLD_2),
		hs_str_int("KEY_ESCAPE", GLFW_KEY_ESCAPE),
		hs_str_int("KEY_ENTER", GLFW_KEY_ENTER),
		hs_str_int("KEY_TAB", GLFW_KEY_TAB),
		hs_str_int("KEY_BACKSPACE", GLFW_KEY_BACKSPACE),
		hs_str_int("KEY_INSERT", GLFW_KEY_INSERT),
		hs_str_int("KEY_DELETE", GLFW_KEY_DELETE),
		hs_str_int("KEY_RIGHT", GLFW_KEY_RIGHT),
		hs_str_int("KEY_LEFT", GLFW_KEY_LEFT),
		hs_str_int("KEY_DOWN", GLFW_KEY_DOWN),
		hs_str_int("KEY_UP", GLFW_KEY_UP),
		hs_str_int("KEY_PAGE_UP", GLFW_KEY_PAGE_UP),
		hs_str_int("KEY_PAGE_DOWN", GLFW_KEY_PAGE_DOWN),
		hs_str_int("KEY_HOME", GLFW_KEY_HOME),
		hs_str_int("KEY_END", GLFW_KEY_END),
		hs_str_int("KEY_CAPS_LOCK", GLFW_KEY_CAPS_LOCK),
		hs_str_int("KEY_SCROLL_LOCK", GLFW_KEY_SCROLL_LOCK),
		hs_str_int("KEY_NUM_LOCK", GLFW_KEY_NUM_LOCK),
		hs_str_int("KEY_PRINT_SCREEN", GLFW_KEY_PRINT_SCREEN),
		hs_str_int("KEY_PAUSE", GLFW_KEY_PAUSE),
		hs_str_int("KEY_F1", GLFW_KEY_F1),
		hs_str_int("KEY_F2", GLFW_KEY_F2),
		hs_str_int("KEY_F3", GLFW_KEY_F3),
		hs_str_int("KEY_F4", GLFW_KEY_F4),
		hs_str_int("KEY_F5", GLFW_KEY_F5),
		hs_str_int("KEY_F6", GLFW_KEY_F6),
		hs_str_int("KEY_F7", GLFW_KEY_F7),
		hs_str_int("KEY_F8", GLFW_KEY_F8),
		hs_str_int("KEY_F9", GLFW_KEY_F9),
		hs_str_int("KEY_F", GLFW_KEY_F),
		hs_str_int("KEY_F", GLFW_KEY_F),
		hs_str_int("KEY_F", GLFW_KEY_F),
		hs_str_int("KEY_F", GLFW_KEY_F),
		hs_str_int("KEY_F", GLFW_KEY_F),
		hs_str_int("KEY_F", GLFW_KEY_F),
		hs_str_int("KEY_F", GLFW_KEY_F),
		hs_str_int("KEY_F", GLFW_KEY_F),
		hs_str_int("KEY_F", GLFW_KEY_F),
		hs_str_int("KEY_F", GLFW_KEY_F),
		hs_str_int("KEY_F", GLFW_KEY_F),
		hs_str_int("KEY_F", GLFW_KEY_F),
		hs_str_int("KEY_F", GLFW_KEY_F),
		hs_str_int("KEY_F", GLFW_KEY_F),
		hs_str_int("KEY_F", GLFW_KEY_F),
		hs_str_int("KEY_F", GLFW_KEY_F),
		hs_str_int("KEY_KP_0", GLFW_KEY_KP_0),
		hs_str_int("KEY_KP_1", GLFW_KEY_KP_1),
		hs_str_int("KEY_KP_2", GLFW_KEY_KP_2),
		hs_str_int("KEY_KP_3", GLFW_KEY_KP_3),
		hs_str_int("KEY_KP_4", GLFW_KEY_KP_4),
		hs_str_int("KEY_KP_5", GLFW_KEY_KP_5),
		hs_str_int("KEY_KP_6", GLFW_KEY_KP_6),
		hs_str_int("KEY_KP_7", GLFW_KEY_KP_7),
		hs_str_int("KEY_KP_8", GLFW_KEY_KP_8),
		hs_str_int("KEY_KP_9", GLFW_KEY_KP_9),
		hs_str_int("KEY_KP_DECIMAL", GLFW_KEY_KP_DECIMAL),
		hs_str_int("KEY_KP_DIVIDE", GLFW_KEY_KP_DIVIDE),
		hs_str_int("KEY_KP_MULTIPLY", GLFW_KEY_KP_MULTIPLY),
		hs_str_int("KEY_KP_SUBTRACT", GLFW_KEY_KP_SUBTRACT),
		hs_str_int("KEY_KP_ADD", GLFW_KEY_KP_ADD),
		hs_str_int("KEY_KP_ENTER", GLFW_KEY_KP_ENTER),
		hs_str_int("KEY_KP_EQUAL", GLFW_KEY_KP_EQUAL),
		hs_str_int("KEY_LEFT_SHIFT", GLFW_KEY_LEFT_SHIFT),
		hs_str_int("KEY_LEFT_CONTROL", GLFW_KEY_LEFT_CONTROL),
		hs_str_int("KEY_LEFT_ALT", GLFW_KEY_LEFT_ALT),
		hs_str_int("KEY_LEFT_SUPER", GLFW_KEY_LEFT_SUPER),
		hs_str_int("KEY_RIGHT_SHIFT", GLFW_KEY_RIGHT_SHIFT),
		hs_str_int("KEY_RIGHT_CONTROL", GLFW_KEY_RIGHT_CONTROL),
		hs_str_int("KEY_RIGHT_ALT", GLFW_KEY_RIGHT_ALT),
		hs_str_int("KEY_RIGHT_SUPER", GLFW_KEY_RIGHT_SUPER),
		hs_str_int("KEY_MENU", GLFW_KEY_MENU),
	};

	hs_create_table_(L, sizeof(tbl)/sizeof(struct hs_tbl_entry), tbl);
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
		lua_call(wdata->L, 3, 0);
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


int window_set_should_close(lua_State *L)
{
	GLFWwindow **win = luaL_checkudata(L, 1, window_tname);
	int value = lua_toboolean(L, 2);

	glfwSetWindowShouldClose(*win, value);
	return 0;
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


int window_get_cursor_pos(lua_State *L)
{
	GLFWwindow **win = luaL_checkudata(L, 1, window_tname);
	double x, y;
	glfwGetCursorPos(*win, &x, &y);
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	return 2;
}


int window_set_input_mode(lua_State *L)
{
	GLFWwindow **win = luaL_checkudata(L, 1, window_tname);
	int mode = luaL_checkinteger(L, 2);
	int value = luaL_checkinteger(L, 3);

	glfwSetInputMode(*win, mode, value);
	return 0;
}
