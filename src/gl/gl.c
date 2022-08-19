#include "gl/glad/glad.h"
#include <GLFW/glfw3.h>
#include <lua.h>
#include <honeysuckle.h>


int gl_init(lua_State *L);
int gl_terminate(lua_State *L);


void setup_gl(lua_State *L, int honey_index)
{
	hs_create_table(L,
		hs_str_cfunc("init", gl_init),
		hs_str_cfunc("terminate", gl_terminate)
	);
	lua_setfield(L, honey_index, "gl");
}


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
