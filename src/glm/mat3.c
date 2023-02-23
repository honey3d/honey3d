#include <lua.h>
#include <lauxlib.h>
#include <cglm/cglm.h>
#include "glm.h"


int glm_mat3_create(lua_State *L)
{
	lua_newuserdata(L, sizeof(mat3));
	luaL_getmetatable(L, glm_mat3_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int glm_mat3_set(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	int col = luaL_checkinteger(L, 2);
	int row = luaL_checkinteger(L, 3);
	float value = luaL_checknumber(L, 4);
	(*m)[col][row] = value;
	return 0;
}


int glm_mat3_get(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	int col = luaL_checkinteger(L, 2);
	int row = luaL_checkinteger(L, 3);
	lua_pushnumber(L, (*m)[col][row]);
	return 1;
}


int glm_mat3_copy_bind(lua_State *L)
{
	mat3 *mat = luaL_checkudata(L, 1, glm_mat3_tname);
	mat3 *dest = luaL_checkudata(L, 2, glm_mat3_tname);
	glm_mat3_copy(*mat, *dest);
	return 0;
}


int glm_mat3_identity_bind(lua_State *L)
{
	mat3 *mat = luaL_checkudata(L, 1, glm_mat3_tname);
	glm_mat3_identity(*mat);
	return 0;
}


int glm_mat3_zero_bind(lua_State *L)
{
	mat3 *mat = luaL_checkudata(L, 1, glm_mat3_tname);
	glm_mat3_zero(*mat);
	return 0;
}


int glm_mat3_mul_bind(lua_State *L)
{
	mat3 *m1 = luaL_checkudata(L, 1, glm_mat3_tname);
	mat3 *m2 = luaL_checkudata(L, 2, glm_mat3_tname);
	mat3 *dest = luaL_checkudata(L, 3, glm_mat3_tname);
	glm_mat3_mul(*m1, *m2, *dest);
	return 0;
}


int glm_mat3_transpose_to_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	mat3 *dest = luaL_checkudata(L, 2, glm_mat3_tname);
	glm_mat3_transpose_to(*m, *dest);
	return 0;
}


int glm_mat3_transpose_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	glm_mat3_transpose(*m);
	return 0;
}


int glm_mat3_mulv_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	vec3 *v = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_mat3_mulv(*m, *v, *dest);
	return 0;
}


int glm_mat3_quat_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	versor *dest = luaL_checkudata(L, 2, glm_versor_tname);
	glm_mat3_quat(*m, *dest);
	return 0;
}


int glm_mat3_scale_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	float s = luaL_checknumber(L, 2);
	glm_mat3_scale(*m, s);
	return 0;
}


int glm_mat3_det_bind(lua_State *L)
{
	mat3 *mat = luaL_checkudata(L, 1, glm_mat3_tname);
	float bind_result = glm_mat3_det(*mat);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_mat3_inv_bind(lua_State *L)
{
	mat3 *mat = luaL_checkudata(L, 1, glm_mat3_tname);
	mat3 *dest = luaL_checkudata(L, 2, glm_mat3_tname);
	glm_mat3_inv(*mat, *dest);
	return 0;
}


int glm_mat3_trace_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	glm_mat3_trace(*m);
	return 0;
}


int glm_mat3_swap_col_bind(lua_State *L)
{
	mat3 *mat = luaL_checkudata(L, 1, glm_mat3_tname);
	int col1 = luaL_checkinteger(L, 2);
	int col2 = luaL_checkinteger(L, 3);
	glm_mat3_swap_col(*mat, col1, col2);
	return 0;
}


int glm_mat3_swap_row_bind(lua_State *L)
{
	mat3 *mat = luaL_checkudata(L, 1, glm_mat3_tname);
	int row1 = luaL_checkinteger(L, 2);
	int row2 = luaL_checkinteger(L, 3);
	glm_mat3_swap_row(*mat, row1, row2);
	return 0;
}


int glm_mat3_rmc_bind(lua_State *L)
{
	vec3 *r = luaL_checkudata(L, 1, glm_vec3_tname);
	mat3 *m = luaL_checkudata(L, 2, glm_mat3_tname);
	vec3 *c = luaL_checkudata(L, 3, glm_vec3_tname);
	float bind_result = glm_mat3_rmc(*r, *m, *c);
	lua_pushnumber(L, bind_result);
	return 1;
}
