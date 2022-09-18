#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <honeysuckle.h>
#include "test/honey-test.h"


#include "import.c"


void test_push_vector()
{
	lua_State *L = luaL_newstate();
	struct aiVector3D v;
	v.x = 1.5;
	v.y = 2.0;
	v.z = 3.6;

	push_vector(L, v);

	lily_assert_int_equal(lua_type(L, -1), LUA_TTABLE);

	lua_getfield(L, -1, "x");
	lily_assert_int_equal(lua_type(L, -1), LUA_TNUMBER);
	lily_assert_float_equal(lua_tonumber(L, -1), 1.5, 0.1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "y");
	lily_assert_int_equal(lua_type(L, -1), LUA_TNUMBER);
	lily_assert_float_equal(lua_tonumber(L, -1), 2.0, 0.1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "z");
	lily_assert_int_equal(lua_type(L, -1), LUA_TNUMBER);
	lily_assert_float_equal(lua_tonumber(L, -1), 3.6, 0.1);
	lua_pop(L, 1);

	lua_close(L);
}


void test_push_face()
{
	lua_State *L = luaL_newstate();
	struct aiFace face;
	int indices[] = { 0, 1, 2, 3, 4, 5 };
	face.mIndices = indices;
	face.mNumIndices = 6;

	push_face(L, face);

	lily_assert_int_equal(lua_type(L, -1), LUA_TTABLE);
	int facetbl = lua_gettop(L);
	lily_assert_int_equal(lua_objlen(L, facetbl), 6);

	lua_rawgeti(L, facetbl, 1);
	lily_assert_int_equal(lua_tointeger(L, -1), 0);
	lua_rawgeti(L, facetbl, 2);
	lily_assert_int_equal(lua_tointeger(L, -1), 1);
	lua_rawgeti(L, facetbl, 3);
	lily_assert_int_equal(lua_tointeger(L, -1), 2);
	lua_rawgeti(L, facetbl, 4);
	lily_assert_int_equal(lua_tointeger(L, -1), 3);
	lua_rawgeti(L, facetbl, 5);
	lily_assert_int_equal(lua_tointeger(L, -1), 4);
	lua_rawgeti(L, facetbl, 6);
	lily_assert_int_equal(lua_tointeger(L, -1), 5);

	lua_close(L);
}


void test_push_aistring()
{
	lua_State *L = luaL_newstate();
	struct aiString str;
	strcpy(str.data, "hello, world!");

	push_aistring(L, str);

	lily_assert_int_equal(lua_type(L, -1), LUA_TSTRING);
	lily_assert_string_equal((char*) lua_tostring(L, -1), "hello, world!");

	lua_close(L);
}


/* --===== mesh tests =====-- */


void create_vertices(struct aiMesh *mesh);
void test_vertices(lua_State *L, int meshtbl);


#define NUM_MESH_VERTICES 8


void test_push_mesh()
{
	lua_State *L = luaL_newstate();
	struct aiMesh mesh;
	mesh.mNumVertices = NUM_MESH_VERTICES;

	/* allocate memory */
	struct aiVector3D vertices[NUM_MESH_VERTICES];
	mesh.mVertices = vertices;

	/* setup mesh */
	create_vertices(&mesh);

	/* push */	
	int top_before = lua_gettop(L);
	push_mesh(L, mesh);
	int meshtbl = lua_gettop(L);

	/* check output */
	lily_assert_int_equal(lua_type(L, meshtbl), LUA_TTABLE);
	lily_assert_int_equal(meshtbl - top_before, 1); /* make sure we cleaned up correctly */
	test_vertices(L, meshtbl);

	lua_close(L);
}


void create_vertices(struct aiMesh *mesh)
{
	mesh->mVertices[0] = (struct aiVector3D) { 0, 0, 0 };
	mesh->mVertices[1] = (struct aiVector3D) { 0, 0, 1 };
	mesh->mVertices[2] = (struct aiVector3D) { 0, 1, 0 };
	mesh->mVertices[3] = (struct aiVector3D) { 0, 1, 1 };
	mesh->mVertices[4] = (struct aiVector3D) { 1, 0, 0 };
	mesh->mVertices[5] = (struct aiVector3D) { 1, 0, 1 };
	mesh->mVertices[6] = (struct aiVector3D) { 1, 1, 0 };
	mesh->mVertices[7] = (struct aiVector3D) { 1, 1, 1 };
}


static int check_vector(lua_State *L, int meshtbl, const char *field, int index, 
                        float x, float y, float z)
{
	lua_getfield(L, meshtbl, field);
	lily_assert(lua_type(L, -1) == LUA_TTABLE, "field '%s' is not a table!", field);
	lua_rawgeti(L, -1, index);
	lily_assert(lua_type(L, -1) == LUA_TTABLE, "%s[%d] is not a table!", field, index);

	lua_getfield(L, -1, "x");
	lily_assert(lua_type(L, -1) == LUA_TNUMBER, "%s[%d].x is not a number!", field, index);
	float vx = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "y");
	lily_assert(lua_type(L, -1) == LUA_TNUMBER, "%s[%d].y is not a number!", field, index);
	float vy = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_getfield(L, -1, "z");
	lily_assert(lua_type(L, -1) == LUA_TNUMBER, "%s[%d].z is not a number!", field, index);
	float vz = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pop(L, 2);
	lily_assert(
		(fabs(vx - x) < 0.1) &&
		(fabs(vy - y) < 0.1) &&
		(fabs(vz - z) < 0.1),
		"%s[%d] is [%f, %f, %f], but expected [%f, %f, %f]!",
		field, index,
		vx, vy, vz,
		x, y, z
	);
}


void test_vertices(lua_State *L, int meshtbl)
{
	check_vector(L, meshtbl, "vertices", 1, 0, 0, 0);
	check_vector(L, meshtbl, "vertices", 2, 0, 0, 1);
	check_vector(L, meshtbl, "vertices", 3, 0, 1, 0);
	check_vector(L, meshtbl, "vertices", 4, 0, 1, 1);
	check_vector(L, meshtbl, "vertices", 5, 1, 0, 0);
	check_vector(L, meshtbl, "vertices", 6, 1, 0, 1);
	check_vector(L, meshtbl, "vertices", 7, 1, 1, 0);
	check_vector(L, meshtbl, "vertices", 8, 1, 1, 1);
}


/* --===== end mesh tests =====-- */


void suite_import()
{
	lily_run_test(test_push_vector);
	lily_run_test(test_push_face);
	lily_run_test(test_push_aistring);

	lily_run_test(test_push_mesh);
}
