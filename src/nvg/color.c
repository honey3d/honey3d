#include <lua.h>
#include <lauxlib.h>
#include <nanovg.h>
#include "nvg.h"


static NVGcolor * create_color(lua_State *L)
{
	NVGcolor *color = lua_newuserdata(L, sizeof(NVGcolor));
	luaL_getmetatable(L, nvg_color_tname);
	lua_setmetatable(L, -2);
	return color;
}


int nvgRGB_bind(lua_State *L)
{
	unsigned char r, g, b;
	r = luaL_checkinteger(L, 1);
	g = luaL_checkinteger(L, 2);
	b = luaL_checkinteger(L, 3);
	NVGcolor *c = create_color(L);
	*c = nvgRGB(r, g, b);
	return 1;
}


int nvgRGBf_bind(lua_State *L)
{
	float r, g, b;
	r = luaL_checknumber(L, 1);
	g = luaL_checknumber(L, 2);
	b = luaL_checknumber(L, 3);
	NVGcolor *c = create_color(L);
	*c = nvgRGBf(r, g, b);
	return 1;
}


int nvgRGBA_bind(lua_State *L)
{
	unsigned char r, g, b, a;
	r = luaL_checkinteger(L, 1);
	g = luaL_checkinteger(L, 2);
	b = luaL_checkinteger(L, 3);
	a = luaL_checkinteger(L, 4);
	NVGcolor *c = create_color(L);
	*c = nvgRGBA(r, g, b, a);
	return 1;
}


int nvgRGBAf_bind(lua_State *L)
{
	float r, g, b, a;
	r = luaL_checknumber(L, 1);
	g = luaL_checknumber(L, 2);
	b = luaL_checknumber(L, 3);
	a = luaL_checknumber(L, 4);
	NVGcolor *c = create_color(L);
	*c = nvgRGBAf(r, g, b, a);
	return 1;
}


int nvgLerpRGBA_bind(lua_State *L)
{
	NVGcolor *c0 = luaL_checkudata(L, 1, nvg_color_tname);
	NVGcolor *c1 = luaL_checkudata(L, 2, nvg_color_tname);
	float u = luaL_checknumber(L, 3);
	NVGcolor *result = create_color(L);
	*result = nvgLerpRGBA(*c0, *c1, u);
	return 1;
}


int nvgTransRGBA_bind(lua_State *L)
{
	NVGcolor *c0 = luaL_checkudata(L, 1, nvg_color_tname);
	unsigned char a = luaL_checkinteger(L, 2);
	NVGcolor *result = create_color(L);
	*result = nvgTransRGBA(*c0, a);
	return 1;
}


int nvgTransRGBAf_bind(lua_State *L)
{
	NVGcolor *c0 = luaL_checkudata(L, 1, nvg_color_tname);
	float a = luaL_checknumber(L, 2);
	NVGcolor *result = create_color(L);
	*result = nvgTransRGBAf(*c0, a);
	return 1;
}


int nvgHSL_bind(lua_State *L)
{
	float h = luaL_checknumber(L, 1);
	float s = luaL_checknumber(L, 2);
	float l = luaL_checknumber(L, 3);
	NVGcolor *result = create_color(L);
	*result = nvgHSL(h, s, l);
	return 1;
}


int nvgHSLA_bind(lua_State *L)
{
	float h = luaL_checknumber(L, 1);
	float s = luaL_checknumber(L, 2);
	float l = luaL_checknumber(L, 3);
	unsigned char a = luaL_checkinteger(L, 4);
	NVGcolor *result = create_color(L);
	*result = nvgHSLA(h, s, l, a);
	return 1;
}
