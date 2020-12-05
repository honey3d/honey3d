#include "glm_bindings.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Mat4 Functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int honey_glm_mat4_copy(lua_State* L)
{
    honey_glm_array* self, *dest;
    honey_lua_parse_arguments
	(L, 1, 2,
	 HONEY_USERDATA, &self,
	 HONEY_USERDATA, &dest);
    
    if (dest->type != MAT4)
	honey_lua_throw_error
	    (L, "destination must be MAT4 (%d); got %d instead",
	     MAT4, dest->type);

    glm_mat4_copy(self->data, dest->data);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_mat4_eye(lua_State* L)
{
    honey_glm_array* self;
    honey_lua_parse_arguments
	(L, 1, 1, HONEY_USERDATA, &self);

    glm_mat4_identity(self->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_mat4_zero(lua_State* L)
{
    honey_glm_array* self;
    honey_lua_parse_arguments
	(L, 1, 1, HONEY_USERDATA, &self);

    glm_mat4_zero(self->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_mat4_mul(lua_State* L)
{
    honey_glm_array* self, *mult, *dest;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 2, HONEY_USERDATA, &self, HONEY_USERDATA, &mult,
	 3, HONEY_USERDATA, &self, HONEY_USERDATA, &mult, HONEY_USERDATA, &dest);

    if (mult->type != MAT4)
	honey_lua_throw_error
	    (L, "second matrix must be of type MAT4 (%d); got %d instead",
	     MAT4, mult->type);

    if (choice == 1) {
	if (dest->type != MAT4)
	    honey_lua_throw_error
		(L, "destination matrix must be of type MAT4 (%d); got %d instead",
		 MAT4, dest->type);
    }
    else {
	lua_pushcfunction(L, honey_glm_new_mat4);
	honey_lua_pcall(L, 0, 1);
	dest = lua_touserdata(L, -1);
    }

    glm_mat4_mul(self->data, mult->data, dest->data);

    if (choice == 0)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_mat4_transpose(lua_State* L)
{
    honey_glm_array* self, *dest;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 1, HONEY_USERDATA, &self, 
	 2, HONEY_USERDATA, &self, HONEY_USERDATA, &dest);

    if (choice == 1) {
	if (dest->type != MAT4)
	    honey_lua_throw_error
		(L, "destination matrix must be of type MAT4 (%d); got %d instead",
		 MAT4, dest->type);
    }

    if (choice == 0)
	glm_mat4_transpose(self->data);
    else
	glm_mat4_transpose_to(self->data, dest->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_mat4_mulv(lua_State* L)
{
    honey_glm_array* self, *v, *dest;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 2, HONEY_USERDATA, &self, HONEY_USERDATA, &v,
	 4, HONEY_USERDATA, &self, HONEY_USERDATA, &v, HONEY_USERDATA, &dest);

    if (v->type != VEC4)
	honey_lua_throw_error
	    (L, "vector must be of type VEC4 (%d); got %d instead",
	     VEC4, v->type);

    if (choice == 0) {
	lua_pushcfunction(L, honey_glm_new_vec4);
	honey_lua_pcall(L, 0, 1);
	dest = lua_touserdata(L, -1);
    }
    else {
	if (dest->type == MAT4)
	    honey_lua_throw_error
		(L, "destination matrix must be of type MAT4 (%d); got %d instead",
		 MAT4, dest->type);
    }

    glm_mat4_mulv(self->data, v->data, dest->data);

    if (choice == 0)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_mat4_scale(lua_State* L)
{
    honey_glm_array* self;
    float s;
    int choice = honey_lua_parse_arguments
	(L, 1,
	 2, HONEY_USERDATA, &self, HONEY_NUMBER, &s);

    glm_mat4_scale(self->data, s);
    
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_mat4_det(lua_State* L)
{
    honey_glm_array* self;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &self);

    float det = glm_mat4_det(self->data);
    lua_pushnumber(L, det);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_mat4_inv(lua_State* L)
{
    honey_glm_array* self, *dest;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 1, HONEY_USERDATA, &self,
	 2, HONEY_USERDATA, &self, HONEY_USERDATA, &dest);

    if (choice == 0) {
	lua_pushcfunction(L, honey_glm_new_mat4);
	honey_lua_pcall(L, 0, 1);
	dest = lua_touserdata(L, -1);
    }
    else {
	if (dest->type == MAT4)
	    honey_lua_throw_error
		(L, "destination matrix must be of type MAT4 (%d); got %d instead",
		 MAT4, dest->type);
    }

    glm_mat4_inv(self->data, dest->data);

    if (choice == 0)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_mat4_basis(lua_State* L)
{
    honey_glm_array* self;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &self);


    lua_createtable(L, 0, 3);
    honey_glm_array *x, *y, *z;

    lua_pushcfunction(L, honey_glm_new_vec3);
    honey_lua_pcall(L, 0, 1);
    x = lua_touserdata(L, -1);
    lua_setfield(L, -2, "x");

    lua_pushcfunction(L, honey_glm_new_vec3);
    honey_lua_pcall(L, 0, 1);
    y = lua_touserdata(L, -1);
    lua_setfield(L, -2, "y");

    lua_pushcfunction(L, honey_glm_new_vec3);
    honey_lua_pcall(L, 0, 1);
    z = lua_touserdata(L, -1);
    lua_setfield(L, -2, "z");
    
    x->data[0] = self->data[0];
    x->data[1] = self->data[1];
    x->data[2] = self->data[2];

    y->data[0] = self->data[4];
    y->data[1] = self->data[5];
    y->data[2] = self->data[6];

    z->data[0] = self->data[8];
    z->data[1] = self->data[9];
    z->data[2] = self->data[10];

    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Affine Transforms
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int honey_glm_translate(lua_State* L)
{
    honey_glm_array *self, *v, *dest;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 2, HONEY_USERDATA, &self, HONEY_USERDATA, &v,
	 3, HONEY_USERDATA, &self, HONEY_USERDATA, &v, HONEY_USERDATA, &dest);

    if (v->type != VEC3)
	honey_lua_throw_error
	    (L, "translation vector must be of type VEC3 (%d); got %d instead",
	     VEC3, v->type);

    if (choice == 0) {
	glm_translate(self->data, v->data);
    }
    else {
	if (dest->type != MAT4)
	    honey_lua_throw_error
		(L, "destination matrix must be of type MAT4 (%d); got %d instead",
		 MAT4, dest->type);
	glm_translate_to(self->data, v->data, dest->data);
    }

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_translate_x(lua_State* L)
{
    honey_glm_array* self;
    float s;
    honey_lua_parse_arguments(L, 1, 2, HONEY_USERDATA, &self, HONEY_NUMBER, &s);

    glm_translate_x(self->data, s);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_translate_y(lua_State* L)
{
    honey_glm_array* self;
    float s;
    honey_lua_parse_arguments(L, 1, 2, HONEY_USERDATA, &self, HONEY_NUMBER, &s);

    glm_translate_y(self->data, s);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_translate_z(lua_State* L)
{
    honey_glm_array* self;
    float s;
    honey_lua_parse_arguments(L, 1, 2, HONEY_USERDATA, &self, HONEY_NUMBER, &s);

    glm_translate_z(self->data, s);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_scalev(lua_State* L)
{
    honey_glm_array* self, *v, *dest;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 2, HONEY_USERDATA, &self, HONEY_USERDATA, &v,
	 3, HONEY_USERDATA, &self, HONEY_USERDATA, &v, HONEY_USERDATA, &dest);

    if (v->type != VEC3)
	honey_lua_throw_error
	    (L, "scale vector must be of type VEC3 (%d); got %d instead",
	     VEC3, v->type);

    if (choice == 0)
	glm_scale(self->data, v->data);
    else {
	if (dest->type != MAT4)
	    honey_lua_throw_error
		(L, "destination matrix must be of type MAT4 (%d); got %d instead",
		 MAT4, dest->type);

	glm_scale_to(self->data, v->data, dest->data);
    }

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_rotate_x(lua_State* L)
{
    honey_glm_array* self, *dest;
    float angle;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 2, HONEY_USERDATA, &self, HONEY_NUMBER, &angle,
	 3, HONEY_USERDATA, &self, HONEY_NUMBER, &angle, HONEY_USERDATA, &dest);

    if (choice == 0)
	dest = self;
    else {
	if (dest->type != MAT4)
	    honey_lua_throw_error
		(L, "destination matrix must be of type MAT4 (%d); got %d instead",
		 MAT4, dest->type);
    }

    glm_rotate_x(self->data, angle, dest->data);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_rotate_y(lua_State* L)
{
    honey_glm_array* self, *dest;
    float angle;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 2, HONEY_USERDATA, &self, HONEY_NUMBER, &angle,
	 3, HONEY_USERDATA, &self, HONEY_NUMBER, &angle, HONEY_USERDATA, &dest);

    if (choice == 0)
	dest = self;
    else {
	if (dest->type != MAT4)
	    honey_lua_throw_error
		(L, "destination matrix must be of type MAT4 (%d); got %d instead",
		 MAT4, dest->type);
    }

    glm_rotate_y(self->data, angle, dest->data);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_rotate_z(lua_State* L)
{
    honey_glm_array* self, *dest;
    float angle;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 2, HONEY_USERDATA, &self, HONEY_NUMBER, &angle,
	 3, HONEY_USERDATA, &self, HONEY_NUMBER, &angle, HONEY_USERDATA, &dest);

    if (choice == 0)
	dest = self;
    else {
	if (dest->type != MAT4)
	    honey_lua_throw_error
		(L, "destination matrix must be of type MAT4 (%d); got %d instead",
		 MAT4, dest->type);
    }

    glm_rotate_z(self->data, angle, dest->data);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_rotate(lua_State* L)
{
    honey_glm_array *self, *pivot, *axis;
    float angle;
    int choice = honey_lua_parse_arguments
	(L, 1,
	 4,
	 HONEY_USERDATA, &self, HONEY_USERDATA, &pivot,
	 HONEY_NUMBER, &angle,  HONEY_USERDATA, &axis);

    if (pivot->type != VEC3)
	honey_lua_throw_error
	    (L, "pivot vector must be of type VEC3 (%d); got %d instead",
	     VEC3, pivot->type);

    if (axis->type != VEC3)
	honey_lua_throw_error
	    (L, "axis vector must be of type VEC3 (%d); got %d instead",
	     VEC3, axis->type);

    glm_rotate_at(self->data, pivot->data, angle, axis->data);

    return 0;
}
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Camera functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

int honey_glm_perspective(lua_State* L)
{
    honey_glm_array *self;
    float fov, aspect, near, far;
    honey_lua_parse_arguments
	(L, 1, 5,
	 HONEY_USERDATA, &self,
	 HONEY_NUMBER, &fov,  HONEY_NUMBER, &aspect,
	 HONEY_NUMBER, &near, HONEY_NUMBER, &far);

    glm_perspective(fov, aspect, near, far, self->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_perspective_resize(lua_State* L)
{
    honey_glm_array *self;
    float new_aspect;
    honey_lua_parse_arguments
	(L, 1, 2, HONEY_USERDATA, &self, HONEY_NUMBER, new_aspect);

    glm_perspective_resize(new_aspect, self->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_lookat(lua_State* L)
{
    honey_glm_array *self, *eye, *center, *up;
    honey_lua_parse_arguments
	(L, 1, 4,
	 HONEY_USERDATA, &self,
	 HONEY_USERDATA, &eye,
	 HONEY_USERDATA, &center,
	 HONEY_USERDATA, &up);

    if (eye->type != VEC3)
	honey_lua_throw_error
	    (L, "eye vector must be of type VEC3 (%d); got %d instead",
	     VEC3, eye->type);

    if (center->type != VEC3)
	honey_lua_throw_error
	    (L, "center vector must be of type VEC3 (%d); got %d instead",
	     VEC3, center->type);

    if (up->type != VEC3)
	honey_lua_throw_error
	    (L, "up vector must be of type VEC3 (%d); got %d instead",
	     VEC3, up->type);

    glm_lookat(eye->data, center->data, up->data, self->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_look(lua_State* L)
{
    honey_glm_array *self, *eye, *dir, *up;
    honey_lua_parse_arguments
	(L, 1, 4,
	 HONEY_USERDATA, &self,
	 HONEY_USERDATA, &eye,
	 HONEY_USERDATA, &dir,
	 HONEY_USERDATA, &up);

    if (eye->type != VEC3)
	honey_lua_throw_error
	    (L, "eye vector must be of type VEC3 (%d); got %d instead",
	     VEC3, eye->type);

    if (dir->type != VEC3)
	honey_lua_throw_error
	    (L, "direction vector must be of type VEC3 (%d); got %d instead",
	     VEC3, dir->type);

    if (up->type != VEC3)
	honey_lua_throw_error
	    (L, "up vector must be of type VEC3 (%d); got %d instead",
	     VEC3, up->type);

    glm_look(eye->data, dir->data, up->data, self->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

