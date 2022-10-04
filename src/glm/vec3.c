#include <lua.h>
#include <honeysuckle.h>
#include <cglm/cglm.h>
#include "util/util.h"
#include "glm.h"

int vec3_create(lua_State *L);
int vec3_set(lua_State *L);
int vec3_get(lua_State *L);

int vec3_normalize(lua_State *L);

int vec3_add(lua_State *L);
int vec3_sub(lua_State *L);
int vec3_scale(lua_State *L);
int vec3_dot(lua_State *L);
int vec3_cross(lua_State *L);

const char *vec3_tname = "glm.vec3";


void setup_vec3(lua_State *L, int glm_tbl)
{
	luaL_newmetatable(L, vec3_tname);
	lua_pop(L, 1);

	int tbl = hs_create_table(L,
		hs_str_cfunc("vec3", vec3_create),
		hs_str_cfunc("vec3_set", vec3_set),
		hs_str_cfunc("vec3_get", vec3_get),

		hs_str_cfunc("vec3_normalize", vec3_normalize),

		hs_str_cfunc("vec3_add", vec3_add),
		hs_str_cfunc("vec3_sub", vec3_sub),
		hs_str_cfunc("vec3_scale", vec3_scale),
		hs_str_cfunc("vec3_dot", vec3_dot),
		hs_str_cfunc("vec3_cross", vec3_cross),
	);

	append_table(L, glm_tbl, tbl);
	lua_pop(L, 1);
}


int vec3_create(lua_State *L)
{
	lua_newuserdata(L, 3*sizeof(float));
	luaL_getmetatable(L, vec3_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int vec3_set(lua_State *L)
{
	float *vec = luaL_checkudata(L, 1, vec3_tname);
	int index = luaL_checkinteger(L, 2);
	double value = luaL_checknumber(L, 3);
	array_set(L, 3, vec, index, value);
	return 0;
}


int vec3_get(lua_State *L)
{
	float *vec = luaL_checkudata(L, 1, vec3_tname);
	int index = luaL_checkinteger(L, 2);
	array_get(L, 3, vec, index);
	return 1;
}


int vec3_normalize(lua_State *L)
{
	float *vec = luaL_checkudata(L, 1, vec3_tname);
	glm_vec3_normalize(vec);
	return 0;
}


int vec3_add(lua_State *L)
{
	float *a = luaL_checkudata(L, 1, vec3_tname);
	float *b = luaL_checkudata(L, 2, vec3_tname);
	float *dest = luaL_checkudata(L, 3, vec3_tname);

	glm_vec3_add(a, b, dest);
	return 0;
}


int vec3_sub(lua_State *L)
{
	float *a = luaL_checkudata(L, 1, vec3_tname);
	float *b = luaL_checkudata(L, 2, vec3_tname);
	float *dest = luaL_checkudata(L, 3, vec3_tname);

	glm_vec3_sub(a, b, dest);
	return 0;
}

int vec3_scale(lua_State *L)
{
	float *v = luaL_checkudata(L, 1, vec3_tname);
	float s = luaL_checknumber(L, 2);
	float *dest = luaL_checkudata(L, 3, vec3_tname);

	glm_vec3_scale(v, s, dest);
	return 0;
}


int vec3_dot(lua_State *L)
{
	float *a = luaL_checkudata(L, 1, vec3_tname);
	float *b = luaL_checkudata(L, 2, vec3_tname);

	float result = glm_vec3_dot(a, b);
	lua_pushnumber(L, result);
	return 1;
}


int vec3_cross(lua_State *L)
{
	float *a = luaL_checkudata(L, 1, vec3_tname);
	float *b = luaL_checkudata(L, 2, vec3_tname);
	float *dest = luaL_checkudata(L, 3, vec3_tname);

	glm_vec3_cross(a, b, dest);
	return 0;
}
