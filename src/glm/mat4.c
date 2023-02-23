#include <lua.h>
#include <lauxlib.h>
#include <cglm/cglm.h>
#include "glm.h"


int glm_mat4_create(lua_State *L)
{
	lua_newuserdata(L, sizeof(mat4));
	luaL_getmetatable(L, glm_mat4_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int glm_mat4_set(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	int col = luaL_checkinteger(L, 2);
	int row = luaL_checkinteger(L, 3);
	float value = luaL_checknumber(L, 4);
	(*m)[col][row] = value;
	return 0;
}


int glm_mat4_get(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	int col = luaL_checkinteger(L, 2);
	int row = luaL_checkinteger(L, 3);
	lua_pushnumber(L, (*m)[col][row]);
	return 1;
}


int glm_mat4_ucopy_bind(lua_State *L)
{
	mat4 *mat = luaL_checkudata(L, 1, glm_mat4_tname);
	mat4 *dest = luaL_checkudata(L, 2, glm_mat4_tname);
	glm_mat4_ucopy(*mat, *dest);
	return 0;
}


int glm_mat4_copy_bind(lua_State *L)
{
	mat4 *mat = luaL_checkudata(L, 1, glm_mat4_tname);
	mat4 *dest = luaL_checkudata(L, 2, glm_mat4_tname);
	glm_mat4_copy(*mat, *dest);
	return 0;
}


int glm_mat4_identity_bind(lua_State *L)
{
	mat4 *mat = luaL_checkudata(L, 1, glm_mat4_tname);
	glm_mat4_identity(*mat);
	return 0;
}


int glm_mat4_zero_bind(lua_State *L)
{
	mat4 *mat = luaL_checkudata(L, 1, glm_mat4_tname);
	glm_mat4_zero(*mat);
	return 0;
}


int glm_mat4_pick3_bind(lua_State *L)
{
	mat4 *mat = luaL_checkudata(L, 1, glm_mat4_tname);
	mat3 *dest = luaL_checkudata(L, 2, glm_mat3_tname);
	glm_mat4_pick3(*mat, *dest);
	return 0;
}


int glm_mat4_pick3t_bind(lua_State *L)
{
	mat4 *mat = luaL_checkudata(L, 1, glm_mat4_tname);
	mat3 *dest = luaL_checkudata(L, 2, glm_mat3_tname);
	glm_mat4_pick3t(*mat, *dest);
	return 0;
}


int glm_mat4_ins3_bind(lua_State *L)
{
	mat3 *mat = luaL_checkudata(L, 1, glm_mat3_tname);
	mat4 *dest = luaL_checkudata(L, 2, glm_mat4_tname);
	glm_mat4_ins3(*mat, *dest);
	return 0;
}


int glm_mat4_mul_bind(lua_State *L)
{
	mat4 *m1 = luaL_checkudata(L, 1, glm_mat4_tname);
	mat4 *m2 = luaL_checkudata(L, 2, glm_mat4_tname);
	mat4 *dest = luaL_checkudata(L, 3, glm_mat4_tname);
	glm_mat4_mul(*m1, *m2, *dest);
	return 0;
}


int glm_mat4_mulv_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	vec4 *v = luaL_checkudata(L, 2, glm_vec4_tname);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_mat4_mulv(*m, *v, *dest);
	return 0;
}


int glm_mat4_mulv3_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	vec3 *v = luaL_checkudata(L, 2, glm_vec3_tname);
	float last = luaL_checknumber(L, 3);
	vec3 *dest = luaL_checkudata(L, 4, glm_vec3_tname);
	glm_mat4_mulv3(*m, *v, last, *dest);
	return 0;
}


int glm_mat4_trace_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	glm_mat4_trace(*m);
	return 0;
}


int glm_mat4_trace3_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	glm_mat4_trace3(*m);
	return 0;
}


int glm_mat4_quat_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	versor *dest = luaL_checkudata(L, 2, glm_versor_tname);
	glm_mat4_quat(*m, *dest);
	return 0;
}


int glm_mat4_transpose_to_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	mat4 *dest = luaL_checkudata(L, 2, glm_mat4_tname);
	glm_mat4_transpose_to(*m, *dest);
	return 0;
}


int glm_mat4_transpose_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	glm_mat4_transpose(*m);
	return 0;
}


int glm_mat4_scale_p_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	float s = luaL_checknumber(L, 2);
	glm_mat4_scale_p(*m, s);
	return 0;
}


int glm_mat4_scale_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	float s = luaL_checknumber(L, 2);
	glm_mat4_scale(*m, s);
	return 0;
}


int glm_mat4_det_bind(lua_State *L)
{
	mat4 *mat = luaL_checkudata(L, 1, glm_mat4_tname);
	float bind_result = glm_mat4_det(*mat);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_mat4_inv_bind(lua_State *L)
{
	mat4 *mat = luaL_checkudata(L, 1, glm_mat4_tname);
	mat4 *dest = luaL_checkudata(L, 2, glm_mat4_tname);
	glm_mat4_inv(*mat, *dest);
	return 0;
}


int glm_mat4_inv_fast_bind(lua_State *L)
{
	mat4 *mat = luaL_checkudata(L, 1, glm_mat4_tname);
	mat4 *dest = luaL_checkudata(L, 2, glm_mat4_tname);
	glm_mat4_inv_fast(*mat, *dest);
	return 0;
}


int glm_mat4_swap_col_bind(lua_State *L)
{
	mat4 *mat = luaL_checkudata(L, 1, glm_mat4_tname);
	int col1 = luaL_checkinteger(L, 2);
	int col2 = luaL_checkinteger(L, 3);
	glm_mat4_swap_col(*mat, col1, col2);
	return 0;
}


int glm_mat4_swap_row_bind(lua_State *L)
{
	mat4 *mat = luaL_checkudata(L, 1, glm_mat4_tname);
	int row1 = luaL_checkinteger(L, 2);
	int row2 = luaL_checkinteger(L, 3);
	glm_mat4_swap_row(*mat, row1, row2);
	return 0;
}


int glm_mat4_rmc_bind(lua_State *L)
{
	vec4 *r = luaL_checkudata(L, 1, glm_vec4_tname);
	mat4 *m = luaL_checkudata(L, 2, glm_mat4_tname);
	vec4 *c = luaL_checkudata(L, 3, glm_vec4_tname);
	float bind_result = glm_mat4_rmc(*r, *m, *c);
	lua_pushnumber(L, bind_result);
	return 1;
}
