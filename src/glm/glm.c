#include <lua.h>
#include <honeysuckle.h>


void setup_glm(lua_State *L, int honey_index)
{
	lua_createtable(L, 0, 1);
	int glm_tbl = lua_gettop(L);

	setup_vec3(L, glm_tbl);
	setup_mat4(L, glm_tbl);

	setup_transform(L, glm_tbl);
	setup_camera(L, glm_tbl);

	lua_setfield(L, honey_index, "glm");
}


void array_get(lua_State *L, int max, float *array, int index)
{
	if (index < 0 || index >= max)
		hs_throw_error(L, "index %d is out of range [0-%d]", index, max-1);
	lua_pushnumber(L, array[index]);
}


void array_set(lua_State *L, int max, float *array, int index, float value)
{
	if (index < 0 || index >= max)
		hs_throw_error(L, "index %d is out of range [0-%d]", index, max-1);
	array[index] = value;
}
