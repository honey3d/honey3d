#include <honeysuckle.h>

int demo(lua_State *L)
{
   lua_Integer i;
   lua_Number n;
   char *string;
   hs_parse_args(L, hs_int(i), hs_num(n), hs_str(string));
   printf("received %ld, %f, and %s\n", i, n, string);
   return 0;
}

int main()
{
   lua_State *L = luaL_newstate();
   luaL_openlibs(L);

   lua_pushcfunction(L, demo);
   lua_setglobal(L, "demo");

   luaL_dostring(L, "demo(12, 34.4, 'hi there!')");
   return 0;
}
