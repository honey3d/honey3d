#include "mesh.h"

int honey_mesh_mt_ref = LUA_NOREF;

struct vertex {
    float position[3];
    float normal[3];
    float tangent[3];
    float bitangent[3];
    float uv[2];
    float color[4];

    unsigned int bones[4];
    float weights[4];
};

struct mesh {
    unsigned int n_vertices;
    struct vertex* vertices;
    unsigned int n_indices;
    unsigned int* indices;
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static int honey_mesh_lua_draw(lua_State* L)
{
    honey_mesh* mesh;
    int* shader;
    honey_lua_parse_arguments(L, 1, 2,
                              HONEY_USERDATA, &mesh,
                              HONEY_USERDATA, &shader);
    honey_mesh_draw(*mesh, *shader);
    return 0;
}

static int honey_mesh_lua_delete(lua_State* L)
{
    honey_mesh* mesh;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &mesh);
    honey_mesh_delete(*mesh);
    return 0;
}

static float get_number(lua_State* L, const char* field, int index)
{
    lua_rawgeti(L, -1, index);
    if (!lua_isnumber(L, -1))
	    honey_lua_throw_error(L, "all elements of '%s' must be numbers; got %s at %d instead",
				  field, lua_typename(L, lua_type(L, -1)), index);

    float number = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return number;
}

static bool load_field(lua_State* L, const char* field, int length, int fields)
{
    lua_getfield(L, 1, field);
    if (lua_isnil(L, -1)) {
	return false;
    }
    if (!lua_istable(L, -1))
	honey_lua_throw_error(L, "expected '%s' to be a table; got %s instead",
			      field,
			      lua_typename(L, lua_type(L, -1)));

    int table_len = lua_objlen(L, -1);
    if (table_len != fields*length)
	honey_lua_throw_error(L, "expected field '%s' to contain %d elements; got %d instead",
			      field, table_len, fields*length);

    return true;
}

static int honey_mesh_lua_build(lua_State* L)
{
    honey_lua_parse_arguments(L, 1, 1, HONEY_TABLE, NULL);

    lua_getfield(L, 1, "position");
    if (lua_isnil(L, -1))
	honey_lua_throw_error(L, "a 'position' table is required but was not found");
    int n_vertices = lua_objlen(L, -1)/3;
    lua_pop(L, 1);
    
    lua_getfield(L, 1, "faces");
    if (lua_isnil(L, -1))
	honey_lua_throw_error(L, "a 'faces' table is required but was not found");
    int n_indices = lua_objlen(L, -1);
    lua_pop(L, 1);

    
    struct mesh m;
    m.n_vertices = n_vertices;
    m.n_indices = n_indices;
    m.vertices = malloc(sizeof(struct vertex) * m.n_vertices);
    m.indices = malloc(sizeof(unsigned int) * m.n_indices);
    
    load_field(L, "position", m.n_vertices, 3);
    for (int i=0; i<m.n_vertices; i++) {
	m.vertices[i].position[0] = get_number(L, "position", 3*i+1);
	m.vertices[i].position[1] = get_number(L, "position", 3*i+2);
	m.vertices[i].position[2] = get_number(L, "position", 3*i+3);
    }
    lua_pop(L, 1);

    load_field(L, "faces", m.n_indices, 1);
    for (int i=0; i<m.n_indices; i++) {
	m.indices[i] = get_number(L, "faces", i+1);
    }
    lua_pop(L, 1);
    
    if (load_field(L, "normal", m.n_vertices, 3)) {
	for (int i=0; i<m.n_vertices; i++) {
	    m.vertices[i].normal[0] = get_number(L, "normal", 3*i+1);
	    m.vertices[i].normal[1] = get_number(L, "normal", 3*i+2);
	    m.vertices[i].normal[2] = get_number(L, "normal", 3*i+3);
	}
    }
    lua_pop(L, 1);

    if (load_field(L, "tangent", m.n_vertices, 3)) {
	for (int i=0; i<m.n_vertices; i++) {
	    m.vertices[i].tangent[0] = get_number(L, "tangent", 3*i+1);
	    m.vertices[i].tangent[1] = get_number(L, "tangent", 3*i+2);
	    m.vertices[i].tangent[2] = get_number(L, "tangent", 3*i+3);
	}
    }
    lua_pop(L, 1);

    if (load_field(L, "bitangent", m.n_vertices, 3)) {
	for (int i=0; i<m.n_vertices; i++) {
	    m.vertices[i].bitangent[0] = get_number(L, "bitangent", 3*i+1);
	    m.vertices[i].bitangent[1] = get_number(L, "bitangent", 3*i+2);
	    m.vertices[i].bitangent[2] = get_number(L, "bitangent", 3*i+3);
	}
    }
    lua_pop(L, 1);

    if (load_field(L, "uv", m.n_vertices, 2)) {
	for (int i=0; i<m.n_vertices; i++) {
	    m.vertices[i].uv[0] = get_number(L, "uv", 2*i+1);
	    m.vertices[i].uv[1] = get_number(L, "uv", 2*i+2);
	}
    }
    lua_pop(L, 1);

    if (load_field(L, "color", m.n_vertices, 4)) {
	for (int i=0; i<4 * m.n_vertices; i++) {
	    m.vertices[i].color[0] = get_number(L, "color", 4*i+1);
	    m.vertices[i].color[1] = get_number(L, "color", 4*i+2);
	    m.vertices[i].color[2] = get_number(L, "color", 4*i+3);
	    m.vertices[i].color[3] = get_number(L, "color", 4*i+4);
	}
    }
    lua_pop(L, 1);

    if (load_field(L, "bones", m.n_vertices, 4)) {
	for (int i=0; i<4 * m.n_vertices; i++) {
	    m.vertices[i].bones[0] = get_number(L, "bones", 4*i+1);
	    m.vertices[i].bones[1] = get_number(L, "bones", 4*i+2);
	    m.vertices[i].bones[2] = get_number(L, "bones", 4*i+3);
	    m.vertices[i].bones[3] = get_number(L, "bones", 4*i+4);
	}
    }
    lua_pop(L, 1);

    if (load_field(L, "weights", m.n_vertices, 4)) {
	for (int i=0; i<4 * m.n_vertices; i++) {
	    m.vertices[i].weights[0] = get_number(L, "weights", 4*i+1);
	    m.vertices[i].weights[1] = get_number(L, "weights", 4*i+2);
	    m.vertices[i].weights[2] = get_number(L, "weights", 4*i+3);
	    m.vertices[i].weights[3] = get_number(L, "weights", 4*i+4);
	}
    }
    lua_pop(L, 1);
    
    honey_mesh* mesh = lua_newuserdata(L, sizeof(honey_mesh));
    honey_result result = honey_mesh_new(mesh, m);
    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_mesh_mt_ref);
    lua_setmetatable(L, -2);

    free(m.vertices);
    free(m.indices);

    return 1;
}

