#include <lua.h>
#include <honeysuckle.h>
#include <ode/ode.h>


/* setup/teardown */
int init_ode(lua_State *L);
int close_ode(lua_State *L);

/* world functions */
int world_create(lua_State *L);
int world_destroy(lua_State *L);
int world_set_gravity(lua_State *L);
int world_get_gravity(lua_State *L);
int world_set_cfm(lua_State *L);
int world_quickstep(lua_State *L);

/* space functions */
int hash_space_create(lua_State *L);
int space_destroy(lua_State *L);
int space_collide(lua_State *L);

/* joint group functions */
int joint_group_create(lua_State *L);
int joint_group_destroy(lua_State *L);
int joint_group_empty(lua_State *L);

/* joint functions */
int joint_create_contact(lua_State *L);
int joint_attach(lua_State *L);

/* body functions */
int body_create(lua_State *L);
int body_set_mass(lua_State *L);
int body_set_position(lua_State *L);
int body_get_position(lua_State *L);
int body_add_force(lua_State *L);
int body_get_force(lua_State *L);
int body_set_linear_vel(lua_State *L);

/* geom functions */
int create_sphere(lua_State *L);
int create_plane(lua_State *L);
int geom_get_class(lua_State *L);
int geom_set_body(lua_State *L);
int geom_get_body(lua_State *L);
int collide(lua_State *L);

/* mass functions */
int mass_create(lua_State *L);
int mass_set_sphere(lua_State *L);


/* contact functions */
int contact_create(lua_State *L);
int contact_surface_set_mode(lua_State *L);
int contact_surface_set_mu(lua_State *L);
int contact_surface_set_bounce(lua_State *L);
int contact_surface_set_bounce_vel(lua_State *L);
int contact_surface_set_soft_cfm(lua_State *L);


#define NEW_METATABLE(name) luaL_newmetatable(L, name); lua_pop(L, 1);
static const char *world_tname = "ode.World";
static const char *space_tname = "ode.Space";
static const char *body_tname  = "ode.Body";
static const char *geom_tname  = "ode.Geom";
static const char *mass_tname  = "ode.Mass";
static const char *joint_group_tname = "ode.JointGroup";
static const char *joint_tname = "ode.Joint";
static const char *contact_tname = "ode.Contact";

