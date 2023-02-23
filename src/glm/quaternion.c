#include <lua.h>
#include <lauxlib.h>
#include <cglm/cglm.h>
#include "glm.h"


int glm_quat_create(lua_State *L)
{
	lua_newuserdata(L, sizeof(versor));
	luaL_getmetatable(L, glm_versor_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int glm_quat_identity_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	glm_quat_identity(*q);
	return 0;
}


int glm_quat_init_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float z = luaL_checknumber(L, 4);
	float w = luaL_checknumber(L, 5);
	glm_quat_init(*q, x, y, z, w);
	return 0;
}


int glm_quat_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	float angle = luaL_checknumber(L, 2);
	float x = luaL_checknumber(L, 3);
	float y = luaL_checknumber(L, 4);
	float z = luaL_checknumber(L, 5);
	glm_quat(*q, angle, x, y, z);
	return 0;
}


int glm_quatv_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	float angle = luaL_checknumber(L, 2);
	vec3 *axis = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_quatv(*q, angle, *axis);
	return 0;
}


int glm_quat_copy_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	versor *dest = luaL_checkudata(L, 2, glm_versor_tname);
	glm_quat_copy(*q, *dest);
	return 0;
}


int glm_quat_from_vecs_bind(lua_State *L)
{
	vec3 *a = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *b = luaL_checkudata(L, 2, glm_vec3_tname);
	versor *dest = luaL_checkudata(L, 3, glm_versor_tname);
	glm_quat_from_vecs(*a, *b, *dest);
	return 0;
}


int glm_quat_norm_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	float bind_result = glm_quat_norm(*q);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_quat_normalize_to_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	versor *dest = luaL_checkudata(L, 2, glm_versor_tname);
	glm_quat_normalize_to(*q, *dest);
	return 0;
}


int glm_quat_normalize_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	glm_quat_normalize(*q);
	return 0;
}


int glm_quat_dot_bind(lua_State *L)
{
	versor *p = luaL_checkudata(L, 1, glm_versor_tname);
	versor *q = luaL_checkudata(L, 2, glm_versor_tname);
	float bind_result = glm_quat_dot(*p, *q);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_quat_conjugate_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	versor *dest = luaL_checkudata(L, 2, glm_versor_tname);
	glm_quat_conjugate(*q, *dest);
	return 0;
}


int glm_quat_inv_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	versor *dest = luaL_checkudata(L, 2, glm_versor_tname);
	glm_quat_inv(*q, *dest);
	return 0;
}


int glm_quat_add_bind(lua_State *L)
{
	versor *p = luaL_checkudata(L, 1, glm_versor_tname);
	versor *q = luaL_checkudata(L, 2, glm_versor_tname);
	versor *dest = luaL_checkudata(L, 3, glm_versor_tname);
	glm_quat_add(*p, *q, *dest);
	return 0;
}


int glm_quat_sub_bind(lua_State *L)
{
	versor *p = luaL_checkudata(L, 1, glm_versor_tname);
	versor *q = luaL_checkudata(L, 2, glm_versor_tname);
	versor *dest = luaL_checkudata(L, 3, glm_versor_tname);
	glm_quat_sub(*p, *q, *dest);
	return 0;
}


int glm_quat_real_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	float bind_result = glm_quat_real(*q);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_quat_imag_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	vec3 *dest = luaL_checkudata(L, 2, glm_vec3_tname);
	glm_quat_imag(*q, *dest);
	return 0;
}


int glm_quat_imagn_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	vec3 *dest = luaL_checkudata(L, 2, glm_vec3_tname);
	glm_quat_imagn(*q, *dest);
	return 0;
}


int glm_quat_imaglen_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	float bind_result = glm_quat_imaglen(*q);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_quat_angle_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	float bind_result = glm_quat_angle(*q);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_quat_axis_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	versor *dest = luaL_checkudata(L, 2, glm_versor_tname);
	glm_quat_axis(*q, *dest);
	return 0;
}


