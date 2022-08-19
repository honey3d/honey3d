#include "gl/glad/glad.h"
#include <GLFW/glfw3.h>
#include <lua.h>
#include <honeysuckle.h>

int gl_init(lua_State *L)
{
	if (!glfwInit()) {
		hs_throw_error(L, "failed to initialize GLFW");
	}
	return 0;
}


int gl_terminate(lua_State *L)
{
	glfwTerminate();
	return 0;
}
