#include "common.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Helper structs
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

struct argument_pair {
    honey_lua_type type;
    void* ptr;
};

struct argument_list {
    unsigned int length;
    struct argument_pair* args;
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Lua binding helper function declarations
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/* string must be able to hold at least 16 characters. */
static int type_to_string(char* string,
			  honey_lua_type type);

static bool check_argument(lua_State* L,
			   honey_lua_type type,
			   int index);

static void get_argument(lua_State* L,
			 void* destination,
			 honey_lua_type type,
			 int index);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * String wrangling helpers
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

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

void honey_lua_throw_error(lua_State* L,
			   char* format_string,
			   ...)
{
    honey_result result;
    va_list args, args_;
    va_start(args,  format_string);
    va_copy(args_, args);

    int string_size = vsnprintf(NULL, 0, format_string, args_);
    va_end(args_);

    char* string = malloc((string_size + 1) * sizeof(char));
    if (string == NULL)
	lua_pushstring(L, "there was an error allocating memory for an error message");
    else {
	vsnprintf(string, string_size + 1, format_string, args);
	lua_pushstring(L, string);
	free(string);
    }
    lua_error(L);
}
    
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Argument parsing functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

static void honey_lua_arg_error(lua_State* L,
                                honey_lua_type type,
                                int position)
{
    char expected_type[16];
    type_to_string(expected_type, type);
    
    char* error_message;
    honey_result result;
    char* got_type = (char*) lua_typename(L, lua_type(L, position));
    result = honey_format_string(&error_message,
                                 "bad argument in position %d: "
                                 "expected %s, but got %s instead.",
                                 position,
                                 expected_type,
                                 got_type);
    if (result != HONEY_OK) {
        lua_pushstring(L, "error allocating memory for error message :(");
    }
    else {
        lua_pushstring(L, error_message);
        free(error_message);
    }
    lua_error(L);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static bool check_arg_list(lua_State* L,
			   struct argument_list arg_list)
{
    struct argument_pair* args = arg_list.args;
    for (int i=0; i<arg_list.length; i++) {
	if (!check_argument(L, args[i].type, i+1))
	    return false;
    }
    return true;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static int arg_list_to_string(char* string,
			      int start_index,
			      struct argument_list arg_list)
{
    struct argument_pair* args = arg_list.args;

    string[start_index] = '(';

    int index = start_index + 1;
    
    for (int i=0; i<arg_list.length; i++) {
	index += type_to_string(string + index, args[i].type);
	if (i != arg_list.length - 1) {
	    string[index + 1] = ',';
	    string[index + 2] = ' ';
	    index += 2;
	}
    }

    string[index] = ')';

    return index+1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void arg_lists_to_string(char** string,
				int n,
				struct argument_list* arg_lists)
{
    unsigned int size = 0;
    for (int i=0; i<n; i++)
	size += 18*arg_lists[i].length + 5;

    *string = calloc(size, sizeof(char));
    int index = 0;

    for (int i=0; i<n; i++) {
	index = arg_list_to_string(*string, index, arg_lists[i]);
	if (i != n) {
	    *string[index] = '\n';
	    index++;
	}
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void get_arg_list(lua_State* L,
			 struct argument_list arg_list)
{
    struct argument_pair* args = arg_list.args;
    for (int i=0; i<arg_list.length; i++) {
	get_argument(L, args[i].ptr, args[i].type, i+1);
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_lua_parse_arguments(lua_State* L, unsigned int n, ...)
{
    struct argument_list* arg_lists = malloc(n * sizeof(struct argument_list));
    if (arg_lists == NULL)
	honey_lua_throw_error(L, "failed to allocate memory for argument parsing!");

    va_list args;
    va_start(args, n);

    for (int i=0; i<n; i++) {
	arg_lists[i].length = va_arg(args, int);
	arg_lists[i].args = malloc(arg_lists[i].length * sizeof(struct argument_pair));
	if (arg_lists[i].args == NULL)
	    honey_lua_throw_error(L, "failed to allocate memory for argument parsing!");

	for (int j=0; j<arg_lists[i].length; j++) {
	    honey_lua_type type = va_arg(args, honey_lua_type);
	    void* destination = va_arg(args, void*);
	}
    }
    
    va_end(args);

    int index = 0;
    
    for (; index<n; index++) {
	if (check_arg_list(L, arg_lists[index])) {
	    get_arg_list(L, arg_lists[index]);
	    break;
	}
    }

    if (index == n) {
	/* no arguments match, throw error */
    }
	
    
    for (int i=0; i<n; i++)
	free(arg_lists[i].args);
    free(arg_lists);

    return index;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Table creation functions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

static void build_table_recursively(lua_State* L,
				    unsigned int n,
				    va_list args)
{
    lua_createtable(L, 0, n);

    for (int i=0; i<n; i++) {
	honey_lua_type type = va_arg(args, honey_lua_type);
	char* name = va_arg(args, char*);
	switch(type) {
	case HONEY_INTEGER:
	    lua_pushinteger(L, va_arg(args, int));
	    break;

	case HONEY_NUMBER:
	    lua_pushnumber(L, va_arg(args, double));
	    break;

	case HONEY_STRING:
	    lua_pushstring(L, va_arg(args, char*));
	    break;

	case HONEY_FUNCTION:
	    lua_pushcfunction(L, va_arg(args, int (*)(lua_State* L)));
	    break;
			      
	case HONEY_TABLE:
	    build_table_recursively(L, va_arg(args, int), args);
	    break;
	    
	case HONEY_NIL:
	    lua_pushnil(L);
	    break;

	case HONEY_USERDATA:
	    /* cannot push userdata from C, skip */
	    continue;

	case HONEY_LIGHTUSERDATA:
	    lua_pushlightuserdata(L, va_arg(args, void*));
	    break;

	default:
	    // this should never happen
	    break;
	}
	lua_setfield(L, -2, name);
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_lua_create_table(lua_State* L,
                            unsigned int n_elements,
			    ...)
{
    va_list args;
    va_start(args, n_elements);
    build_table_recursively(L, n_elements, args);
    va_end(args);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Lua pcall wrapping
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

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
    
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_exit(lua_State* L)
{
    if (honey_window_info_ref == LUA_NOREF ||
        honey_window_info_ref == LUA_REFNIL) {
        lua_pushstring(L, "Window information is not set!");
        lua_error(L);
    }

    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_window_info_ref);
    honey_window_information* info = lua_touserdata(L, -1);
    lua_pop(L, 1);

    glfwSetWindowShouldClose(info->window, true);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Lua binding helper function definitions
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/* string must be able to hold at least 16 characters. */
static int type_to_string(char* string,
			  honey_lua_type type)
{
    switch(type) {
    case HONEY_BOOLEAN:
	memcpy(string, "boolean", 8);
	return 7;

    case HONEY_INTEGER:
	memcpy(string, "integer", 8);
	return 7;

    case HONEY_NUMBER:
	memcpy(string, "number", 7);
	return 6;

    case HONEY_STRING:
	memcpy(string, "string", 7);
	return 6;

    case HONEY_FUNCTION:
	memcpy(string, "function", 9);
	return 8;

    case HONEY_TABLE:
	memcpy(string, "table", 6);
	return 5;

    case HONEY_NIL:
	memcpy(string, "nil", 4);
	return 3;

    case HONEY_USERDATA:
	memcpy(string, "userdata", 9);
	return 8;

    case HONEY_LIGHTUSERDATA:
	memcpy(string, "light userdata", 16);
	return 15;

    case HONEY_ANY:
	memcpy(string, "any", 4);
	return 3;

    default:
	return 0;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static bool check_argument(lua_State* L,
			   honey_lua_type type,
			   int index)
{
    switch(type) {
    case HONEY_BOOLEAN:
	if (!lua_isboolean(L, index))
	    return false;
	break;

    case HONEY_INTEGER:
    case HONEY_NUMBER:
	if (!lua_isnumber(L, index))
	    return false;
	break;

    case HONEY_STRING:
	if (!lua_isstring(L, index))
	    return false;
	break;

    case HONEY_FUNCTION:
	if (!lua_isfunction(L, index))
	    return false;
	break;

    case HONEY_TABLE:
	if (!lua_istable(L, index))
	    return false;
	break;

    case HONEY_NIL:
	if (!lua_isnil(L, index))
	    return false;
	break;

    case HONEY_USERDATA:
	if (!lua_isuserdata(L, index))
	    return false;
	break;

    case HONEY_LIGHTUSERDATA:
	if (!lua_islightuserdata(L, index))
	    return false;
	break;

    default:
	break;
    }


    return true;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void get_argument(lua_State* L,
			 void* destination,
			 honey_lua_type type,
			 int index)
{
    switch (type) {
    case HONEY_BOOLEAN:
	{
	    bool* result = destination;
	    *result = lua_toboolean(L, index);
	}
	break;

    case HONEY_INTEGER:
	{
	    int* result = destination;
	    *result = lua_tointeger(L, index);
	}
	break;

    case HONEY_NUMBER:
	{
	    float* result = destination;
	    *result = lua_tonumber(L, index);
	}
	break;

    case HONEY_STRING:
	{
	    char** result = destination;
	    *result = (char*) lua_tostring(L, index);
	}
	break;
            
    case HONEY_TABLE:
	break;

    case HONEY_FUNCTION:
	break;

    case HONEY_NIL:
	break;

    case HONEY_USERDATA:
	{
	    void** result = destination;
	    *result = lua_touserdata(L, index);
	}
	break;

    case HONEY_LIGHTUSERDATA:
	{
	    void** result = destination;
	    *result = lua_touserdata(L, index);
	}
	break;

    case HONEY_ANY:
	break;

    default:
	/* should never get here! */
	break;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
