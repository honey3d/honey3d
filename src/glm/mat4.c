#include <lua.h>
#include <honeysuckle.h>
#include <cglm/cglm.h>
#include "util/util.h"
#include "glm.h"

int mat4_create(lua_State *L);
int mat4_set(lua_State *L);
int mat4_get(lua_State *L);
int mat4_identity(lua_State *L);

const char *mat4_tname = "glm.mat4";

void setup_mat4(lua_State *L, int glm_tbl)
{
	luaL_newmetatable(L, mat4_tname);
	lua_pop(L, 1);

	int tbl = hs_create_table(L,
		hs_str_cfunc("mat4", mat4_create),
		hs_str_cfunc("mat4_set", mat4_set),
		hs_str_cfunc("mat4_get", mat4_get),
		hs_str_cfunc("mat4_identity", mat4_identity),
	);

	append_table(L, glm_tbl, tbl);
	lua_pop(L, 1);
}


int mat4_create(lua_State *L)
{
	lua_newuserdata(L, 16*sizeof(float));
	luaL_getmetatable(L, mat4_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int mat4_set(lua_State *L)
{
	float *matrix = luaL_checkudata(L, 1, mat4_tname);
	int index = luaL_checkinteger(L, 2);
	float value = luaL_checknumber(L, 3);
	array_set(L, 16, matrix, index, value);
	return 0;
}


int mat4_get(lua_State *L)
{
	float *matrix = luaL_checkudata(L, 1, mat4_tname);
	int index = luaL_checkinteger(L, 2);
	array_get(L, 16, matrix, index);
	return 1;
}


int mat4_identity(lua_State *L)
{
	void *m = luaL_checkudata(L, 1, mat4_tname);
	glm_mat4_identity(m);
	return 0;
}
