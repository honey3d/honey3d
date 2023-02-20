#include <lua.h>
#include <lauxlib.h>
#include <nanovg.h>
#include <nanovg_gl.h>
#include "nvg.h"


/* --===== paths =====-- */

int nvgBeginPath_bind(lua_State *L)
{
	struct NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgBeginPath(*ctx);
	return 0;
}


int nvgMoveTo_bind(lua_State *L)
{
	struct NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	nvgMoveTo(*ctx, x, y);	
	return 0;
}


int nvgLineTo_bind(lua_State *L)
{
	struct NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	nvgLineTo(*ctx, x, y);	
	return 0;
}


int nvgBezierTo_bind(lua_State *L)
{
	struct NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float c1x = luaL_checknumber(L, 2);
	float c1y = luaL_checknumber(L, 3);
	float c2x = luaL_checknumber(L, 4);
	float c2y = luaL_checknumber(L, 5);
	float x   = luaL_checknumber(L, 6);
	float y   = luaL_checknumber(L, 7);
	nvgBezierTo(*ctx, c1x, c1y, c2x, c2y, x, y);	
	return 0;
}


int nvgQuadTo_bind(lua_State *L)
{
	struct NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float cx = luaL_checknumber(L, 2);
	float cy = luaL_checknumber(L, 3);
	float x  = luaL_checknumber(L, 4);
	float y  = luaL_checknumber(L, 5);
	nvgQuadTo(*ctx, cx, cy, x, y);	
	return 0;
}


int nvgArcTo_bind(lua_State *L)
{
	struct NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x1 = luaL_checknumber(L, 2);
	float y1 = luaL_checknumber(L, 3);
	float x2 = luaL_checknumber(L, 4);
	float y2 = luaL_checknumber(L, 5);
	float radius = luaL_checknumber(L, 6);
	nvgArcTo(*ctx, x1, y1, x2, y2, radius);
	return 0;
}


int nvgClosePath_bind(lua_State *L)
{
	struct NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgClosePath(*ctx);
	return 0;
}


int nvgPathWinding_bind(lua_State *L)
{
	struct NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	int dir = luaL_checkinteger(L, 2);
	nvgPathWinding(*ctx, dir);
	return 0;
}


int nvgArc_bind(lua_State *L)
{
	struct NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float cx = luaL_checknumber(L, 2);
	float cy = luaL_checknumber(L, 3);
	float r  = luaL_checknumber(L, 4);
	float a0 = luaL_checknumber(L, 5);
	float a1 = luaL_checknumber(L, 6);
	int dir  = luaL_checkinteger(L, 7);
	nvgArc(*ctx, cx, cy, r, a0, a1, dir);
	return 0;
}


int nvgRect_bind(lua_State *L)
{
	struct NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float w = luaL_checknumber(L, 4);
	float h = luaL_checknumber(L, 5);
	nvgRect(*ctx, x, y, w, h);
	return 0;
}

int nvgRoundedRect_bind(lua_State *L)
{
	struct NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float w = luaL_checknumber(L, 4);
	float h = luaL_checknumber(L, 5);
	float r = luaL_checknumber(L, 6);
	nvgRoundedRect(*ctx, x, y, w, h, r);
	return 0;
}

int nvgRoundedRectVarying_bind(lua_State *L)
{
	struct NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float w = luaL_checknumber(L, 4);
	float h = luaL_checknumber(L, 5);
	float rtl = luaL_checknumber(L, 6);
	float rtr = luaL_checknumber(L, 7);
	float rbl = luaL_checknumber(L, 8);
	float rbr = luaL_checknumber(L, 9);
	nvgRoundedRectVarying(*ctx, x, y, w, h, rtl, rtr, rbl, rbr);
	return 0;
}

int nvgEllipse_bind(lua_State *L)
{
	struct NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float cx = luaL_checknumber(L, 2);
	float cy = luaL_checknumber(L, 3);
	float rx = luaL_checknumber(L, 4);
	float ry = luaL_checknumber(L, 5);
	nvgEllipse(*ctx, cx, cy, rx, ry);
	return 0;
}

int nvgCircle_bind(lua_State *L)
{
	struct NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float cx = luaL_checknumber(L, 2);
	float cy = luaL_checknumber(L, 3);
	float r = luaL_checknumber(L, 4);
	nvgCircle(*ctx, cx, cy, r);
	return 0;
}

int nvgFill_bind(lua_State *L)
{
	struct NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgFill(*ctx);
	return 0;
}


int nvgStroke_bind(lua_State *L)
{
	struct NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgStroke(*ctx);
	return 0;
}
