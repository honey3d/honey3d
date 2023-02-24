#include <lua.h>
#include <lauxlib.h>
#include <ode/ode.h>
#include "ode_bindings.h"


struct body_data_t {
	lua_State *L;
	int callback_ref;
};

struct body_t {
	dBodyID id;
	struct body_data_t data;
};


void ode_push_body(lua_State *L, dBodyID bb)
{
	struct body_t *b = lua_newuserdata(L, sizeof(struct body_t));
	b->id = bb;
	b->data.L = L;
	b->data.callback_ref = LUA_NOREF;
	dBodySetData(b->id, &(b->data));
	luaL_getmetatable(L, ode_body_tname);
	lua_setmetatable(L, -2);
}


int dBodyCreate_bind(lua_State *L)
{
	dWorldID *w = luaL_checkudata(L, 1, ode_world_tname);
	dBodyID b = dBodyCreate(*w);
	ode_push_body(L, b);
	return 1;
}


int dBodyDestroy_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dBodyDestroy(*b);
	return 0;
}


int dBodySetPosition_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal x = luaL_checkinteger(L, 2);
	dReal y = luaL_checkinteger(L, 3);
	dReal z = luaL_checkinteger(L, 4);
	dBodySetPosition(*b, x, y, z);
	return 0;
}


int dBodySetRotation_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dMatrix3 R;
	R[0] = luaL_checknumber(L, 2);
	R[1] = luaL_checknumber(L, 3);
	R[2] = luaL_checknumber(L, 4);

	R[4] = luaL_checknumber(L, 5);
	R[5] = luaL_checknumber(L, 6);
	R[6] = luaL_checknumber(L, 7);

	R[8] = luaL_checknumber(L, 8);
	R[9] = luaL_checknumber(L, 9);
	R[10] = luaL_checknumber(L, 10);

	dBodySetRotation(*b, R);
	return 0;
}


int dBodySetQuaternion_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dQuaternion q;
	q[0] = luaL_checknumber(L, 2);
	q[1] = luaL_checknumber(L, 3);
	q[2] = luaL_checknumber(L, 4);
	q[3] = luaL_checknumber(L, 5);
	dBodySetQuaternion(*b, q);
	return 0;
}


int dBodySetLinearVel_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal x = luaL_checkinteger(L, 2);
	dReal y = luaL_checkinteger(L, 3);
	dReal z = luaL_checkinteger(L, 4);
	dBodySetLinearVel(*b, x, y, z);
	return 0;
}


int dBodySetAngularVel_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal x = luaL_checkinteger(L, 2);
	dReal y = luaL_checkinteger(L, 3);
	dReal z = luaL_checkinteger(L, 4);
	dBodySetAngularVel(*b, x, y, z);
	return 0;
}


int dBodyGetPosition_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	const dReal * bind_result = dBodyGetPosition(*b);
	lua_pushnumber(L, bind_result[0]);
	lua_pushnumber(L, bind_result[1]);
	lua_pushnumber(L, bind_result[2]);
	return 3;
}


int dBodyGetRotation_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	const dReal * bind_result = dBodyGetRotation(*b);
	lua_pushnumber(L, bind_result[0]);
	lua_pushnumber(L, bind_result[1]);
	lua_pushnumber(L, bind_result[2]);
	return 3;
}


int dBodyGetQuaternion_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	const dReal * bind_result = dBodyGetQuaternion(*b);
	lua_pushnumber(L, bind_result[0]);
	lua_pushnumber(L, bind_result[1]);
	lua_pushnumber(L, bind_result[2]);
	return 3;
}


int dBodyGetLinearVel_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	const dReal * bind_result = dBodyGetLinearVel(*b);
	lua_pushnumber(L, bind_result[0]);
	lua_pushnumber(L, bind_result[1]);
	lua_pushnumber(L, bind_result[2]);
	return 3;
}


int dBodyGetAngularVel_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	const dReal * bind_result = dBodyGetAngularVel(*b);
	lua_pushnumber(L, bind_result[0]);
	lua_pushnumber(L, bind_result[1]);
	lua_pushnumber(L, bind_result[2]);
	return 3;
}


int dBodySetMass_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	const dMass *mass = luaL_checkudata(L, 2, ode_mass_tname);
	dBodySetMass(*b, mass);
	return 0;
}


