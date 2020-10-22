#ifndef HONEY_LUA_H
#define HONEY_LUA_H

#include "../common.h"

typedef enum {
    HONEY_INT,
    HONEY_NUM,
    HONEY_STRING,
    HONEY_FUNC
} honey_lua_type;

typedef struct {
    char* name;
    honey_lua_type type;
    union {
	int integer;
	double number;
	char* string;
	int (*function)(lua_State*);
    } data;
} honey_lua_element;

/** @brief Push an element to the lua stack.
 *
 * @param[in] L The lua state to push the element to.
 * @param[in] element The honey_lua_element to push to the stack.
 *
 * @returns Nothing.
 */
void honey_lua_push_element(lua_State* L,
			    honey_lua_element element);

/** @brief Create a lua table populated with various elements.
 *
 * @param[in] L The lua state to push the table to.
 * @param[in] elements Array of elements to populate the table.
 * @param[in] n_elements The number of elements in the array.
 *
 * @returns Nothing.
 */
void honey_lua_create_table(lua_State* L,
			    honey_lua_element* elements,
			    unsigned int n_elements);

#endif
