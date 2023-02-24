#include <lua.h>
#include <lauxlib.h>
#include <ode/ode.h>
#include "ode_bindings.h"


void ode_push_joint(lua_State *L, dJointID j)
{
	dJointID *ju = lua_newuserdata(L, sizeof(dJointID));
	*ju = j;
	luaL_getmetatable(L, ode_joint_tname);
	lua_setmetatable(L, -2);
}


void ode_push_jointgroup(lua_State *L, dJointGroupID jg)
{
	dJointGroupID *jgu = lua_newuserdata(L, sizeof(dJointGroupID));
	*jgu = jg;
	luaL_getmetatable(L, ode_jointgroup_tname);
	lua_setmetatable(L, -2);
}


int dJointCreateBall_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dJointGroupID *g = luaL_checkudata(L, 2, ode_jointgroup_tname);
	dJointID bind_result = dJointCreateBall(*w, *g);
	ode_push_joint(L, bind_result);
	return 1;
}


int dJointCreateHinge_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dJointGroupID *g = luaL_checkudata(L, 2, ode_jointgroup_tname);
	dJointID bind_result = dJointCreateHinge(*w, *g);
	ode_push_joint(L, bind_result);
	return 1;
}


int dJointCreateSlider_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dJointGroupID *g = luaL_checkudata(L, 2, ode_jointgroup_tname);
	dJointID bind_result = dJointCreateSlider(*w, *g);
	ode_push_joint(L, bind_result);
	return 1;
}


static int get_field(lua_State *L, int tbl, const char *key, int type)
{
	lua_getfield(L, tbl, key);
	int actual_type = lua_type(L, -1);
	if (actual_type != type) {
		luaL_error(L, 
			"field \"%s\" must have type %s but is %s instead",
			key, lua_typename(L, type), lua_typename(L, actual_type)
		);
	}
}

static int parse_surface_params(lua_State *L, struct dSurfaceParameters *surface, int tbl)
{
	get_field(L, tbl, "mode", LUA_TNUMBER);
	surface->mode = lua_tointeger(L, -1);

	get_field(L, tbl, "mu", LUA_TNUMBER);
	surface->mu = lua_tointeger(L, -1);

	get_field(L, tbl, "mu2", LUA_TNUMBER);
	surface->mu2 = lua_tointeger(L, -1);
	
	get_field(L, tbl, "rho", LUA_TNUMBER);
	surface->rho = lua_tointeger(L, -1);

	get_field(L, tbl, "rho2", LUA_TNUMBER);
	surface->rho2 = lua_tointeger(L, -1);

	get_field(L, tbl, "rhoN", LUA_TNUMBER);
	surface->rhoN = lua_tointeger(L, -1);

	get_field(L, tbl, "bounce", LUA_TNUMBER);
	surface->bounce = lua_tointeger(L, -1);

	get_field(L, tbl, "bounce_vel", LUA_TNUMBER);
	surface->bounce_vel = lua_tointeger(L, -1);

	get_field(L, tbl, "soft_erp", LUA_TNUMBER);
	surface->soft_erp = lua_tointeger(L, -1);

	get_field(L, tbl, "soft_cfm", LUA_TNUMBER);
	surface->soft_cfm = lua_tointeger(L, -1);

	get_field(L, tbl, "motion1", LUA_TNUMBER);
	surface->motion1 = lua_tointeger(L, -1);

	get_field(L, tbl, "motion2", LUA_TNUMBER);
	surface->motion2 = lua_tointeger(L, -1);

	get_field(L, tbl, "motionN", LUA_TNUMBER);
	surface->motionN = lua_tointeger(L, -1);

	get_field(L, tbl, "slip1", LUA_TNUMBER);
	surface->slip1 = lua_tointeger(L, -1);

	get_field(L, tbl, "slip2", LUA_TNUMBER);
	surface->slip2 = lua_tointeger(L, -1);

	lua_pop(L, 15);
}

static int parse_contact_tbl(lua_State *L, dContact *contact, int tbl)
{
	get_field(L, tbl, "surface", LUA_TTABLE);
	int surface_tbl = lua_gettop(L);
	parse_surface_params(L, &(contact->surface), surface_tbl);
	lua_pop(L, 1);

	get_field(L, tbl, "geom", LUA_TUSERDATA);
	dContactGeom *g = lua_touserdata(L, -1);
	contact->geom = *g;
	lua_pop(L, 1);

	get_field(L, tbl, "fdir1", LUA_TTABLE);
	int fdir_tbl = lua_gettop(L);
	lua_rawgeti(L, fdir_tbl, 1);
	contact->fdir1[0] = lua_tonumber(L, -1);
	lua_rawgeti(L, fdir_tbl, 1);
	contact->fdir1[1] = lua_tonumber(L, -1);
	lua_rawgeti(L, fdir_tbl, 1);
	contact->fdir1[2] = lua_tonumber(L, -1);
	lua_pop(L, 4);
}

