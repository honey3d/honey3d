#include <lua.h>
#include <lauxlib.h>
#include <ode/ode.h>
#include "ode_bindings.h"


void ode_push_geom(lua_State *L, dGeomID g)
{
	dGeomID *gu = lua_newuserdata(L, sizeof(dGeomID));
	*gu = g;
	luaL_getmetatable(L, ode_geom_tname);
	lua_setmetatable(L, -2);
}


void ode_push_space(lua_State *L, dSpaceID s)
{
	dSpaceID *su = lua_newuserdata(L, sizeof(dSpaceID));
	*su = s;
	luaL_getmetatable(L, ode_space_tname);
	lua_setmetatable(L, -2);
}


void ode_push_contactgeom(lua_State *L, dContactGeom cg)
{
	dContactGeom *cgu = lua_newuserdata(L, sizeof(dContactGeom));
	*cgu = cg;
}


void ode_push_trimeshdata(lua_State *L, dTriMeshDataID d)
{
	dTriMeshDataID *du = lua_newuserdata(L, sizeof(dTriMeshDataID));
	*du = d;
	luaL_getmetatable(L, ode_trimeshdata_tname);
	lua_setmetatable(L, -2);
}


void ode_push_heightfielddata(lua_State *L, dHeightfieldDataID d)
{
	dHeightfieldDataID *du = lua_newuserdata(L, sizeof(dHeightfieldDataID));
	*du = d;
	luaL_getmetatable(L, ode_heightfielddata_tname);
	lua_setmetatable(L, -2);
}


int dGeomDestroy_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dGeomDestroy(*g);
	return 0;
}


int dGeomSetBody_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dBodyID *b = luaL_checkudata(L, 2, ode_body_tname);
	dGeomSetBody(*g, *b);
	return 0;
}


int dGeomGetBody_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dBodyID bind_result = dGeomGetBody(*g);
	ode_push_body(L, bind_result);
	return 1;
}


int dGeomSetPosition_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dGeomSetPosition(*g, x, y, z);
	return 0;
}


int dGeomSetRotation_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
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
	dGeomSetRotation(*g, R);
	return 0;
}


int dGeomSetQuaternion_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dQuaternion q;
	q[0] = luaL_checknumber(L, 2);
	q[1] = luaL_checknumber(L, 3);
	q[2] = luaL_checknumber(L, 4);
	q[3] = luaL_checknumber(L, 5);
	dGeomSetQuaternion(*g, q);
	return 0;
}


int dGeomGetPosition_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	const dReal * bind_result = dGeomGetPosition(*g);
	lua_pushnumber(L, bind_result[0]);
	lua_pushnumber(L, bind_result[1]);
	lua_pushnumber(L, bind_result[2]);
	return 3;
}


int dGeomGetRotation_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	const dReal * bind_result = dGeomGetRotation(*g);
	lua_pushnumber(L, bind_result[0]);
	lua_pushnumber(L, bind_result[1]);
	lua_pushnumber(L, bind_result[2]);
	lua_pushnumber(L, bind_result[4]);
	lua_pushnumber(L, bind_result[5]);
	lua_pushnumber(L, bind_result[6]);
	lua_pushnumber(L, bind_result[8]);
	lua_pushnumber(L, bind_result[9]);
	lua_pushnumber(L, bind_result[10]);
	return 9;
}


int dGeomGetQuaternion_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dQuaternion result;
	dGeomGetQuaternion(*g, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	lua_pushnumber(L, result[3]);
	return 4;
}


int dGeomSetOffsetPosition_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dGeomSetOffsetPosition(*g, x, y, z);
	return 0;
}


int dGeomSetOffsetRotation_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
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
	dGeomSetOffsetRotation(*g, R);
	return 0;
}


int dGeomSetOffsetQuaternion_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dQuaternion Q;
	Q[0] = luaL_checknumber(L, 2);
	Q[1] = luaL_checknumber(L, 3);
	Q[2] = luaL_checknumber(L, 4);
	Q[3] = luaL_checknumber(L, 5);
	dGeomSetOffsetQuaternion(*g, Q);
	return 0;
}


int dGeomSetOffsetWorldPosition_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dGeomSetOffsetWorldPosition(*g, x, y, z);
	return 0;
}


int dGeomSetOffsetWorldRotation_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
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
	dGeomSetOffsetWorldRotation(*g, R);
	return 0;
}


