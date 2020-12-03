#include "mesh.h"

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

void honey_setup_mesh(lua_State* L)
{
    honey_lua_create_table
	(L, 3,
	 HONEY_FUNCTION, "load",  honey_mesh_load,
	 HONEY_FUNCTION, "draw",  honey_mesh_lua_draw,
	 HONEY_FUNCTION, "delete",  honey_mesh_lua_delete);
    lua_setfield(L, -2, "mesh");
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static honey_mesh assimp_to_honey_mesh(struct aiMesh* mesh,
                                       struct aiScene* scene)
{
  unsigned int vertex_step = 6;
  bool mesh_has_uvs = false;
  unsigned int n_vertices = mesh->mNumVertices;
  
  if (mesh->mTextureCoords[0]) {
    mesh_has_uvs = true;
    vertex_step = 8;
  }

  float* vertices = malloc(sizeof(float) * vertex_step * n_vertices);
  for (int i=0; i<n_vertices; i++) {
    int j = i*vertex_step;
    /* positions */
    vertices[j+0] = mesh->mVertices[i].x;
    vertices[j+1] = mesh->mVertices[i].y;
    vertices[j+2] = mesh->mVertices[i].z;

    /* normals */
    vertices[j+3] = mesh->mNormals[i].x;
    vertices[j+4] = mesh->mNormals[i].y;
    vertices[j+5] = mesh->mNormals[i].z;

    /* uvs? */
    if (mesh_has_uvs) {
      vertices[j+6] = mesh->mTextureCoords[0][i].x;
      vertices[j+7] = mesh->mTextureCoords[0][i].y;
    }
  }

  unsigned int n_indices = mesh->mNumFaces*3;
  unsigned int* indices = malloc(sizeof(unsigned int) * n_indices);
  for (int i=0; i<mesh->mNumFaces; i++) {
    int j = 3*i;
    struct aiFace face = mesh->mFaces[i];
    indices[j+0] = face.mIndices[0];
    indices[j+1] = face.mIndices[1];
    indices[j+2] = face.mIndices[2];
  }

  honey_mesh result;

  if (mesh_has_uvs) {
    unsigned int n_attributes = 3;
    unsigned int attribute_sizes[] = { 3, 3, 2 };
    honey_mesh_new(&result,
                   vertices, n_vertices,
                   n_attributes, attribute_sizes,
                   indices, n_indices);
  }
  else {
    unsigned int n_attributes = 2;
    unsigned int attribute_sizes[] = { 3, 3 };
    honey_mesh_new(&result,
                   vertices, n_vertices,
                   n_attributes, attribute_sizes,
                   indices, n_indices);
  }

  free(vertices);
  free(indices);

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
                            float* vertices,
                            unsigned int n_vertices,
                            unsigned int n_attributes,
                            unsigned int* attribute_sizes,
                            unsigned int* indices,
                            unsigned int n_indices) {
    if (vertices == NULL || n_vertices == 0) {
        return HONEY_MESH_BAD_VERTEX_DATA;
    }
    if (indices == NULL || n_indices == 0) {
        return HONEY_MESH_BAD_INDEX_DATA;
    }

    unsigned int vertex_size = 0;
    for (int i=0; i<n_attributes; i++) {
        vertex_size += attribute_sizes[i];
    }

    (*mesh).n_vertices = n_vertices;
    (*mesh).n_indices  = n_indices;

    glGenVertexArrays(1, &((*mesh).vertex_array));
    glGenBuffers(1, &((*mesh).vertex_buffer));
    glGenBuffers(1, &((*mesh).element_buffer));

    glBindVertexArray((*mesh).vertex_array);

    glBindBuffer(GL_ARRAY_BUFFER, (*mesh).vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER,
                 vertex_size * n_vertices * sizeof(float),
                 vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*mesh).element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 n_indices * sizeof(unsigned int),
                 indices, GL_STATIC_DRAW);

    /* set up vertex attributes */
    unsigned int offset = 0;
    for (int i=0; i<n_attributes; i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i,
                              attribute_sizes[i],
                              GL_FLOAT,
                              GL_FALSE,
                              vertex_size*sizeof(float),
                              (void*) (offset*sizeof(float)));
        offset += attribute_sizes[i];
    }
  
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