int dBodyGetMass_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dMass * mass = luaL_checkudata(L, 2, ode_mass_tname);
	dBodyGetMass(*b, mass);
	return 0;
}


int dBodyAddForce_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal fx = luaL_checkinteger(L, 2);
	dReal fy = luaL_checkinteger(L, 3);
	dReal fz = luaL_checkinteger(L, 4);
	dBodyAddForce(*b, fx, fy, fz);
	return 0;
}


int dBodyAddTorque_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal fx = luaL_checkinteger(L, 2);
	dReal fy = luaL_checkinteger(L, 3);
	dReal fz = luaL_checkinteger(L, 4);
	dBodyAddTorque(*b, fx, fy, fz);
	return 0;
}


int dBodyAddRelForce_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal fx = luaL_checkinteger(L, 2);
	dReal fy = luaL_checkinteger(L, 3);
	dReal fz = luaL_checkinteger(L, 4);
	dBodyAddRelForce(*b, fx, fy, fz);
	return 0;
}


int dBodyAddRelTorque_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal fx = luaL_checkinteger(L, 2);
	dReal fy = luaL_checkinteger(L, 3);
	dReal fz = luaL_checkinteger(L, 4);
	dBodyAddRelTorque(*b, fx, fy, fz);
	return 0;
}


int dBodyAddForceAtPos_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal fx = luaL_checkinteger(L, 2);
	dReal fy = luaL_checkinteger(L, 3);
	dReal fz = luaL_checkinteger(L, 4);
	dReal px = luaL_checkinteger(L, 5);
	dReal py = luaL_checkinteger(L, 6);
	dReal pz = luaL_checkinteger(L, 7);
	dBodyAddForceAtPos(*b, fx, fy, fz, px, py, pz);
	return 0;
}


int dBodyAddForceAtRelPos_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal fx = luaL_checkinteger(L, 2);
	dReal fy = luaL_checkinteger(L, 3);
	dReal fz = luaL_checkinteger(L, 4);
	dReal px = luaL_checkinteger(L, 5);
	dReal py = luaL_checkinteger(L, 6);
	dReal pz = luaL_checkinteger(L, 7);
	dBodyAddForceAtRelPos(*b, fx, fy, fz, px, py, pz);
	return 0;
}


int dBodyAddRelForceAtPos_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal fx = luaL_checkinteger(L, 2);
	dReal fy = luaL_checkinteger(L, 3);
	dReal fz = luaL_checkinteger(L, 4);
	dReal px = luaL_checkinteger(L, 5);
	dReal py = luaL_checkinteger(L, 6);
	dReal pz = luaL_checkinteger(L, 7);
	dBodyAddRelForceAtPos(*b, fx, fy, fz, px, py, pz);
	return 0;
}


int dBodyAddRelForceAtRelPos_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal fx = luaL_checkinteger(L, 2);
	dReal fy = luaL_checkinteger(L, 3);
	dReal fz = luaL_checkinteger(L, 4);
	dReal px = luaL_checkinteger(L, 5);
	dReal py = luaL_checkinteger(L, 6);
	dReal pz = luaL_checkinteger(L, 7);
	dBodyAddRelForceAtRelPos(*b, fx, fy, fz, px, py, pz);
	return 0;
}


int dBodyGetForce_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	const dReal * bind_result = dBodyGetForce(*b);
	lua_pushnumber(L, bind_result[0]);
	lua_pushnumber(L, bind_result[1]);
	lua_pushnumber(L, bind_result[2]);
	return 3;
}


int dBodyGetTorque_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	const dReal * bind_result = dBodyGetTorque(*b);
	lua_pushnumber(L, bind_result[0]);
	lua_pushnumber(L, bind_result[1]);
	lua_pushnumber(L, bind_result[2]);
	return 3;
}


int dBodySetForce_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal x = luaL_checkinteger(L, 2);
	dReal y = luaL_checkinteger(L, 3);
	dReal z = luaL_checkinteger(L, 4);
	dBodySetForce(*b, x, y, z);
	return 0;
}


int dBodySetTorque_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal x = luaL_checkinteger(L, 2);
	dReal y = luaL_checkinteger(L, 3);
	dReal z = luaL_checkinteger(L, 4);
	dBodySetTorque(*b, x, y, z);
	return 0;
}


