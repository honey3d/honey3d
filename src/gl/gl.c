#include <stdlib.h>
#include <stdbool.h>
#include "gl/glad/glad.h"
#include <GLFW/glfw3.h>
#include <lua.h>
#include <honeysuckle.h>
#include "gl.h"

/* needs to be here because glad uses macros to define glBufferData */
#ifdef HONEY_TEST_H
#undef glBufferData
#define glBufferData mock_glBufferData_
#endif


int gl_init(lua_State *L);
int glad_init(lua_State *L);
int gl_terminate(lua_State *L);
int gl_get_error(lua_State *L);

void setup_gl(lua_State *L, int honey_index)
{
	int data_types = hs_create_table(L,
		hs_str_int("uint", GL_UNSIGNED_INT),
		hs_str_int("int", GL_INT),
		hs_str_int("float", GL_FLOAT),
	);

	int error_types = hs_create_table(L,
		hs_str_int("noError", GL_NO_ERROR),
		hs_str_int("invalidEnum", GL_INVALID_ENUM),
		hs_str_int("invalidValue", GL_INVALID_VALUE),
		hs_str_int("invalidOperation", GL_INVALID_OPERATION),
		hs_str_int("invalidFramebufferOperation", GL_INVALID_FRAMEBUFFER_OPERATION),
		hs_str_int("outOfMemory", GL_OUT_OF_MEMORY),
	);

	int gl_index = hs_create_table(L,
		hs_str_cfunc("init", gl_init),
		hs_str_cfunc("initGlad", glad_init),
		hs_str_cfunc("terminate", gl_terminate),
		hs_str_cfunc("getError", gl_get_error),

		hs_str_tbl("dataType", data_types),
		hs_str_tbl("errorType", error_types),
	);

	setup_shader(L, gl_index);
	setup_drawing(L, gl_index);
	setup_data(L, gl_index);
	lua_setfield(L, honey_index, "gl");
}


int gl_init(lua_State *L)
{
	if (!glfwInit()) {
		hs_throw_error(L, "failed to initialize GLFW");
	}
	return 0;
}


int glad_init(lua_State *L)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		hs_throw_error(L, "failed to initialize GLAD");
	}
}


int gl_terminate(lua_State *L)
{
	glfwTerminate();
	return 0;
}


int gl_get_error(lua_State *L)
{
	lua_pushinteger(L, glGetError());
	return 1;
}
