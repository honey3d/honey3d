#include <lua.h>
#include <lauxlib.h>
#include <nanovg.h>
#include <nanovg_gl.h>
#include "nvg.h"


int nvgResetTransform_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgResetTransform(*ctx);
	return 0;
}


int nvgTransform_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float a = luaL_checknumber(L, 2);
	float b = luaL_checknumber(L, 3);
	float c = luaL_checknumber(L, 4);
	float d = luaL_checknumber(L, 5);
	float e = luaL_checknumber(L, 6);
	float f = luaL_checknumber(L, 7);
	nvgTransform(*ctx, a, b, c, d, e, f);
	return 0;
}


int nvgTranslate_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	nvgTranslate(*ctx, x, y);
	return 0;
}


int nvgRotate_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float angle = luaL_checknumber(L, 2);
	nvgRotate(*ctx, angle);
	return 0;
}


int nvgSkewX_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float angle = luaL_checknumber(L, 2);
	nvgSkewX(*ctx, angle);
	return 0;
}


int nvgSkewY_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float angle = luaL_checknumber(L, 2);
	nvgSkewY(*ctx, angle);
	return 0;
}


int nvgScale_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	nvgScale(*ctx, x, y);
	return 0;
}


int nvgCurrentTransform_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float xform[6];
	nvgCurrentTransform(*ctx, xform);
	for (int i=0; i<6; i++) {
		lua_pushnumber(L, xform[i]);
	}
	return 6;
}
