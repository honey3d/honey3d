#include "mesh.h"

static int honey_mesh_lua_draw(lua_State* L)
{
    honey_mesh* mesh;
    int shader;
    honey_lua_parse_arguments(L, 2,
                              HONEY_USERDATA, &mesh,
                              HONEY_INTEGER, &shader);
    honey_mesh_draw(*mesh, shader);
    return 0;
}

static int honey_mesh_lua_delete(lua_State* L)
{
    honey_mesh* mesh;
    honey_lua_parse_arguments(L, 1, HONEY_USERDATA, &mesh);
    honey_mesh_delete(*mesh);
    return 0;
}

void honey_setup_mesh(lua_State* L)
{
    honey_lua_element mesh_elements[] = {
        { "draw", HONEY_FUNCTION, { .function = honey_mesh_lua_draw } },
        { "delete", HONEY_FUNCTION, { .function = honey_mesh_lua_delete } },
    };

    honey_lua_create_table(L, mesh_elements, 2);
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
    honey_shader_use(shader);
  
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