int glm_quat_mul_bind(lua_State *L)
{
	versor *p = luaL_checkudata(L, 1, glm_versor_tname);
	versor *q = luaL_checkudata(L, 2, glm_versor_tname);
	versor *dest = luaL_checkudata(L, 3, glm_versor_tname);
	glm_quat_mul(*p, *q, *dest);
	return 0;
}


int glm_quat_mat4_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	mat4 *dest = luaL_checkudata(L, 2, glm_mat4_tname);
	glm_quat_mat4(*q, *dest);
	return 0;
}


int glm_quat_mat4t_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	mat4 *dest = luaL_checkudata(L, 2, glm_mat4_tname);
	glm_quat_mat4t(*q, *dest);
	return 0;
}


int glm_quat_mat3_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	mat3 *dest = luaL_checkudata(L, 2, glm_mat3_tname);
	glm_quat_mat3(*q, *dest);
	return 0;
}


int glm_quat_mat3t_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	mat3 *dest = luaL_checkudata(L, 2, glm_mat3_tname);
	glm_quat_mat3t(*q, *dest);
	return 0;
}


int glm_quat_lerp_bind(lua_State *L)
{
	versor *from = luaL_checkudata(L, 1, glm_versor_tname);
	versor *to = luaL_checkudata(L, 2, glm_versor_tname);
	float t = luaL_checknumber(L, 3);
	versor *dest = luaL_checkudata(L, 4, glm_versor_tname);
	glm_quat_lerp(*from, *to, t, *dest);
	return 0;
}


int glm_quat_nlerp_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	versor *r = luaL_checkudata(L, 2, glm_versor_tname);
	float t = luaL_checknumber(L, 3);
	versor *dest = luaL_checkudata(L, 4, glm_versor_tname);
	glm_quat_nlerp(*q, *r, t, *dest);
	return 0;
}


int glm_quat_slerp_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	versor *r = luaL_checkudata(L, 2, glm_versor_tname);
	float t = luaL_checknumber(L, 3);
	versor *dest = luaL_checkudata(L, 4, glm_versor_tname);
	glm_quat_slerp(*q, *r, t, *dest);
	return 0;
}


int glm_quat_look_bind(lua_State *L)
{
	vec3 *eye = luaL_checkudata(L, 1, glm_vec3_tname);
	versor *ori = luaL_checkudata(L, 2, glm_versor_tname);
	mat4 *dest = luaL_checkudata(L, 3, glm_mat4_tname);
	glm_quat_look(*eye, *ori, *dest);
	return 0;
}


int glm_quat_for_bind(lua_State *L)
{
	vec3 *dir = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *up = luaL_checkudata(L, 2, glm_vec3_tname);
	versor *dest = luaL_checkudata(L, 3, glm_versor_tname);
	glm_quat_for(*dir, *up, *dest);
	return 0;
}


int glm_quat_forp_bind(lua_State *L)
{
	vec3 *from = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *to = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *up = luaL_checkudata(L, 3, glm_vec3_tname);
	versor *dest = luaL_checkudata(L, 4, glm_versor_tname);
	glm_quat_forp(*from, *to, *up, *dest);
	return 0;
}


int glm_quat_rotatev_bind(lua_State *L)
{
	versor *q = luaL_checkudata(L, 1, glm_versor_tname);
	vec3 *v = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *dest = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_quat_rotatev(*q, *v, *dest);
	return 0;
}


int glm_quat_rotate_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	versor *q = luaL_checkudata(L, 2, glm_versor_tname);
	mat4 *dest = luaL_checkudata(L, 3, glm_mat4_tname);
	glm_quat_rotate(*m, *q, *dest);
	return 0;
}


int glm_quat_rotate_at_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	versor *q = luaL_checkudata(L, 2, glm_versor_tname);
	vec3 *pivot = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_quat_rotate_at(*m, *q, *pivot);
	return 0;
}


int glm_quat_rotate_atm_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	versor *q = luaL_checkudata(L, 2, glm_versor_tname);
	vec3 *pivot = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_quat_rotate_atm(*m, *q, *pivot);
	return 0;
}
