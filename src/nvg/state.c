#include <lua.h>
#include <lauxlib.h>
#include <nanovg.h>
#include <nanovg_gl.h>
#include "nvg.h"


int nvgSave_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgSave(*ctx);
	return 0;
}


int nvgRestore_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgRestore(*ctx);
	return 0;
}


int nvgReset_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgReset(*ctx);
	return 0;
}
