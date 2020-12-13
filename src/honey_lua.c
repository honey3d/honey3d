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
static const char* type_to_string(honey_lua_type type);

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

static bool check_arg_list(lua_State* L,
			   struct argument_list arg_list)
{
    if (arg_list.length != lua_gettop(L))
	return false;
    struct argument_pair* args = arg_list.args;
    for (int i=0; i<arg_list.length; i++) {
	if (!check_argument(L, args[i].type, i+1))
	    return false;
    }
    return true;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void arg_list_to_string(char** string,
			      struct argument_list arg_list)
{
    struct argument_pair* args = arg_list.args;

    size_t size = sizeof(char) * (18*arg_list.length + 5);
    *string = malloc(size);

    memcpy(*string, "(", 2);

    for (int i=0; i<arg_list.length; i++) {
	strcat(*string, type_to_string(args[i].type));
	if (i != arg_list.length-1)
	    strcat(*string, ", ");
    }
    strcat(*string, ")");
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

    char* arg_list_string;

    for (int i=0; i<n; i++) {
	arg_list_to_string(&arg_list_string, arg_lists[i]);
	strcat(*string, arg_list_string);
	free(arg_list_string);
	if (i != n-1)
	    strcat(*string, "\n");
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void arguments_to_string(lua_State* L, char** string)
{
    unsigned int argc = lua_gettop(L);

    size_t size = sizeof(char) * (18*argc + 5);
    *string = malloc(size);

    memcpy(*string, "(", 2);

    char type_string[16];
    for (int i=0; i<argc; i++) {
	int type = lua_type(L, i+1);
	strncat(*string, lua_typename(L, type), 16*sizeof(char));
	if (i != argc-1)
	    strncat(*string, ", ", 4*sizeof(char));
    }
    strncat(*string, ")", 4);
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

	    arg_lists[i].args[j].type = type;
	    arg_lists[i].args[j].ptr = destination;
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
	char* arg_lists_str, *argv, *error;
	arg_lists_to_string(&arg_lists_str, n, arg_lists);
	arguments_to_string(L, &argv);
	honey_format_string
	    (&error,
	     "expected arguments of the form\n%s\nbut received\n%s",
	     arg_lists_str, argv);
	lua_pushstring(L, error);
	free(arg_lists_str);
	free(argv);
	free(error);
	lua_error(L);
    }
	
    
    for (int i=0; i<n; i++)
	free(arg_lists[i].args);
    free(arg_lists);

    return index;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_lua_parse_params(lua_State* L, int n, int m, ...)
{
    int table_index = lua_gettop(L);
    
    va_list args;
    va_start(args, m);

    for (int i=0; i<n; i++) {
        const char* param = va_arg(args, const char*);
        void (*function)(lua_State*, void*) = va_arg(args, void (*)(lua_State*, void*));
        void* data = va_arg(args, void*);
        
        lua_getfield(L, table_index, param);
        if (lua_isnil(L, -1) && n < m)
            honey_lua_throw_error
                (L, "required parameter '%s' was not found in param table!", param);

        function(L, data);
        lua_pop(L, 1);
    }

    va_end(args);
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
static const char* type_to_string(honey_lua_type type)
{
    switch(type) {
    case HONEY_BOOLEAN:
	return "boolean";

    case HONEY_INTEGER:
	return "integer";

    case HONEY_NUMBER:
	return "number";

    case HONEY_STRING:
	return "string";

    case HONEY_FUNCTION:
	return "function";

    case HONEY_TABLE:
	return "table";

    case HONEY_NIL:
	return "nil";

    case HONEY_USERDATA:
	return "userdata";

    case HONEY_LIGHTUSERDATA:
	return "light userdata";

    case HONEY_ANY:
	return "any";

    default:
	return "ERROR";
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