int dJointCreateContact_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dJointGroupID *g = luaL_checkudata(L, 2, ode_jointgroup_tname);
	luaL_checktype(L, 3, LUA_TTABLE);
	dContact contact;
	parse_contact_tbl(L, &contact, 3);
	dJointID bind_result = dJointCreateContact(*w, *g, &contact);
	ode_push_joint(L, bind_result);
	return 1;
}


int dJointCreateUniversal_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dJointGroupID *g = luaL_checkudata(L, 2, ode_jointgroup_tname);
	dJointID bind_result = dJointCreateUniversal(*w, *g);
	ode_push_joint(L, bind_result);
	return 1;
}


int dJointCreateHinge2_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dJointGroupID *g = luaL_checkudata(L, 2, ode_jointgroup_tname);
	dJointID bind_result = dJointCreateHinge2(*w, *g);
	ode_push_joint(L, bind_result);
	return 1;
}


int dJointCreatePR_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dJointGroupID *g = luaL_checkudata(L, 2, ode_jointgroup_tname);
	dJointID bind_result = dJointCreatePR(*w, *g);
	ode_push_joint(L, bind_result);
	return 1;
}


int dJointCreatePU_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dJointGroupID *g = luaL_checkudata(L, 2, ode_jointgroup_tname);
	dJointID bind_result = dJointCreatePU(*w, *g);
	ode_push_joint(L, bind_result);
	return 1;
}


int dJointCreatePiston_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dJointGroupID *g = luaL_checkudata(L, 2, ode_jointgroup_tname);
	dJointID bind_result = dJointCreatePiston(*w, *g);
	ode_push_joint(L, bind_result);
	return 1;
}


int dJointCreateFixed_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dJointGroupID *g = luaL_checkudata(L, 2, ode_jointgroup_tname);
	dJointID bind_result = dJointCreateFixed(*w, *g);
	ode_push_joint(L, bind_result);
	return 1;
}


int dJointCreateAMotor_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dJointGroupID *g = luaL_checkudata(L, 2, ode_jointgroup_tname);
	dJointID bind_result = dJointCreateAMotor(*w, *g);
	ode_push_joint(L, bind_result);
	return 1;
}


int dJointCreateLMotor_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dJointGroupID *g = luaL_checkudata(L, 2, ode_jointgroup_tname);
	dJointID bind_result = dJointCreateLMotor(*w, *g);
	ode_push_joint(L, bind_result);
	return 1;
}


int dJointCreatePlane2D_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dJointGroupID *g = luaL_checkudata(L, 2, ode_jointgroup_tname);
	dJointID bind_result = dJointCreatePlane2D(*w, *g);
	ode_push_joint(L, bind_result);
	return 1;
}


int dJointCreateDBall_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dJointGroupID *g = luaL_checkudata(L, 2, ode_jointgroup_tname);
	dJointID bind_result = dJointCreateDBall(*w, *g);
	ode_push_joint(L, bind_result);
	return 1;
}


int dJointCreateDHinge_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dJointGroupID *g = luaL_checkudata(L, 2, ode_jointgroup_tname);
	dJointID bind_result = dJointCreateDHinge(*w, *g);
	ode_push_joint(L, bind_result);
	return 1;
}


int dJointCreateTransmission_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dJointGroupID *g = luaL_checkudata(L, 2, ode_jointgroup_tname);
	dJointID bind_result = dJointCreateTransmission(*w, *g);
	ode_push_joint(L, bind_result);
	return 1;
}


int dJointDestroy_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dJointDestroy(*j);
	return 0;
}


int dJointGroupCreate_bind(lua_State *L)
{
	int max_size = luaL_checkinteger(L, 1);
	dJointGroupID bind_result = dJointGroupCreate(max_size);
	ode_push_jointgroup(L, bind_result);
	return 1;
}


int dJointGroupDestroy_bind(lua_State *L)
{
	dJointGroupID *g = luaL_checkudata(L, 1, ode_jointgroup_tname);
	dJointGroupDestroy(*g);
	return 0;
}


