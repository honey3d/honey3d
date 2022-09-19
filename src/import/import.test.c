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

	/* the numbers should be one higher because of lua's 1-indexing */
	lua_rawgeti(L, facetbl, 1);
	lily_assert_int_equal(lua_tointeger(L, -1), 1);
	lua_rawgeti(L, facetbl, 2);
	lily_assert_int_equal(lua_tointeger(L, -1), 2);
	lua_rawgeti(L, facetbl, 3);
	lily_assert_int_equal(lua_tointeger(L, -1), 3);
	lua_rawgeti(L, facetbl, 4);
	lily_assert_int_equal(lua_tointeger(L, -1), 4);
	lua_rawgeti(L, facetbl, 5);
	lily_assert_int_equal(lua_tointeger(L, -1), 5);
	lua_rawgeti(L, facetbl, 6);
	lily_assert_int_equal(lua_tointeger(L, -1), 6);

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

void create_faces(struct aiMesh *mesh);
void test_faces(lua_State *L, int meshtbl);

void create_normals(struct aiMesh *mesh);
void test_normals(lua_State *L, int meshtbl);

void create_tangents(struct aiMesh *mesh);
void test_tangents(lua_State *L, int meshtbl);

void test_nil(lua_State *L, int meshtbl, const char *field);


#define NUM_MESH_VERTICES 4
#define NUM_MESH_FACES 2


#define ALLOCATE_MEMORY() \
	struct aiVector3D vertices[NUM_MESH_VERTICES]; \
	mesh.mVertices = vertices; \
	struct aiVector3D normals[NUM_MESH_VERTICES]; \
	mesh.mNormals = normals; \
	struct aiVector3D tangents[NUM_MESH_VERTICES]; \
	struct aiVector3D bitangents[NUM_MESH_VERTICES]; \
	mesh.mTangents = tangents; \
	mesh.mBitangents = bitangents; \
	struct aiFace faces[NUM_MESH_FACES]; \
	unsigned int index_array[3*NUM_MESH_FACES]; \
	for (int i=0; i<NUM_MESH_FACES; i++) \
		faces[i].mIndices = index_array + (3*i); \
	mesh.mFaces = faces;



void test_push_mesh()
{
	lua_State *L = luaL_newstate();
	struct aiMesh mesh;
	mesh.mNumVertices = NUM_MESH_VERTICES;
	mesh.mNumFaces = 0;

	/* allocate memory */
	ALLOCATE_MEMORY();
	mesh.mNormals = NULL;
	mesh.mTangents = NULL;
	mesh.mBitangents = NULL;

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
	test_nil(L, meshtbl, "faces");

	lua_close(L);
}


void test_push_mesh_faces()
{
	lua_State *L = luaL_newstate();
	struct aiMesh mesh;
	mesh.mNumVertices = NUM_MESH_VERTICES;
	mesh.mNumFaces = NUM_MESH_FACES;

	/* allocate memory */
	ALLOCATE_MEMORY();
	mesh.mNormals = NULL;
	mesh.mTangents = NULL;
	mesh.mBitangents = NULL;

	/* setup mesh */
	create_vertices(&mesh);
	create_faces(&mesh);

	/* push */	
	int top_before = lua_gettop(L);
	push_mesh(L, mesh);
	int meshtbl = lua_gettop(L);

	/* check output */
	lily_assert_int_equal(lua_type(L, meshtbl), LUA_TTABLE);
	lily_assert_int_equal(meshtbl - top_before, 1); /* make sure we cleaned up correctly */
	test_vertices(L, meshtbl);
	test_faces(L, meshtbl);

	lua_close(L);
}


void test_push_mesh_normals()
{
	lua_State *L = luaL_newstate();
	struct aiMesh mesh;
	mesh.mNumVertices = NUM_MESH_VERTICES;
	mesh.mNumFaces = NUM_MESH_FACES;

	/* allocate memory */
	ALLOCATE_MEMORY();
	mesh.mTangents = NULL;
	mesh.mBitangents = NULL;

	/* setup mesh */
	create_vertices(&mesh);
	create_faces(&mesh);
	create_normals(&mesh);

	/* push */	
	int top_before = lua_gettop(L);
	push_mesh(L, mesh);
	int meshtbl = lua_gettop(L);

	/* check output */
	lily_assert_int_equal(lua_type(L, meshtbl), LUA_TTABLE);
	lily_assert_int_equal(meshtbl - top_before, 1); /* make sure we cleaned up correctly */
	test_vertices(L, meshtbl);
	test_faces(L, meshtbl);
	test_normals(L, meshtbl);

	lua_close(L);
}


void test_push_mesh_tangents()
{
	lua_State *L = luaL_newstate();
	struct aiMesh mesh;
	mesh.mNumVertices = NUM_MESH_VERTICES;
	mesh.mNumFaces = NUM_MESH_FACES;

	/* allocate memory */
	ALLOCATE_MEMORY();

	/* setup mesh */
	create_vertices(&mesh);
	create_faces(&mesh);
	create_normals(&mesh);
	create_tangents(&mesh);

	/* push */	
	int top_before = lua_gettop(L);
	push_mesh(L, mesh);
	int meshtbl = lua_gettop(L);

	/* check output */
	lily_assert_int_equal(lua_type(L, meshtbl), LUA_TTABLE);
	lily_assert_int_equal(meshtbl - top_before, 1); /* make sure we cleaned up correctly */
	test_vertices(L, meshtbl);
	test_faces(L, meshtbl);
	test_normals(L, meshtbl);
	test_tangents(L, meshtbl);

	lua_close(L);

}