void honey_setup_mesh(lua_State* L)
{
    honey_lua_create_table
	(L, 2,
	 HONEY_TABLE, "__index", 1,
	 HONEY_FUNCTION, "draw", honey_mesh_lua_draw,

	 HONEY_FUNCTION, "__gc", honey_mesh_lua_delete);
    honey_mesh_mt_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    lua_pushcfunction(L, honey_mesh_load);
    lua_setfield(L, -2, "loadMesh");

    lua_pushcfunction(L, honey_mesh_lua_build);
    lua_setfield(L, -2, "buildMesh");
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static honey_mesh assimp_to_honey_mesh(struct aiMesh* ai_mesh,
                                       struct aiScene* scene)
{
    struct mesh m;
    bool has_normals = ai_mesh->mNormals != NULL;
    bool has_tangents = ai_mesh->mTangents != NULL;
    bool has_uvs = ai_mesh->mTextureCoords != NULL;
    bool has_colors = ai_mesh->mColors != NULL;

    m.n_vertices = ai_mesh->mNumVertices;
    
    m.vertices = malloc(m.n_vertices * sizeof(struct vertex));
    for (int i=0; i<m.n_vertices; i++) {
	m.vertices[i].position[0] = ai_mesh->mVertices[i].x;
	m.vertices[i].position[1] = ai_mesh->mVertices[i].y;
	m.vertices[i].position[2] = ai_mesh->mVertices[i].z;

	if (has_normals) {
	    m.vertices[i].normal[0] = ai_mesh->mNormals[i].x;
	    m.vertices[i].normal[1] = ai_mesh->mNormals[i].y;
	    m.vertices[i].normal[2] = ai_mesh->mNormals[i].z;
	}
	else {
	    m.vertices[i].normal[0] = 0;
	    m.vertices[i].normal[1] = 0;
	    m.vertices[i].normal[2] = 0;
	}

	if (has_tangents) {
	    m.vertices[i].tangent[0] = ai_mesh->mTangents[i].x;
	    m.vertices[i].tangent[1] = ai_mesh->mTangents[i].y;
	    m.vertices[i].tangent[2] = ai_mesh->mTangents[i].z;

	    m.vertices[i].bitangent[0] = ai_mesh->mBitangents[i].x;
	    m.vertices[i].bitangent[1] = ai_mesh->mBitangents[i].y;
	    m.vertices[i].bitangent[2] = ai_mesh->mBitangents[i].z;
	}
	else {
	    m.vertices[i].tangent[0] = 0;
	    m.vertices[i].tangent[1] = 0;
	    m.vertices[i].tangent[2] = 0;

	    m.vertices[i].bitangent[0] = 0;
	    m.vertices[i].bitangent[1] = 0;
	    m.vertices[i].bitangent[2] = 0;
	}
	
	if (has_uvs) {
	    m.vertices[i].uv[0] = ai_mesh->mTextureCoords[0][i].x;
	    m.vertices[i].uv[1] = ai_mesh->mTextureCoords[0][i].y;
	}
	else {
	    m.vertices[i].uv[0] = 0;
	    m.vertices[i].uv[1] = 0;
	}
    }

    m.n_indices = ai_mesh->mNumFaces*3;
    m.indices = malloc(sizeof(unsigned int) * m.n_indices);
    for (int i=0; i<ai_mesh->mNumFaces; i++) {
	int j = 3*i;
	struct aiFace face = ai_mesh->mFaces[i];
	m.indices[j+0] = face.mIndices[0];
	m.indices[j+1] = face.mIndices[1];
	m.indices[j+2] = face.mIndices[2];
    }

    honey_mesh result;
    honey_mesh_new(&result, m);

    free(m.vertices);
    free(m.indices);

    return result;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void process_nodes_recursively(lua_State* L,
				      struct aiScene* scene,
				      struct aiNode* node,
				      int* n_meshes)
{
    for (int i=0; i<node->mNumMeshes; i++) {
	honey_mesh* mesh = lua_newuserdata(L, sizeof(honey_mesh));
	lua_rawgeti(L, LUA_REGISTRYINDEX, honey_mesh_mt_ref);
	lua_setmetatable(L, -2);
	
	struct aiMesh* assimp_mesh = scene->mMeshes[node->mMeshes[i]];
	*mesh = assimp_to_honey_mesh(assimp_mesh, scene);
	lua_rawseti(L, -2, *n_meshes);
	(*n_meshes)++;
    }

    for (int i=0; i<node->mNumChildren; i++) {
	process_nodes_recursively(L, scene, node->mChildren[i], n_meshes);
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_mesh_load(lua_State* L)
{
    char* filename;
    honey_lua_parse_arguments(L, 1, 1, HONEY_STRING, &filename);

    int n_meshes = 1;

    struct aiScene* scene = aiImportFile(filename,
					 aiProcess_Triangulate |
					 aiProcess_FlipUVs);
    if (scene == NULL) {
	char* error;
	honey_format_string(&error, "could not open file '%s'", filename);
	lua_pushstring(L, error);
	free(error);
	lua_error(L);
    }

    if (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
	scene->mRootNode == NULL) {
	char* error;
	honey_format_string(&error, "could not read mesh(es) in '%s'", filename);
	lua_pushstring(L, error);
	free(error);
	lua_error(L);
    }

    lua_createtable(L, 0, 0);

    process_nodes_recursively(L, scene, scene->mRootNode, &n_meshes);

    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

honey_result honey_mesh_new(honey_mesh* mesh,
			    struct mesh m)
{
    if (m.vertices == NULL || m.n_vertices == 0) {
	return HONEY_MESH_BAD_VERTEX_DATA;
    }
    if (m.indices == NULL || m.n_indices == 0) {
	return HONEY_MESH_BAD_INDEX_DATA;
    }

    mesh->n_vertices = m.n_vertices;
    mesh->n_indices  = m.n_indices;

    glGenVertexArrays(1, &(mesh->vertex_array));
    glGenBuffers(1, &(mesh->vertex_buffer));
    glGenBuffers(1, &(mesh->element_buffer));

    glBindVertexArray(mesh->vertex_array);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER,
		 m.n_vertices * sizeof(struct vertex),
		 m.vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		 m.n_indices * sizeof(unsigned int),
		 m.indices, GL_STATIC_DRAW);

    /* set up vertex attributes */
    size_t offset = 0;
    /* position */
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			  sizeof(struct vertex), offset);
    offset += 3*sizeof(float);

    /* normal */
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
			  sizeof(struct vertex), offset);
    offset += 3*sizeof(float);

    /* tangent */
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
			  sizeof(struct vertex), offset);
    offset += 3*sizeof(float);

    /* bitangent */
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
			  sizeof(struct vertex), offset);
    offset += 3*sizeof(float);

    /* UV */
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE,
			  sizeof(struct vertex), offset);
    offset += 2*sizeof(float);

    /* color */
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE,
			  sizeof(struct vertex), offset);
    offset += 4*sizeof(float);

    /* bone indices */
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_UNSIGNED_INT, GL_FALSE,
			  sizeof(struct vertex), offset);
    offset += 4*sizeof(unsigned int);

    /* bone weights */
    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE,
			  sizeof(struct vertex), offset);

    /* done */
    glBindVertexArray(0);

    return HONEY_OK;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_mesh_draw(honey_mesh mesh, int shader) {
    glUseProgram(shader);
  
    glBindVertexArray(mesh.vertex_array);
    glDrawElements(GL_TRIANGLES, mesh.n_indices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_mesh_delete(honey_mesh mesh) {
    glDeleteVertexArrays(1, &(mesh.vertex_array));
    glDeleteBuffers(1, &(mesh.vertex_buffer));
    glDeleteBuffers(1, &(mesh.element_buffer));
}
