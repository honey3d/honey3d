#include "scene_tree.h"
#include "glm_bindings.h"

int honey_node_mt_ref = LUA_NOREF;

void honey_setup_scene_tree(lua_State* L)
{
    honey_lua_create_table
	(L, 1,
	 HONEY_TABLE, "__index", 6,
	 HONEY_FUNCTION, "updateTransform", honey_node_update_transform,
	 HONEY_FUNCTION, "updateCascade", honey_node_update_cascade,
	 HONEY_FUNCTION, "drawCascade", honey_node_draw_cascade,
	 HONEY_FUNCTION, "translate", honey_node_translate,
	 HONEY_FUNCTION, "rotate", honey_node_rotate,
	 HONEY_FUNCTION, "scale", honey_node_scale);
    honey_node_mt_ref = luaL_ref(L, LUA_REGISTRYINDEX);

    lua_pushcfunction(L, honey_node_new);
    lua_setfield(L, -2, "node");
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Basic node functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int honey_node_new(lua_State* L)
{
    honey_glm_array *position, *rotation, *scale;
    honey_lua_parse_arguments
	(L, 1, 4,
	 HONEY_ANY, NULL,
	 HONEY_USERDATA, &position,
	 HONEY_USERDATA, &rotation,
	 HONEY_USERDATA, &scale);

    lua_createtable(L, 5, 0);

    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_node_mt_ref);
    lua_setmetatable(L, -2);

    lua_pushvalue(L, 1);
    if (!lua_isnil(L, -1)) {
	/* add self to parent.children */
	lua_getfield(L, -1, "children");
	int length = lua_objlen(L, -1);

	lua_pushinteger(L, length+1);
	lua_pushvalue(L, 5);
	lua_settable(L, -3);
	lua_pop(L, 1);
    }
    lua_setfield(L, -2, "parent");

    if (position->type != VEC3)
	honey_lua_throw_error
	    (L, "position vector must be of type VEC3 (%d); got %d instead",
	     VEC3, position->type);
    lua_pushvalue(L, 2);
    lua_setfield(L, -2, "position");

    if (rotation->type != VEC3)
	honey_lua_throw_error
	    (L, "rotation vector must be of type VEC3 (%d); got %d instead",
	     VEC3, rotation->type);
    lua_pushvalue(L, 3);
    lua_setfield(L, -2, "rotation");

    if (scale->type != VEC3)
	honey_lua_throw_error
	    (L, "scale vector must be of type VEC3 (%d); got %d instead",
	     VEC3, scale->type);
    lua_pushvalue(L, 4);
    lua_setfield(L, -2, "scale");

    /* create transform */
    lua_pushcfunction(L, honey_glm_new_mat4);
    honey_lua_pcall(L, 0, 1);

    /* call honey.glm.eye() */
    lua_pushcfunction(L, honey_glm_mat4_eye);
    lua_pushvalue(L, -2);
    honey_lua_pcall(L, 1, 0);

    lua_setfield(L, -2, "transform");
    
    /* call node:updateTransform() */
    lua_getfield(L, -1, "updateTransform");
    lua_pushvalue(L, -2);
    honey_lua_pcall(L, 1, 0);

    /* create children */
    lua_createtable(L, 0, 0);
    lua_setfield(L, -2, "children");

    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_node_update_transform(lua_State* L)
{
    honey_lua_parse_arguments(L, 1, 1, HONEY_TABLE, NULL);

    /* self.transform:eye() */
    lua_pushcfunction(L, honey_glm_mat4_eye);
    lua_getfield(L, 1, "transform");
    lua_pushvalue(L, -1);
    honey_lua_pcall(L, 1, 0);

    /* self.transform:translate(self.position) */
    lua_pushcfunction(L, honey_glm_translate);
    lua_pushvalue(L, 2);
    lua_getfield(L, 1, "position");
    honey_lua_pcall(L, 2, 0);

    /* self.transform:rotateZ(self.rotation:at(2)) */
    lua_pushcfunction(L, honey_glm_rotate_z);
    lua_pushvalue(L, 2);
    lua_getfield(L, 1, "position");
    honey_glm_array* position = lua_touserdata(L, -1);
    lua_pop(L, 1);
    lua_pushnumber(L, position->data[2]);
    honey_lua_pcall(L, 2, 0);

    /* self.transform:rotateY(self.rotation:at(1)) */
    lua_pushcfunction(L, honey_glm_rotate_y);
    lua_pushvalue(L, 2);
    lua_pushnumber(L, position->data[1]);
    honey_lua_pcall(L, 2, 0);

    /* self.transform:rotateX(self.rotation:at(0)) */
    lua_pushcfunction(L, honey_glm_rotate_x);
    lua_pushvalue(L, 2);
    lua_pushnumber(L, position->data[0]);
    honey_lua_pcall(L, 2, 0);

    lua_getfield(L, 1, "parent");
    if (!lua_isnil(L, -1)) {
	lua_pushcfunction(L, honey_glm_mat4_mul);
	lua_getfield(L, -2, "transform");
	lua_pushvalue(L, 2);
	lua_pushvalue(L, -1);
	honey_lua_pcall(L, 3, 0);
    }
    lua_pop(L, 1);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_node_update_cascade(lua_State* L)
{
    float dt;
    honey_lua_parse_arguments(L, 1, 2, HONEY_TABLE, NULL, HONEY_NUMBER, &dt);

    /* call self.update if it exists */
    lua_getfield(L, 1, "update");
    if (!lua_isnil(L, -1)) {
	lua_pushvalue(L, 1);
	lua_pushnumber(L, dt);
	honey_lua_pcall(L, 2, 0);
    }
    else
	lua_pop(L, 1);

    lua_pushcfunction(L, honey_node_update_transform);
    lua_pushvalue(L, 1);
    honey_lua_pcall(L, 1, 0);

    /* update cascade for each child node */
    lua_getfield(L, 1, "children");
    int n_children = lua_objlen(L, -1);
    for (int i=0; i<n_children; i++) {
	lua_rawgeti(L, -1, i+1);
	lua_pushcfunction(L, honey_node_update_cascade);
	lua_pushvalue(L, -2);
	lua_pushnumber(L, dt);
	honey_lua_pcall(L, 2, 0);
	lua_pop(L, 1);
    }
	
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_node_draw_cascade(lua_State* L)
{
    honey_lua_parse_arguments(L, 1, 1, HONEY_TABLE, NULL);

    /* call self.draw if it exists */
    lua_getfield(L, 1, "draw");
    if (!lua_isnil(L, -1)) {
	lua_pushvalue(L, 1);
	honey_lua_pcall(L, 1, 0);
    }
    else
	lua_pop(L, 1);

    /* draw cascade for each child node */
    lua_getfield(L, 1, "children");
    int n_children = lua_objlen(L, -1);
    for (int i=0; i<n_children; i++) {
	lua_rawgeti(L, -1, i+1);
	lua_pushcfunction(L, honey_node_draw_cascade);
	lua_pushvalue(L, -2);
	honey_lua_pcall(L, 1, 0);
	lua_pop(L, 1);
    }
	
    return 0;
}    

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_node_translate(lua_State* L)
{
    honey_glm_array* v;
    honey_lua_parse_arguments(L, 1, 2, HONEY_TABLE, NULL, HONEY_USERDATA, &v);

    lua_pushcfunction(L, honey_glm_vec3_add);
    lua_getfield(L, 1, "transform");
    lua_pushvalue(L, 2);
    lua_pushvalue(L, -2);
    honey_lua_pcall(L, 3, 0);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_node_rotate(lua_State* L)
{
    char* axisName;
    float angle;
    int index;

    honey_lua_parse_arguments
	(L, 1, 3,
	 HONEY_TABLE, NULL, HONEY_STRING, &axisName, HONEY_NUMBER, &angle);

    switch (axisName[0]) {
    case 'x':
	index = 0;
	break;

    case 'y':
	index = 1;
	break;

    case 'z':
	index = 2;
	break;

    default:
	honey_lua_throw_error
	    (L, "axis string must be one of 'x', 'y', or 'z'; got '%s' instead", axisName);
    }

    lua_getfield(L, 1, "rotation");
    honey_glm_array* rotation = lua_touserdata(L, -1);
    lua_pop(L, 1);

    rotation->data[index] += angle;

    return 0;
}
	
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_node_scale(lua_State* L)
{
    char* axisName;
    float s;
    int index;

    int choice = honey_lua_parse_arguments
	(L, 2,
	 2,
	 HONEY_TABLE, NULL, HONEY_NUMBER, &s,
	 3,
	 HONEY_TABLE, NULL, HONEY_STRING, &axisName, HONEY_NUMBER, &s);

    lua_getfield(L, 1, "scale");
    honey_glm_array* scale = lua_touserdata(L, -1);
    lua_pop(L, 1);

    if (choice == 0) {
	for (int i=0; i<3; i++)
	    scale->data[i] *= s;
    }
    else {
	switch (axisName[0]) {
	case 'x':
	    index = 0;
	    break;

	case 'y':
	    index = 1;
	    break;

	case 'z':
	    index = 2;
	    break;

	default:
	    honey_lua_throw_error
		(L, "axis string must be one of 'x', 'y', or 'z'; got '%s' instead", axisName);
	}

	scale->data[index] *= s;
    }

    return 0;
}
