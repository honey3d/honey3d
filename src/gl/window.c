#include "gl/glad/glad.h"
#include <GLFW/glfw3.h>
#include <lua.h>
#include <honeysuckle.h>


void create_glfw_window_hints_table(lua_State *L)
{
	hs_create_table(L,
		hs_str_int("resizable", GLFW_RESIZABLE)
	);
}

int gl_init(lua_State *L)
{
	if (glfwInit() != GLFW_TRUE) {
		hs_throw_error(L, "failed to initialize GLFW");
	}
	return 0;
}