void create_vertices(struct aiMesh *mesh)
{
	mesh->mVertices[0] = (struct aiVector3D) { 0, 0, 0 };
	mesh->mVertices[1] = (struct aiVector3D) { 0, 0, 1 };
	mesh->mVertices[2] = (struct aiVector3D) { 1, 0, 0 };
	mesh->mVertices[3] = (struct aiVector3D) { 1, 0, 1 };
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
	check_vector(L, meshtbl, "vertices", 3, 1, 0, 0);
	check_vector(L, meshtbl, "vertices", 4, 1, 0, 1);
}


static void setup_face(struct aiFace *face, int v0, int v1, int v2)
{
	face->mNumIndices = 3;
	face->mIndices[0] = v0;
	face->mIndices[1] = v1;
	face->mIndices[2] = v2;
}


void create_faces(struct aiMesh *mesh)
{
	setup_face(mesh->mFaces + 0, 0, 1, 3);
	setup_face(mesh->mFaces + 1, 0, 3, 2);
}


static int check_face(lua_State *L, int meshtbl, const char *field, int index, 
                      int v0, int v1, int v2)
{
	lua_getfield(L, meshtbl, field);
	lily_assert(lua_type(L, -1) == LUA_TTABLE, "field '%s' is not a table!", field);
	lua_rawgeti(L, -1, index);
	lily_assert(lua_type(L, -1) == LUA_TTABLE, "%s[%d] is not a table!", field, index);

	lua_rawgeti(L, -1, 1);
	lily_assert(lua_type(L, -1) == LUA_TNUMBER, "%s[%d][1] is not a number!", field, index);
	int vv0 = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_rawgeti(L, -1, 2);
	lily_assert(lua_type(L, -1) == LUA_TNUMBER, "%s[%d][2] is not a number!", field, index);
	int vv1 = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_rawgeti(L, -1, 3);
	lily_assert(lua_type(L, -1) == LUA_TNUMBER, "%s[%d][3] is not a number!", field, index);
	int vv2 = lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_pop(L, 2);
	lily_assert(
		(v0 == vv0) &&
		(v1 == vv1) &&
		(v2 == vv2),
		"%s[%d] is [%d, %d, %d], but expected [%d, %d, %d]!",
		field, index,
		vv0, vv1, vv2,
		v0, v1, v2
	);
}


void test_faces(lua_State *L, int meshtbl)
{
	check_face(L, meshtbl, "faces", 1, 1, 2, 4);
	check_face(L, meshtbl, "faces", 2, 1, 4, 3);
}


void create_normals(struct aiMesh *mesh)
{
	/* these normals are deliberately not, uh, normalized
	 * in order to distinguish them for the purposes of testing.
	 * (this could also happen in real life -- assimp won't normalize
	 * normals taken straight from the object file)
	 */
	mesh->mNormals[0] = (struct aiVector3D) { 0, 0.1, 0 };
	mesh->mNormals[1] = (struct aiVector3D) { 0, 0.2, 0 };
	mesh->mNormals[2] = (struct aiVector3D) { 0, 0.4, 0 };
	mesh->mNormals[3] = (struct aiVector3D) { 0, 1.0, 0 };
}


void test_normals(lua_State *L, int meshtbl)
{
	check_vector(L, meshtbl, "normals", 1, 0, 0.1, 0);
	check_vector(L, meshtbl, "normals", 2, 0, 0.2, 0);
	check_vector(L, meshtbl, "normals", 3, 0, 0.4, 0);
	check_vector(L, meshtbl, "normals", 4, 0, 1.0, 0);
}


void create_tangents(struct aiMesh *mesh)
{
	/* these tangents are not normalized -- see note in create_normals */
	mesh->mTangents[0] = (struct aiVector3D) { 0.1, 0, 0 };
	mesh->mTangents[1] = (struct aiVector3D) { 0.2, 0, 0 };
	mesh->mTangents[2] = (struct aiVector3D) { 0.4, 0, 0 };
	mesh->mTangents[3] = (struct aiVector3D) { 1.0, 0, 0 };

	mesh->mBitangents[0] = (struct aiVector3D) { 0, 0, 0.1 };
	mesh->mBitangents[1] = (struct aiVector3D) { 0, 0, 0.2 };
	mesh->mBitangents[2] = (struct aiVector3D) { 0, 0, 0.4 };
	mesh->mBitangents[3] = (struct aiVector3D) { 0, 0, 1.0 };
}


void test_tangents(lua_State *L, int meshtbl)
{
	check_vector(L, meshtbl, "tangents", 1, 0.1, 0, 0);
	check_vector(L, meshtbl, "tangents", 2, 0.2, 0, 0);
	check_vector(L, meshtbl, "tangents", 3, 0.4, 0, 0);
	check_vector(L, meshtbl, "tangents", 4, 1.0, 0, 0);

	check_vector(L, meshtbl, "bitangents", 1, 0, 0, 0.1);
	check_vector(L, meshtbl, "bitangents", 2, 0, 0, 0.2);
	check_vector(L, meshtbl, "bitangents", 3, 0, 0, 0.4);
	check_vector(L, meshtbl, "bitangents", 4, 0, 0, 1.0);
}



void test_nil(lua_State *L, int meshtbl, const char *field)
{
	lua_getfield(L, meshtbl, field);
	lily_assert(lua_type(L, -1) == LUA_TNIL, "field '%s' is not nil!");
	lua_pop(L, 1);
}


/* --===== end mesh tests =====-- */


void suite_import()
{
	lily_run_test(test_push_vector);
	lily_run_test(test_push_face);
	lily_run_test(test_push_aistring);

	lily_run_test(test_push_mesh);
	lily_run_test(test_push_mesh_faces);
	lily_run_test(test_push_mesh_normals);
	lily_run_test(test_push_mesh_tangents);
}
