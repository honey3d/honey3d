#include <lua.h>
#include <honeysuckle.h>
#include "gl/glad/glad.h"
#include <GLFW/glfw3.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg.h>
#include <nanovg_gl.h>
#include "vector.h"


static const char *nvg_ctx_tname = "nvg.Context";


/* --===== contexts =====-- */

int nvg_context(lua_State *L)
{
	struct NVGcontext **vg = lua_newuserdata(L, sizeof(struct NVGcontext *));
	*vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
	luaL_getmetatable(L, nvg_ctx_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int nvg_delete(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgDeleteGL3(*vg);
	return 0;
}


/* --===== frames =====-- */

int nvg_begin_frame(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	float width      = luaL_checknumber(L, 2);
	float height     = luaL_checknumber(L, 3);
	float pixelRatio = luaL_checknumber(L, 4);

	nvgBeginFrame(*vg, width, height, pixelRatio);
	return 0;
}


int nvg_cancel_frame(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgCancelFrame(*vg);
	return 0;
}


int nvg_end_frame(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgEndFrame(*vg);
	return 0;
}


/* --===== paths =====-- */

int nvg_begin_path(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgBeginPath(*vg);
	return 0;
}


int nvg_move_to(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	nvgMoveTo(*vg, x, y);	
	return 0;
}


int nvg_line_to(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	nvgLineTo(*vg, x, y);	
	return 0;
}


int nvg_bezier_to(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	float c1x = luaL_checknumber(L, 2);
	float c1y = luaL_checknumber(L, 3);
	float c2x = luaL_checknumber(L, 4);
	float c2y = luaL_checknumber(L, 5);
	float x   = luaL_checknumber(L, 6);
	float y   = luaL_checknumber(L, 7);
	nvgBezierTo(*vg, c1x, c1y, c2x, c2y, x, y);	
	return 0;
}


int nvg_quad_to(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	float cx = luaL_checknumber(L, 2);
	float cy = luaL_checknumber(L, 3);
	float x  = luaL_checknumber(L, 4);
	float y  = luaL_checknumber(L, 5);
	nvgQuadTo(*vg, cx, cy, x, y);	
	return 0;
}


int nvg_arc_to(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	float x1 = luaL_checknumber(L, 2);
	float y1 = luaL_checknumber(L, 3);
	float x2 = luaL_checknumber(L, 4);
	float y2 = luaL_checknumber(L, 5);
	float radius = luaL_checknumber(L, 6);
	nvgArcTo(*vg, x1, y1, x2, y2, radius);
	return 0;
}


int nvg_close_path(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgClosePath(*vg);
	return 0;
}


int nvg_path_winding(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	int dir = luaL_checkinteger(L, 2);
	nvgPathWinding(*vg, dir);
	return 0;
}


int nvg_arc(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	float cx = luaL_checknumber(L, 2);
	float cy = luaL_checknumber(L, 3);
	float r  = luaL_checknumber(L, 4);
	float a0 = luaL_checknumber(L, 5);
	float a1 = luaL_checknumber(L, 6);
	int dir  = luaL_checkinteger(L, 7);
	nvgArc(*vg, cx, cy, r, a0, a1, dir);
	return 0;
}

/* ... */

int nvg_fill(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgFill(*vg);
	return 0;
}


int nvg_stroke(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	nvgStroke(*vg);
	return 0;
}


/* --===== render styles =====-- */

int nvg_stroke_color(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	NVGcolor color;
	color.r = luaL_checknumber(L, 2);
	color.g = luaL_checknumber(L, 3);
	color.b = luaL_checknumber(L, 4);
	color.a = luaL_checknumber(L, 5);
	nvgStrokeColor(*vg, color);
	return 0;
}


int nvg_stroke_width(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, nvg_ctx_tname);
	float size = luaL_checknumber(L, 2);
	nvgStrokeWidth(*vg, size);
	return 0;
}


/* --===== complete =====-- */

void setup_nvg(lua_State *L, int honey_tbl)
{
	luaL_newmetatable(L, nvg_ctx_tname);
	lua_pushcfunction(L, nvg_delete);
	lua_setfield(L, -2, "__gc");
	lua_pop(L, 1);

	hs_create_table(L,
		hs_str_cfunc("Context", nvg_context),

		hs_str_cfunc("BeginFrame", nvg_begin_frame),
		hs_str_cfunc("CancelFrame", nvg_cancel_frame),
		hs_str_cfunc("EndFrame", nvg_end_frame),

		hs_str_cfunc("BeginPath", nvg_begin_path),
		hs_str_cfunc("MoveTo", nvg_move_to),
		hs_str_cfunc("LineTo", nvg_line_to),
		hs_str_cfunc("BezierTo", nvg_bezier_to),
		hs_str_cfunc("QuadTo", nvg_quad_to),
		hs_str_cfunc("ArcTo", nvg_arc_to),
		hs_str_cfunc("ClosePath", nvg_close_path),
		hs_str_cfunc("PathWinding", nvg_path_winding),
		hs_str_cfunc("Arc", nvg_arc),
		hs_str_cfunc("Fill", nvg_fill),
		hs_str_cfunc("Stroke", nvg_stroke),

		hs_str_cfunc("StrokeColor", nvg_stroke_color),
		hs_str_cfunc("StrokeWidth", nvg_stroke_width),
	);

	lua_setfield(L, honey_tbl, "nvg");
}
