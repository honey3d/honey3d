#include <lua.h>
#include <honeysuckle.h>
#include <cglm/cglm.h>
#include "util/util.h"


int translate(lua_State *L);
int rotate(lua_State *L);
int rotate_z(lua_State *L);


void setup_transform(lua_State *L, int glm_tbl)
{
	int tbl = hs_create_table(L,
		hs_str_cfunc("translate", translate),
		hs_str_cfunc("rotate", rotate),
		hs_str_cfunc("rotate_z", rotate_z),
	);

	append_table(L, glm_tbl, tbl);
	lua_pop(L, 1);
}


int translate(lua_State *L)
{
	void *m_ptr, *v_ptr;
	hs_parse_args(L, hs_user(m_ptr), hs_user(v_ptr));
	mat4 *m = m_ptr;
	vec3 *v = v_ptr;

	glm_translate(*m, *v);
	return 0;
}


int rotate(lua_State *L)
{
	void *m_ptr, *axis_ptr;
	lua_Number angle;
	hs_parse_args(L, hs_user(m_ptr), hs_num(angle), hs_user(axis_ptr));
	mat4 *m = m_ptr;
	vec3 *axis = axis_ptr;

	glm_rotate(*m, angle, *axis);
	return 0;
}


int rotate_z(lua_State *L)
{
	void *src_ptr, *dest_ptr;
	lua_Number angle;
	hs_parse_args(L, hs_user(src_ptr), hs_num(angle), hs_user(dest_ptr));
	mat4 *source = src_ptr;
	mat4 *dest = dest_ptr;

	glm_rotate_z(*source, angle, *dest);
	return 0;
}
