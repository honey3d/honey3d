#include <honeysuckle.h>

int main()
{
   lua_State *L = luaL_newstate();
   luaL_openlibs(L);

   /* create the table
    * { "one"=1, "two"=2, "half"=0.5, "runme"=[some function] }
    */
   luaL_dostring(L,
		 "return function(self) \n"	\
		 "print(self.one)\n" \
		 "print(self.two)\n" \
		 "print(self.half)\n" \
		 "end");
   int func_index = lua_gettop(L);

   hs_create_table(L,
		   hs_str_int("one", 1),
		   hs_str_int("two", 2),
		   hs_str_num("half", 0.5f),
		   hs_str_func("runme", func_index));
   lua_setglobal(L, "runnable");

   luaL_dostring(L, "runnable:runme()");
   return 0;
}
