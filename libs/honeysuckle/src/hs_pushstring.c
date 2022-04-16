#include <stdlib.h>

#include "honeysuckle.h"

void hs_vpushstring(lua_State *L, const char *format_string, va_list args)
{
   va_list args_;
   va_copy(args_, args);

   int string_size = vsnprintf(NULL, 0, format_string, args_);
   va_end(args_);

   char *string = malloc((string_size+1) * sizeof(char));
   if (string == NULL) {
      lua_pushstring(L, "there was an error allocating memory for a string");
      lua_error(L);
   }

   vsnprintf(string, string_size+1, format_string, args);
   lua_pushstring(L, string);
   free(string);
}


void hs_pushstring(lua_State *L, const char *format_string, ...)
{
   va_list args;
   va_start(args, format_string);
   hs_vpushstring(L, format_string, args);
   va_end(args);
}
