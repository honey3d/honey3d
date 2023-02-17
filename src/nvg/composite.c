#include <lua.h>
#include <lauxlib.h>
#include <nanovg.h>
#include "nvg.h"


int nvgGlobalCompositeOperation_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	int op = luaL_checkinteger(L, 2);
	nvgGlobalCompositeOperation(*ctx, op);
	return 0;
}


int nvgGlobalCompositeBlendFunc_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	int sfactor = luaL_checkinteger(L, 2);
	int dfactor = luaL_checkinteger(L, 3);
	nvgGlobalCompositeBlendFunc(*ctx, sfactor, dfactor);
	return 0;
}


int nvgGlobalCompositeBlendFuncSeparate_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	int src_rgb = luaL_checkinteger(L, 2);
	int dst_rgb = luaL_checkinteger(L, 3);
	int src_alpha = luaL_checkinteger(L, 4);
	int dst_alpha = luaL_checkinteger(L, 5);
	nvgGlobalCompositeBlendFuncSeparate(*ctx, src_rgb, dst_rgb, src_alpha, dst_alpha);
	return 0;
}
