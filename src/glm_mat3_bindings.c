#include "glm_bindings.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Mat3 Functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int honey_glm_mat3_copy(lua_State* L)
{
    honey_glm_array* self, *dest;
    honey_lua_parse_arguments
	(L, 1, 2,
	 HONEY_USERDATA, &self,
	 HONEY_USERDATA, &dest);
    
    if (dest->type != MAT3)
	honey_lua_throw_error
	    (L, "destination must be MAT3 (%d); got %d instead",
	     MAT3, dest->type);

    glm_mat3_copy(self->data, dest->data);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_mat3_eye(lua_State* L)
{
    honey_glm_array* self;
    honey_lua_parse_arguments
	(L, 1, 1, HONEY_USERDATA, &self);

    glm_mat3_identity(self->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_mat3_zero(lua_State* L)
{
    honey_glm_array* self;
    honey_lua_parse_arguments
	(L, 1, 1, HONEY_USERDATA, &self);

    glm_mat3_zero(self->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_mat3_mul(lua_State* L)
{
    honey_glm_array* self, *mult, *dest;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 2, HONEY_USERDATA, &self, HONEY_USERDATA, &mult,
	 3, HONEY_USERDATA, &self, HONEY_USERDATA, &mult, HONEY_USERDATA, &dest);

    if (mult->type != MAT3)
	honey_lua_throw_error
	    (L, "second matrix must be of type MAT3 (%d); got %d instead",
	     MAT3, mult->type);

    if (choice == 1) {
	if (dest->type != MAT3)
	    honey_lua_throw_error
		(L, "destination matrix must be of type MAT3 (%d); got %d instead",
		 MAT3, dest->type);
    }
    else {
	lua_pushcfunction(L, honey_glm_new_mat3);
	honey_lua_pcall(L, 0, 1);
	dest = lua_touserdata(L, -1);
    }

    glm_mat3_mul(self->data, mult->data, dest->data);

    if (choice == 0)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_mat3_transpose(lua_State* L)
{
    honey_glm_array* self, *dest;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 1, HONEY_USERDATA, &self, 
	 2, HONEY_USERDATA, &self, HONEY_USERDATA, &dest);

    if (choice == 1) {
	if (dest->type != MAT3)
	    honey_lua_throw_error
		(L, "destination matrix must be of type MAT3 (%d); got %d instead",
		 MAT3, dest->type);
    }

    if (choice == 0)
	glm_mat3_transpose(self->data);
    else
	glm_mat3_transpose_to(self->data, dest->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_mat3_mulv(lua_State* L)
{
    honey_glm_array* self, *v, *dest;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 2, HONEY_USERDATA, &self, HONEY_USERDATA, &v,
	 3, HONEY_USERDATA, &self, HONEY_USERDATA, &v, HONEY_USERDATA, &dest);

    if (v->type != VEC3)
	honey_lua_throw_error
	    (L, "vector must be of type VEC3 (%d); got %d instead",
	     VEC3, v->type);

    if (choice == 0) {
	lua_pushcfunction(L, honey_glm_new_vec3);
	honey_lua_pcall(L, 0, 1);
	dest = lua_touserdata(L, -1);
    }
    else {
	if (dest->type == MAT3)
	    honey_lua_throw_error
		(L, "destination matrix must be of type MAT3 (%d); got %d instead",
		 MAT3, dest->type);
    }

    glm_mat3_mulv(self->data, v->data, dest->data);

    if (choice == 0)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_mat3_scale(lua_State* L)
{
    honey_glm_array* self;
    float s;
    int choice = honey_lua_parse_arguments
	(L, 1,
	 2, HONEY_USERDATA, &self, HONEY_NUMBER, &s);

    glm_mat3_scale(self->data, s);
    
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_mat3_det(lua_State* L)
{
    honey_glm_array* self;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &self);

    float det = glm_mat3_det(self->data);
    lua_pushnumber(L, det);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_mat3_inv(lua_State* L)
{
    honey_glm_array* self, *dest;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 1, HONEY_USERDATA, &self,
	 2, HONEY_USERDATA, &self, HONEY_USERDATA, &dest);

    if (choice == 0) {
	lua_pushcfunction(L, honey_glm_new_mat3);
	honey_lua_pcall(L, 0, 1);
	dest = lua_touserdata(L, -1);
    }
    else {
	if (dest->type == MAT3)
	    honey_lua_throw_error
		(L, "destination matrix must be of type MAT3 (%d); got %d instead",
		 MAT3, dest->type);
    }

    glm_mat3_inv(self->data, dest->data);

    if (choice == 0)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
