#include <stdlib.h>

#include "honeysuckle.h"

static void push_value(lua_State *L, hs_type type, hs_value value)
{
   switch (type) {
   case HS_BOOL:
      lua_pushboolean(L, value.boolean);
      break;

   case HS_INT:
      lua_pushinteger(L, value.integer);
      break;

   case HS_NUM:
      lua_pushnumber(L, value.number);
      break;

   case HS_STR:
      lua_pushstring(L, value.string);
      break;

   case HS_TBL:
      lua_pushvalue(L, value.stack_index);
      break;

   case HS_FUNC:
      lua_pushvalue(L, value.stack_index);
      break;

   case HS_CFUNC:
      lua_pushcfunction(L, value.function);
      break;

   case HS_USER:
      lua_pushvalue(L, value.stack_index);
      break;

   case HS_LIGHT:
      lua_pushlightuserdata(L, value.userdata);
      break;

   default:
      hs_throw_error(L, "attempted to push data of invalid type %d", type);
      break;
   }
}


static inline bool poppable(hs_type type)
{
   if (type == HS_TBL ||
       type == HS_FUNC ||
       type == HS_USER) {
      return true;
   }
   return false;
}


static void print_stack(lua_State *L)
{
   printf("stack: %d [", lua_gettop(L));
   for (int i=0; i<lua_gettop(L); i++) {
      printf(" %s, ", lua_typename(L, lua_type(L, i+1)));
   }
   printf("]\n");
}


int descending(const void *a, const void *b)
{
   return (*(int*)b - *(int*)a);
}

int hs_create_table_(lua_State *L,
		     int n_elements,
		     struct hs_tbl_entry *elements)
{
   // printf("start\n");
   
   // print_stack(L);
   lua_createtable(L, 0, n_elements);
   int index = lua_gettop(L);
   // print_stack(L);

   for (int i=0; i<n_elements; i++) {
      // printf("pushing element %d...\n", i);
      struct hs_tbl_entry *e = elements + i;
      push_value(L, e->key_type, e->key);
      // print_stack(L);
      push_value(L, e->value_type, e->value);
      // print_stack(L);
      lua_rawset(L, index);
      // print_stack(L);
   }

   int n_poppable = 0;
   int pop_indices[n_elements];
   
   for (int i=0; i<n_elements; i++) {
      struct hs_tbl_entry *e = elements + i;
      if (poppable(e->key_type))
	 pop_indices[n_poppable++] = e->key.stack_index;
      if (poppable(e->value_type))
	 pop_indices[n_poppable++] = e->value.stack_index;
   }

   // printf("cleaning up\n");
   
   qsort(pop_indices, n_poppable, sizeof(int), descending);
   for (int i=0; i<n_poppable; i++) {
      lua_remove(L, pop_indices[i]);
      index -= 1;
      // print_stack(L);
   }
   

   // printf("exit\n");
   
   return index;
}
