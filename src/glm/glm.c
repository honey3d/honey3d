#include <lua.h>
#include <honeysuckle.h>


void setup_glm(lua_State *L, int honey_index)
{
	lua_createtable(L, 0, 1);
	int glm_index = lua_gettop(L);

	setup_mat4(L, glm_index);
	setup_transform(L, glm_index);
	lua_setfield(L, honey_index, "glm");
}
