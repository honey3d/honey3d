/* --===== paths =====-- */

int nvg_begin_path(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, ctx_tname);
	nvgBeginPath(*vg);
	return 0;
}


int nvg_move_to(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	nvgMoveTo(*vg, x, y);	
	return 0;
}


int nvg_line_to(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, ctx_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	nvgLineTo(*vg, x, y);	
	return 0;
}


int nvg_bezier_to(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, ctx_tname);
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
	struct NVGcontext **vg = luaL_checkudata(L, 1, ctx_tname);
	float cx = luaL_checknumber(L, 2);
	float cy = luaL_checknumber(L, 3);
	float x  = luaL_checknumber(L, 4);
	float y  = luaL_checknumber(L, 5);
	nvgQuadTo(*vg, cx, cy, x, y);	
	return 0;
}


int nvg_arc_to(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, ctx_tname);
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
	struct NVGcontext **vg = luaL_checkudata(L, 1, ctx_tname);
	nvgClosePath(*vg);
	return 0;
}


int nvg_path_winding(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, ctx_tname);
	int dir = luaL_checkinteger(L, 2);
	nvgPathWinding(*vg, dir);
	return 0;
}


int nvg_arc(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, ctx_tname);
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
	struct NVGcontext **vg = luaL_checkudata(L, 1, ctx_tname);
	nvgFill(*vg);
	return 0;
}


int nvg_stroke(lua_State *L)
{
	struct NVGcontext **vg = luaL_checkudata(L, 1, ctx_tname);
	nvgStroke(*vg);
	return 0;
}


