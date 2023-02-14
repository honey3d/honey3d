#include <lua.h>
#include <honeysuckle.h>
#include "gl/glad/glad.h"
#include <GLFW/glfw3.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg.h>
#include <nanovg_gl.h>
#include "vector.h"


static const char *nvg_ctx_tname = "nvg.Context";


/* --===== contexts =====-- */

int nvg_context(lua_State *L)
{
	struct NVGcontext **vg = lua_newuserdata(L, sizeof(struct NVGcontext *));
	*vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
	luaL_getmetatable(L, nvg_ctx_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int nvg_delete(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgDeleteGL3(*vg);
	return 0;
}


/* --===== frames =====-- */

int nvg_begin_frame(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	float width      = luaL_checknumber(L, 2);
	float height     = luaL_checknumber(L, 3);
	float pixelRatio = luaL_checknumber(L, 4);

	nvgBeginFrame(*vg, width, height, pixelRatio);
	return 0;
}


int nvg_cancel_frame(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgCancelFrame(*vg);
	return 0;
}


int nvg_end_frame(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgEndFrame(*vg);
	return 0;
}



/* --===== complete =====-- */

void setup_nvg(lua_State *L, int honey_tbl)
{
	luaL_newmetatable(L, nvg_ctx_tname);
	lua_pushcfunction(L, nvg_delete);
	lua_setfield(L, -2, "__gc");
	lua_pop(L, 1);

	hs_create_table(L,
		hs_str_cfunc("Context", nvg_context),

		hs_str_cfunc("BeginFrame", nvg_begin_frame),
		hs_str_cfunc("CancelFrame", nvg_cancel_frame),
		hs_str_cfunc("EndFrame", nvg_end_frame),
	);

	lua_setfield(L, honey_tbl, "nvg");
}
