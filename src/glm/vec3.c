#include <lua.h>
#include <lauxlib.h>
#include <cglm/cglm.h>
#include "util/util.h"
#include "glm.h"


int glm_vec3_create(lua_State *L)
{
	lua_newuserdata(L, sizeof(vec3));
	luaL_getmetatable(L, glm_vec3_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int glm_vec3_set(lua_State *L)
{
	vec3 *vec = luaL_checkudata(L, 1, glm_vec3_tname);
	int index = luaL_checkinteger(L, 2);
	double value = luaL_checknumber(L, 3);
	(*vec)[index] = value;
	return 0;
}


int glm_vec3_get(lua_State *L)
{
	vec3 *vec = luaL_checkudata(L, 1, glm_vec3_tname);
	int index = luaL_checkinteger(L, 2);
	lua_pushnumber(L, (*vec)[index]);
	return 1;
}


int glm_vec3_bind(lua_State *L)
{
	vec4 *v4 = luaL_checkudata(L, 1, glm_vec4_tname);
	vec3 *dest = luaL_checkudata(L, 2, glm_vec3_tname);
	glm_vec3(*v4, *dest);
	return 0;
}


int glm_vec3_copy_bind(lua_State *L)
{
	vec3 *a = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 2, glm_vec3_tname);
	glm_vec3_copy(*a, *dest);
	return 0;
}


int glm_vec3_zero_bind(lua_State *L)
{
	vec3 *v = luaL_checkudata(L, 1, glm_vec3_tname);
	glm_vec3_zero(*v);
	return 0;
}


int glm_vec3_one_bind(lua_State *L)
{
	vec3 *v = luaL_checkudata(L, 1, glm_vec3_tname);
	glm_vec3_one(*v);
	return 0;
}


int glm_vec3_dot_bind(lua_State *L)
{
	vec3 *a = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *b = luaL_checkudata(L, 2, glm_vec3_tname);
	float bind_result = glm_vec3_dot(*a, *b);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_vec3_cross_bind(lua_State *L)
{
	vec3 *a = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *b = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *d = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_cross(*a, *b, *d);
	return 0;
}


int glm_vec3_crossn_bind(lua_State *L)
{
	vec3 *a = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *b = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_crossn(*a, *b, *dest);
	return 0;
}


int glm_vec3_norm2_bind(lua_State *L)
{
	vec3 *v = luaL_checkudata(L, 1, glm_vec3_tname);
	float bind_result = glm_vec3_norm2(*v);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_vec3_norm_bind(lua_State *L)
{
	vec3 *vec = luaL_checkudata(L, 1, glm_vec3_tname);
	float bind_result = glm_vec3_norm(*vec);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_vec3_add_bind(lua_State *L)
{
	vec3 *a = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *b = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_add(*a, *b, *dest);
	return 0;
}


int glm_vec3_adds_bind(lua_State *L)
{
	vec3 *a = luaL_checkudata(L, 1, glm_vec3_tname);
	float s = luaL_checknumber(L, 2);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_adds(*a, s, *dest);
	return 0;
}


int glm_vec3_sub_bind(lua_State *L)
{
	vec3 *v1 = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *v2 = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_sub(*v1, *v2, *dest);
	return 0;
}


int glm_vec3_subs_bind(lua_State *L)
{
	vec3 *v = luaL_checkudata(L, 1, glm_vec3_tname);
	float s = luaL_checknumber(L, 2);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_subs(*v, s, *dest);
	return 0;
}


int glm_vec3_mul_bind(lua_State *L)
{
	vec3 *a = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *b = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *d = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_mul(*a, *b, *d);
	return 0;
}


int glm_vec3_scale_bind(lua_State *L)
{
	vec3 *v = luaL_checkudata(L, 1, glm_vec3_tname);
	float s = luaL_checknumber(L, 2);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_scale(*v, s, *dest);
	return 0;
}


int glm_vec3_scale_as_bind(lua_State *L)
{
	vec3 *v = luaL_checkudata(L, 1, glm_vec3_tname);
	float s = luaL_checknumber(L, 2);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_scale_as(*v, s, *dest);
	return 0;
}


int glm_vec3_div_bind(lua_State *L)
{
	vec3 *a = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *b = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_div(*a, *b, *dest);
	return 0;
}


int glm_vec3_divs_bind(lua_State *L)
{
	vec3 *v = luaL_checkudata(L, 1, glm_vec3_tname);
	float s = luaL_checknumber(L, 2);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_divs(*v, s, *dest);
	return 0;
}


int glm_vec3_addadd_bind(lua_State *L)
{
	vec3 *a = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *b = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_addadd(*a, *b, *dest);
	return 0;
}


int glm_vec3_subadd_bind(lua_State *L)
{
	vec3 *a = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *b = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_subadd(*a, *b, *dest);
	return 0;
}


int glm_vec3_muladd_bind(lua_State *L)
{
	vec3 *a = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *b = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_muladd(*a, *b, *dest);
	return 0;
}


int glm_vec3_muladds_bind(lua_State *L)
{
	vec3 *a = luaL_checkudata(L, 1, glm_vec3_tname);
	float s = luaL_checknumber(L, 2);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_muladds(*a, s, *dest);
	return 0;
}


int glm_vec3_maxadd_bind(lua_State *L)
{
	vec3 *a = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *b = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_maxadd(*a, *b, *dest);
	return 0;
}


int glm_vec3_minadd_bind(lua_State *L)
{
	vec3 *a = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *b = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_minadd(*a, *b, *dest);
	return 0;
}


int glm_vec3_flipsign_bind(lua_State *L)
{
	vec3 *v = luaL_checkudata(L, 1, glm_vec3_tname);
	glm_vec3_flipsign(*v);
	return 0;
}


int glm_vec3_flipsign_to_bind(lua_State *L)
{
	vec3 *v = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 2, glm_vec3_tname);
	glm_vec3_flipsign_to(*v, *dest);
	return 0;
}


int glm_vec3_inv_bind(lua_State *L)
{
	vec3 *v = luaL_checkudata(L, 1, glm_vec3_tname);
	glm_vec3_inv(*v);
	return 0;
}


int glm_vec3_inv_to_bind(lua_State *L)
{
	vec3 *v = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 2, glm_vec3_tname);
	glm_vec3_inv_to(*v, *dest);
	return 0;
}


int glm_vec3_negate_bind(lua_State *L)
{
	vec3 *v = luaL_checkudata(L, 1, glm_vec3_tname);
	glm_vec3_negate(*v);
	return 0;
}


int glm_vec3_negate_to_bind(lua_State *L)
{
	vec3 *v = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 2, glm_vec3_tname);
	glm_vec3_negate_to(*v, *dest);
	return 0;
}


int glm_vec3_normalize_bind(lua_State *L)
{
	vec3 *v = luaL_checkudata(L, 1, glm_vec3_tname);
	glm_vec3_normalize(*v);
	return 0;
}


int glm_vec3_normalize_to_bind(lua_State *L)
{
	vec3 *vec = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 2, glm_vec3_tname);
	glm_vec3_normalize_to(*vec, *dest);
	return 0;
}


