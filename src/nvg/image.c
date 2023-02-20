#include <lua.h>
#include <lauxlib.h>
#include <nanovg.h>
#include <nanovg_gl.h>
#include "nvg.h"


int nvgCreateImage_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	const char *filename = luaL_checkstring(L, 2);
	int flags = luaL_checkinteger(L, 3);
	int handle = nvgCreateImage(*ctx, filename, flags);
	lua_pushinteger(L, handle);
	return 1;
}


int nvgImageSize_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	int handle = luaL_checkinteger(L, 2);
	int w, h;
	nvgImageSize(*ctx, handle, &w, &h);
	lua_pushinteger(L, w);
	lua_pushinteger(L, h);
	return 2;
}


int nvgDeleteImage_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	int handle = luaL_checkinteger(L, 2);
	nvgDeleteImage(*ctx, handle);
	return 0;
}
