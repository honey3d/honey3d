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

#define HONEY_ERROR_DATA_STRING_LENGTH 4096

static struct {
  char string1[HONEY_ERROR_DATA_STRING_LENGTH];
  char string2[HONEY_ERROR_DATA_STRING_LENGTH];
} honey_error_data;

void honey_error_clear_strings();
void honey_error_set_string1(char* string);
void honey_error_set_string2(char* string);

/** @brief Generate a human-readable error message.
 *
 * @param[out] error_string A string with at least 3*HONEY_ERROR_DATA_STRING_LENGTH characters to store the result
 * @param[in] error The error to generate a message for
 */
void honey_human_readable_error(char* error_string, honey_result error);

/** @brief Generate a string from a format string.
 *
 * This function allocates memory for the destination; the user is
 * responsible for deallocating it. As a side effect of this, the destination
 * pointer cannot overlap with any of the varargs.
 *
 * @param[out] string Pointer to the destination string.
 * @param[in] format_string The format string used to generate the result.
 * @param[in] ... The arguments for the format string.
 *
 * @returns HONEY_OK on success; HONEY_MEMORY_ALLOCATION_ERROR on a
 * memory allocation error.
 */
honey_result honey_format_string(char** string,
                                 char* format_string,
                                 ...);

/* lua binding functions */

typedef enum {
    HONEY_BOOL,
    HONEY_INT,
    HONEY_NUM,
    HONEY_STRING,
    HONEY_FUNC,
    HONEY_TABLE,
    HONEY_NIL,
    HONEY_USERDATA,
    HONEY_LIGHTUSERDATA,
    HONEY_ANY
} honey_lua_type;

/** @brief Check that a functions' arguments are of the correct type.
 *
 * @param[in] L The lua state to validate.
 * @param[in] n_types The number of types to validate.
 * @param[in] ... Variadic list of honey_lua_types to validate against the stack.
 *
 * @returns true if the validation was successful; false otherwise, pushing an error message
 * to the lua stack.
 */
bool honey_lua_validate_types(lua_State* L, unsigned int n_types, ...);

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

/** @brief Get the traceback for use after an error.
 */
int honey_lua_traceback(lua_State* L);

/** @brief Wrapper for lua_pcall that uses a honey_lua_traceback as an error handler.
 */
int honey_lua_pcall(lua_State* L, int nargs, int nret);

#endif
