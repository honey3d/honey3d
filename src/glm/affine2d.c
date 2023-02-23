#include <lua.h>
#include <lauxlib.h>
#include <cglm/cglm.h>
#include "glm.h"


int glm_translate2d_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	vec2 *v = luaL_checkudata(L, 2, glm_vec2_tname);
	glm_translate2d(*m, *v);
	return 0;
}


int glm_translate2d_to_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	vec2 *v = luaL_checkudata(L, 2, glm_vec2_tname);
	mat3 *dest = luaL_checkudata(L, 1, glm_mat3_tname);
	glm_translate2d_to(*m, *v, *dest);
	return 0;
}


int glm_translate2d_x_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	float x = luaL_checknumber(L, 2);
	glm_translate2d_x(*m, x);
	return 0;
}


int glm_translate2d_y_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	float y = luaL_checknumber(L, 2);
	glm_translate2d_y(*m, y);
	return 0;
}


int glm_translate2d_make_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	vec2 *v = luaL_checkudata(L, 2, glm_vec2_tname);
	glm_translate2d_make(*m, *v);
	return 0;
}


int glm_scale2d_to_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	vec2 *v = luaL_checkudata(L, 2, glm_vec2_tname);
	mat3 *dest = luaL_checkudata(L, 1, glm_mat3_tname);
	glm_scale2d_to(*m, *v, *dest);
	return 0;
}


int glm_scale2d_make_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	vec2 *v = luaL_checkudata(L, 2, glm_vec2_tname);
	glm_scale2d_make(*m, *v);
	return 0;
}


int glm_scale2d_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	vec2 *v = luaL_checkudata(L, 2, glm_vec2_tname);
	glm_scale2d(*m, *v);
	return 0;
}


int glm_scale2d_uni_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	float s = luaL_checknumber(L, 2);
	glm_scale2d_uni(*m, s);
	return 0;
}


int glm_rotate2d_make_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	float angle = luaL_checknumber(L, 2);
	glm_rotate2d_make(*m, angle);
	return 0;
}


int glm_rotate2d_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	float angle = luaL_checknumber(L, 2);
	glm_rotate2d(*m, angle);
	return 0;
}


int glm_rotate2d_to_bind(lua_State *L)
{
	mat3 *m = luaL_checkudata(L, 1, glm_mat3_tname);
	float angle = luaL_checknumber(L, 2);
	mat3 *dest = luaL_checkudata(L, 1, glm_mat3_tname);
	glm_rotate2d_to(*m, angle, *dest);
	return 0;
}
