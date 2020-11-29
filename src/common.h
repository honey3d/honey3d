/** @file */

#ifndef HONEY_COMMON_H
#define HONEY_COMMON_H

// standard c libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// POSIX options
#include <unistd.h>

// lua interpreter
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

// glad
#include "glad/glad.h"
#include <GLFW/glfw3.h>

// c opengl mathematics function
#define CGLM_ALL_UNALIGNED
#include <cglm/cglm.h>
#include <cglm/call.h>

// assimp
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// stb image
#include "stb_image/stb_image.h"

typedef GLFWwindow* honey_window;

typedef struct {
    honey_window window;
    int width;
    int height;
    bool fullscreen;
} honey_window_information;

extern int honey_window_info_ref;
extern int honey_window_resize_callback_ref;
extern int honey_window_resize_callback_data_ref;
extern int honey_window_focus_callback_ref;
extern int honey_window_focus_callback_data_ref;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef enum {
  /* generic results */
  HONEY_OK,
  HONEY_MEMORY_ALLOCATION_ERROR,
  HONEY_FILE_READ_ERROR,

  /* shader errors */
  HONEY_VERTEX_SHADER_COMPILATION_ERROR,
  HONEY_FRAGMENT_SHADER_COMPILATION_ERROR,
  HONEY_SHADER_LINK_ERROR,

  /* mesh errors */
  HONEY_MESH_BAD_VERTEX_DATA,
  HONEY_MESH_BAD_INDEX_DATA,

  /* model errors */
  HONEY_MODEL_LOAD_ERROR,
  
  HONEY_N_ERRORS
} honey_result;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

typedef enum { VEC3,
	       VEC4,
	       MAT3,
	       MAT4
} honey_glm_array_type;

typedef struct {
  honey_glm_array_type type;
  unsigned int size;
  float* data;
} honey_glm_array;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

honey_result honey_format_string(char** string,
                                 char* format_string,
                                 ...);

/** @brief Throw an error with a string generated by a printf format string.
 *
 * This function attempts to create a string from the given format string; 
 * if an error should occur, it will instead throw a lua error with the appropriate
 * message. 
 *
 * @param[in] L The Lua state to throw an error from.
 * @param[in] format_string The format string used to generate the error message.
 * @param[in] ... The arguments for the format string.
 *
 * @returns Nothing.
 */
void honey_lua_throw_error(lua_State* L,
			   char* format_string,
			   ...);

/* lua binding functions */

typedef enum {
    HONEY_BOOLEAN,
    HONEY_INTEGER,
    HONEY_NUMBER,
    HONEY_STRING,
    HONEY_FUNCTION,
    HONEY_TABLE,
    HONEY_NIL,
    HONEY_USERDATA,
    HONEY_LIGHTUSERDATA,
    HONEY_ANY
} honey_lua_type;

/** @brief Get arguments from a function, checking to ensure the types match.
 *
 * Each argument type should be specified as [# of args], type, ptr, type, ptr...,
 * e.g.
 * ```
 * honey_lua_parse_arguments(L, 3, 
 *     // option 0
 *     2, HONEY_INTEGER, &a, HONEY_INTEGER, &b,
 *     // option 1
 *     1, HONEY_INTEGER, &a,
 *     // option 2
 *     0);
 * ```
 *
 * Note that this function will check for correct types of HONEY_TABLE, HONEY_NIL, and
 * HONEY_FUNCTION, but does not expect a pointer to them. It performs no check for 
 * HONEY_ANY, and also does not expect a pointer.
 *
 * @param[in] L The lua state to parse arguments from.
 * @param[in] n The number of argument options to parse.
 * @param[in] ... Variadic list of argument options.
 *
 * @returns The zero-indexed index of the actual argument option used. Throws an
 * error if no options matched the provided arguments.
 */
int honey_lua_parse_arguments(lua_State* L, unsigned int n, ...);

/** @brief Wrap C objects for lua. */
typedef struct honey_lua_element {
    char* name;
    honey_lua_type type;
    union {
        int integer;
        double number;
        char* string;
        int (*function)(lua_State*);
        struct {
            int n_elements;
            struct honey_lua_element* elements;
        } table;
        void* pointer;
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

/** @brief Create and populate a lua table.
 *
 * This function expects a list of the form `type, name, element, type, name, element...`.
 * In the case of a sub-table, the format is 
 * `type, name, n_elements, subtype, subname, subelement...`.
 * This can be nested as deeply as one wishes.
 *
 * As userdata cannot be pushed from C, attempting to push HONEY_USERDATA will result in
 * an error.
 *
 * @param[in] L The lua state to push the table to.
 * @param[in] n_elements The number of elements in the array.
 * @param[in] ... Variadic list of table elements.
 *
 * @returns Nothing.
 */
void honey_lua_create_table(lua_State* L,
			    unsigned int n_elements,
			    ...);

/** @brief Get the traceback for use after an error.
 */
int honey_lua_traceback(lua_State* L);

/** @brief Wrapper for lua_pcall that uses a honey_lua_traceback as an error handler.
 */
int honey_lua_pcall(lua_State* L, int nargs, int nret);

/** @brief Trigger honey to exit.
 *
 * @returns Nothing.
 */
int honey_exit(lua_State* L);

#endif
