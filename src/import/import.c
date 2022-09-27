#include <lua.h>
#include <honeysuckle.h>
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include "import.h"


#ifndef LILY_TEST_H

static void push_scene(lua_State *L, struct aiScene *scene);

int import_file(lua_State *L)
{
	char *filename;
	hs_parse_args(L, hs_str(filename));

	const struct aiScene *scene = aiImportFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (scene == NULL)
		hs_throw_error(L, "failed to load file '%s'", filename);
	
	push_scene(L, (struct aiScene*) scene);
	return 1;
}


void setup_import(lua_State *L, int honey_tbl)
{
	hs_create_table(L,
		hs_str_cfunc("importFile", import_file),
	);

	lua_setfield(L, honey_tbl, "import");
}

#endif


static void push_vector(lua_State *L, struct aiVector3D vec)
{
	hs_create_table(L,
		hs_str_num("x", vec.x),
		hs_str_num("y", vec.y),
		hs_str_num("z", vec.z),
	);
}


static void push_face(lua_State *L, struct aiFace face)
{
	lua_createtable(L, face.mNumIndices, 0);
	int tbl = lua_gettop(L);

	for (int i=0; i<face.mNumIndices; i++) {
		/* add one to the index bc lua is 1-indexed */
		lua_pushinteger(L, face.mIndices[i]+1);
		lua_rawseti(L, tbl, i+1);
	}
}


static void push_aistring(lua_State *L, struct aiString str)
{
	lua_pushstring(L, str.data);
}


#ifndef TEST_IMPORT_SCENE

/* mesh components:
 * DONE:
 * mBitangents
 * mFaces
 * mNormals
 * mNumFaces
 * mNumVertices
 * mTangents
 * mVertices
 * mNumUVComponents
 * mTextureCoords
 *
 * TODO:
 * mAnimMeshes
 * mBones
 * mColors
 * mMaterialIndex
 * mMethod
 * mName
 * mNumAnimMeshes
 * mNumBones
 * mPrimitiveTypes
 * mTextureCoordsNames
 */
