#include <lua.h>
#include <lauxlib.h>
#include <nanovg.h>
#include <nanovg_gl.h>
#include "nvg.h"


int nvgCreateFont_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	const char *name = luaL_checkstring(L, 2);
	const char *filename = luaL_checkstring(L, 3);
	lua_pushinteger(L,
		nvgCreateFont(*ctx, name, filename)
	);
	return 1;
}

int nvgCreateFontAtIndex_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	const char *name = luaL_checkstring(L, 2);
	const char *filename = luaL_checkstring(L, 3);
	int index = luaL_checkinteger(L, 4);
	lua_pushinteger(L,
		nvgCreateFontAtIndex(*ctx, name, filename, index)
	);
	return 1;

}

int nvgFindFont_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	const char *name = luaL_checkstring(L, 2);
	lua_pushinteger(L,
		nvgFindFont(*ctx, name)
	);
	return 1;
}

int nvgAddFallbackFontId_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	int baseFont = luaL_checkinteger(L, 2);
	int fallbackFont = luaL_checkinteger(L, 3);
	int font = nvgAddFallbackFontId(*ctx, baseFont, fallbackFont);
	lua_pushinteger(L, font);
	return 1;
}

int nvgAddFallbackFont_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	const char *baseFont = luaL_checkstring(L, 2);
	const char *fallbackFont = luaL_checkstring(L, 3);
	int font = nvgAddFallbackFont(*ctx, baseFont, fallbackFont);
	lua_pushinteger(L, font);
	return 1;
}

int nvgResetFallbackFontsId_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	int baseFont = luaL_checkinteger(L, 2);
	nvgResetFallbackFontsId(*ctx, baseFont);
	return 0;
}

int nvgResetFallbackFonts_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	const char *baseFont = luaL_checkstring(L, 2);
	nvgResetFallbackFonts(*ctx, baseFont);
	return 0;
}

int nvgFontSize_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float size = luaL_checknumber(L, 2);
	nvgFontSize(*ctx, size);
	return 0;
}

int nvgFontBlur_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float blur = luaL_checknumber(L, 2);
	nvgFontBlur(*ctx, blur);
	return 0;
}

int nvgTextLetterSpacing_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float spacing = luaL_checknumber(L, 2);
	nvgTextLetterSpacing(*ctx, spacing);
	return 0;
}

int nvgTextLineHeight_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float lineHeight = luaL_checknumber(L, 2);
	nvgTextLineHeight(*ctx, lineHeight);
	return 0;
}

int nvgTextAlign_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	int align = luaL_checkinteger(L, 2);
	nvgTextAlign(*ctx, align);
	return 0;
}

int nvgFontFaceId_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	int font = luaL_checknumber(L, 2);
	nvgFontFaceId(*ctx, font);
	return 0;
}

int nvgFontFace_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	const char *font = luaL_checkstring(L, 2);
	nvgFontFace(*ctx, font);
	return 0;
}

int nvgText_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	const char *string = luaL_checkstring(L, 4);
	nvgText(*ctx, x, y, string, NULL);
	return 0;
}

int nvgTextBox_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float breakRowWidth = luaL_checknumber(L, 4);
	const char *string = luaL_checkstring(L, 5);
	nvgTextBox(*ctx, x, y, breakRowWidth, string, NULL);
	return 0;
}

int nvgTextBounds_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	const char *string = luaL_checkstring(L, 4);
	float bounds[4];
	nvgTextBounds(*ctx, x, y, string, NULL, bounds);
	for (int i=0; i<4; i++) {
		lua_pushnumber(L, bounds[i]);
	}
	return 4;
}

int nvgTextBoxBounds_bind(lua_State *L)
{
	NVGcontext **ctx = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	const char *string = luaL_checkstring(L, 4);
	float breakRowWidth = luaL_checknumber(L, 5);
	float bounds[4];
	nvgTextBoxBounds(*ctx, x, y, breakRowWidth, string, NULL, bounds);
	for (int i=0; i<4; i++) {
		lua_pushnumber(L, bounds[i]);
	}
	return 4;
}
