#include <lua.h>
#include <honeysuckle.h>
#include <assimp/scene.h>
#include "import.h"


void push_vector(lua_State *L, struct aiVector3D vec)
{
	hs_create_table(L,
		hs_str_num("x", vec.x),
		hs_str_num("y", vec.y),
		hs_str_num("z", vec.z),
	);
}


void push_aistring(lua_State *L, struct aiString str)
{
	lua_pushstring(L, str.data);
}
