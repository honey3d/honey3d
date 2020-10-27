#include "mesh.h"

int honey_mesh_new(lua_State* L)
{
    float* vertices;
    unsigned int* indices;
    int n_vertices, n_indices;
    honey_lua_parse_arguments(L, 5,
                              HONEY_USERDATA, &vertices,
                              HONEY_USERDATA, &indices,
                              HONEY_TABLE,
                              HONEY_INTEGER, &n_vertices,
                              HONEY_INTEGER, &n_indices);

    size_t n_attributes = lua_objlen(L, 3);
    unsigned int* attribute_sizes = malloc(n_attributes * sizeof(unsigned int));
    if (attribute_sizes == NULL) {
        lua_pushstring(L, "failed to allocate memory for vertex attributes");
        lua_error(L);
    }

    unsigned int vertex_size = 0;
    for (int i=0; i<n_attributes; i++) {
        lua_rawgeti(L, 2, i+1);
        attribute_sizes[i] = lua_tointeger(L, -1);
        vertex_size += attribute_sizes[i];
    }
    lua_pop(L, n_attributes);

    honey_mesh* mesh = lua_newuserdata(L, sizeof(honey_mesh));
    mesh->n_indices = n_indices;

    glGenVertexArrays(1, &mesh->vertex_array);
    glGenBuffers(1, &mesh->vertex_buffer);
    glGenBuffers(1, &mesh->element_buffer);

    glBindVertexArray(mesh->vertex_array);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER,
                 vertex_size * n_vertices * sizeof(float),
                 vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 n_indices * sizeof(unsigned int),
                 indices, GL_STATIC_DRAW);

    unsigned int offset = 0;
    for (int i=0; i<n_attributes; i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i,
                              attribute_sizes[i],
                              GL_FLOAT, GL_FALSE,
                              vertex_size * sizeof(float),
                              (void*) (offset * sizeof(float)));
        offset += attribute_sizes[i];
    }

    glBindVertexArray(0);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_mesh_draw(lua_State* L)
{
    honey_mesh* mesh;
    int shader;
    honey_lua_parse_arguments(L, 2,
                              HONEY_USERDATA, &mesh,
                              HONEY_INTEGER, &shader);
    
    glUseProgram(shader);
  
    glBindVertexArray(mesh->vertex_array);
    glDrawElements(GL_TRIANGLES, mesh->n_indices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_mesh_delete(lua_State* L)
{
    honey_mesh* mesh;
    honey_lua_parse_arguments(L, 1, HONEY_USERDATA, &mesh);
    glDeleteVertexArrays(1, &(mesh->vertex_array));
    glDeleteBuffers(1, &(mesh->vertex_buffer));
    glDeleteBuffers(1, &(mesh->element_buffer));
}
