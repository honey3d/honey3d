#include <stdlib.h>

#include "honeysuckle.h"

void hs_throw_error(lua_State *L, const char *format_string, ...)
{
   va_list args;
   va_start(args, format_string);
   hs_vpushstring(L, format_string, args);
   va_end(args);
   lua_error(L);
}
