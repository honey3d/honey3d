#include <lua.h>
#include <lauxlib.h>
#include <cglm/cglm.h>
#include "glm.h"


int glm_vec2_create(lua_State *L)
{
	lua_newuserdata(L, sizeof(vec2));
	luaL_getmetatable(L, glm_vec2_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int glm_vec2_set(lua_State *L)
{
	vec2 *vec = luaL_checkudata(L, 1, glm_vec2_tname);
	int index = luaL_checkinteger(L, 2);
	double value = luaL_checknumber(L, 3);
	(*vec)[index] = value;
	return 0;
}


int glm_vec2_get(lua_State *L)
{
	vec2 *vec = luaL_checkudata(L, 1, glm_vec2_tname);
	int index = luaL_checkinteger(L, 2);
	lua_pushnumber(L, (*vec)[index]);
	return 1;
}


int glm_vec2_bind(lua_State *L)
{
	luaL_checktype(L, 1, LUA_TUSERDATA);
	float **v = lua_touserdata(L, 1);
	vec2 *dest = luaL_checkudata(L, 2, glm_vec2_tname);
	glm_vec2(*v, *dest);
	return 0;
}


int glm_vec2_copy_bind(lua_State *L)
{
	vec2 *a = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *dest = luaL_checkudata(L, 2, glm_vec2_tname);
	glm_vec2_copy(*a, *dest);
	return 0;
}


int glm_vec2_zero_bind(lua_State *L)
{
	vec2 *v = luaL_checkudata(L, 1, glm_vec2_tname);
	glm_vec2_zero(*v);
	return 0;
}


int glm_vec2_one_bind(lua_State *L)
{
	vec2 *v = luaL_checkudata(L, 1, glm_vec2_tname);
	glm_vec2_one(*v);
	return 0;
}


int glm_vec2_dot_bind(lua_State *L)
{
	vec2 *a = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *b = luaL_checkudata(L, 2, glm_vec2_tname);
	float bind_result = glm_vec2_dot(*a, *b);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_vec2_cross_bind(lua_State *L)
{
	vec2 *a = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *b = luaL_checkudata(L, 2, glm_vec2_tname);
	glm_vec2_cross(*a, *b);
	return 0;
}


int glm_vec2_norm2_bind(lua_State *L)
{
	vec2 *v = luaL_checkudata(L, 1, glm_vec2_tname);
	float bind_result = glm_vec2_norm2(*v);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_vec2_norm_bind(lua_State *L)
{
	vec2 *vec = luaL_checkudata(L, 1, glm_vec2_tname);
	float bind_result = glm_vec2_norm(*vec);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_vec2_add_bind(lua_State *L)
{
	vec2 *a = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *b = luaL_checkudata(L, 2, glm_vec2_tname);
	vec2 *dest = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_vec2_add(*a, *b, *dest);
	return 0;
}


int glm_vec2_adds_bind(lua_State *L)
{
	vec2 *a = luaL_checkudata(L, 1, glm_vec2_tname);
	float s = luaL_checknumber(L, 2);
	vec2 *dest = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_vec2_adds(*a, s, *dest);
	return 0;
}


int glm_vec2_sub_bind(lua_State *L)
{
	vec2 *v1 = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *v2 = luaL_checkudata(L, 2, glm_vec2_tname);
	vec2 *dest = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_vec2_sub(*v1, *v2, *dest);
	return 0;
}


int glm_vec2_subs_bind(lua_State *L)
{
	vec2 *v = luaL_checkudata(L, 1, glm_vec2_tname);
	float s = luaL_checknumber(L, 2);
	vec2 *dest = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_vec2_subs(*v, s, *dest);
	return 0;
}


int glm_vec2_mul_bind(lua_State *L)
{
	vec2 *a = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *b = luaL_checkudata(L, 2, glm_vec2_tname);
	vec2 *d = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_vec2_mul(*a, *b, *d);
	return 0;
}


int glm_vec2_scale_bind(lua_State *L)
{
	vec2 *v = luaL_checkudata(L, 1, glm_vec2_tname);
	float s = luaL_checknumber(L, 2);
	vec2 *dest = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_vec2_scale(*v, s, *dest);
	return 0;
}


int glm_vec2_scale_as_bind(lua_State *L)
{
	vec2 *v = luaL_checkudata(L, 1, glm_vec2_tname);
	float s = luaL_checknumber(L, 2);
	vec2 *dest = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_vec2_scale_as(*v, s, *dest);
	return 0;
}


int glm_vec2_div_bind(lua_State *L)
{
	vec2 *a = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *b = luaL_checkudata(L, 2, glm_vec2_tname);
	vec2 *dest = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_vec2_div(*a, *b, *dest);
	return 0;
}


int glm_vec2_divs_bind(lua_State *L)
{
	vec2 *v = luaL_checkudata(L, 1, glm_vec2_tname);
	float s = luaL_checknumber(L, 2);
	vec2 *dest = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_vec2_divs(*v, s, *dest);
	return 0;
}


int glm_vec2_addadd_bind(lua_State *L)
{
	vec2 *a = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *b = luaL_checkudata(L, 2, glm_vec2_tname);
	vec2 *dest = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_vec2_addadd(*a, *b, *dest);
	return 0;
}


int glm_vec2_subadd_bind(lua_State *L)
{
	vec2 *a = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *b = luaL_checkudata(L, 2, glm_vec2_tname);
	vec2 *dest = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_vec2_subadd(*a, *b, *dest);
	return 0;
}


int glm_vec2_muladd_bind(lua_State *L)
{
	vec2 *a = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *b = luaL_checkudata(L, 2, glm_vec2_tname);
	vec2 *dest = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_vec2_muladd(*a, *b, *dest);
	return 0;
}


int glm_vec2_muladds_bind(lua_State *L)
{
	vec2 *a = luaL_checkudata(L, 1, glm_vec2_tname);
	float s = luaL_checknumber(L, 2);
	vec2 *dest = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_vec2_muladds(*a, s, *dest);
	return 0;
}


int glm_vec2_maxadd_bind(lua_State *L)
{
	vec2 *a = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *b = luaL_checkudata(L, 2, glm_vec2_tname);
	vec2 *dest = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_vec2_maxadd(*a, *b, *dest);
	return 0;
}


int glm_vec2_minadd_bind(lua_State *L)
{
	vec2 *a = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *b = luaL_checkudata(L, 2, glm_vec2_tname);
	vec2 *dest = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_vec2_minadd(*a, *b, *dest);
	return 0;
}


int glm_vec2_negate_bind(lua_State *L)
{
	vec2 *v = luaL_checkudata(L, 1, glm_vec2_tname);
	glm_vec2_negate(*v);
	return 0;
}


int glm_vec2_negate_to_bind(lua_State *L)
{
	vec2 *v = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *dest = luaL_checkudata(L, 2, glm_vec2_tname);
	glm_vec2_negate_to(*v, *dest);
	return 0;
}


int glm_vec2_normalize_bind(lua_State *L)
{
	vec2 *v = luaL_checkudata(L, 1, glm_vec2_tname);
	glm_vec2_normalize(*v);
	return 0;
}


int glm_vec2_normalize_to_bind(lua_State *L)
{
	vec2 *vec = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *dest = luaL_checkudata(L, 2, glm_vec2_tname);
	glm_vec2_normalize_to(*vec, *dest);
	return 0;
}


int glm_vec2_rotate_bind(lua_State *L)
{
	vec2 *v = luaL_checkudata(L, 1, glm_vec2_tname);
	float angle = luaL_checknumber(L, 2);
	vec2 *dest = luaL_checkudata(L, 2, glm_vec2_tname);
	glm_vec2_rotate(*v, angle, *dest);
	return 0;
}


int glm_vec2_distance2_bind(lua_State *L)
{
	vec2 *v1 = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *v2 = luaL_checkudata(L, 2, glm_vec2_tname);
	float bind_result = glm_vec2_distance2(*v1, *v2);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_vec2_distance_bind(lua_State *L)
{
	vec2 *v1 = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *v2 = luaL_checkudata(L, 2, glm_vec2_tname);
	float bind_result = glm_vec2_distance(*v1, *v2);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_vec2_maxv_bind(lua_State *L)
{
	vec2 *v1 = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *v2 = luaL_checkudata(L, 2, glm_vec2_tname);
	vec2 *dest = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_vec2_maxv(*v1, *v2, *dest);
	return 0;
}


int glm_vec2_minv_bind(lua_State *L)
{
	vec2 *v1 = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *v2 = luaL_checkudata(L, 2, glm_vec2_tname);
	vec2 *dest = luaL_checkudata(L, 3, glm_vec2_tname);
	glm_vec2_minv(*v1, *v2, *dest);
	return 0;
}


int glm_vec2_clamp_bind(lua_State *L)
{
	vec2 *v = luaL_checkudata(L, 1, glm_vec2_tname);
	float minVal = luaL_checknumber(L, 2);
	float maxVal = luaL_checknumber(L, 3);
	glm_vec2_clamp(*v, minVal, maxVal);
	return 0;
}


int glm_vec2_lerp_bind(lua_State *L)
{
	vec2 *from = luaL_checkudata(L, 1, glm_vec2_tname);
	vec2 *to = luaL_checkudata(L, 2, glm_vec2_tname);
	float t = luaL_checknumber(L, 3);
	vec2 *dest = luaL_checkudata(L, 4, glm_vec2_tname);
	glm_vec2_lerp(*from, *to, t, *dest);
	return 0;
}