int dGeomSetOffsetWorldQuaternion_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dQuaternion Q;
	Q[0] = luaL_checknumber(L, 2);
	Q[1] = luaL_checknumber(L, 3);
	Q[2] = luaL_checknumber(L, 4);
	Q[3] = luaL_checknumber(L, 5);
	dGeomSetOffsetWorldQuaternion(*g, Q);
	return 0;
}


int dGeomGetOffsetPosition_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	const dReal * bind_result = dGeomGetOffsetPosition(*g);
	lua_pushnumber(L, bind_result[0]);
	lua_pushnumber(L, bind_result[1]);
	lua_pushnumber(L, bind_result[2]);
	return 3;
}


int dGeomGetOffsetRotation_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	const dReal * bind_result = dGeomGetOffsetRotation(*g);
	lua_pushnumber(L, bind_result[0]);
	lua_pushnumber(L, bind_result[1]);
	lua_pushnumber(L, bind_result[2]);
	lua_pushnumber(L, bind_result[4]);
	lua_pushnumber(L, bind_result[5]);
	lua_pushnumber(L, bind_result[6]);
	lua_pushnumber(L, bind_result[8]);
	lua_pushnumber(L, bind_result[9]);
	lua_pushnumber(L, bind_result[10]);
	return 9;
}


int dGeomGetOffsetQuaternion_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dQuaternion result;
	dGeomGetOffsetQuaternion(*g, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	lua_pushnumber(L, result[3]);
	return 4;
}


int dGeomClearOffset_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dGeomClearOffset(*g);
	return 0;
}


int dGeomGetAABB_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dReal aabb[6];
	dGeomGetAABB(*g, aabb);
	lua_pushnumber(L, aabb[0]);
	lua_pushnumber(L, aabb[1]);
	lua_pushnumber(L, aabb[2]);
	lua_pushnumber(L, aabb[3]);
	lua_pushnumber(L, aabb[4]);
	lua_pushnumber(L, aabb[5]);
	return 6;
}


int dGeomIsSpace_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	int bind_result = dGeomIsSpace(*g);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dGeomGetSpace_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dSpaceID bind_result = dGeomGetSpace(*g);
	ode_push_space(L, bind_result);
	return 1;
}


int dGeomGetClass_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	int bind_result = dGeomGetClass(*g);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dGeomSetCategoryBits_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	unsigned long bits = luaL_checkinteger(L, 2);
	dGeomSetCategoryBits(*g, bits);
	return 0;
}


int dGeomSetCollideBits_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	unsigned long bits = luaL_checkinteger(L, 2);
	dGeomSetCollideBits(*g, bits);
	return 0;
}


int dGeomGetCategoryBits_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	unsigned long bind_result = dGeomGetCategoryBits(*g);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dGeomGetCollideBits_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	unsigned long bind_result = dGeomGetCollideBits(*g);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dGeomEnable_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dGeomEnable(*g);
	return 0;
}


int dGeomDisable_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dGeomDisable(*g);
	return 0;
}


int dGeomIsEnabled_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	int bind_result = dGeomIsEnabled(*g);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dCollide_bind(lua_State *L)
{
	dGeomID *o1 = luaL_checkudata(L, 1, ode_geom_tname);
	dGeomID *o2 = luaL_checkudata(L, 2, ode_geom_tname);
	int flags = luaL_checkinteger(L, 3);
	size_t count = flags & 0xff; /* lower 16 bits for flags are the number of contacts requested */
	dContactGeom *contacts = malloc(count * sizeof(dContactGeom));
	if (contacts == NULL) {
		return luaL_error(L, "failed to allocate %lu bytes for contacts buffer", count * sizeof(dContactGeom));
	}
	count = dCollide(*o1, *o2, flags, contacts, sizeof(dContactGeom));
	
	lua_createtable(L, count, 0);
	int tbl = lua_gettop(L);
	for (int i=0; i<count; i++) {
		ode_push_contactgeom(L, contacts[i]);
		lua_rawseti(L, tbl, i+1);
	}
	return 1;
}


struct near_data_t {
	lua_State *L;
	int ref;
};

static void near(void *data, dGeomID o1, dGeomID o2)
{
	struct near_data_t *d = data;
	lua_State *L = d->L;

	lua_rawgeti(L, LUA_REGISTRYINDEX, d->ref);
	ode_push_geom(L, o1);
	ode_push_geom(L, o2);
	lua_call(L, 2, 0);
}

