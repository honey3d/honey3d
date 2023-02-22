#include <lua.h>
#include <lauxlib.h>
#include "util/util.h"
#include "import.h"

#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include <tinyobj/tinyobj_loader_c.h>


void read_file(void *ctx, const char *filename, int is_mtl, const char *obj_filename, char **buf, size_t *len)
{
	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	*len = ftell(f);
	fseek(f, 0, SEEK_SET);

	*buf = malloc(*len);
	fread(*buf, *len, 1, f);
	fclose(f);
}


static void push_float_array(lua_State *L, float *arr, size_t len)
{
	lua_createtable(L, len, 0);
	int tbl = lua_gettop(L);
	for (int i=0; i<len; i++) {
		lua_pushnumber(L, arr[i]);
		lua_rawseti(L, tbl, i+1);
	}
}


static void push_int_array(lua_State *L, int *arr, size_t len)
{
	lua_createtable(L, len, 0);
	int tbl = lua_gettop(L);
	for (int i=0; i<len; i++) {
		lua_pushinteger(L, arr[i]);
		lua_rawseti(L, tbl, i+1);
	}
}


static void push_material(lua_State *L, tinyobj_material_t mtl)
{
	lua_createtable(L, 0, 18);
	int tbl = lua_gettop(L);

	lua_pushstring(L, mtl.name);
	lua_setfield(L, tbl, "name");

	push_float_array(L, mtl.ambient, 3);
	lua_setfield(L, tbl, "ambient");
	push_float_array(L, mtl.diffuse, 3);
	lua_setfield(L, tbl, "diffuse");
	push_float_array(L, mtl.specular, 3);
	lua_setfield(L, tbl, "specular");
	push_float_array(L, mtl.transmittance, 3);
	lua_setfield(L, tbl, "transmittance");
	push_float_array(L, mtl.emission, 3);
	lua_setfield(L, tbl, "emission");
	lua_pushnumber(L, mtl.shininess);
	lua_setfield(L, tbl, "shininess");
	lua_pushnumber(L, mtl.ior);
	lua_setfield(L, tbl, "ior");
	lua_pushnumber(L, mtl.dissolve);
	lua_setfield(L, tbl, "dissolve");

	lua_pushinteger(L, mtl.illum);
	lua_setfield(L, tbl, "illum");

	lua_pushinteger(L, mtl.pad0);
	lua_setfield(L, tbl, "pad0");

	lua_pushstring(L, mtl.ambient_texname);
	lua_setfield(L, tbl, "ambient_texname");
	lua_pushstring(L, mtl.diffuse_texname);
	lua_setfield(L, tbl, "diffuse_texname");
	lua_pushstring(L, mtl.specular_texname);
	lua_setfield(L, tbl, "specular_texname");
	lua_pushstring(L, mtl.specular_highlight_texname);
	lua_setfield(L, tbl, "specular_highlight_texname");
	lua_pushstring(L, mtl.bump_texname);
	lua_setfield(L, tbl, "bump_texname");
	lua_pushstring(L, mtl.displacement_texname);
	lua_setfield(L, tbl, "displacement_texname");
	lua_pushstring(L, mtl.alpha_texname);
	lua_setfield(L, tbl, "alpha_texname");
}


int tinyobj_parse_obj_bind(lua_State *L)
{
	tinyobj_attrib_t attrib;
	tinyobj_shape_t *shapes;
	size_t num_shapes;
	tinyobj_material_t *materials;
	size_t num_materials;

	const char *file_name = luaL_checkstring(L, 1);
	unsigned int flags = luaL_checkinteger(L, 2);

	int result = tinyobj_parse_obj(
		&attrib, &shapes, &num_shapes, &materials, &num_materials, 
		file_name, read_file, L, flags
	);

	if (result != TINYOBJ_SUCCESS) {
		luaL_error(L, "failed to parse OBJ file \"%s\"", file_name);
	}

	/* push attrib */
	lua_createtable(L, 0, 7);
	int attrib_tbl = lua_gettop(L);

	/* push attrib.pad0 */
	lua_pushinteger(L, attrib.pad0);
	lua_setfield(L, attrib_tbl, "pad0");

	/* attrib.vertices */
	push_float_array(L, attrib.vertices, 3*attrib.num_vertices);
	lua_setfield(L, attrib_tbl, "vertices");

	/* attrib.normals */
	push_float_array(L, attrib.normals, 3*attrib.num_normals);
	lua_setfield(L, attrib_tbl, "normals");

	/* attrib.texcoords */
	push_float_array(L, attrib.texcoords, 3*attrib.num_texcoords);
	lua_setfield(L, attrib_tbl, "texcoords");

	/* attrib.faces */
	lua_createtable(L, attrib.num_faces, 0);
	int face_array_tbl = lua_gettop(L);
	for (int i=0; i<attrib.num_faces; i++) {
		lua_createtable(L, 0, 3);
		int face_tbl = lua_gettop(L);
		/* push struct elements */
		lua_pushinteger(L, attrib.faces[i].v_idx);
		lua_setfield(L, face_tbl, "v_idx");
		lua_pushinteger(L, attrib.faces[i].vt_idx);
		lua_setfield(L, face_tbl, "vt_idx");
		lua_pushinteger(L, attrib.faces[i].vn_idx);
		lua_setfield(L, face_tbl, "vn_idx");
		/* append table into array */
		lua_rawseti(L, face_array_tbl, i+1);
	}
	lua_setfield(L, attrib_tbl, "faces");

	/* attrib.face_num_verts */
	push_int_array(L, attrib.face_num_verts, attrib.num_face_num_verts);
	lua_setfield(L, attrib_tbl, "face_num_verts");

	/* attrib.material_ids 
	 * (we use the same len as face_num_verts because materials are per face) 
	 */
	push_int_array(L, attrib.material_ids, attrib.num_face_num_verts);
	lua_setfield(L, attrib_tbl, "material_ids");

	/* shapes */
	lua_createtable(L, num_shapes, 0);
	int shape_array_tbl = lua_gettop(L);
	for (int i=0; i<num_shapes; i++) {
		lua_createtable(L, 0, 3);
		int shape_tbl = lua_gettop(L);
		/* struct elements */
		lua_pushstring(L, shapes[i].name);
		lua_setfield(L, shape_tbl, "name");
		lua_pushinteger(L, shapes[i].face_offset);
		lua_setfield(L, shape_tbl, "face_offset");
		lua_pushinteger(L, shapes[i].length);
		lua_setfield(L, shape_tbl, "length");
		/* append to array */
		lua_rawseti(L, shape_array_tbl, i+1);
	}
	
	/* materials */
	lua_createtable(L, num_materials, 0);
	int materials_array_tbl = lua_gettop(L);
	for (int i=0; i<num_materials; i++) {
		push_material(L, materials[i]);
		lua_rawseti(L, materials_array_tbl, i+1);
	}
	
	return 3;
}



void setup_import(lua_State *L, int honey_tbl)
{
	struct honey_tbl_t tinyobj[] = {
		H_FUNC("parse_obj", tinyobj_parse_obj_bind),
		H_INT("FLAG_TRIANGULATE", TINYOBJ_FLAG_TRIANGULATE),
		H_END,
	};
	create_table(L, tinyobj);
	lua_setfield(L, honey_tbl, "tinyobj");
}
