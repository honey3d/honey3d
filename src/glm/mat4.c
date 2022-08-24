#include <lua.h>
#include <honeysuckle.h>
#include <cglm/cglm.h>
#include "util/util.h"
#include "glm.h"

int mat4_create(lua_State *L);
int mat4_set(lua_State *L);
int mat4_get(lua_State *L);
int mat4_identity(lua_State *L);

void setup_mat4(lua_State *L, int glm_tbl)
{
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
	return 1;
}


int mat4_set(lua_State *L)
{
	void *ptr;
	lua_Integer index;
	lua_Number value;
	hs_parse_args(L, hs_user(ptr), hs_int(index), hs_num(value));
	array_set(L, 16, ptr, index, value);
	return 0;
}


int mat4_get(lua_State *L)
{
	void *ptr;
	lua_Integer index;
	hs_parse_args(L, hs_user(ptr), hs_int(index));
	array_get(L, 16, ptr, index);
	return 1;
}


int mat4_identity(lua_State *L)
{
	void *ptr;
	hs_parse_args(L, hs_user(ptr));
	mat4 *m = ptr;

	glm_mat4_identity(*m);
	return 0;
}
