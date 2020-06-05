#include "../include/model.h"

static honey_mesh assimp_to_honey_mesh(struct aiMesh* mesh, struct aiScene* scene) {
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

static void process_assimp_node(honey_model* model, struct aiNode* node, struct aiScene* scene) {
  for (int i=0; i<node->mNumMeshes; i++) {
    struct aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    model->meshes[model->n_meshes] = assimp_to_honey_mesh(mesh, scene);
    model->n_meshes++;
  }

  for (int i=0; i<node->mNumChildren; i++) {
    process_assimp_node(model, node->mChildren[i], scene);
  }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  
honey_result honey_model_load(honey_model* model,
                             char* path) {
  model->n_meshes = 0;
  
  struct aiScene* scene = aiImportFile(path,
                                             aiProcess_Triangulate |
                                             aiProcess_FlipUVs);
  if (scene == NULL) {
    honey_error_set_string1(path);
    return HONEY_FILE_READ_ERROR;
  }

  if (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      scene->mRootNode == NULL) {
    honey_error_set_string1(path);
    return HONEY_MODEL_LOAD_ERROR;
  }
  
  process_assimp_node(model, scene->mRootNode, scene);

  return HONEY_OK;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_model_draw(honey_model* model, honey_shader shader) {
  for (int i=0; i<model->n_meshes; i++) {
    honey_mesh_draw(model->meshes[i], shader);
  }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_model_delete(honey_model* model) {
  for (int i=0; i<model->n_meshes; i++) {
    honey_mesh_delete(model->meshes[i]);
  }
}