int dBodySetDynamic_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dBodySetDynamic(*b);
	return 0;
}


int dBodySetKinematic_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dBodySetKinematic(*b);
	return 0;
}


int dBodyIsKinematic_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	int bind_result = dBodyIsKinematic(*b);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dBodyGetRelPointPos_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal px = luaL_checkinteger(L, 2);
	dReal py = luaL_checkinteger(L, 3);
	dReal pz = luaL_checkinteger(L, 4);
	dVector3 result;
	dBodyGetRelPointPos(*b, px, py, pz, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dBodyGetRelPointVel_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal px = luaL_checkinteger(L, 2);
	dReal py = luaL_checkinteger(L, 3);
	dReal pz = luaL_checkinteger(L, 4);
	dVector3 result;
	dBodyGetRelPointVel(*b, px, py, pz, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dBodyGetPointVel_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal px = luaL_checkinteger(L, 2);
	dReal py = luaL_checkinteger(L, 3);
	dReal pz = luaL_checkinteger(L, 4);
	dVector3 result;
	dBodyGetPointVel(*b, px, py, pz, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dBodyGetPosRelPoint_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal px = luaL_checkinteger(L, 2);
	dReal py = luaL_checkinteger(L, 3);
	dReal pz = luaL_checkinteger(L, 4);
	dVector3 result;
	dBodyGetPosRelPoint(*b, px, py, pz, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dBodyVectorToWorld_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal px = luaL_checkinteger(L, 2);
	dReal py = luaL_checkinteger(L, 3);
	dReal pz = luaL_checkinteger(L, 4);
	dVector3 result;
	dBodyVectorToWorld(*b, px, py, pz, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dBodyVectorFromWorld_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal px = luaL_checkinteger(L, 2);
	dReal py = luaL_checkinteger(L, 3);
	dReal pz = luaL_checkinteger(L, 4);
	dVector3 result;
	dBodyVectorFromWorld(*b, px, py, pz, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dBodyEnable_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dBodyEnable(*b);
	return 0;
}


int dBodyDisable_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dBodyDisable(*b);
	return 0;
}


int dBodyIsEnabled_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	int bind_result = dBodyIsEnabled(*b);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dBodySetAutoDisableFlag_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	int do_auto_disable = lua_toboolean(L, 2);
	dBodySetAutoDisableFlag(*b, do_auto_disable);
	return 0;
}


int dBodyGetAutoDisableFlag_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	int bind_result = dBodyGetAutoDisableFlag(*b);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dBodySetAutoDisableLinearThreshold_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal linear_threshold = luaL_checkinteger(L, 2);
	dBodySetAutoDisableLinearThreshold(*b, linear_threshold);
	return 0;
}


int dBodyGetAutoDisableLinearThreshold_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal bind_result = dBodyGetAutoDisableLinearThreshold(*b);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dBodySetAutoDisableAngularThreshold_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal angular_threshold = luaL_checkinteger(L, 2);
	dBodySetAutoDisableAngularThreshold(*b, angular_threshold);
	return 0;
}


int dBodyGetAutoDisableAngularThreshold_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal bind_result = dBodyGetAutoDisableAngularThreshold(*b);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dBodySetAutoDisableSteps_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	int steps = luaL_checkinteger(L, 2);
	dBodySetAutoDisableSteps(*b, steps);
	return 0;
}


int dBodyGetAutoDisableSteps_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	int bind_result = dBodyGetAutoDisableSteps(*b);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dBodySetAutoDisableTime_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal time = luaL_checkinteger(L, 2);
	dBodySetAutoDisableTime(*b, time);
	return 0;
}


int dBodyGetAutoDisableTime_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal bind_result = dBodyGetAutoDisableTime(*b);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dBodySetAutoDisableAverageSamplesCount_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	unsigned int average_samples_count = luaL_checkinteger(L, 2);
	dBodySetAutoDisableAverageSamplesCount(*b, average_samples_count);
	return 0;
}


int dBodyGetAutoDisableAverageSamplesCount_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	int bind_result = dBodyGetAutoDisableAverageSamplesCount(*b);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dBodySetAutoDisableDefaults_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dBodySetAutoDisableDefaults(*b);
	return 0;
}


