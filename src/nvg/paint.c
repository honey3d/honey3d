#include <lua.h>
#include <lauxlib.h>
#include <nanovg.h>
#include <nanovg_gl.h>
#include "nvg.h"


static void create_paint(lua_State *L, NVGpaint paint)
{
	NVGpaint *p = lua_newuserdata(L, sizeof(NVGpaint));
	*p = paint;
	luaL_getmetatable(L, nvg_paint_tname);
	lua_setmetatable(L, -2);
}

int nvgLinearGradient_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float sx = luaL_checknumber(L, 2);
	float sy = luaL_checknumber(L, 3);
	float ex = luaL_checknumber(L, 4);
	float ey = luaL_checknumber(L, 5);
	NVGcolor *icol = luaL_checkudata(L, 6, nvg_color_tname);
	NVGcolor *ocol = luaL_checkudata(L, 7, nvg_color_tname);
	create_paint(L,
		nvgLinearGradient(*ctx, sx, sy, ex, ey, *icol, *ocol)
	);
	return 1;
}

int nvgBoxGradient_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float w = luaL_checknumber(L, 4);
	float h = luaL_checknumber(L, 5);
	float r = luaL_checknumber(L, 6);
	float f = luaL_checknumber(L, 7);
	NVGcolor *icol = luaL_checkudata(L, 8, nvg_color_tname);
	NVGcolor *ocol = luaL_checkudata(L, 9, nvg_color_tname);
	create_paint(L,
		nvgBoxGradient(*ctx, x, y, w, h, r, f, *icol, *ocol)
	);
	return 1;
}

int nvgRadialGradient_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float cx = luaL_checknumber(L, 2);
	float cy = luaL_checknumber(L, 3);
	float inr = luaL_checknumber(L, 4);
	float outr = luaL_checknumber(L, 5);
	NVGcolor *icol = luaL_checkudata(L, 6, nvg_color_tname);
	NVGcolor *ocol = luaL_checkudata(L, 7, nvg_color_tname);
	create_paint(L,
		nvgRadialGradient(*ctx, cx, cy, inr, outr, *icol, *ocol)
	);
	return 1;
}

int nvgImagePattern_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float ox = luaL_checknumber(L, 2);
	float oy = luaL_checknumber(L, 3);
	float ex = luaL_checknumber(L, 4);
	float ey = luaL_checknumber(L, 5);
	float angle = luaL_checknumber(L, 6);
	int image = luaL_checkinteger(L, 7);
	float alpha = luaL_checknumber(L, 8);
	create_paint(L,
		nvgImagePattern(*ctx, ox, oy, ex, ey, angle, image, alpha)
	);
	return 1;
}
