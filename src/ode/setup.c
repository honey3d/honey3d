#include <lua.h>
#include <lauxlib.h>
#include <ode/ode.h>
#include "util/util.h"
#include "ode_bindings.h"


/* setup/teardown */
int init_ode(lua_State *L);
int close_ode(lua_State *L);

#define X(name, mt) const char *mt = name;
ODE_METATABLES
#undef X


void setup_ode(lua_State *L, int honey_tbl)
{
	/* setup metatables */
	#define X(name, mt) luaL_newmetatable(L, mt); lua_pop(L, 1);
	ODE_METATABLES
	#undef X

	/* create main table */
	struct honey_tbl_t ode[] = {
		H_FUNC("InitODE", init_ode),
		H_FUNC("CloseODE", close_ode),
		#define X(name, func) H_FUNC(name, func),
		ODE_FUNCTIONS
		#undef X
		H_END
	};
	create_table(L, ode);
	int ode_tbl = lua_gettop(L);

	/* add empty (normal) joint group */
	ode_push_jointgroup(L, 0);
	lua_setfield(L, ode_tbl, "JointGroup0");

	/* add null space */
	ode_push_space(L, 0);
	lua_setfield(L, ode_tbl, "Space0");

	lua_setfield(L, honey_tbl, "ode");
}


/* --===== setup/teardown =====-- */

int init_ode(lua_State *L)
{
	dInitODE();
	return 0;
}


int close_ode(lua_State *L)
{
	dCloseODE();
	return 0;
}
