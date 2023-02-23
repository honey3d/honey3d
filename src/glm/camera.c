#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <cglm/cglm.h>
#include "glm.h"


int glm_frustum_bind(lua_State *L)
{
	float left = luaL_checknumber(L, 1);
	float right = luaL_checknumber(L, 2);
	float bottom = luaL_checknumber(L, 3);
	float top = luaL_checknumber(L, 4);
	float nearVal = luaL_checknumber(L, 5);
	float farVal = luaL_checknumber(L, 6);
	mat4 *dest = luaL_checkudata(L, 7, glm_mat4_tname);
	glm_frustum(left, right, bottom, top, nearVal, farVal, *dest);
	return 0;
}


int glm_ortho_bind(lua_State *L)
{
	float left = luaL_checknumber(L, 1);
	float right = luaL_checknumber(L, 2);
	float bottom = luaL_checknumber(L, 3);
	float top = luaL_checknumber(L, 4);
	float nearVal = luaL_checknumber(L, 5);
	float farVal = luaL_checknumber(L, 6);
	mat4 *dest = luaL_checkudata(L, 7, glm_mat4_tname);
	glm_ortho(left, right, bottom, top, nearVal, farVal, *dest);
	return 0;
}


int glm_ortho_aabb_bind(lua_State *L)
{
	vec3 *aa = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *bb = luaL_checkudata(L, 2, glm_vec3_tname);
	mat4 *dest = luaL_checkudata(L, 3, glm_mat4_tname);
	vec3 box[2];
	memcpy(box, *aa, sizeof(vec3));
	memcpy(box+1, *bb, sizeof(vec3));
	glm_ortho_aabb(box, *dest);
	return 0;
}


int glm_ortho_aabb_p_bind(lua_State *L)
{
	vec3 *aa = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *bb = luaL_checkudata(L, 2, glm_vec3_tname);
	float padding = luaL_checknumber(L, 3);
	mat4 *dest = luaL_checkudata(L, 4, glm_mat4_tname);
	vec3 box[2];
	memcpy(box, *aa, sizeof(vec3));
	memcpy(box+1, *bb, sizeof(vec3));
	glm_ortho_aabb_p(box, padding, *dest);
	return 0;
}


int glm_ortho_aabb_pz_bind(lua_State *L)
{
	vec3 *aa = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *bb = luaL_checkudata(L, 2, glm_vec3_tname);
	float padding = luaL_checknumber(L, 3);
	mat4 *dest = luaL_checkudata(L, 4, glm_mat4_tname);
	vec3 box[2];
	memcpy(box, *aa, sizeof(vec3));
	memcpy(box+1, *bb, sizeof(vec3));
	glm_ortho_aabb_pz(box, padding, *dest);
	return 0;
}


int glm_ortho_default_bind(lua_State *L)
{
	float aspect = luaL_checknumber(L, 1);
	mat4 *dest = luaL_checkudata(L, 2, glm_mat4_tname);
	glm_ortho_default(aspect, *dest);
	return 0;
}


int glm_ortho_default_s_bind(lua_State *L)
{
	float aspect = luaL_checknumber(L, 1);
	float size = luaL_checknumber(L, 2);
	mat4 *dest = luaL_checkudata(L, 3, glm_mat4_tname);
	glm_ortho_default_s(aspect, size, *dest);
	return 0;
}


int glm_perspective_bind(lua_State *L)
{
	float fovy = luaL_checknumber(L, 1);
	float aspect = luaL_checknumber(L, 2);
	float nearVal = luaL_checknumber(L, 3);
	float farVal = luaL_checknumber(L, 4);
	mat4 *dest = luaL_checkudata(L, 5, glm_mat4_tname);
	glm_perspective(fovy, aspect, nearVal, farVal, *dest);
	return 0;
}


int glm_persp_move_far_bind(lua_State *L)
{
	mat4 *proj = luaL_checkudata(L, 1, glm_mat4_tname);
	float deltaFar = luaL_checknumber(L, 2);
	glm_persp_move_far(*proj, deltaFar);
	return 0;
}


int glm_perspective_default_bind(lua_State *L)
{
	float aspect = luaL_checknumber(L, 1);
	mat4 *dest = luaL_checkudata(L, 2, glm_mat4_tname);
	glm_perspective_default(aspect, *dest);
	return 0;
}


