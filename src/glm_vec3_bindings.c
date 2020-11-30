#include "glm_bindings.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Vec3 Functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */


int honey_glm_vec3_copy(lua_State* L)
{
    honey_glm_array *self, *dest;
    honey_lua_parse_arguments
	(L, 1, 2, HONEY_USERDATA, &self, HONEY_USERDATA, &dest);

    if (dest->type != VEC3)
	honey_lua_throw_error(L, "destination must be VEC3 (%d); got %d instead",
			      dest->type);

    glm_vec3_copy(self->data, dest->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_zero(lua_State* L)
{
    honey_glm_array *self;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &self);

    glm_vec3_zero(self->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_eye(lua_State* L)
{
    honey_glm_array *self;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &self);

    glm_vec3_one(self->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_dot(lua_State* L)
{
    honey_glm_array *a, *b;
    honey_lua_parse_arguments
	(L, 1, 2,
	 HONEY_USERDATA, &a,
	 HONEY_USERDATA, &b);

    if (b->type != VEC3)
	honey_lua_throw_error(L, "destination must be VEC3 (%d); got %d instead",
			      VEC3, b->type);

    float result = glm_vec3_dot(a->data, b->data);

    lua_pushnumber(L, result);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static bool get_vec3_arrays(lua_State* L,
			    honey_glm_array** a,
			    honey_glm_array** b,
			    honey_glm_array** dest)
{
    int choice = honey_lua_parse_arguments
	(L, 2,
	 2, HONEY_USERDATA, a, HONEY_USERDATA, b,
	 3, HONEY_USERDATA, a, HONEY_USERDATA, b, HONEY_USERDATA, dest);

    if ((*b)->type != VEC3)
	honey_lua_throw_error
	    (L, "second argument must be VEC3 (%d); got %d instead",
	     VEC3, (*b)->type);

    if (choice == 1) {
	if ((*dest)->type != VEC3)
	    honey_lua_throw_error
		(L, "third argument must be VEC3 (%d); got %d instead",
		 VEC3, (*dest)->type);
    }
    else {
	honey_glm_new_vec3(L);
	*dest = lua_touserdata(L, -1);
    }

    return choice == 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static bool get_vec3_scalars(lua_State* L,
			     honey_glm_array** a,
			     float* s,
			     honey_glm_array** dest)
{
    int choice = honey_lua_parse_arguments
	(L, 2,
	 2, HONEY_USERDATA, a, HONEY_NUMBER, s,
	 3, HONEY_USERDATA, a, HONEY_NUMBER, s, HONEY_USERDATA, dest);

    if (choice == 1) {
	if ((*dest)->type != VEC3)
	    honey_lua_throw_error
		(L, "third argument must be VEC3 (%d); got %d instead",
		 VEC3, (*dest)->type);
    }
    else {
	honey_glm_new_vec3(L);
	*dest = lua_touserdata(L, -1);
    }

    return choice == 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_cross(lua_State* L)
{
    honey_glm_array *a, *b, *dest;
    bool new_dest = get_vec3_arrays(L, &a, &b, &dest);
    
    glm_vec3_cross(a->data, b->data, dest->data);

    if (new_dest)
	return 1;
    return 0;
}
	
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_crossn(lua_State* L)
{
    honey_glm_array *a, *b, *dest;
    bool new_dest = get_vec3_arrays(L, &a, &b, &dest);
    
    glm_vec3_crossn(a->data, b->data, dest->data);

    if (new_dest)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_norm2(lua_State* L)
{
    honey_glm_array *self;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &self);
    float result = glm_vec3_norm2(self->data);
    lua_pushnumber(L, result);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_norm(lua_State* L)
{
    honey_glm_array *self;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &self);
    float result = glm_vec3_norm(self->data);
    lua_pushnumber(L, result);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_add(lua_State* L)
{
    honey_glm_array *a, *b, *dest;
    bool new_dest = get_vec3_arrays(L, &a, &b, &dest);
    
    glm_vec3_add(a->data, b->data, dest->data);

    if (new_dest)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_adds(lua_State* L)
{
    honey_glm_array *self, *dest;
    float s;
    bool new_dest = get_vec3_scalars(L, &self, &s, &dest);

    glm_vec3_adds(self->data, s, dest->data);

    if (new_dest)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_sub(lua_State* L)
{
    honey_glm_array *a, *b, *dest;
    bool new_dest = get_vec3_arrays(L, &a, &b, &dest);
    
    glm_vec3_sub(a->data, b->data, dest->data);

    if (new_dest)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_subs(lua_State* L)
{
    honey_glm_array *self, *dest;
    float s;
    bool new_dest = get_vec3_scalars(L, &self, &s, &dest);

    glm_vec3_subs(self->data, s, dest->data);

    if (new_dest)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_mul(lua_State* L)
{
    honey_glm_array *a, *b, *dest;
    bool new_dest = get_vec3_arrays(L, &a, &b, &dest);
    
    glm_vec3_mul(a->data, b->data, dest->data);

    if (new_dest)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_scale(lua_State* L)
{
    honey_glm_array *self, *dest;
    float s;
    bool new_dest = get_vec3_scalars(L, &self, &s, &dest);

    glm_vec3_scale(self->data, s, dest->data);

    if (new_dest)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_scale_as(lua_State* L)
{
    honey_glm_array *self, *dest;
    float s;
    bool new_dest = get_vec3_scalars(L, &self, &s, &dest);

    glm_vec3_scale_as(self->data, s, dest->data);

    if (new_dest)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_div(lua_State* L)
{
    honey_glm_array *a, *b, *dest;
    bool new_dest = get_vec3_arrays(L, &a, &b, &dest);
    
    glm_vec3_div(a->data, b->data, dest->data);

    if (new_dest)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_negate(lua_State* L)
{
    honey_glm_array *self, *dest;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 1, HONEY_USERDATA, &self,
	 2, HONEY_USERDATA, &self, HONEY_USERDATA, &dest);

    if (choice == 0)
	glm_vec3_negate(self->data);
    else
	glm_vec3_negate_to(self->data, dest->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_normalize(lua_State* L)
{
    honey_glm_array *self, *dest;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 1, HONEY_USERDATA, &self,
	 2, HONEY_USERDATA, &self, HONEY_USERDATA, &dest);

    if (choice == 0)
	glm_vec3_normalize(self->data);
    else
	glm_vec3_normalize_to(self->data, dest->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_angle(lua_State* L)
{
    honey_glm_array *a, *b;
    honey_lua_parse_arguments
	(L, 1, 2,
	 HONEY_USERDATA, &a, HONEY_USERDATA, &b);

    if (b->type != VEC3)
	honey_lua_throw_error
	    (L, "second argument must be VEC3 (%d); got %d instead",
	     VEC3, b->type);

    float angle = glm_vec3_angle(a->data, b->data);
    lua_pushnumber(L, angle);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_clamp(lua_State* L)
{
    honey_glm_array* self;
    float min, max;
    honey_lua_parse_arguments(L, 1, 3,
			      HONEY_USERDATA, &self,
			      HONEY_NUMBER, &min,
			      HONEY_NUMBER, &max);

    glm_vec3_clamp(self->data, min, max);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec3_lerp(lua_State* L)
{
    honey_glm_array *a, *b, *dest;
    float s;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 3, HONEY_USERDATA, &a, HONEY_USERDATA, &b, HONEY_NUMBER, &s,
	 4, HONEY_USERDATA, &a, HONEY_USERDATA, &b, HONEY_NUMBER, &s, HONEY_USERDATA, &dest);

    if (b->type != VEC3)
	honey_lua_throw_error
	    (L, "second argument must be VEC3 (%d); got %d instead",
	     VEC3, b->type);

    if (choice == 1) {
	if (dest->type != VEC3)
	    honey_lua_throw_error
		(L, "fourth argument must be VEC3 (%d); got %d instead",
		 VEC3, dest->type);
    }
    else {
	honey_glm_new_vec3(L);
	dest = lua_touserdata(L, -1);
    }
	
    glm_vec3_lerp(a->data, b->data, s, dest->data);

    if (choice == 0)
	return 1;
    return 0;
}
