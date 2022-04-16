#include "honeysuckle.h"

const char * hs_type_to_string(hs_type type)
{
   switch(type) {
   case HS_BOOL:
      return "boolean";
   case HS_INT:
      return "integer";
   case HS_NUM:
      return "number";
   case HS_STR:
      return "string";
   case HS_TBL:
      return "table";
   case HS_FUNC:
      return "function";
   case HS_CFUNC:
      return "C function";
   case HS_USER:
      return "userdata";
   case HS_LIGHT:
      return "light userdata";
   case HS_NIL:
      return "nil";
   case HS_ANY:
      return "any";
   default:
      return "(unknown)";
   }
}
