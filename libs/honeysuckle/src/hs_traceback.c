#include "honeysuckle.h"

int hs_traceback(lua_State *L)
{
   if (!lua_isstring(L, 1))
      /* 'message' is not a string, keep intact */
      return 1;

   lua_getglobal(L, "debug");
   if (!lua_istable(L, -1)) {
      lua_pop(L, 1);
      return 1;
   }

   lua_getfield(L, -1, "traceback");
   if (!lua_isfunction(L, -1)) {
      lua_pop(L, 2);
      return 1;
   }

   lua_pushvalue(L, 1);
   lua_pushinteger(L, 2);
   lua_call(L, 2, 1);
   return 1;
}


int hs_call(lua_State *L, int nargs, int nret)
{
   int traceback_pos = lua_gettop(L) - nargs;
   lua_pushcfunction(L, hs_traceback);
   lua_insert(L, traceback_pos);

   int result = lua_pcall(L, nargs, nret, traceback_pos);
   lua_remove(L, traceback_pos);
   return result;
}
