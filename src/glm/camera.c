#include <lua.h>
#include <honeysuckle.h>
#include <cglm/cglm.h>
#include "util/util.h"


int perspective(lua_State *L);


void setup_camera(lua_State *L, int glm_tbl)
{
	int tbl = hs_create_table(L,
		hs_str_cfunc("perspective", perspective),
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