static void push_mesh(lua_State *L, struct aiMesh *mesh)
{
	/* --=== create mesh table ===-- */
	lua_createtable(L, 0, 1);
	int meshtbl = lua_gettop(L);

	int count = mesh->mNumVertices;
	int pop_count = 0;

	/* --=== create tables ===-- */

	/* positions */
	lua_createtable(L, count, 0);
	int vertices = lua_gettop(L);
	pop_count += 1;

	/* normals */
	int normals = 0;
	if (mesh->mNormals != NULL) {
		lua_createtable(L, count, 0);
		normals = lua_gettop(L);
		pop_count += 1;
	}

	/* tangents & bitangents */
	int tangents = 0;
	int bitangents = 0;
	if (mesh->mTangents != NULL) {
		lua_createtable(L, count, 0);
		tangents = lua_gettop(L);
		lua_createtable(L, count, 0);
		bitangents = lua_gettop(L);
		pop_count += 2;
	}

	/* uvs */
	int uvs = 0;
	int uv_components = 0;
	int uv_channels[AI_MAX_NUMBER_OF_TEXTURECOORDS];
	for (int i=0; i<AI_MAX_NUMBER_OF_TEXTURECOORDS; i++) {
		if (mesh->mTextureCoords[i] != NULL) {
			if (!uvs) {
				/* ensure uv table is created */
				lua_createtable(L, 1, 0);
				uvs = lua_gettop(L);
				lua_createtable(L, 1, 0);
				uv_components = lua_gettop(L);
				pop_count += 2;
			}
			lua_createtable(L, count, 0);
			uv_channels[i] = lua_gettop(L);
			pop_count += 1;

			/* store table in uvs */
			lua_pushvalue(L, uv_channels[i]);
			lua_rawseti(L, uvs, i+1);
			/* store dimensionality */
			lua_pushinteger(L, mesh->mNumUVComponents[i]);
			lua_rawseti(L, uv_components, i+1);
		}
		else
			uv_channels[i] = 0;
	}

	/* --=== populate vertices ===-- */

	for (int i=0; i<count; i++) {
		/* positions */
		push_vector(L, mesh->mVertices[i]);
		lua_rawseti(L, vertices, i+1);

		/* normals */
		if (normals) {
			push_vector(L, mesh->mNormals[i]);
			lua_rawseti(L, normals, i+1);
		}

		/* tangents */
		if (tangents) {
			push_vector(L, mesh->mTangents[i]);
			lua_rawseti(L, tangents, i+1);
			push_vector(L, mesh->mBitangents[i]);
			lua_rawseti(L, bitangents, i+1);
		}

		/* uvs */
		if (uvs) {
			for (int j=0; j<AI_MAX_NUMBER_OF_TEXTURECOORDS; j++) {
				if (uv_channels[j]) {
					push_vector(L, mesh->mTextureCoords[j][i]);
					lua_rawseti(L, uv_channels[j], i+1);
				}
			}
		}
	}

	/* --=== populate faces ===-- */

	int faces = 0;
	if (mesh->mNumFaces != 0) {
		lua_createtable(L, mesh->mNumFaces, 0);
		faces = lua_gettop(L);
		pop_count += 1;
		for (int i=0; i<mesh->mNumFaces; i++) {
			push_face(L, mesh->mFaces[i]);
			lua_rawseti(L, faces, i+1);
		}
	}

	/* --=== assign values ===-- */

	lua_pushvalue(L, vertices);
	lua_setfield(L, meshtbl, "vertices");

	if (normals) {
		lua_pushvalue(L, normals);
		lua_setfield(L, meshtbl, "normals");
	}

	if (tangents) {
		lua_pushvalue(L, tangents);
		lua_setfield(L, meshtbl, "tangents");
		lua_pushvalue(L, bitangents);
		lua_setfield(L, meshtbl, "bitangents");
	}

	if (faces) {
		lua_pushvalue(L, faces);
		lua_setfield(L, meshtbl, "faces");
	}

	if (uvs) {
		lua_pushvalue(L, uvs);
		lua_setfield(L, meshtbl, "uvs");
		lua_pushvalue(L, uv_components);
		lua_setfield(L, meshtbl, "numUvComponents");
	}

	/* --=== clean up ===-- */
	lua_pop(L, pop_count);
}


static void push_node(lua_State *L, struct aiNode *node)
{
	lua_createtable(L, 0, 0);
	int nodetbl = lua_gettop(L);

	int pop_count = 0;
	
	if (node->mMeshes != NULL) {
		lua_createtable(L, node->mNumMeshes, 0);
		int meshes = lua_gettop(L);
		for (int i=0; i<node->mNumMeshes; i++) {
			lua_pushinteger(L, node->mMeshes[i]+1);
			lua_rawseti(L, meshes, i+1);
		}
		lua_setfield(L, nodetbl, "meshes");
	}

	if (node->mChildren != NULL) {
		lua_createtable(L, node->mNumChildren, 0);
		int children = lua_gettop(L);
		for (int i=0; i<node->mNumChildren; i++) {
			push_node(L, node->mChildren[i]);
			lua_rawseti(L, children, i+1);
		}
		lua_setfield(L, nodetbl, "children");
	}
}

#endif


static void push_scene(lua_State *L, struct aiScene *scene)
{
	/* meshes */
	lua_createtable(L, scene->mNumMeshes, 0);
	int meshtbl = lua_gettop(L);
	for (int i=0; i<scene->mNumMeshes; i++) {
		push_mesh(L, scene->mMeshes[i]);
		lua_rawseti(L, meshtbl, i+1);
	}

	/* nodes */
	push_node(L, scene->mRootNode);
	int nodetbl = lua_gettop(L);

	/* scene */
	hs_create_table(L,
		hs_str_tbl("rootNode", nodetbl),
		hs_str_tbl("meshes", meshtbl),
	);
}