int dSpaceCollide_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	luaL_checktype(L, 2, LUA_TFUNCTION);
	lua_pushvalue(L, 2);
	int ref = luaL_ref(L, LUA_REGISTRYINDEX);
	struct near_data_t data = { L, ref };
	dSpaceCollide(*space, &data, near);
	luaL_unref(L, LUA_REGISTRYINDEX, ref);
	return 0;
}


int dSpaceCollide2_bind(lua_State *L)
{
	dGeomID *o1 = luaL_checkudata(L, 1, ode_geom_tname);
	dGeomID *o2 = luaL_checkudata(L, 2, ode_geom_tname);
	luaL_checktype(L, 3, LUA_TFUNCTION);
	lua_pushvalue(L, 3);
	int ref = luaL_ref(L, LUA_REGISTRYINDEX);
	struct near_data_t data = { L, ref };
	dSpaceCollide2(*o1, *o2, &data, near);
	luaL_unref(L, LUA_REGISTRYINDEX, ref);
	return 0;
}


int dSimpleSpaceCreate_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	dSpaceID bind_result = dSimpleSpaceCreate(*space);
	ode_push_space(L, bind_result);
	return 1;
}


int dHashSpaceCreate_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	dSpaceID bind_result = dHashSpaceCreate(*space);
	ode_push_space(L, bind_result);
	return 1;
}


int dQuadTreeSpaceCreate_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	dVector3 Center;
	Center[0] = luaL_checknumber(L, 2);
	Center[1] = luaL_checknumber(L, 3);
	Center[2] = luaL_checknumber(L, 4);
	dVector3 Extents;
	Extents[0] = luaL_checknumber(L, 5);
	Extents[1] = luaL_checknumber(L, 6);
	Extents[2] = luaL_checknumber(L, 7);
	int Depth = luaL_checkinteger(L, 8);
	dSpaceID bind_result = dQuadTreeSpaceCreate(*space, Center, Extents, Depth);
	ode_push_space(L, bind_result);
	return 1;
}


int dSpaceDestroy_bind(lua_State *L)
{
	dSpaceID *s = luaL_checkudata(L, 1, ode_space_tname);
	dSpaceDestroy(*s);
	return 0;
}


int dHashSpaceSetLevels_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	int minlevel = luaL_checkinteger(L, 2);
	int maxlevel = luaL_checkinteger(L, 3);
	dHashSpaceSetLevels(*space, minlevel, maxlevel);
	return 0;
}


int dHashSpaceGetLevels_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	int minlevel, maxlevel;
	dHashSpaceGetLevels(*space, &minlevel, &maxlevel);
	lua_pushinteger(L, minlevel);
	lua_pushinteger(L, maxlevel);
	return 2;
}


int dSpaceSetCleanup_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	int mode = luaL_checkinteger(L, 2);
	dSpaceSetCleanup(*space, mode);
	return 0;
}


int dSpaceGetCleanup_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	int bind_result = dSpaceGetCleanup(*space);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dSpaceSetSublevel_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	int sublevel = luaL_checkinteger(L, 2);
	dSpaceSetSublevel(*space, sublevel);
	return 0;
}


int dSpaceGetSublevel_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	int bind_result = dSpaceGetSublevel(*space);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dSpaceAdd_bind(lua_State *L)
{
	dSpaceID *s = luaL_checkudata(L, 1, ode_space_tname);
	dGeomID *g = luaL_checkudata(L, 2, ode_geom_tname);
	dSpaceAdd(*s, *g);
	return 0;
}


int dSpaceRemove_bind(lua_State *L)
{
	dSpaceID *s = luaL_checkudata(L, 1, ode_space_tname);
	dGeomID *g = luaL_checkudata(L, 2, ode_geom_tname);
	dSpaceRemove(*s, *g);
	return 0;
}


