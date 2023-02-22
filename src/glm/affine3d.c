#include <lua.h>
#include <lauxlib.h>
#include <cglm/cglm.h>
#include "glm.h"


int glm_uniscaled_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	bool bind_result = glm_uniscaled(*m);
	lua_pushboolean(L, bind_result);
	return 1;
}


int glm_decompose_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	vec4 *t = luaL_checkudata(L, 2, glm_vec4_tname);
	mat4 *r = luaL_checkudata(L, 3, glm_mat4_tname);
	vec3 *s = luaL_checkudata(L, 4, glm_vec3_tname);
	glm_decompose(*m, *t, *r, *s);
	return 0;
}


int glm_decompose_rs_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	mat4 *r = luaL_checkudata(L, 2, glm_mat4_tname);
	vec3 *s = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_decompose_rs(*m, *r, *s);
	return 0;
}


int glm_decompose_scalev_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	vec3 *s = luaL_checkudata(L, 2, glm_vec3_tname);
	glm_decompose_scalev(*m, *s);
	return 0;
}


int glm_rotate_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	float angle = luaL_checknumber(L, 2);
	vec3 *axis = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_rotate(*m, angle, *axis);
	return 0;
}


int glm_rotate_at_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	vec3 *pivot = luaL_checkudata(L, 2, glm_vec3_tname);
	float angle = luaL_checknumber(L, 3);
	vec3 *axis = luaL_checkudata(L, 4, glm_vec3_tname);
	glm_rotate_at(*m, *pivot, angle, *axis);
	return 0;
}


int glm_rotate_atm_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	vec3 *pivot = luaL_checkudata(L, 2, glm_vec3_tname);
	float angle = luaL_checknumber(L, 3);
	vec3 *axis = luaL_checkudata(L, 4, glm_vec3_tname);
	glm_rotate_atm(*m, *pivot, angle, *axis);
	return 0;
}


int glm_rotate_make_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	float angle = luaL_checknumber(L, 2);
	vec3 *axis = luaL_checkudata(L, 3, glm_vec3_tname);
	glm_rotate_make(*m, angle, *axis);
	return 0;
}


int glm_rotate_x_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	float angle = luaL_checknumber(L, 2);
	mat4 *dest = luaL_checkudata(L, 3, glm_mat4_tname);
	glm_rotate_x(*m, angle, *dest);
	return 0;
}


int glm_rotate_y_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	float angle = luaL_checknumber(L, 2);
	mat4 *dest = luaL_checkudata(L, 3, glm_mat4_tname);
	glm_rotate_y(*m, angle, *dest);
	return 0;
}


int glm_rotate_z_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	float angle = luaL_checknumber(L, 2);
	mat4 *dest = luaL_checkudata(L, 3, glm_mat4_tname);
	glm_rotate_z(*m, angle, *dest);
	return 0;
}


int glm_scale_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	vec3 *v = luaL_checkudata(L, 2, glm_vec3_tname);
	glm_scale(*m, *v);
	return 0;
}


int glm_scale_make_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	vec3 *v = luaL_checkudata(L, 2, glm_vec3_tname);
	glm_scale_make(*m, *v);
	return 0;
}


int glm_scale_to_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	vec3 *v = luaL_checkudata(L, 2, glm_vec3_tname);
	mat4 *dest = luaL_checkudata(L, 3, glm_mat4_tname);
	glm_scale_to(*m, *v, *dest);
	return 0;
}


int glm_scale_uni_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	float s = luaL_checknumber(L, 2);
	glm_scale_uni(*m, s);
	return 0;
}


int glm_translate_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	vec3 *v = luaL_checkudata(L, 2, glm_vec3_tname);
	glm_translate(*m, *v);
	return 0;
}


int glm_translate_make_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	vec3 *v = luaL_checkudata(L, 2, glm_vec3_tname);
	glm_translate_make(*m, *v);
	return 0;
}


int glm_translate_to_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	vec3 *v = luaL_checkudata(L, 2, glm_vec3_tname);
	mat4 *dest = luaL_checkudata(L, 3, glm_mat4_tname);
	glm_translate_to(*m, *v, *dest);
	return 0;
}


int glm_translate_x_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	float x = luaL_checknumber(L, 2);
	glm_translate_x(*m, x);
	return 0;
}


int glm_translate_y_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	float y = luaL_checknumber(L, 2);
	glm_translate_y(*m, y);
	return 0;
}


int glm_translate_z_bind(lua_State *L)
{
	mat4 *m = luaL_checkudata(L, 1, glm_mat4_tname);
	float z = luaL_checknumber(L, 2);
	glm_translate_z(*m, z);
	return 0;
}
