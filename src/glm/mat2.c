#include <lua.h>
#include <lauxlib.h>
#include <cglm/cglm.h>
#include "glm.h"


int glm_mat2_create(lua_State *L)
{
	lua_newuserdata(L, sizeof(mat2));
	luaL_getmetatable(L, glm_mat2_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int glm_mat2_set(lua_State *L)
{
	mat2 *m = luaL_checkudata(L, 1, glm_mat2_tname);
	int col = luaL_checkinteger(L, 2);
	int row = luaL_checkinteger(L, 3);
	float value = luaL_checknumber(L, 4);
	(*m)[col][row] = value;
	return 0;
}


int glm_mat2_get(lua_State *L)
{
	mat2 *m = luaL_checkudata(L, 1, glm_mat2_tname);
	int col = luaL_checkinteger(L, 2);
	int row = luaL_checkinteger(L, 3);
	lua_pushnumber(L, (*m)[col][row]);
	return 1;
}


int glm_mat2_copy_bind(lua_State *L)
{
	mat2 *mat = luaL_checkudata(L, 1, glm_mat2_tname);
	mat2 *dest = luaL_checkudata(L, 2, glm_mat2_tname);
	glm_mat2_copy(*mat, *dest);
	return 0;
}


int glm_mat2_identity_bind(lua_State *L)
{
	mat2 *mat = luaL_checkudata(L, 1, glm_mat2_tname);
	glm_mat2_identity(*mat);
	return 0;
}


int glm_mat2_zero_bind(lua_State *L)
{
	mat2 *mat = luaL_checkudata(L, 1, glm_mat2_tname);
	glm_mat2_zero(*mat);
	return 0;
}


int glm_mat2_mul_bind(lua_State *L)
{
	mat2 *m1 = luaL_checkudata(L, 1, glm_mat2_tname);
	mat2 *m2 = luaL_checkudata(L, 2, glm_mat2_tname);
	mat2 *dest = luaL_checkudata(L, 3, glm_mat2_tname);
	glm_mat2_mul(*m1, *m2, *dest);
	return 0;
}


int glm_mat2_transpose_to_bind(lua_State *L)
{
	mat2 *m = luaL_checkudata(L, 1, glm_mat2_tname);
	mat2 *dest = luaL_checkudata(L, 2, glm_mat2_tname);
	glm_mat2_transpose_to(*m, *dest);
	return 0;
}


int glm_mat2_transpose_bind(lua_State *L)
{
	mat2 *m = luaL_checkudata(L, 1, glm_mat2_tname);
	glm_mat2_transpose(*m);
	return 0;
}


int glm_mat2_mulv_bind(lua_State *L)
{
	mat2 *m = luaL_checkudata(L, 1, glm_mat2_tname);
	vec2 *v = luaL_checkudata(L, 2, glm_vec2_tname);
	vec2 *dest = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_mat2_mulv(*m, *v, *dest);
	return 0;
}


int glm_mat2_scale_bind(lua_State *L)
{
	mat2 *m = luaL_checkudata(L, 1, glm_mat2_tname);
	float s = luaL_checknumber(L, 2);
	glm_mat2_scale(*m, s);
	return 0;
}


int glm_mat2_det_bind(lua_State *L)
{
	mat2 *mat = luaL_checkudata(L, 1, glm_mat2_tname);
	float bind_result = glm_mat2_det(*mat);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_mat2_inv_bind(lua_State *L)
{
	mat2 *mat = luaL_checkudata(L, 1, glm_mat2_tname);
	mat2 *dest = luaL_checkudata(L, 2, glm_mat2_tname);
	glm_mat2_inv(*mat, *dest);
	return 0;
}


int glm_mat2_trace_bind(lua_State *L)
{
	mat2 *m = luaL_checkudata(L, 1, glm_mat2_tname);
	glm_mat2_trace(*m);
	return 0;
}


int glm_mat2_swap_col_bind(lua_State *L)
{
	mat2 *mat = luaL_checkudata(L, 1, glm_mat2_tname);
	int col1 = luaL_checkinteger(L, 2);
	int col2 = luaL_checkinteger(L, 3);
	glm_mat2_swap_col(*mat, col1, col2);
	return 0;
}


int glm_mat2_swap_row_bind(lua_State *L)
{
	mat2 *mat = luaL_checkudata(L, 1, glm_mat2_tname);
	int row1 = luaL_checkinteger(L, 2);
	int row2 = luaL_checkinteger(L, 3);
	glm_mat2_swap_row(*mat, row1, row2);
	return 0;
}


int glm_mat2_rmc_bind(lua_State *L)
{
	vec2 *r = luaL_checkudata(L, 1, glm_vec2_tname);
	mat2 *m = luaL_checkudata(L, 2, glm_mat2_tname);
	vec2 *c = luaL_checkudata(L, 3, glm_vec2_tname);
	float bind_result = glm_mat2_rmc(*r, *m, *c);
	lua_pushnumber(L, bind_result);
	return 1;
}
