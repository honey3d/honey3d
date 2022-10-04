#include <lua.h>
#include <honeysuckle.h>
#include <cglm/cglm.h>
#include "util/util.h"
#include "glm.h"


int perspective(lua_State *L);
int look(lua_State *L);


void setup_camera(lua_State *L, int glm_tbl)
{
	int tbl = hs_create_table(L,
		hs_str_cfunc("perspective", perspective),
		hs_str_cfunc("look", look),
	);

	append_table(L, glm_tbl, tbl);
	lua_pop(L, 1);
}


int perspective(lua_State *L)
{
	lua_Number fov, aspect, near, far;
	void *dest_ptr;
	hs_parse_args(L, hs_num(fov), hs_num(aspect), hs_num(near), hs_num(far), hs_user(dest_ptr));
	mat4 *dest = dest_ptr;

	glm_perspective(fov, aspect, near, far, *dest);
	return 0;
}


int look(lua_State *L)
{
	float *eye = luaL_checkudata(L, 1, vec3_tname);
	float *dir = luaL_checkudata(L, 2, vec3_tname);
	float *up  = luaL_checkudata(L, 3, vec3_tname);
	void *dest  = luaL_checkudata(L, 4, mat4_tname);

	glm_look(eye, dir, up, dest);
	return 0;
}
