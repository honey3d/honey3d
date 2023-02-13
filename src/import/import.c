#include <lua.h>
#include <honeysuckle.h>
#include "import.h"

#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include <tinyobj/tinyobj_loader_c.h>

int dummy(lua_State *L)
{
	return 0;
}


void setup_import(lua_State *L, int honey_tbl)
{
	hs_create_table(L,
		hs_str_cfunc("dummy", dummy),
	);

	lua_setfield(L, honey_tbl, "import");
}
