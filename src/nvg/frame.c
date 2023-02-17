#include <lua.h>
#include <lauxlib.h>
#include <nanovg.h>
#include "nvg.h"


int nvgBeginFrame_bind(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	float width      = luaL_checknumber(L, 2);
	float height     = luaL_checknumber(L, 3);
	float pixelRatio = luaL_checknumber(L, 4);

	nvgBeginFrame(*vg, width, height, pixelRatio);
	return 0;
}


int nvgCancelFrame_bind(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgCancelFrame(*vg);
	return 0;
}


int nvgEndFrame_bind(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgEndFrame(*vg);
	return 0;
}
