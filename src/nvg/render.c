#include <lua.h>
#include <lauxlib.h>
#include <nanovg.h>
#include <nanovg_gl.h>
#include "nvg.h"


int	ShapeAntiAlias_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	int enabled = luaL_toboolean(L, 2);
	nvgShapeAntiAlias(*ctx, enabled);
	return 0;
}


int nvgStrokeColor_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	NVGcolor *color = luaL_checkudata(L, 2, nvg_color_tname);
	nvgStrokeColor(*ctx, *color);
	return 0;
}


int nvgStrokePaint_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	NVGpaint *paint = luaL_checkudata(L, 2, nvg_paint_tname);
	nvgStrokePaint(*ctx, *paint);
	return 0;
}


int nvgFillColor_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	NVGcolor *color = luaL_checkudata(L, 2, nvg_color_tname);
	nvgFillColor(*ctx, *color);
	return 0;
}


int nvgFillPaint_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	NVGpaint *paint = luaL_checkudata(L, 2, nvg_paint_tname);
	nvgFillPaint(*ctx, *paint);
	return 0;
}


int nvgMiterLimit_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float limit = luaL_checknumber(L, 2);
	nvgMiterLimit(*ctx, limit);
	return 0;
}


int nvgStrokeWidth_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float width = luaL_checknumber(L, 2);
	nvgStrokeWidth(*ctx, width);
	return 0;
}


int nvgLineCap_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	int cap = luaL_checkinteger(L, 2);
	nvgLineCap(*ctx, cap);
	return 0;
}


int nvgLineJoin_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	int join = luaL_checkinteger(L, 2);
	nvgLineJoin(*ctx, join);
	return 0;
}


int nvgGlobalAlpha_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float alpha = luaL_checknumber(L, 2);
	nvgGlobalAlpha(*ctx, alpha);
	return 0;
}
