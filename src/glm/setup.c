#include <lua.h>
#include <lauxlib.h>
#include <cglm/version.h>
#include "util/util.h"
#include "glm.h"


const char *glm_mat2_tname = "glm.mat2";
const char *glm_mat3_tname = "glm.mat3";
const char *glm_mat4_tname = "glm.mat4";
const char *glm_vec2_tname = "glm.vec2";
const char *glm_vec3_tname = "glm.vec3";
const char *glm_vec4_tname = "glm.vec4";
const char *glm_versor_tname = "glm.versor";


int glm_version(lua_State *L)
{
	lua_pushinteger(L, CGLM_VERSION_MAJOR);
	lua_pushinteger(L, CGLM_VERSION_MINOR);
	lua_pushinteger(L, CGLM_VERSION_PATCH);
	return 3;
}


void setup_glm(lua_State *L, int honey_index)
{
	luaL_newmetatable(L, glm_mat2_tname); lua_pop(L, 1);
	luaL_newmetatable(L, glm_mat3_tname); lua_pop(L, 1);
	luaL_newmetatable(L, glm_mat4_tname); lua_pop(L, 1);
	luaL_newmetatable(L, glm_vec2_tname); lua_pop(L, 1);
	luaL_newmetatable(L, glm_vec3_tname); lua_pop(L, 1);
	luaL_newmetatable(L, glm_vec4_tname); lua_pop(L, 1);
	luaL_newmetatable(L, glm_versor_tname); lua_pop(L, 1);

	struct honey_tbl_t glm[] = {
		#define X(name, func) H_FUNC(name, func),
		GLM_FUNCTIONS
		#undef X
		H_FUNC("version", glm_version),
		H_END,
	};
	create_table(L, glm);
	lua_setfield(L, honey_index, "glm");
}


void array_get(lua_State *L, int max, float *array, int index)
{
	if (index < 0 || index >= max)
		luaL_error(L, "index %d is out of range [0-%d]", index, max-1);
	lua_pushnumber(L, array[index]);
}


void array_set(lua_State *L, int max, float *array, int index, float value)
{
	if (index < 0 || index >= max)
		luaL_error(L, "index %d is out of range [0-%d]", index, max-1);
	array[index] = value;
}