int dJointGroupEmpty_bind(lua_State *L)
{
	dJointGroupID *g = luaL_checkudata(L, 1, ode_jointgroup_tname);
	dJointGroupEmpty(*g);
	return 0;
}


int dJointAttach_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dBodyID *body1 = luaL_checkudata(L, 2, ode_body_tname);
	dBodyID *body2 = luaL_checkudata(L, 3, ode_body_tname);
	dJointAttach(*j, *body1, *body2);
	return 0;
}


int dJointEnable_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dJointEnable(*j);
	return 0;
}


int dJointDisable_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dJointDisable(*j);
	return 0;
}


int dJointIsEnabled_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int bind_result = dJointIsEnabled(*j);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dJointGetType_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int bind_result = dJointGetType(*j);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dJointGetBody_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int index = luaL_checkinteger(L, 2);
	dBodyID bind_result = dJointGetBody(*j, index);
	ode_push_body(L, bind_result);
	return 1;
}


int dAreConnected_bind(lua_State *L)
{
	dBodyID *b1 = luaL_checkudata(L, 1, ode_body_tname);
	dBodyID *b2 = luaL_checkudata(L, 2, ode_body_tname);
	int bind_result = dAreConnected(*b1, *b2);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dAreConnectedExcluding_bind(lua_State *L)
{
	dBodyID *b1 = luaL_checkudata(L, 1, ode_body_tname);
	dBodyID *b2 = luaL_checkudata(L, 2, ode_body_tname);
	int joint_type = luaL_checkinteger(L, 3);
	int bind_result = dAreConnectedExcluding(*b1, *b2, joint_type);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dJointSetBallAnchor_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetBallAnchor(*j, x, y, z);
	return 0;
}


int dJointGetBallAnchor_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetBallAnchor(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetBallAnchor2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetBallAnchor2(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointSetHingeAnchor_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetHingeAnchor(*j, x, y, z);
	return 0;
}


int dJointSetHingeAxis_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetHingeAxis(*j, x, y, z);
	return 0;
}


int dJointGetHingeAnchor_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetHingeAnchor(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetHingeAnchor2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetHingeAnchor2(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetHingeAxis_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetHingeAxis(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetHingeAngle_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetHingeAngle(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetHingeAngleRate_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetHingeAngleRate(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointSetSliderAxis_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetSliderAxis(*j, x, y, z);
	return 0;
}


int dJointGetSliderAxis_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetSliderAxis(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetSliderPosition_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetSliderPosition(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetSliderPositionRate_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetSliderPositionRate(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointSetUniversalAnchor_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetUniversalAnchor(*j, x, y, z);
	return 0;
}


int dJointSetUniversalAxis1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetUniversalAxis1(*j, x, y, z);
	return 0;
}


int dJointSetUniversalAxis2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetUniversalAxis2(*j, x, y, z);
	return 0;
}


int dJointGetUniversalAnchor_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetUniversalAnchor(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetUniversalAnchor2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetUniversalAnchor2(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetUniversalAxis1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetUniversalAxis1(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetUniversalAxis2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetUniversalAxis2(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetUniversalAngle1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetUniversalAngle1(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetUniversalAngle2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetUniversalAngle2(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetUniversalAngles_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal angle1, angle2;
	dJointGetUniversalAngles(*j, &angle1, &angle2);
	lua_pushnumber(L, angle1);
	lua_pushnumber(L, angle2);
	return 2;
}


int dJointGetUniversalAngle1Rate_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetUniversalAngle1Rate(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetUniversalAngle2Rate_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetUniversalAngle2Rate(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointSetHinge2Anchor_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetHinge2Anchor(*j, x, y, z);
	return 0;
}


int dJointSetHinge2Axis1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetHinge2Axis1(*j, x, y, z);
	return 0;
}


int dJointSetHinge2Axis2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetHinge2Axis2(*j, x, y, z);
	return 0;
}


int dJointGetHinge2Anchor_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetHinge2Anchor(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetHinge2Anchor2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetHinge2Anchor2(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetHinge2Axis1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetHinge2Axis1(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetHinge2Axis2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetHinge2Axis2(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetHinge2Angle1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetHinge2Angle1(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetHinge2Angle1Rate_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetHinge2Angle1Rate(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetHinge2Angle2Rate_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetHinge2Angle2Rate(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointSetPRAxis1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetPRAxis1(*j, x, y, z);
	return 0;
}


int dJointGetPRAxis1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetPRAxis1(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointSetPRAxis2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetPRAxis2(*j, x, y, z);
	return 0;
}


int dJointGetPRAxis2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetPRAxis2(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointSetPRAnchor_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetPRAnchor(*j, x, y, z);
	return 0;
}


int dJointGetPRAnchor_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetPRAnchor(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetPRPosition_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetPRPosition(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetPUPosition_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetPUPosition(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetPUPositionRate_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetPUPositionRate(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointSetPUAnchor_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetPUAnchor(*j, x, y, z);
	return 0;
}


int dJointGetPUAnchor_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetPUAnchor(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointSetPUAnchorDelta_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dReal dx = luaL_checknumber(L, 5);
	dReal dy = luaL_checknumber(L, 6);
	dReal dz = luaL_checknumber(L, 7);
	dJointSetPUAnchorDelta(*j, x, y, z, dx, dy, dz);
	return 0;
}


int dJointSetPUAxis1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetPUAxis1(*j, x, y, z);
	return 0;
}


int dJointGetPUAxis1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetPUAxis1(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointSetPUAxis2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetPUAxis2(*j, x, y, z);
	return 0;
}


int dJointGetPUAxis2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetPUAxis2(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointSetPUAxis3_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetPUAxis3(*j, x, y, z);
	return 0;
}


int dJointGetPUAxis3_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetPUAxis3(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointSetPUAxisP_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetPUAxisP(*j, x, y, z);
	return 0;
}


int dJointGetPUAxisP_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetPUAxisP(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetPUAngles_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal angle1, angle2;
	dJointGetPUAngles(*j, &angle1, &angle2);
	lua_pushnumber(L, angle1);
	lua_pushnumber(L, angle2);
	return 2;
}


int dJointGetPUAngle1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetPUAngle1(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetPUAngle2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetPUAngle2(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetPUAngle1Rate_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetPUAngle1Rate(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetPUAngle2Rate_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetPUAngle2Rate(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointSetPistonAnchor_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetPistonAnchor(*j, x, y, z);
	return 0;
}


int dJointGetPistonAnchor_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetPistonAnchor(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetPistonAnchor2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetPistonAnchor2(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointSetPistonAxis_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetPistonAxis(*j, x, y, z);
	return 0;
}


int dJointGetPistonAxis_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetPistonAxis(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointSetPistonAxisDelta_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dReal dx = luaL_checknumber(L, 5);
	dReal dy = luaL_checknumber(L, 6);
	dReal dz = luaL_checknumber(L, 7);
	dJointSetPistonAxisDelta(*j, x, y, z, dx, dy, dz);
	return 0;
}


int dJointGetPistonPosition_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetPistonPosition(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetPistonPositionRate_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetPistonPositionRate(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetPistonAngle_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetPistonAngle(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetPistonAngleRate_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetPistonAngleRate(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointAddPistonForce_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal force = luaL_checknumber(L, 2);
	dJointAddPistonForce(*j, force);
	return 0;
}


int dJointSetFixed_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dJointSetFixed(*j);
	return 0;
}


int dJointSetAMotorMode_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int mode = luaL_checkinteger(L, 2);
	dJointSetAMotorMode(*j, mode);
	return 0;
}


int dJointGetAMotorMode_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int bind_result = dJointGetAMotorMode(*j);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dJointSetAMotorNumAxes_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int num = luaL_checkinteger(L, 2);
	dJointSetAMotorNumAxes(*j, num);
	return 0;
}


int dJointGetAMotorNumAxes_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int bind_result = dJointGetAMotorNumAxes(*j);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dJointSetAMotorAxis_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int anum = luaL_checkinteger(L, 2);
	int rel = luaL_checkinteger(L, 3);
	dReal x = luaL_checknumber(L, 4);
	dReal y = luaL_checknumber(L, 5);
	dReal z = luaL_checknumber(L, 6);
	dJointSetAMotorAxis(*j, anum, rel, x, y, z);
	return 0;
}


int dJointGetAMotorAxis_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int anum = luaL_checkinteger(L, 2);
	dVector3 result;
	dJointGetAMotorAxis(*j, anum, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetAMotorAxisRel_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int anum = luaL_checkinteger(L, 2);
	int bind_result = dJointGetAMotorAxisRel(*j, anum);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dJointSetAMotorAngle_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int anum = luaL_checkinteger(L, 2);
	dReal angle = luaL_checknumber(L, 3);
	dJointSetAMotorAngle(*j, anum, angle);
	return 0;
}


int dJointGetAMotorAngle_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int anum = luaL_checkinteger(L, 2);
	dReal bind_result = dJointGetAMotorAngle(*j, anum);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetAMotorAngleRate_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int anum = luaL_checkinteger(L, 2);
	dReal bind_result = dJointGetAMotorAngleRate(*j, anum);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointSetLMotorNumAxes_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int num = luaL_checkinteger(L, 2);
	dJointSetLMotorNumAxes(*j, num);
	return 0;
}


int dJointGetLMotorNumAxes_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int bind_result = dJointGetLMotorNumAxes(*j);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dJointSetLMotorAxis_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int anum = luaL_checkinteger(L, 2);
	int rel = luaL_checkinteger(L, 3);
	dReal x = luaL_checknumber(L, 4);
	dReal y = luaL_checknumber(L, 5);
	dReal z = luaL_checknumber(L, 6);
	dJointSetLMotorAxis(*j, anum, rel, x, y, z);
	return 0;
}


int dJointGetLMotorAxis_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int anum = luaL_checkinteger(L, 2);
	dVector3 result;
	dJointGetLMotorAxis(*j, anum, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointSetDBallAnchor1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetDBallAnchor1(*j, x, y, z);
	return 0;
}


int dJointSetDBallAnchor2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetDBallAnchor2(*j, x, y, z);
	return 0;
}


int dJointGetDBallAnchor1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetDBallAnchor1(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetDBallAnchor2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetDBallAnchor2(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetDBallDistance_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetDBallDistance(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointSetDBallDistance_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal dist = luaL_checknumber(L, 2);
	dJointSetDBallDistance(*j, dist);
	return 0;
}


int dJointSetDHingeAxis_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetDHingeAxis(*j, x, y, z);
	return 0;
}


int dJointGetDHingeAxis_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetDHingeAxis(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointSetDHingeAnchor1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetDHingeAnchor1(*j, x, y, z);
	return 0;
}


int dJointSetDHingeAnchor2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetDHingeAnchor2(*j, x, y, z);
	return 0;
}


int dJointGetDHingeAnchor1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetDHingeAnchor1(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetDHingeAnchor2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetDHingeAnchor2(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetDHingeDistance_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetDHingeDistance(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointSetTransmissionMode_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int mode = luaL_checkinteger(L, 2);
	dJointSetTransmissionMode(*j, mode);
	return 0;
}


int dJointGetTransmissionMode_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int bind_result = dJointGetTransmissionMode(*j);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dJointGetTransmissionContactPoint1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetTransmissionContactPoint1(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetTransmissionContactPoint2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetTransmissionContactPoint2(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointSetTransmissionAxis1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetTransmissionAxis1(*j, x, y, z);
	return 0;
}


int dJointSetTransmissionAxis2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetTransmissionAxis2(*j, x, y, z);
	return 0;
}


int dJointGetTransmissionAxis1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetTransmissionAxis1(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetTransmissionAxis2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetTransmissionAxis2(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointSetTransmissionAnchor1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetTransmissionAnchor1(*j, x, y, z);
	return 0;
}


int dJointSetTransmissionAnchor2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetTransmissionAnchor2(*j, x, y, z);
	return 0;
}


int dJointGetTransmissionAnchor1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetTransmissionAnchor1(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetTransmissionAnchor2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetTransmissionAnchor2(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointSetTransmissionRatio_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal ratio = luaL_checknumber(L, 2);
	dJointSetTransmissionRatio(*j, ratio);
	return 0;
}


int dJointGetTransmissionRatio_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetTransmissionRatio(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointSetTransmissionAxis_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dJointSetTransmissionAxis(*j, x, y, z);
	return 0;
}


int dJointGetTransmissionAxis_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dVector3 result;
	dJointGetTransmissionAxis(*j, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dJointGetTransmissionAngle1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetTransmissionAngle1(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetTransmissionAngle2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetTransmissionAngle2(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetTransmissionRadius1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetTransmissionRadius1(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetTransmissionRadius2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetTransmissionRadius2(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointSetTransmissionRadius1_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal radius = luaL_checknumber(L, 2);
	dJointSetTransmissionRadius1(*j, radius);
	return 0;
}


int dJointSetTransmissionRadius2_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal radius = luaL_checknumber(L, 2);
	dJointSetTransmissionRadius2(*j, radius);
	return 0;
}


int dJointSetTransmissionBacklash_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal backlash = luaL_checknumber(L, 2);
	dJointSetTransmissionBacklash(*j, backlash);
	return 0;
}


int dJointGetTransmissionBacklash_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal bind_result = dJointGetTransmissionBacklash(*j);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointSetHingeParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal value = luaL_checknumber(L, 3);
	dJointSetHingeParam(*j, parameter, value);
	return 0;
}


int dJointSetSliderParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal value = luaL_checknumber(L, 3);
	dJointSetSliderParam(*j, parameter, value);
	return 0;
}


int dJointSetHinge2Param_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal value = luaL_checknumber(L, 3);
	dJointSetHinge2Param(*j, parameter, value);
	return 0;
}


int dJointSetUniversalParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal value = luaL_checknumber(L, 3);
	dJointSetUniversalParam(*j, parameter, value);
	return 0;
}


int dJointSetAMotorParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal value = luaL_checknumber(L, 3);
	dJointSetAMotorParam(*j, parameter, value);
	return 0;
}


int dJointSetLMotorParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal value = luaL_checknumber(L, 3);
	dJointSetLMotorParam(*j, parameter, value);
	return 0;
}


int dJointSetPRParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal value = luaL_checknumber(L, 3);
	dJointSetPRParam(*j, parameter, value);
	return 0;
}


int dJointSetPUParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal value = luaL_checknumber(L, 3);
	dJointSetPUParam(*j, parameter, value);
	return 0;
}


int dJointSetPistonParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal value = luaL_checknumber(L, 3);
	dJointSetPistonParam(*j, parameter, value);
	return 0;
}


int dJointSetDBallParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal value = luaL_checknumber(L, 3);
	dJointSetDBallParam(*j, parameter, value);
	return 0;
}


int dJointSetDHingeParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal value = luaL_checknumber(L, 3);
	dJointSetDHingeParam(*j, parameter, value);
	return 0;
}


int dJointSetTransmissionParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal value = luaL_checknumber(L, 3);
	dJointSetTransmissionParam(*j, parameter, value);
	return 0;
}


int dJointGetHingeParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal bind_result = dJointGetHingeParam(*j, parameter);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetSliderParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal bind_result = dJointGetSliderParam(*j, parameter);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetHinge2Param_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal bind_result = dJointGetHinge2Param(*j, parameter);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetUniversalParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal bind_result = dJointGetUniversalParam(*j, parameter);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetAMotorParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal bind_result = dJointGetAMotorParam(*j, parameter);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetLMotorParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal bind_result = dJointGetLMotorParam(*j, parameter);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetPRParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal bind_result = dJointGetPRParam(*j, parameter);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetPUParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal bind_result = dJointGetPUParam(*j, parameter);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetPistonParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal bind_result = dJointGetPistonParam(*j, parameter);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetDBallParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal bind_result = dJointGetDBallParam(*j, parameter);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetDHingeParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal bind_result = dJointGetDHingeParam(*j, parameter);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointGetTransmissionParam_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	int parameter = luaL_checkinteger(L, 2);
	dReal bind_result = dJointGetTransmissionParam(*j, parameter);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dJointAddHingeTorque_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal torque = luaL_checknumber(L, 2);
	dJointAddHingeTorque(*j, torque);
	return 0;
}


int dJointAddUniversalTorques_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal torque1 = luaL_checknumber(L, 2);
	dReal torque2 = luaL_checknumber(L, 3);
	dJointAddUniversalTorques(*j, torque1, torque2);
	return 0;
}


int dJointAddSliderForce_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal force = luaL_checknumber(L, 2);
	dJointAddSliderForce(*j, force);
	return 0;
}


int dJointAddHinge2Torques_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal torque1 = luaL_checknumber(L, 2);
	dReal torque2 = luaL_checknumber(L, 3);
	dJointAddHinge2Torques(*j, torque1, torque2);
	return 0;
}


int dJointAddAMotorTorques_bind(lua_State *L)
{
	dJointID *j = luaL_checkudata(L, 1, ode_joint_tname);
	dReal torque0 = luaL_checknumber(L, 2);
	dReal torque1 = luaL_checknumber(L, 3);
	dReal torque2 = luaL_checknumber(L, 4);
	dJointAddAMotorTorques(*j, torque0, torque1, torque2);
	return 0;
}
