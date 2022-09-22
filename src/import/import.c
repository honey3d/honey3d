#include <lua.h>
#include <honeysuckle.h>
#include <assimp/scene.h>
#include "import.h"


void push_vector(lua_State *L, struct aiVector3D vec)
{
	hs_create_table(L,
		hs_str_num("x", vec.x),
		hs_str_num("y", vec.y),
		hs_str_num("z", vec.z),
	);
}


void push_face(lua_State *L, struct aiFace face)
{
	lua_createtable(L, face.mNumIndices, 0);
	int tbl = lua_gettop(L);

	for (int i=0; i<face.mNumIndices; i++) {
		/* add one to the index bc lua is 1-indexed */
		lua_pushinteger(L, face.mIndices[i]+1);
		lua_rawseti(L, tbl, i+1);
	}
}


void push_aistring(lua_State *L, struct aiString str)
{
	lua_pushstring(L, str.data);
}


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
void push_mesh(lua_State *L, struct aiMesh mesh)
{
	/* --=== create mesh table ===-- */
	lua_createtable(L, 0, 1);
	int meshtbl = lua_gettop(L);

	int count = mesh.mNumVertices;
	int pop_count = 0;

	/* --=== create tables ===-- */

	/* positions */
	lua_createtable(L, count, 0);
	int vertices = lua_gettop(L);
	pop_count += 1;

	/* normals */
	int normals = 0;
	if (mesh.mNormals != NULL) {
		lua_createtable(L, count, 0);
		normals = lua_gettop(L);
		pop_count += 1;
	}

	/* tangents & bitangents */
	int tangents = 0;
	int bitangents = 0;
	if (mesh.mTangents != NULL) {
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
		if (mesh.mTextureCoords[i] != NULL) {
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
			lua_pushinteger(L, mesh.mNumUVComponents[i]);
			lua_rawseti(L, uv_components, i+1);
		}
	}

	/* --=== populate vertices ===-- */

	for (int i=0; i<count; i++) {
		/* positions */
		push_vector(L, mesh.mVertices[i]);
		lua_rawseti(L, vertices, i+1);

		/* normals */
		if (normals) {
			push_vector(L, mesh.mNormals[i]);
			lua_rawseti(L, normals, i+1);
		}

		/* tangents */
		if (tangents) {
			push_vector(L, mesh.mTangents[i]);
			lua_rawseti(L, tangents, i+1);
			push_vector(L, mesh.mBitangents[i]);
			lua_rawseti(L, bitangents, i+1);
		}

		/* uvs */
		if (uvs) {
			for (int j=0; j<AI_MAX_NUMBER_OF_TEXTURECOORDS; j++) {
				if (uv_channels[j]) {
					push_vector(L, mesh.mTextureCoords[j][i]);
					lua_rawseti(L, uv_channels[j], i+1);
				}
			}
		}
	}

	/* --=== populate faces ===-- */

	int faces = 0;
	if (mesh.mNumFaces != 0) {
		lua_createtable(L, mesh.mNumFaces, 0);
		faces = lua_gettop(L);
		pop_count += 1;
		for (int i=0; i<mesh.mNumFaces; i++) {
			push_face(L, mesh.mFaces[i]);
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
