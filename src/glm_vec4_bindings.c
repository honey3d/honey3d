#include "glm_bindings.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Vec4 Functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */


int honey_glm_vec4_copy(lua_State* L)
{
    honey_glm_array *self, *dest;
    honey_lua_parse_arguments
	(L, 1, 2, HONEY_USERDATA, &self, HONEY_USERDATA, &dest);

    if (dest->type != VEC4)
	honey_lua_throw_error(L, "destination must be VEC4 (%d); got %d instead",
			      dest->type);

    glm_vec4_copy(self->data, dest->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec4_zero(lua_State* L)
{
    honey_glm_array *self;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &self);

    glm_vec4_zero(self->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec4_eye(lua_State* L)
{
    honey_glm_array *self;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &self);

    glm_vec4_one(self->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec4_dot(lua_State* L)
{
    honey_glm_array *a, *b;
    honey_lua_parse_arguments
	(L, 1, 2,
	 HONEY_USERDATA, &a,
	 HONEY_USERDATA, &b);

    if (b->type != VEC4)
	honey_lua_throw_error(L, "destination must be VEC4 (%d); got %d instead",
			      VEC4, b->type);

    float result = glm_vec4_dot(a->data, b->data);

    lua_pushnumber(L, result);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static bool get_vec4_arrays(lua_State* L,
			    honey_glm_array** a,
			    honey_glm_array** b,
			    honey_glm_array** dest)
{
    int choice = honey_lua_parse_arguments
	(L, 2,
	 2, HONEY_USERDATA, a, HONEY_USERDATA, b,
	 3, HONEY_USERDATA, a, HONEY_USERDATA, b, HONEY_USERDATA, dest);

    if ((*b)->type != VEC4)
	honey_lua_throw_error
	    (L, "second argument must be VEC4 (%d); got %d instead",
	     VEC4, (*b)->type);

    if (choice == 1) {
	if ((*dest)->type != VEC4)
	    honey_lua_throw_error
		(L, "third argument must be VEC4 (%d); got %d instead",
		 VEC4, (*dest)->type);
    }
    else {
	honey_glm_new_vec4(L);
	*dest = lua_touserdata(L, -1);
    }

    return choice == 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static bool get_vec4_scalars(lua_State* L,
			     honey_glm_array** a,
			     float* s,
			     honey_glm_array** dest)
{
    int choice = honey_lua_parse_arguments
	(L, 2,
	 2, HONEY_USERDATA, a, HONEY_NUMBER, s,
	 3, HONEY_USERDATA, a, HONEY_NUMBER, s, HONEY_USERDATA, dest);

    if (choice == 1) {
	if ((*dest)->type != VEC4)
	    honey_lua_throw_error
		(L, "third argument must be VEC4 (%d); got %d instead",
		 VEC4, (*dest)->type);
    }
    else {
	honey_glm_new_vec4(L);
	*dest = lua_touserdata(L, -1);
    }

    return choice == 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec4_norm2(lua_State* L)
{
    honey_glm_array *self;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &self);
    float result = glm_vec4_norm2(self->data);
    lua_pushnumber(L, result);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec4_norm(lua_State* L)
{
    honey_glm_array *self;
    honey_lua_parse_arguments(L, 1, 1, HONEY_USERDATA, &self);
    float result = glm_vec4_norm(self->data);
    lua_pushnumber(L, result);
    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec4_add(lua_State* L)
{
    honey_glm_array *a, *b, *dest;
    bool new_dest = get_vec4_arrays(L, &a, &b, &dest);
    
    glm_vec4_add(a->data, b->data, dest->data);

    if (new_dest)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec4_adds(lua_State* L)
{
    honey_glm_array *self, *dest;
    float s;
    bool new_dest = get_vec4_scalars(L, &self, &s, &dest);

    glm_vec4_adds(self->data, s, dest->data);

    if (new_dest)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec4_sub(lua_State* L)
{
    honey_glm_array *a, *b, *dest;
    bool new_dest = get_vec4_arrays(L, &a, &b, &dest);
    
    glm_vec4_sub(a->data, b->data, dest->data);

    if (new_dest)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec4_subs(lua_State* L)
{
    honey_glm_array *self, *dest;
    float s;
    bool new_dest = get_vec4_scalars(L, &self, &s, &dest);

    glm_vec4_subs(self->data, s, dest->data);

    if (new_dest)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec4_mul(lua_State* L)
{
    honey_glm_array *a, *b, *dest;
    bool new_dest = get_vec4_arrays(L, &a, &b, &dest);
    
    glm_vec4_mul(a->data, b->data, dest->data);

    if (new_dest)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec4_scale(lua_State* L)
{
    honey_glm_array *self, *dest;
    float s;
    bool new_dest = get_vec4_scalars(L, &self, &s, &dest);

    glm_vec4_scale(self->data, s, dest->data);

    if (new_dest)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec4_scale_as(lua_State* L)
{
    honey_glm_array *self, *dest;
    float s;
    bool new_dest = get_vec4_scalars(L, &self, &s, &dest);

    glm_vec4_scale_as(self->data, s, dest->data);

    if (new_dest)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec4_div(lua_State* L)
{
    honey_glm_array *a, *b, *dest;
    bool new_dest = get_vec4_arrays(L, &a, &b, &dest);
    
    glm_vec4_div(a->data, b->data, dest->data);

    if (new_dest)
	return 1;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec4_negate(lua_State* L)
{
    honey_glm_array *self, *dest;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 1, HONEY_USERDATA, &self,
	 2, HONEY_USERDATA, &self, HONEY_USERDATA, &dest);

    if (choice == 0)
	glm_vec4_negate(self->data);
    else
	glm_vec4_negate_to(self->data, dest->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec4_normalize(lua_State* L)
{
    honey_glm_array *self, *dest;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 1, HONEY_USERDATA, &self,
	 2, HONEY_USERDATA, &self, HONEY_USERDATA, &dest);

    if (choice == 0)
	glm_vec4_normalize(self->data);
    else
	glm_vec4_normalize_to(self->data, dest->data);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec4_clamp(lua_State* L)
{
    honey_glm_array* self;
    float min, max;
    honey_lua_parse_arguments(L, 1, 3,
			      HONEY_USERDATA, &self,
			      HONEY_NUMBER, &min,
			      HONEY_NUMBER, &max);

    glm_vec4_clamp(self->data, min, max);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_glm_vec4_lerp(lua_State* L)
{
    honey_glm_array *a, *b, *dest;
    float s;
    int choice = honey_lua_parse_arguments
	(L, 2,
	 3, HONEY_USERDATA, &a, HONEY_USERDATA, &b, HONEY_NUMBER, &s,
	 4, HONEY_USERDATA, &a, HONEY_USERDATA, &b, HONEY_NUMBER, &s, HONEY_USERDATA, &dest);

    if (b->type != VEC4)
	honey_lua_throw_error
	    (L, "second argument must be VEC4 (%d); got %d instead",
	     VEC4, b->type);

    if (choice == 1) {
	if (dest->type != VEC4)
	    honey_lua_throw_error
		(L, "fourth argument must be VEC4 (%d); got %d instead",
		 VEC4, dest->type);
    }
    else {
	honey_glm_new_vec4(L);
	dest = lua_touserdata(L, -1);
    }
	
    glm_vec4_lerp(a->data, b->data, s, dest->data);

    if (choice == 0)
	return 1;
    return 0;
}