int dSpaceQuery_bind(lua_State *L)
{
	dSpaceID *s = luaL_checkudata(L, 1, ode_space_tname);
	dGeomID *g = luaL_checkudata(L, 2, ode_geom_tname);
	int bind_result = dSpaceQuery(*s, *g);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dSpaceGetNumGeoms_bind(lua_State *L)
{
	dSpaceID *s = luaL_checkudata(L, 1, ode_space_tname);
	int bind_result = dSpaceGetNumGeoms(*s);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dSpaceGetGeom_bind(lua_State *L)
{
	dSpaceID *s = luaL_checkudata(L, 1, ode_space_tname);
	int i = luaL_checkinteger(L, 2);
	dGeomID bind_result = dSpaceGetGeom(*s, i);
	ode_push_geom(L, bind_result);
	return 1;
}


int dCreateSphere_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	dReal radius = luaL_checknumber(L, 2);
	dGeomID bind_result = dCreateSphere(*space, radius);
	ode_push_geom(L, bind_result);
	return 1;
}


int dGeomSphereSetRadius_bind(lua_State *L)
{
	dGeomID *sphere = luaL_checkudata(L, 1, ode_geom_tname);
	dReal radius = luaL_checknumber(L, 2);
	dGeomSphereSetRadius(*sphere, radius);
	return 0;
}


int dGeomSphereGetRadius_bind(lua_State *L)
{
	dGeomID *sphere = luaL_checkudata(L, 1, ode_geom_tname);
	dReal bind_result = dGeomSphereGetRadius(*sphere);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dGeomSpherePointDepth_bind(lua_State *L)
{
	dGeomID *sphere = luaL_checkudata(L, 1, ode_geom_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dReal bind_result = dGeomSpherePointDepth(*sphere, x, y, z);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dCreateBox_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	dReal lx = luaL_checknumber(L, 2);
	dReal ly = luaL_checknumber(L, 3);
	dReal lz = luaL_checknumber(L, 4);
	dGeomID bind_result = dCreateBox(*space, lx, ly, lz);
	ode_push_geom(L, bind_result);
	return 1;
}


int dGeomBoxSetLengths_bind(lua_State *L)
{
	dGeomID *box = luaL_checkudata(L, 1, ode_geom_tname);
	dReal lx = luaL_checknumber(L, 2);
	dReal ly = luaL_checknumber(L, 3);
	dReal lz = luaL_checknumber(L, 4);
	dGeomBoxSetLengths(*box, lx, ly, lz);
	return 0;
}


int dGeomBoxGetLengths_bind(lua_State *L)
{
	dGeomID *box = luaL_checkudata(L, 1, ode_geom_tname);
	dVector3 result;
	dGeomBoxGetLengths(*box, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int dGeomBoxPointDepth_bind(lua_State *L)
{
	dGeomID *box = luaL_checkudata(L, 1, ode_geom_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dReal bind_result = dGeomBoxPointDepth(*box, x, y, z);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dCreatePlane_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	dReal a = luaL_checknumber(L, 2);
	dReal b = luaL_checknumber(L, 3);
	dReal c = luaL_checknumber(L, 4);
	dReal d = luaL_checknumber(L, 5);
	dGeomID bind_result = dCreatePlane(*space, a, b, c, d);
	ode_push_geom(L, bind_result);
	return 1;
}


int dGeomPlaneSetParams_bind(lua_State *L)
{
	dGeomID *plane = luaL_checkudata(L, 1, ode_geom_tname);
	dReal a = luaL_checknumber(L, 2);
	dReal b = luaL_checknumber(L, 3);
	dReal c = luaL_checknumber(L, 4);
	dReal d = luaL_checknumber(L, 5);
	dGeomPlaneSetParams(*plane, a, b, c, d);
	return 0;
}


int dGeomPlaneGetParams_bind(lua_State *L)
{
	dGeomID *plane = luaL_checkudata(L, 1, ode_geom_tname);
	dVector4 result;
	dGeomPlaneGetParams(*plane, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	lua_pushnumber(L, result[3]);
	return 4;
}


int dGeomPlanePointDepth_bind(lua_State *L)
{
	dGeomID *plane = luaL_checkudata(L, 1, ode_geom_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dReal bind_result = dGeomPlanePointDepth(*plane, x, y, z);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dCreateCapsule_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	dReal radius = luaL_checknumber(L, 2);
	dReal length = luaL_checknumber(L, 3);
	dGeomID bind_result = dCreateCapsule(*space, radius, length);
	ode_push_geom(L, bind_result);
	return 1;
}


int dGeomCapsuleSetParams_bind(lua_State *L)
{
	dGeomID *capsule = luaL_checkudata(L, 1, ode_geom_tname);
	dReal radius = luaL_checknumber(L, 2);
	dReal length = luaL_checknumber(L, 3);
	dGeomCapsuleSetParams(*capsule, radius, length);
	return 0;
}


int dGeomCapsuleGetParams_bind(lua_State *L)
{
	dGeomID *capsule = luaL_checkudata(L, 1, ode_geom_tname);
	dReal radius, length;
	dGeomCapsuleGetParams(*capsule, &radius, &length);
	lua_pushnumber(L, radius);
	lua_pushnumber(L, length);
	return 2;
}


int dGeomCapsulePointDepth_bind(lua_State *L)
{
	dGeomID *capsule = luaL_checkudata(L, 1, ode_geom_tname);
	dReal x = luaL_checknumber(L, 2);
	dReal y = luaL_checknumber(L, 3);
	dReal z = luaL_checknumber(L, 4);
	dReal bind_result = dGeomCapsulePointDepth(*capsule, x, y, z);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dCreateCylinder_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	dReal radius = luaL_checknumber(L, 2);
	dReal length = luaL_checknumber(L, 3);
	dGeomID bind_result = dCreateCylinder(*space, radius, length);
	ode_push_geom(L, bind_result);
	return 1;
}


int dGeomCylinderSetParams_bind(lua_State *L)
{
	dGeomID *cylinder = luaL_checkudata(L, 1, ode_geom_tname);
	dReal radius = luaL_checknumber(L, 2);
	dReal length = luaL_checknumber(L, 3);
	dGeomCylinderSetParams(*cylinder, radius, length);
	return 0;
}


int dGeomCylinderGetParams_bind(lua_State *L)
{
	dGeomID *cylinder = luaL_checkudata(L, 1, ode_geom_tname);
	dReal radius, length;
	dGeomCylinderGetParams(*cylinder, &radius, &length);
	lua_pushnumber(L, radius);
	lua_pushnumber(L, length);
	return 2;
}


int dCreateRay_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	dReal length = luaL_checknumber(L, 2);
	dGeomID bind_result = dCreateRay(*space, length);
	ode_push_geom(L, bind_result);
	return 1;
}


int dGeomRaySetLength_bind(lua_State *L)
{
	dGeomID *ray = luaL_checkudata(L, 1, ode_geom_tname);
	dReal length = luaL_checknumber(L, 2);
	dGeomRaySetLength(*ray, length);
	return 0;
}


int dGeomRayGetLength_bind(lua_State *L)
{
	dGeomID *ray = luaL_checkudata(L, 1, ode_geom_tname);
	dReal bind_result = dGeomRayGetLength(*ray);
	lua_pushnumber(L, bind_result);
	return 1;
}


int dGeomRaySet_bind(lua_State *L)
{
	dGeomID *ray = luaL_checkudata(L, 1, ode_geom_tname);
	dReal px = luaL_checknumber(L, 2);
	dReal py = luaL_checknumber(L, 3);
	dReal pz = luaL_checknumber(L, 4);
	dReal dx = luaL_checknumber(L, 5);
	dReal dy = luaL_checknumber(L, 6);
	dReal dz = luaL_checknumber(L, 7);
	dGeomRaySet(*ray, px, py, pz, dx, dy, dz);
	return 0;
}


int dGeomRayGet_bind(lua_State *L)
{
	dGeomID *ray = luaL_checkudata(L, 1, ode_geom_tname);
	dVector3 start;
	dVector3 dir;
	dGeomRayGet(*ray, start, dir);
	lua_pushnumber(L, start[0]);
	lua_pushnumber(L, start[1]);
	lua_pushnumber(L, start[2]);
	lua_pushnumber(L, dir[0]);
	lua_pushnumber(L, dir[1]);
	lua_pushnumber(L, dir[2]);
	return 6;
}


int dGeomRaySetClosestHit_bind(lua_State *L)
{
	dGeomID *ray = luaL_checkudata(L, 1, ode_geom_tname);
	int ClosestHit = luaL_checkinteger(L, 2);
	dGeomRaySetClosestHit(*ray, ClosestHit);
	return 0;
}


int dGeomRayGetClosestHit_bind(lua_State *L)
{
	dGeomID *ray = luaL_checkudata(L, 1, ode_geom_tname);
	int bind_result = dGeomRayGetClosestHit(*ray);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dGeomRaySetFirstContact_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	int first_contact = luaL_checkinteger(L, 2);
	dGeomRaySetFirstContact(*g, first_contact);
	return 0;
}


int dGeomRayGetFirstContact_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	int bind_result = dGeomRayGetFirstContact(*g);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dGeomRaySetBackfaceCull_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	int backfaceCull = luaL_checkinteger(L, 2);
	dGeomRaySetBackfaceCull(*g, backfaceCull);
	return 0;
}


int dGeomRayGetBackfaceCull_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	int bind_result = dGeomRayGetBackfaceCull(*g);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dGeomTriMeshDataCreate_bind(lua_State *L)
{
	dTriMeshDataID bind_result = dGeomTriMeshDataCreate();
	ode_push_trimeshdata(L, bind_result);
	return 1;
}


int dGeomTriMeshDataDestroy_bind(lua_State *L)
{
	dTriMeshDataID *g = luaL_checkudata(L, 1, ode_trimeshdata_tname);
	dGeomTriMeshDataDestroy(*g);
	return 0;
}


int dGeomTriMeshDataBuild_bind(lua_State *L)
{
	dTriMeshDataID *g = luaL_checkudata(L, 1, ode_trimeshdata_tname);
	luaL_checktype(L, 2, LUA_TTABLE);
	luaL_checktype(L, 3, LUA_TTABLE);
	const int vertex_tbl = 2;
	const int index_tbl = 3;

	int VertexStride = 3*sizeof(double);
	int VertexCount = lua_objlen(L, vertex_tbl)/3;
	double *Vertices = malloc(3 * VertexCount * sizeof(double));
	if (Vertices == NULL) {
		return luaL_error(L, "failed to allocate %lu bytes for vertex buffer", VertexCount * sizeof(double));
	}
	for (int i=0; i<VertexCount; i++) {
		lua_rawgeti(L, vertex_tbl, i+1);
		Vertices[i] = lua_tonumber(L, -1);
		lua_pop(L, 1);
	}

	int IndexCount = lua_objlen(L, index_tbl)/3;
	int TriStride = 3*sizeof(unsigned int);
	unsigned int *Indices = malloc(3 * IndexCount * sizeof(unsigned int));
	if (Indices == NULL) {
		return luaL_error(L, "failed to allocate %lu bytes for index buffer", IndexCount * sizeof(unsigned int));
	}
	dGeomTriMeshDataBuildDouble(*g, Vertices, VertexStride, VertexCount, Indices, IndexCount, TriStride);
	return 0;
}


int dCreateTriMesh_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	dTriMeshDataID *Data = luaL_checkudata(L, 2, ode_trimeshdata_tname);
	dTriCallback * Callback = NULL;
	dTriArrayCallback * ArrayCallback = NULL;
	dTriRayCallback * RayCallback = NULL;
	dGeomID bind_result = dCreateTriMesh(*space, *Data, Callback, ArrayCallback, RayCallback);
	ode_push_geom(L, bind_result);
	return 1;
}


int dGeomTriMeshSetData_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dTriMeshDataID *Data = luaL_checkudata(L, 2, ode_trimeshdata_tname);
	dGeomTriMeshSetData(*g, *Data);
	return 0;
}


int dGeomTriMeshClearTCCache_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dGeomTriMeshClearTCCache(*g);
	return 0;
}


int dGeomTriMeshEnableTC_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	int geomClass = luaL_checkinteger(L, 2);
	int enable = luaL_checkinteger(L, 3);
	dGeomTriMeshEnableTC(*g, geomClass, enable);
	return 0;
}


int dGeomTriMeshIsTCEnabled_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	int geomClass = luaL_checkinteger(L, 2);
	int bind_result = dGeomTriMeshIsTCEnabled(*g, geomClass);
	lua_pushinteger(L, bind_result);
	return 1;
}


int dGeomHeightfieldDataCreate_bind(lua_State *L)
{
	dHeightfieldDataID bind_result = dGeomHeightfieldDataCreate();
	ode_push_heightfielddata(L, bind_result);
	return 1;
}


int dGeomHeightfieldDataDestroy_bind(lua_State *L)
{
	dHeightfieldDataID *d = luaL_checkudata(L, 1, ode_heightfielddata_tname);
	dGeomHeightfieldDataDestroy(*d);
	return 0;
}


int dGeomHeightfieldDataBuildDouble_bind(lua_State *L)
{
	dHeightfieldDataID *d = luaL_checkudata(L, 1, ode_heightfielddata_tname);
	luaL_checktype(L, 2, LUA_TTABLE);
	int data_tbl = 2;
	dReal width = luaL_checknumber(L, 3);
	dReal depth = luaL_checknumber(L, 4);
	int widthSamples = luaL_checkinteger(L, 5);
	int depthSamples = luaL_checkinteger(L, 6);
	size_t height_size = widthSamples * depthSamples * sizeof(double);
	double * pHeightData = malloc(height_size);
	if (pHeightData == NULL) {
		return luaL_error(L, "failed to allocate %lu bytes for pHeightData buffer", height_size);
	}

	/* read data_tbl into pHeightData */
	for (int y=0; y<depthSamples; y++) {
		for (int x=0; x<widthSamples; x++) {
			int index = x + (depthSamples * y);
			lua_rawgeti(L, data_tbl, index+1);
			pHeightData[index] = lua_tonumber(L, -1);
			lua_pop(L, 1);
		}
	}

	dReal scale = luaL_checknumber(L, 7);
	dReal offset = luaL_checknumber(L, 8);
	dReal thickness = luaL_checknumber(L, 9);
	int bWrap = luaL_checkinteger(L, 10);
	dGeomHeightfieldDataBuildDouble(
		*d, 
		pHeightData, 1, 
		width, depth, widthSamples, depthSamples, 
		scale, offset, thickness, bWrap
	);
	return 0;
}


struct hf_data_t {
	lua_State *L;
	int ref;
};
static dReal hf_callback(void *userdata, int x, int z)
{
	struct hf_data_t *d = userdata;
	lua_State *L = d->L;
	lua_rawgeti(L, LUA_REGISTRYINDEX, d->ref);
	lua_pushinteger(L, x);
	lua_pushinteger(L, z);
	lua_call(L, 2, 1);
	dReal result = lua_tonumber(L, -1);
	lua_pop(L, 1);
	return result;
}
int dGeomHeightfieldDataBuildCallback_bind(lua_State *L)
{
	dHeightfieldDataID *d = luaL_checkudata(L, 1, ode_heightfielddata_tname);
	luaL_checktype(L, 2, LUA_TFUNCTION);
	lua_pushvalue(L, 2);
	int ref = luaL_ref(L, LUA_REGISTRYINDEX);
	struct hf_data_t userData = { L, ref };
	dHeightfieldGetHeight * pCallback = hf_callback;
	dReal width = luaL_checknumber(L, 3);
	dReal depth = luaL_checknumber(L, 4);
	int widthSamples = luaL_checkinteger(L, 5);
	int depthSamples = luaL_checkinteger(L, 6);
	dReal scale = luaL_checknumber(L, 7);
	dReal offset = luaL_checknumber(L, 8);
	dReal thickness = luaL_checknumber(L, 9);
	int bWrap = luaL_checkinteger(L, 10);
	dGeomHeightfieldDataBuildCallback(*d, &userData, pCallback, width, depth, widthSamples, depthSamples, scale, offset, thickness, bWrap);
	return 0;
}


int dGeomHeightfieldDataSetBounds_bind(lua_State *L)
{
	dHeightfieldDataID *d = luaL_checkudata(L, 1, ode_heightfielddata_tname);
	dReal min_height = luaL_checknumber(L, 2);
	dReal max_height = luaL_checknumber(L, 3);
	dGeomHeightfieldDataSetBounds(*d, min_height, max_height);
	return 0;
}


int dCreateHeightfield_bind(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, ode_space_tname);
	dHeightfieldDataID *data = luaL_checkudata(L, 2, ode_heightfielddata_tname);
	int bPlaceable = luaL_checkinteger(L, 3);
	dGeomID bind_result = dCreateHeightfield(*space, *data, bPlaceable);
	ode_push_geom(L, bind_result);
	return 1;
}


int dGeomHeightfieldSetHeightfieldData_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dHeightfieldDataID *Data = luaL_checkudata(L, 1, ode_heightfielddata_tname);
	dGeomHeightfieldSetHeightfieldData(*g, *Data);
	return 0;
}


int dGeomHeightfieldGetHeightfieldData_bind(lua_State *L)
{
	dGeomID *g = luaL_checkudata(L, 1, ode_geom_tname);
	dHeightfieldDataID bind_result = dGeomHeightfieldGetHeightfieldData(*g);
	ode_push_heightfielddata(L, bind_result);
	return 1;
}
