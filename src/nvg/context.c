#include <lua.h>
#include <lauxlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg.h>
#include <nanovg_gl.h>
#include "nvg.h"


int nvgCreateContext_bind(lua_State *L)
{
	struct NVGcontext **vg = lua_newuserdata(L, sizeof(struct NVGcontext *));
	*vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
	luaL_getmetatable(L, nvg_ctx_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int nvgDeleteContext_bind(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgDeleteGL3(*vg);
	return 0;
}
