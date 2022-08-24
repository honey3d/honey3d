#include <lua.h>
#include <honeysuckle.h>
#include <cglm/cglm.h>
#include "util/util.h"
#include "glm.h"

int vec3_create(lua_State *L);
int vec3_set(lua_State *L);
int vec3_get(lua_State *L);

void setup_vec3(lua_State *L, int glm_tbl)
{
	int tbl = hs_create_table(L,
		hs_str_cfunc("vec3", vec3_create),
		hs_str_cfunc("vec3_set", vec3_set),
		hs_str_cfunc("vec3_get", vec3_get),
	);

	append_table(L, glm_tbl, tbl);
	lua_pop(L, 1);
}


int vec3_create(lua_State *L)
{
	lua_newuserdata(L, 3*sizeof(float));
	return 1;
}


int vec3_set(lua_State *L)
{
	void *ptr;
	lua_Integer index;
	lua_Number value;
	hs_parse_args(L, hs_user(ptr), hs_int(index), hs_num(value));
	array_set(L, 3, ptr, index, value);
	return 0;
}


int vec3_get(lua_State *L)
{
	void *ptr;
	lua_Integer index;
	lua_Number value;
	hs_parse_args(L, hs_user(ptr), hs_int(index));
	array_get(L, 3, ptr, index);
	return 1;
}
