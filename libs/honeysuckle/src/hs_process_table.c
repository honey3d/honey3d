#include "honeysuckle.h"

void hs_pt_set_boolean(bool value, void *data)
{
   *(bool *) data = value;
}

void hs_pt_set_integer(lua_Integer value, void *data)
{
   *(lua_Integer *) data = value;
}

void hs_pt_set_number(lua_Number value, void *data)
{
   *(lua_Number *) data = value;
}

void hs_pt_set_string(const char *value, void *data)
{
   *(const char **) data = value;
}


static bool process_key(lua_State *L, struct hs_table_processor *p)
{
   switch (p->type) {
   case HS_BOOL:
      if (!lua_isboolean(L, -1))
	 hs_throw_error(L,
			"expected key '%s' to be of type boolean, "\
			"but got type %s instead",
			p->key,
			lua_typename(L, lua_type(L, -1)));
      p->func.boolean(lua_toboolean(L, -1), p->data);
      break;

   case HS_INT:
      if (!lua_isnumber(L, -1))
	 hs_throw_error(L,
			"expected key '%s' to be of type integer, "\
			"but got type %s instead",
			p->key,
			lua_typename(L, lua_type(L, -1)));
      p->func.integer(lua_tointeger(L, -1), p->data);
      break;

   case HS_NUM:
      if (!lua_isnumber(L, -1))
	 hs_throw_error(L,
			"expected key '%s' to be of type number, "\
			"but got type %s instead",
			p->key,
			lua_typename(L, lua_type(L, -1)));
      p->func.number(lua_tonumber(L, -1), p->data);
      break;

   case HS_STR:
      if (!lua_isstring(L, -1))
	 hs_throw_error(L,
			"expected key '%s' to be of type string, "\
			"but got type %s instead",
			p->key,
			lua_typename(L, lua_type(L, -1)));
      p->func.string(lua_tostring(L, -1), p->data);
      break;

   default:
      // bad type value, throw error
      hs_throw_error(L, "bad expected type '%d' for key '%s'",
		     p->type, p->key);
      break;
   }
}

void hs_process_table_(lua_State *L,
		       int table_index,
		       int n_processors,
		       struct hs_table_processor *processors)
{
   for (int i=0; i<n_processors; i++) {
      lua_getfield(L, table_index, processors[i].key);
      if (!lua_isnil(L, -1))
	 process_key(L, processors+i);
      lua_pop(L, 1);
   }
}