int glm_vec3_angle_bind(lua_State *L)
{
	vec3 *v1 = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *v2 = luaL_checkudata(L, 2, glm_vec3_tname);
	float bind_result = glm_vec3_angle(*v1, *v2);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_vec3_rotate_bind(lua_State *L)
{
	vec3 *v = luaL_checkudata(L, 1, glm_vec3_tname);
	float angle = luaL_checknumber(L, 2);
	vec3 *axis = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_rotate(*v, angle, *axis);
	return 0;
}


int glm_vec3_rotate_m4_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	vec3 *v = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_rotate_m4(*m, *v, *dest);
	return 0;
}


int glm_vec3_rotate_m3_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	vec3 *v = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_rotate_m3(*m, *v, *dest);
	return 0;
}


int glm_vec3_proj_bind(lua_State *L)
{
	vec3 *a = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *b = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_proj(*a, *b, *dest);
	return 0;
}


int glm_vec3_center_bind(lua_State *L)
{
	vec3 *v1 = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *v2 = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_center(*v1, *v2, *dest);
	return 0;
}


int glm_vec3_distance2_bind(lua_State *L)
{
	vec3 *v1 = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *v2 = luaL_checkudata(L, 2, glm_vec3_tname);
	float bind_result = glm_vec3_distance2(*v1, *v2);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_vec3_distance_bind(lua_State *L)
{
	vec3 *v1 = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *v2 = luaL_checkudata(L, 2, glm_vec3_tname);
	float bind_result = glm_vec3_distance(*v1, *v2);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_vec3_maxv_bind(lua_State *L)
{
	vec3 *v1 = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *v2 = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_maxv(*v1, *v2, *dest);
	return 0;
}


int glm_vec3_minv_bind(lua_State *L)
{
	vec3 *v1 = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *v2 = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_vec3_minv(*v1, *v2, *dest);
	return 0;
}


int glm_vec3_ortho_bind(lua_State *L)
{
	vec3 *v = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 2, glm_vec3_tname);
	glm_vec3_ortho(*v, *dest);
	return 0;
}


int glm_vec3_clamp_bind(lua_State *L)
{
	vec3 *v = luaL_checkudata(L, 1, glm_vec3_tname);
	float minVal = luaL_checknumber(L, 2);
	float maxVal = luaL_checknumber(L, 3);
	glm_vec3_clamp(*v, minVal, maxVal);
	return 0;
}


int glm_vec3_lerp_bind(lua_State *L)
{
	vec3 *from = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *to = luaL_checkudata(L, 2, glm_vec3_tname);
	float t = luaL_checknumber(L, 3);
	vec3 *dest = luaL_checkudata(L, 4, glm_vec3_tname);
	glm_vec3_lerp(*from, *to, t, *dest);
	return 0;
}
