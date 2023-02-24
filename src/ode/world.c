#include <lua.h>
#include <lauxlib.h>
#include <ode/ode.h>
#include "ode_bindings.h"


void ode_push_world(lua_State *L, dWorldID w)
{
	dWorldID *wu = lua_newuserdata(L, sizeof(dWorldID));
	*wu = w;
	luaL_getmetatable(L, ode_world_tname);
	lua_setmetatable(L, -2);
}


int dWorldCreate_bind(lua_State *L)
{
	dWorldID w = lua_newuserdata(L, sizeof(dWorldID));
	ode_push_world(L, w);
	return 1;
}


int dWorldDestroy_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dWorldDestroy(*w);
	return 0;
}


int dWorldSetGravity_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dReal x = luaL_checkinteger(L, 2);
	dReal y = luaL_checkinteger(L, 3);
	dReal z = luaL_checkinteger(L, 4);
	dWorldSetGravity(*w, x, y, z);
	return 0;
}


int dWorldGetGravity_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dVector3 gravity;
	dWorldGetGravity(*w, gravity);
	lua_pushnumber(L, gravity[0]);
	lua_pushnumber(L, gravity[1]);
	lua_pushnumber(L, gravity[2]);
	return 3;
}


int dWorldSetERP_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dReal erp = luaL_checkinteger(L, 2);
	dWorldSetERP(*w, erp);
	return 0;
}


int dWorldGetERP_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dReal bind_result = dWorldGetERP(*w);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dWorldSetCFM_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dReal cfm = luaL_checkinteger(L, 2);
	dWorldSetCFM(*w, cfm);
	return 0;
}


int dWorldGetCFM_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dReal bind_result = dWorldGetCFM(*w);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dWorldSetAutoDisableFlag_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	int do_auto_disable = luaL_checkinteger(L, 2);
	dWorldSetAutoDisableFlag(*w, do_auto_disable);
	return 0;
}


int dWorldGetAutoDisableFlag_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	int bind_result = dWorldGetAutoDisableFlag(*w);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dWorldSetAutoDisableLinearThreshold_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dReal linear_threshold = luaL_checkinteger(L, 2);
	dWorldSetAutoDisableLinearThreshold(*w, linear_threshold);
	return 0;
}


int dWorldGetAutoDisableLinearThreshold_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dReal bind_result = dWorldGetAutoDisableLinearThreshold(*w);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dWorldSetAutoDisableAngularThreshold_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dReal angular_threshold = luaL_checkinteger(L, 2);
	dWorldSetAutoDisableAngularThreshold(*w, angular_threshold);
	return 0;
}


int dWorldGetAutoDisableAngularThreshold_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dReal bind_result = dWorldGetAutoDisableAngularThreshold(*w);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dWorldSetAutoDisableSteps_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	int steps = luaL_checkinteger(L, 2);
	dWorldSetAutoDisableSteps(*w, steps);
	return 0;
}


int dWorldGetAutoDisableSteps_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	int bind_result = dWorldGetAutoDisableSteps(*w);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dWorldSetAutoDisableTime_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dReal time = luaL_checkinteger(L, 2);
	dWorldSetAutoDisableTime(*w, time);
	return 0;
}


int dWorldGetAutoDisableTime_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dReal bind_result = dWorldGetAutoDisableTime(*w);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dWorldImpulseToForce_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dReal stepsize = luaL_checkinteger(L, 2);
	dReal ix = luaL_checkinteger(L, 3);
	dReal iy = luaL_checkinteger(L, 4);
	dReal iz = luaL_checkinteger(L, 5);
	dVector3 force;
	dWorldImpulseToForce(*w, stepsize, ix, iy, iz, force);
	lua_pushnumber(L, force[0]);
	lua_pushnumber(L, force[1]);
	lua_pushnumber(L, force[2]);
	return 3;
}


int dWorldStep_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dReal stepsize = luaL_checkinteger(L, 2);
	dWorldStep(*w, stepsize);
	return 0;
}


int dWorldQuickStep_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dReal stepsize = luaL_checkinteger(L, 2);
	dWorldQuickStep(*w, stepsize);
	return 0;
}


int dWorldSetQuickStepNumIterations_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	int num = luaL_checkinteger(L, 2);
	dWorldSetQuickStepNumIterations(*w, num);
	return 0;
}


int dWorldGetQuickStepNumIterations_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	int bind_result = dWorldGetQuickStepNumIterations(*w);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dWorldSetQuickStepW_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dReal over_relaxation = luaL_checkinteger(L, 2);
	dWorldSetQuickStepW(*w, over_relaxation);
	return 0;
}


int dWorldGetQuickStepW_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dReal bind_result = dWorldGetQuickStepW(*w);
	lua_pushinteger(L, bind_result);
	return 1;
}


