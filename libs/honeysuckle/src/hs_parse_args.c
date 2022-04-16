#include <stdio.h>

#include "honeysuckle.h"

static bool check_parse(lua_State *L, int index, struct hs_arg *expected)
{
   switch(expected->type) {
   case HS_BOOL:
      if (!lua_isboolean(L, index))
	 return false;
      *(expected->ptr.boolean) = lua_toboolean(L, index);
      return true;

   case HS_INT:
      if (!lua_isnumber(L, index))
	 return false;
      *(expected->ptr.integer) = lua_tointeger(L, index);
      return true;

   case HS_NUM:
      if (!lua_isnumber(L, index))
	 return false;
      *(expected->ptr.number) = lua_tonumber(L, index);
      return true;

   case HS_STR:
      if (!lua_isstring(L, index) || lua_isnumber(L, index))
	 return false;
      *(expected->ptr.string) = (char *) lua_tostring(L, index);
      return true;

   case HS_TBL:
      if (!lua_istable(L, index))
	 return false;
      *(expected->ptr.stack_index) = index;
      return true;

   case HS_FUNC:
      if (!lua_isfunction(L, index))
	 return false;
      *(expected->ptr.stack_index) = index;
      return true;

   case HS_CFUNC:
      if (!lua_iscfunction(L, index))
	 return false;
      *(expected->ptr.function) = lua_tocfunction(L, index);
      return true;

   case HS_USER:
      if (!lua_isuserdata(L, index))
	 return false;
      *(expected->ptr.userdata) = lua_touserdata(L, index);
      return true;

   case HS_LIGHT:
      if (!lua_islightuserdata(L, index))
	 return false;
      *(expected->ptr.userdata) = lua_touserdata(L, index);
      return true;

   case HS_NIL:
      if (!lua_isnil(L, index))
	 return false;
      *(expected->ptr.stack_index) = index;

   case HS_ANY:
      *(expected->ptr.stack_index) = index;
      return true;

   default:
      return false;
   }
}


static bool try_parse_args(lua_State *L, int n_args, struct hs_arg *arguments)
{
   int args_provided = lua_gettop(L);
   if (args_provided != n_args)
      return false;

   for (int i=0; i<n_args; i++) {
      bool success = check_parse(L, i+1, arguments + i);
      if (!success)
	 return false;
   }
   return true;
}


void hs_parse_args_(lua_State *L, int n_args, struct hs_arg *arguments)
{
   bool success = try_parse_args(L, n_args, arguments);
   if (!success) {
      lua_pushstring(L, "expected arguments of the form (");
      for (int i=0; i<n_args; i++) {
	 lua_pushstring(L, hs_type_to_string(arguments[i].type));
	 lua_pushstring(L, ", ");
      }
      lua_pop(L, 1);
      lua_pushstring(L, "); received (");
      const int n_provided = lua_gettop(L);
      for (int i=0; i<n_provided; i++) {
	 lua_pushstring(L, lua_typename(L, lua_type(L, i+1)));
	 lua_pushstring(L, ", ");
      }
      lua_pop(L, 1);
      lua_pushstring(L, ") instead");
      lua_concat(L, 1 + (2*n_args) + (2*n_provided));
      lua_error(L);
   }
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static void hs_overloaded_error(lua_State *L, va_list args)
{
   lua_pushstring(L, "hs_overloaded failed");
   lua_error(L);
}


int hs_parse_overloaded_(lua_State *L, ...)
{
   va_list args, args_error;
   va_start(args, L);
   va_copy(args_error, args);

   int choice = 0;

   while(true) {
      int n_args = va_arg(args, int);
      if (n_args == -1)
	 break;
      else {
	 struct hs_arg *arguments = va_arg(args, struct hs_arg *);
	 if (try_parse_args(L, n_args, arguments))
	    return choice;
      }
      choice++;
   }

   hs_overloaded_error(L, args_error);
   
   va_end(args);
   va_end(args_error);
}
