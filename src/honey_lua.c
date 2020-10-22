#include "common.h"

void honey_lua_create_table(lua_State* L,
			    honey_lua_element* elements,
			    unsigned int n_elements)
{
    lua_createtable(L, 0, n_elements);

    for (int i=0; i<n_elements; i++) {
	honey_lua_push_element(L, elements[i]);
	lua_setfield(L, -2, elements[i].name);
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_lua_push_element(lua_State* L, honey_lua_element element)
{
    switch(element.type) {
    case HONEY_INT:
	lua_pushinteger(L, element.data.integer);
	break;

    case HONEY_NUM:
	lua_pushnumber(L, element.data.number);
	break;

    case HONEY_STRING:
	lua_pushstring(L, element.data.string);
	break;

    case HONEY_FUNC:
	lua_pushcfunction(L, element.data.function);
	break;

    default:
	// this should never happen
	break;
    }
}
