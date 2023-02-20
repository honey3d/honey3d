#include <lua.h>
#include <lauxlib.h>
#include <nanovg.h>
#include <nanovg_gl.h>
#include "nvg.h"


int nvgScissor_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float w = luaL_checknumber(L, 4);
	float h = luaL_checknumber(L, 5);
	nvgScissor(*ctx, x, y, w, h);
	return 0;
}

int nvgIntersectScissor_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float w = luaL_checknumber(L, 4);
	float h = luaL_checknumber(L, 5);
	nvgIntersectScissor(*ctx, x, y, w, h);
	return 0;
}

int nvgResetScissor_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgResetScissor(*ctx);
	return 0;
}