void setup_ode(lua_State *L, int honey_tbl)
{
	/* setup metatables */
	NEW_METATABLE(world_tname);
	NEW_METATABLE(space_tname);
	NEW_METATABLE(body_tname);
	NEW_METATABLE(geom_tname);
	NEW_METATABLE(mass_tname);
	NEW_METATABLE(joint_group_tname);
	NEW_METATABLE(joint_tname);
	NEW_METATABLE(contact_tname);


	/* create main table */
	hs_create_table(L,
		hs_str_cfunc("InitODE", init_ode),
		hs_str_cfunc("CloseODE", close_ode),

		hs_str_cfunc("WorldCreate", world_create),
		hs_str_cfunc("WorldDestroy", world_destroy),
		hs_str_cfunc("WorldSetGravity", world_set_gravity),
		hs_str_cfunc("WorldGetGravity", world_get_gravity),
		hs_str_cfunc("WorldSetCFM", world_set_cfm),
		hs_str_cfunc("WorldQuickStep", world_quickstep),

		hs_str_cfunc("HashSpaceCreate", hash_space_create),
		hs_str_cfunc("SpaceDestroy", space_destroy),
		hs_str_cfunc("SpaceCollide", space_collide),

		hs_str_cfunc("JointGroupCreate", joint_group_create),
		hs_str_cfunc("JointGroupDestroy", joint_group_destroy),
		hs_str_cfunc("JointGroupEmpty", joint_group_empty),

		hs_str_cfunc("JointCreateContact", joint_create_contact),
		hs_str_cfunc("JointAttach", joint_attach),

		hs_str_cfunc("BodyCreate", body_create),
		hs_str_cfunc("BodySetMass", body_set_mass),
		hs_str_cfunc("BodySetPosition", body_set_position),
		hs_str_cfunc("BodyGetPosition", body_get_position),
		hs_str_cfunc("BodyAddForce", body_add_force),
		hs_str_cfunc("BodyGetForce", body_get_force),
		hs_str_cfunc("BodySetLinearVel", body_set_linear_vel),

		hs_str_cfunc("CreateSphere", create_sphere),
		hs_str_cfunc("CreatePlane", create_plane),
		hs_str_cfunc("GeomGetClass", geom_get_class),
		hs_str_cfunc("GeomSetBody", geom_set_body),
		hs_str_cfunc("GeomGetBody", geom_get_body),
		hs_str_cfunc("Collide", collide),

		hs_str_cfunc("MassCreate", mass_create),
		hs_str_cfunc("MassSetSphere", mass_set_sphere),

		hs_str_cfunc("ContactCreate", contact_create),
		hs_str_cfunc("ContactSurfaceSetMode", contact_surface_set_mode),
		hs_str_cfunc("ContactSurfaceSetMu", contact_surface_set_mu),
		hs_str_cfunc("ContactSurfaceSetBounce", contact_surface_set_bounce),
		hs_str_cfunc("ContactSurfaceSetBounceVel", contact_surface_set_bounce_vel),
		hs_str_cfunc("ContactSurfaceSetSoftCFM", contact_surface_set_soft_cfm),

		/* contact surface mode enum */
		hs_str_int("ContactBounce", dContactBounce),
		hs_str_int("ContactSoftCFM", dContactSoftCFM),

		/* helpful */
		hs_str_num("Infinity", dInfinity),
	);

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


/* --===== world functions =====-- */

int world_create(lua_State *L)
{
	dWorldID *world = lua_newuserdata(L, sizeof(dWorldID *));
	*world = dWorldCreate();
	luaL_getmetatable(L, world_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int world_destroy(lua_State *L)
{
	dWorldID *world = luaL_checkudata(L, 1, world_tname);
	dWorldDestroy(*world);
	return 0;
}


int world_set_gravity(lua_State *L)
{
	dWorldID *world = luaL_checkudata(L, 1, world_tname);
	double gx = luaL_checknumber(L, 2);
	double gy = luaL_checknumber(L, 3);
	double gz = luaL_checknumber(L, 4);
	dWorldSetGravity(*world, gx, gy, gz);
	return 0;
}


int world_get_gravity(lua_State *L)
{
	dWorldID *world = luaL_checkudata(L, 1, world_tname);
	dVector3 result;
	dWorldGetGravity(*world, result);
	lua_pushnumber(L, result[0]);
	lua_pushnumber(L, result[1]);
	lua_pushnumber(L, result[2]);
	return 3;
}


int world_set_cfm(lua_State *L)
{
	dWorldID *world = luaL_checkudata(L, 1, world_tname);
	double cfm = luaL_checknumber(L, 2);
	dWorldSetCFM(*world, cfm);
	return 0;
}


int world_quickstep(lua_State *L)
{
	dWorldID *world = luaL_checkudata(L, 1, world_tname);
	double stepsize = luaL_checknumber(L, 2);
	dWorldQuickStep(*world, stepsize);
	return 0;
}


/* --===== space functions =====-- */

int hash_space_create(lua_State *L)
{
	dSpaceID *space = lua_newuserdata(L, sizeof(dSpaceID *));
	*space = dHashSpaceCreate(NULL);
	luaL_getmetatable(L, space_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int space_destroy(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, space_tname);
	dSpaceDestroy(*space);
	return 0;
}


static void near_callback(void *data, dGeomID o1, dGeomID o2)
{
	lua_State *L = data;
	lua_pushvalue(L, 2); /* user callback should be at stack index 2 */

	dGeomID *ptr1 = lua_newuserdata(L, sizeof(dGeomID *));
	*ptr1 = o1;
	luaL_getmetatable(L, geom_tname);
	lua_setmetatable(L, -2);

	dGeomID *ptr2 = lua_newuserdata(L, sizeof(dGeomID *));
	*ptr2 = o2;
	luaL_getmetatable(L, geom_tname);
	lua_setmetatable(L, -2);

	lua_call(L, 2, 0);
}

int space_collide(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, space_tname);
	luaL_argcheck(L, lua_type(L, 2) == LUA_TFUNCTION, 2, "");
	dSpaceCollide(*space, L, near_callback);
	return 0;
}


/* --===== joint group functions =====-- */

int joint_group_create(lua_State *L)
{
	dJointGroupID *group = lua_newuserdata(L, sizeof(dJointGroupID *));
	*group = dJointGroupCreate(0);
	luaL_getmetatable(L, joint_group_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int joint_group_destroy(lua_State *L)
{
	dJointGroupID *group = luaL_checkudata(L, 1, joint_group_tname);
	dJointGroupDestroy(*group);
	return 0;
}


int joint_group_empty(lua_State *L)
{
	dJointGroupID *group = luaL_checkudata(L, 1, joint_group_tname);
	dJointGroupEmpty(*group);
	return 0;
}


/* --===== joint functions =====-- */

int joint_create_contact(lua_State *L)
{
	dWorldID *world = luaL_checkudata(L, 1, world_tname);
	dJointGroupID group = NULL;
	if (lua_type(L, 2) != LUA_TNIL) {
		dJointGroupID *ptr = luaL_checkudata(L, 2, joint_group_tname);
		group = *ptr;
	}
	dContact *contact = luaL_checkudata(L, 3, contact_tname);

	dJointID *joint = lua_newuserdata(L, sizeof(dJointID *));
	*joint = dJointCreateContact(*world, group, contact);
	luaL_getmetatable(L, joint_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int joint_attach(lua_State *L)
{
	dJointID *joint = luaL_checkudata(L, 1, joint_tname);
	dBodyID *body1 = luaL_checkudata(L, 2, body_tname);
	dBodyID *body2 = luaL_checkudata(L, 3, body_tname);

	dJointAttach(*joint, *body1, *body2);
	return 0;
}




/* --===== body functions =====-- */

int body_create(lua_State *L)
{
	dWorldID *world = luaL_checkudata(L, 1, world_tname);

	dBodyID *body = lua_newuserdata(L, sizeof(dBodyID *));
	*body = dBodyCreate(*world);
	luaL_getmetatable(L, body_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int body_set_mass(lua_State *L)
{
	dBodyID *body = luaL_checkudata(L, 1, body_tname);
	dMass *mass = luaL_checkudata(L, 2, mass_tname);

	dBodySetMass(*body, mass);
	return 0;
}


int body_set_position(lua_State *L)
{
	dBodyID *body = luaL_checkudata(L, 1, body_tname);
	double x = luaL_checknumber(L, 2);
	double y = luaL_checknumber(L, 3);
	double z = luaL_checknumber(L, 4);

	dBodySetPosition(*body, x, y, z);
	return 0;
}


int body_get_position(lua_State *L)
{
	dBodyID *body = luaL_checkudata(L, 1, body_tname);
	const dReal *pos = dBodyGetPosition(*body);

	lua_pushnumber(L, pos[0]);
	lua_pushnumber(L, pos[1]);
	lua_pushnumber(L, pos[2]);
	return 3;
}


int body_add_force(lua_State *L)
{
	dBodyID *body = luaL_checkudata(L, 1, body_tname);
	double fx = luaL_checknumber(L, 2);
	double fy = luaL_checknumber(L, 3);
	double fz = luaL_checknumber(L, 4);

	dBodyAddForce(*body, fx, fy, fz);
	return 0;
}


int body_get_force(lua_State *L)
{
	dBodyID *body = luaL_checkudata(L, 1, body_tname);
	
	const dReal *f = dBodyGetForce(*body);
	lua_pushnumber(L, f[0]);
	lua_pushnumber(L, f[1]);
	lua_pushnumber(L, f[2]);
	return 3;
}


int body_set_linear_vel(lua_State *L)
{
	dBodyID *body = luaL_checkudata(L, 1, body_tname);
	double vx = luaL_checknumber(L, 2);
	double vy = luaL_checknumber(L, 3);
	double vz = luaL_checknumber(L, 4);

	dBodySetLinearVel(*body, vx, vy, vz);
	return 0;
}


/* --===== geom functions =====-- */

int create_sphere(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, space_tname);
	double radius = luaL_checknumber(L, 2);

	dGeomID *geom = lua_newuserdata(L, sizeof(dGeomID *));
	*geom = dCreateSphere(*space, radius);
	luaL_getmetatable(L, geom_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int create_plane(lua_State *L)
{
	dSpaceID *space = luaL_checkudata(L, 1, space_tname);
	double a = luaL_checknumber(L, 2);
	double b = luaL_checknumber(L, 3);
	double c = luaL_checknumber(L, 4);
	double d = luaL_checknumber(L, 5);

	dGeomID *geom = lua_newuserdata(L, sizeof(dGeomID *));
	*geom = dCreatePlane(*space, a, b, c, d);
	luaL_getmetatable(L, geom_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int geom_get_class(lua_State *L)
{
	dGeomID *geom = luaL_checkudata(L, 1, geom_tname);
	int class = dGeomGetClass(*geom);
	lua_pushinteger(L, class);
	return 1;
}


int geom_set_body(lua_State *L)
{
	dGeomID *geom = luaL_checkudata(L, 1, geom_tname);
	dBodyID *body = luaL_checkudata(L, 2, body_tname);
	dGeomSetBody(*geom, *body);
	return 0;
}


int geom_get_body(lua_State *L)
{
	dGeomID *geom = luaL_checkudata(L, 1, geom_tname);

	dBodyID *body = lua_newuserdata(L, sizeof(dBodyID *));
	*body = dGeomGetBody(*geom);
	luaL_getmetatable(L, body_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int collide(lua_State *L)
{
	dGeomID *o1 = luaL_checkudata(L, 1, geom_tname);
	dGeomID *o2 = luaL_checkudata(L, 2, geom_tname);
	dContact *contact = luaL_checkudata(L, 3, contact_tname);

	int count = dCollide(*o1, *o2, 1, &(contact->geom), sizeof(dContactGeom));
	lua_pushinteger(L, count);
	return 1;
}


/* --===== mass functions =====-- */

int mass_create(lua_State *L)
{
	lua_newuserdata(L, sizeof(dMass));
	luaL_getmetatable(L, mass_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int mass_set_sphere(lua_State *L)
{
	dMass *mass = luaL_checkudata(L, 1, mass_tname);
	double density = luaL_checknumber(L, 2);
	double radius = luaL_checknumber(L, 3);

	dMassSetSphere(mass, density, radius);
	return 0;
}


/* --===== contact functions =====-- */

int contact_create(lua_State *L)
{
	lua_newuserdata(L, sizeof(dContact));
	luaL_getmetatable(L, contact_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int contact_surface_set_mode(lua_State *L)
{
	dContact *contact = luaL_checkudata(L, 1, contact_tname);
	int mode = luaL_checkinteger(L, 2);
	contact->surface.mode = mode;
	return 0;
}


int contact_surface_set_mu(lua_State *L)
{
	dContact *contact = luaL_checkudata(L, 1, contact_tname);
	double mu = luaL_checknumber(L, 2);
	contact->surface.mu = mu;
	return 0;
}


int contact_surface_set_bounce(lua_State *L)
{
	dContact *contact = luaL_checkudata(L, 1, contact_tname);
	double bounce = luaL_checknumber(L, 2);
	contact->surface.bounce = bounce;
	return 0;
}


int contact_surface_set_bounce_vel(lua_State *L)
{
	dContact *contact = luaL_checkudata(L, 1, contact_tname);
	double bounce_vel = luaL_checknumber(L, 2);
	contact->surface.bounce_vel = bounce_vel;
	return 0;
}


int contact_surface_set_soft_cfm(lua_State *L)
{
	dContact *contact = luaL_checkudata(L, 1, contact_tname);
	double soft_cfm = luaL_checknumber(L, 2);
	contact->surface.soft_cfm = soft_cfm;
	return 0;
}
