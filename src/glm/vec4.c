#include <lua.h>
#include <lauxlib.h>
#include <cglm/cglm.h>
#include "glm.h"


int glm_vec4_create(lua_State *L)
{
	lua_newuserdata(L, sizeof(vec4));
	luaL_getmetatable(L, glm_vec4_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int glm_vec4_set(lua_State *L)
{
	vec4 *vec = luaL_checkudata(L, 1, glm_vec4_tname);
	int index = luaL_checkinteger(L, 2);
	double value = luaL_checknumber(L, 3);
	(*vec)[index] = value;
	return 0;
}


int glm_vec4_get(lua_State *L)
{
	vec4 *vec = luaL_checkudata(L, 1, glm_vec4_tname);
	int index = luaL_checkinteger(L, 2);
	lua_pushnumber(L, (*vec)[index]);
	return 1;
}


int glm_vec4_bind(lua_State *L)
{
	vec3 *v3 = luaL_checkudata(L, 1, glm_vec3_tname);
	float last = luaL_checknumber(L, 2);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4(*v3, last, *dest);
	return 0;
}


int glm_vec4_copy3_bind(lua_State *L)
{
	vec4 *a = luaL_checkudata(L, 1, glm_vec4_tname);
	vec3 *dest = luaL_checkudata(L, 2, glm_vec3_tname);
	glm_vec4_copy3(*a, *dest);
	return 0;
}


int glm_vec4_copy_bind(lua_State *L)
{
	vec4 *v = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *dest = luaL_checkudata(L, 2, glm_vec4_tname);
	glm_vec4_copy(*v, *dest);
	return 0;
}


int glm_vec4_ucopy_bind(lua_State *L)
{
	vec4 *v = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *dest = luaL_checkudata(L, 2, glm_vec4_tname);
	glm_vec4_ucopy(*v, *dest);
	return 0;
}


int glm_vec4_zero_bind(lua_State *L)
{
	vec4 *v = luaL_checkudata(L, 1, glm_vec4_tname);
	glm_vec4_zero(*v);
	return 0;
}


int glm_vec4_dot_bind(lua_State *L)
{
	vec4 *a = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *b = luaL_checkudata(L, 2, glm_vec4_tname);
	float bind_result = glm_vec4_dot(*a, *b);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_vec4_norm2_bind(lua_State *L)
{
	vec4 *v = luaL_checkudata(L, 1, glm_vec4_tname);
	float bind_result = glm_vec4_norm2(*v);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_vec4_norm_bind(lua_State *L)
{
	vec4 *vec = luaL_checkudata(L, 1, glm_vec4_tname);
	float bind_result = glm_vec4_norm(*vec);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_vec4_add_bind(lua_State *L)
{
	vec4 *a = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *b = luaL_checkudata(L, 2, glm_vec4_tname);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4_add(*a, *b, *dest);
	return 0;
}


int glm_vec4_adds_bind(lua_State *L)
{
	vec4 *v = luaL_checkudata(L, 1, glm_vec4_tname);
	float s = luaL_checknumber(L, 2);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4_adds(*v, s, *dest);
	return 0;
}


int glm_vec4_sub_bind(lua_State *L)
{
	vec4 *a = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *b = luaL_checkudata(L, 2, glm_vec4_tname);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4_sub(*a, *b, *dest);
	return 0;
}


int glm_vec4_subs_bind(lua_State *L)
{
	vec4 *v = luaL_checkudata(L, 1, glm_vec4_tname);
	float s = luaL_checknumber(L, 2);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4_subs(*v, s, *dest);
	return 0;
}


int glm_vec4_mul_bind(lua_State *L)
{
	vec4 *a = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *b = luaL_checkudata(L, 2, glm_vec4_tname);
	vec4 *d = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4_mul(*a, *b, *d);
	return 0;
}


int glm_vec4_scale_bind(lua_State *L)
{
	vec4 *v = luaL_checkudata(L, 1, glm_vec4_tname);
	float s = luaL_checknumber(L, 2);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4_scale(*v, s, *dest);
	return 0;
}


int glm_vec4_scale_as_bind(lua_State *L)
{
	vec4 *v = luaL_checkudata(L, 1, glm_vec4_tname);
	float s = luaL_checknumber(L, 2);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4_scale_as(*v, s, *dest);
	return 0;
}


int glm_vec4_div_bind(lua_State *L)
{
	vec4 *a = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *b = luaL_checkudata(L, 2, glm_vec4_tname);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4_div(*a, *b, *dest);
	return 0;
}


int glm_vec4_divs_bind(lua_State *L)
{
	vec4 *v = luaL_checkudata(L, 1, glm_vec4_tname);
	float s = luaL_checknumber(L, 2);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4_divs(*v, s, *dest);
	return 0;
}


int glm_vec4_addadd_bind(lua_State *L)
{
	vec4 *a = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *b = luaL_checkudata(L, 2, glm_vec4_tname);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4_addadd(*a, *b, *dest);
	return 0;
}


int glm_vec4_subadd_bind(lua_State *L)
{
	vec4 *a = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *b = luaL_checkudata(L, 2, glm_vec4_tname);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4_subadd(*a, *b, *dest);
	return 0;
}


int glm_vec4_muladd_bind(lua_State *L)
{
	vec4 *a = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *b = luaL_checkudata(L, 2, glm_vec4_tname);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4_muladd(*a, *b, *dest);
	return 0;
}


int glm_vec4_muladds_bind(lua_State *L)
{
	vec4 *a = luaL_checkudata(L, 1, glm_vec4_tname);
	float s = luaL_checknumber(L, 2);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4_muladds(*a, s, *dest);
	return 0;
}


int glm_vec4_maxadd_bind(lua_State *L)
{
	vec4 *a = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *b = luaL_checkudata(L, 2, glm_vec4_tname);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4_maxadd(*a, *b, *dest);
	return 0;
}


int glm_vec4_minadd_bind(lua_State *L)
{
	vec4 *a = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *b = luaL_checkudata(L, 2, glm_vec4_tname);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4_minadd(*a, *b, *dest);
	return 0;
}


int glm_vec4_flipsign_bind(lua_State *L)
{
	vec4 *v = luaL_checkudata(L, 1, glm_vec4_tname);
	glm_vec4_flipsign(*v);
	return 0;
}


int glm_vec4_flipsign_to_bind(lua_State *L)
{
	vec4 *v = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *dest = luaL_checkudata(L, 2, glm_vec4_tname);
	glm_vec4_flipsign_to(*v, *dest);
	return 0;
}


int glm_vec4_inv_bind(lua_State *L)
{
	vec4 *v = luaL_checkudata(L, 1, glm_vec4_tname);
	glm_vec4_inv(*v);
	return 0;
}


int glm_vec4_inv_to_bind(lua_State *L)
{
	vec4 *v = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *dest = luaL_checkudata(L, 2, glm_vec4_tname);
	glm_vec4_inv_to(*v, *dest);
	return 0;
}


int glm_vec4_negate_bind(lua_State *L)
{
	vec4 *v = luaL_checkudata(L, 1, glm_vec4_tname);
	glm_vec4_negate(*v);
	return 0;
}


int glm_vec4_negate_to_bind(lua_State *L)
{
	vec4 *v = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *dest = luaL_checkudata(L, 2, glm_vec4_tname);
	glm_vec4_negate_to(*v, *dest);
	return 0;
}


int glm_vec4_normalize_bind(lua_State *L)
{
	vec4 *v = luaL_checkudata(L, 1, glm_vec4_tname);
	glm_vec4_normalize(*v);
	return 0;
}


int glm_vec4_normalize_to_bind(lua_State *L)
{
	vec4 *vec = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *dest = luaL_checkudata(L, 2, glm_vec4_tname);
	glm_vec4_normalize_to(*vec, *dest);
	return 0;
}


int glm_vec4_distance_bind(lua_State *L)
{
	vec4 *v1 = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *v2 = luaL_checkudata(L, 2, glm_vec4_tname);
	float bind_result = glm_vec4_distance(*v1, *v2);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_vec4_maxv_bind(lua_State *L)
{
	vec4 *v1 = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *v2 = luaL_checkudata(L, 2, glm_vec4_tname);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4_maxv(*v1, *v2, *dest);
	return 0;
}


int glm_vec4_minv_bind(lua_State *L)
{
	vec4 *v1 = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *v2 = luaL_checkudata(L, 2, glm_vec4_tname);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_vec4_minv(*v1, *v2, *dest);
	return 0;
}


int glm_vec4_clamp_bind(lua_State *L)
{
	vec4 *v = luaL_checkudata(L, 1, glm_vec4_tname);
	float minVal = luaL_checknumber(L, 2);
	float maxVal = luaL_checknumber(L, 3);
	glm_vec4_clamp(*v, minVal, maxVal);
	return 0;
}


int glm_vec4_lerp_bind(lua_State *L)
{
	vec4 *from = luaL_checkudata(L, 1, glm_vec4_tname);
	vec4 *to = luaL_checkudata(L, 2, glm_vec4_tname);
	float t = luaL_checknumber(L, 3);
	vec4 *dest = luaL_checkudata(L, 4, glm_vec4_tname);
	glm_vec4_lerp(*from, *to, t, *dest);
	return 0;
}


int glm_vec4_cubic_bind(lua_State *L)
{
	float s = luaL_checknumber(L, 1);
	vec4 *dest = luaL_checkudata(L, 2, glm_vec4_tname);
	glm_vec4_cubic(s, *dest);
	return 0;
}
