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
int gl_enable(lua_State *L);
int gl_disable(lua_State *L);

void setup_gl(lua_State *L, int honey_index)
{
	int gl_index = hs_create_table(L,
		/* functions */
		hs_str_cfunc("Init", gl_init),
		hs_str_cfunc("InitGlad", glad_init),
		hs_str_cfunc("Terminate", gl_terminate),
		hs_str_cfunc("GetError", gl_get_error),
		hs_str_cfunc("Enable", gl_enable),
		hs_str_cfunc("Disable", gl_disable),

		/******** enums ********/
		/* data types */
		hs_str_int("UNSIGNED_BYTE", GL_UNSIGNED_BYTE),
		hs_str_int("UNSIGNED_INT", GL_UNSIGNED_INT),
		hs_str_int("INT", GL_INT),
		hs_str_int("FLOAT", GL_FLOAT),

		/* error types */
		hs_str_int("NO_ERROR", GL_NO_ERROR),
		hs_str_int("INVALID_ENUM", GL_INVALID_ENUM),
		hs_str_int("INVALID_VALUE", GL_INVALID_VALUE),
		hs_str_int("INVALID_OPERATION", GL_INVALID_OPERATION),
		hs_str_int("INVALID_FRAMEBUFFER_OPERATION", GL_INVALID_FRAMEBUFFER_OPERATION),
		hs_str_int("OUT_OF_MEMORY", GL_OUT_OF_MEMORY),

		/* opengl capabilities */
		hs_str_int("DEPTH_TEST", GL_DEPTH_TEST),
	);

	setup_shader(L, gl_index);
	setup_drawing(L, gl_index);
	setup_data(L, gl_index);
	setup_texture(L, gl_index);

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


int gl_enable(lua_State *L)
{
	lua_Integer cap;
	hs_parse_args(L, hs_int(cap));
	glEnable(cap);
	return 0;
}


int gl_disable(lua_State *L)
{
	lua_Integer cap;
	hs_parse_args(L, hs_int(cap));
	glDisable(cap);
	return 0;
}