int glm_perspective_resize_bind(lua_State *L)
{
	float aspect = luaL_checknumber(L, 1);
	mat4 *proj = luaL_checkudata(L, 2, glm_mat4_tname);
	glm_perspective_resize(aspect, *proj);
	return 0;
}


int glm_lookat_bind(lua_State *L)
{
	vec3 *eye = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *center = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *up = luaL_checkudata(L, 3, glm_vec3_tname);
	mat4 *dest = luaL_checkudata(L, 4, glm_mat4_tname);
	glm_lookat(*eye, *center, *up, *dest);
	return 0;
}


int glm_look_bind(lua_State *L)
{
	vec3 *eye = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *dir = luaL_checkudata(L, 2, glm_vec3_tname);
	vec3 *up = luaL_checkudata(L, 3, glm_vec3_tname);
	mat4 *dest = luaL_checkudata(L, 4, glm_mat4_tname);
	glm_look(*eye, *dir, *up, *dest);
	return 0;
}


int glm_look_anyup_bind(lua_State *L)
{
	vec3 *eye = luaL_checkudata(L, 1, glm_vec3_tname);
	vec3 *dir = luaL_checkudata(L, 2, glm_vec3_tname);
	mat4 *dest = luaL_checkudata(L, 3, glm_mat4_tname);
	glm_look_anyup(*eye, *dir, *dest);
	return 0;
}


int glm_persp_decomp_bind(lua_State *L)
{
	mat4 *proj = luaL_checkudata(L, 1, glm_mat4_tname);
	float nearVal, farVal, top, bottom, left, right;
	glm_persp_decomp(*proj, &nearVal, &farVal, &top, &bottom, &left, &right);
	lua_pushnumber(L, nearVal);
	lua_pushnumber(L, farVal);
	lua_pushnumber(L, top);
	lua_pushnumber(L, bottom);
	lua_pushnumber(L, left);
	lua_pushnumber(L, right);
	return 6;
}


/* glm_persp_decompv would provide an identical interface to glm_persp_decomp, so it's not bound */


int glm_persp_decomp_x_bind(lua_State *L)
{
	mat4 *proj = luaL_checkudata(L, 1, glm_mat4_tname);
	float left, right;
	glm_persp_decomp_x(*proj, &left, &right);
	lua_pushnumber(L, left);
	lua_pushnumber(L, right);
	return 2;
}


int glm_persp_decomp_y_bind(lua_State *L)
{
	mat4 *proj = luaL_checkudata(L, 1, glm_mat4_tname);
	float top, bottom;
	glm_persp_decomp_y(*proj, &top, &bottom);
	lua_pushnumber(L, top);
	lua_pushnumber(L, bottom);
	return 2;
}


int glm_persp_decomp_z_bind(lua_State *L)
{
	mat4 *proj = luaL_checkudata(L, 1, glm_mat4_tname);
	float nearVal, farVal;
	glm_persp_decomp_z(*proj, &nearVal, &farVal);
	lua_pushnumber(L, nearVal);
	lua_pushnumber(L, farVal);
	return 2;
}


int glm_persp_decomp_far_bind(lua_State *L)
{
	mat4 *proj = luaL_checkudata(L, 1, glm_mat4_tname);
	float farVal;
	glm_persp_decomp_far(*proj, &farVal);
	return 0;
}


int glm_persp_decomp_near_bind(lua_State *L)
{
	mat4 *proj = luaL_checkudata(L, 1, glm_mat4_tname);
	float nearVal;
	glm_persp_decomp_near(*proj, &nearVal);
	return 0;
}


int glm_persp_fovy_bind(lua_State *L)
{
	mat4 *proj = luaL_checkudata(L, 1, glm_mat4_tname);
	float bind_result = glm_persp_fovy(*proj);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_persp_aspect_bind(lua_State *L)
{
	mat4 *proj = luaL_checkudata(L, 1, glm_mat4_tname);
	float bind_result = glm_persp_aspect(*proj);
	lua_pushnumber(L, bind_result);
	return 1;
}


int glm_persp_sizes_bind(lua_State *L)
{
	mat4 *proj = luaL_checkudata(L, 1, glm_mat4_tname);
	float fovy = luaL_checknumber(L, 2);
	vec4 *dest = luaL_checkudata(L, 3, glm_vec4_tname);
	glm_persp_sizes(*proj, fovy, *dest);
	return 0;
}
