#include "gl/glad/glad.h"
#include <GLFW/glfw3.h>
#include <lua.h>


int gl_init(lua_State *L)
{
	if (glfwInit() != GLFW_TRUE) {
		hs_throw_error(L, "failed to initialize GLFW");
	}
	return 0;
}