static void moved_cb(dBodyID b)
{
	struct body_data_t *data = dBodyGetData(b);
	lua_State *L = data->L;
	int ref = data->callback_ref;
	lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
	lua_call(L, 0, 0);
}

int dBodySetMovedCallback_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	luaL_checktype(L, 2, LUA_TFUNCTION);
	int callback = 2;

	struct body_data_t *data = dBodyGetData(*b);
	lua_pushvalue(L, callback);
	data->callback_ref = luaL_ref(L, LUA_REGISTRYINDEX);

	dBodySetMovedCallback(*b, moved_cb);
	return 0;
}


int dBodyGetLinearDamping_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal bind_result = dBodyGetLinearDamping(*b);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dBodyGetAngularDamping_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal bind_result = dBodyGetAngularDamping(*b);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dBodySetLinearDamping_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal scale = luaL_checkinteger(L, 2);
	dBodySetLinearDamping(*b, scale);
	return 0;
}


int dBodySetAngularDamping_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal scale = luaL_checkinteger(L, 2);
	dBodySetAngularDamping(*b, scale);
	return 0;
}


int dBodySetDamping_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal linear_scale = luaL_checkinteger(L, 2);
	dReal angular_scale = luaL_checkinteger(L, 3);
	dBodySetDamping(*b, linear_scale, angular_scale);
	return 0;
}


int dBodyGetLinearDampingThreshold_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal bind_result = dBodyGetLinearDampingThreshold(*b);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dBodyGetAngularDampingThreshold_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal bind_result = dBodyGetAngularDampingThreshold(*b);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dBodySetLinearDampingThreshold_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal threshold = luaL_checkinteger(L, 2);
	dBodySetLinearDampingThreshold(*b, threshold);
	return 0;
}


int dBodySetAngularDampingThreshold_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal threshold = luaL_checkinteger(L, 2);
	dBodySetAngularDampingThreshold(*b, threshold);
	return 0;
}


int dBodySetDampingDefaults_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dBodySetDampingDefaults(*b);
	return 0;
}


int dBodyGetMaxAngularSpeed_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal bind_result = dBodyGetMaxAngularSpeed(*b);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dBodySetMaxAngularSpeed_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal max_speed = luaL_checkinteger(L, 2);
	dBodySetMaxAngularSpeed(*b, max_speed);
	return 0;
}


int dBodySetFiniteRotationMode_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	int mode = luaL_checkinteger(L, 2);
	dBodySetFiniteRotationMode(*b, mode);
	return 0;
}


int dBodyGetFiniteRotationMode_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	int bind_result = dBodyGetFiniteRotationMode(*b);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dBodySetFiniteRotationAxis_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dReal x = luaL_checkinteger(L, 2);
	dReal y = luaL_checkinteger(L, 3);
	dReal z = luaL_checkinteger(L, 4);
	dBodySetFiniteRotationAxis(*b, x, y, z);
	return 0;
}


int dBodyGetFiniteRotationAxis_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dVector3 result;
	dBodyGetFiniteRotationAxis(*b, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dBodyGetNumJoints_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	int bind_result = dBodyGetNumJoints(*b);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dBodyGetJoint_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	int index = luaL_checkinteger(L, 2);
	dJointID bind_result = dBodyGetJoint(*b, index);
	ode_push_joint(L, bind_result);
	return 1;
}


int dBodyGetWorld_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dWorldID bind_result = dBodyGetWorld(*b);
	ode_push_world(L, bind_result);
	return 1;
}


int dBodySetGravityMode_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	int mode = lua_toboolean(L, 2);
	dBodySetGravityMode(*b, mode);
	return 0;
}


int dBodyGetGravityMode_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	int bind_result = dBodyGetGravityMode(*b);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dBodyGetFirstGeom_bind(lua_State *L)
{
	dBodyID *b = luaL_checkudata(L, 1, ode_body_tname);
	dGeomID bind_result = dBodyGetFirstGeom(*b);
	ode_push_geom(L, bind_result);
	return 1;
}


int dBodyGetNextGeom_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dGeomID bind_result = dBodyGetNextGeom(*g);
	ode_push_geom(L, bind_result);
	return 1;
}
