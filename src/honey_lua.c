#include "common.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

honey_result honey_format_string(char** string,
                                 char* format_string,
                                 ...)
{
    honey_result res;
    va_list args, args_;
    va_start(args, format_string);
    va_copy(args_, args);

    int string_size = vsnprintf(NULL, 0, format_string, args_);
    va_end(args_);
    *string = malloc((string_size+1) * sizeof(char));
    if (*string == NULL)
        res = HONEY_MEMORY_ALLOCATION_ERROR;
    else {
        vsnprintf(*string, string_size+1, format_string, args);
        res = HONEY_OK;
    }
    
    va_end(args);
    
    return res;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

bool honey_lua_validate_types(lua_State* L,
                              unsigned int n_types,
                              ...)
{
    va_list args;
    va_start(args, n_types);

    for (int i=0; i<n_types; i++) {
        honey_lua_type expected_type = va_arg(args, honey_lua_type);
        honey_result result;
        char* error_message;

        switch(expected_type) {
        case HONEY_BOOL:
            if (!lua_isboolean(L, i+1)) {
                result = honey_format_string(&error_message,
                                             "Expected boolean in position %d",
                                             i);
                if (result != HONEY_OK)
                    lua_pushstring(L, "Expected boolean; allocation error occurred for more detailed message.");
                else {
                    lua_pushstring(L, error_message);
                    free(error_message);
                }
                return false;
            }
            break;
            
        case HONEY_INT:
        case HONEY_NUM:
            if (!lua_isnumber(L, i+1)) {
                result = honey_format_string(&error_message,
                                             "Expected number in position %d",
                                             i);
                if (result != HONEY_OK)
                    lua_pushstring(L, "Expected number; allocation error occurred for more detailed message.");
                else {
                    lua_pushstring(L, error_message);
                    free(error_message);
                }
                return false;
            }
            break;

        case HONEY_STRING:
            if (!lua_isstring(L, i+1)) {
                result = honey_format_string(&error_message,
                                             "Expected string in position %d",
                                             i);
                if (result != HONEY_OK)
                    lua_pushstring(L, "Expected string; allocation error occurred for more detailed message.");
                else {
                    lua_pushstring(L, error_message);
                    free(error_message);
                }
                return false;
            }
            break;

        case HONEY_FUNC:
            if (!lua_isfunction(L, i+1)) {
                result = honey_format_string(&error_message,
                                             "Expected function in position %d",
                                             i);
                if (result != HONEY_OK)
                    lua_pushstring(L, "Expected function; allocation error occurred for more detailed message.");
                else {
                    lua_pushstring(L, error_message);
                    free(error_message);
                }
                return false;
            }
            break;

        case HONEY_TABLE:
            if (!lua_istable(L, i+1)) {
                result = honey_format_string(&error_message,
                                             "Expected table in position %d",
                                             i);
                if (result != HONEY_OK)
                    lua_pushstring(L, "Expected table; allocation error occurred for more detailed message.");
                else {
                    lua_pushstring(L, error_message);
                    free(error_message);
                }
                return false;
            }
            break;
            
        case HONEY_NIL:
            if (!lua_isnil(L, i+1)) {
                result = honey_format_string(&error_message,
                                             "Expected nil in position %d",
                                             i);
                if (result != HONEY_OK)
                    lua_pushstring(L, "Expected nil; allocation error occurred for more detailed message.");
                else {
                    lua_pushstring(L, error_message);
                    free(error_message);
                }
                return false;
            }
            break;

        case HONEY_ANY:
            break;

        default:
            break;
        }
    }

    va_end(args);
    return true;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

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

    case HONEY_TABLE:
        honey_lua_create_table(L,
                               element.data.table.elements,
                               element.data.table.n_elements);
        break;

    default:
        // this should never happen
        break;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_lua_traceback(lua_State* L)
{
    if (!lua_isstring(L, 1))
        /* 'message' is not a string, keep intact. */
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

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_lua_pcall(lua_State* L, int nargs, int nret)
{
    int traceback_pos = lua_gettop(L) - nargs;
    lua_pushcfunction(L, honey_lua_traceback);
    lua_insert(L, traceback_pos);

    int result = lua_pcall(L, nargs, nret, traceback_pos);
    lua_remove(L, traceback_pos);
    return result;
}
    
