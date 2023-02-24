#include <lua.h>
#include <lauxlib.h>
#include <ode/ode.h>
#include "util/util.h"
#include "ode_bindings.h"


/* setup/teardown */
int init_ode(lua_State *L);
int close_ode(lua_State *L);


#define NEW_METATABLE(name) luaL_newmetatable(L, name); lua_pop(L, 1);
const char *ode_world_tname = "ode.WorldID";
const char *ode_space_tname = "ode.SpaceID";
const char *ode_body_tname  = "ode.BodyID";
const char *ode_geom_tname  = "ode.GeomID";
const char *ode_mass_tname  = "ode.Mass";
const char *ode_joint_tname = "ode.JointID";
const char *ode_jointgroup_tname = "ode.JointGroupID";
const char *ode_contact_tname = "ode.Contact";


void setup_ode(lua_State *L, int honey_tbl)
{
	/* setup metatables */
	NEW_METATABLE(ode_world_tname);
	NEW_METATABLE(ode_space_tname);
	NEW_METATABLE(ode_body_tname);
	NEW_METATABLE(ode_geom_tname);
	NEW_METATABLE(ode_mass_tname);
	NEW_METATABLE(ode_joint_tname);
	NEW_METATABLE(ode_jointgroup_tname);
	NEW_METATABLE(ode_contact_tname);

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
