#include <honeysuckle.h>

#include <stdbool.h>

#include "logging/logging.h"
#include "gl/honey_gl.h"


struct honey_window window;

static int resize_callback_ref = LUA_NOREF;
static int resize_data_ref = LUA_NOREF;

static int focus_callback_ref = LUA_NOREF;
static int focus_data_ref = LUA_NOREF;

static void error_callback(int code, const char *description);
static void resize_callback(GLFWwindow *w, int width, int height);
static void focus_callback(GLFWwindow *w, int focus);

static int create_window(lua_State *L);

static int window_get_size(lua_State *L);
static int window_set_size(lua_State *L);
static int window_set_resize_callback(lua_State *L);
static int window_unset_resize_callback(lua_State *L);


void setup_window(lua_State *L, int tbl_index)
{
   /* initialize window struct */
   window.created = false;
   window.L = L;
   
   /* set error handler */
   glfwSetErrorCallback(error_callback);

   /* create window table */
   hs_create_table
      (L,
       hs_str_cfunc("createWindow", create_window),
       hs_str_cfunc("getSize", window_get_size),
       hs_str_cfunc("setSize", window_set_size),
       hs_str_cfunc("setResizeCallback", window_set_resize_callback),
       hs_str_cfunc("unsetResizeCallback", window_unset_resize_callback)
       );

   /* set honey table entry */
   lua_setfield(L, tbl_index, "window");
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * glfw callbacks
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

static void error_callback(int code, const char *description)
{
   honey_error("GLFW error %d: %s", code, description);
   hs_throw_error(window.L, "(GLFW error %d) %s", code, description);
}


static void resize_callback(GLFWwindow *w, int width, int height)
{
   lua_State *L = window.L;

   if (resize_callback_ref == LUA_NOREF)
      /* no resize callback set */
      return;

   /* push callback function */
   hs_rload(L, resize_callback_ref);

   lua_pushinteger(L, width);
   lua_pushinteger(L, height);

   if (resize_data_ref == LUA_NOREF || resize_data_ref == LUA_REFNIL)
      lua_pushnil(L);
   else
      hs_rload(L, resize_data_ref);

   hs_call(L, 3, 0);
}


static void focus_callback(GLFWwindow *w, int focus)
{
   lua_State *L = window.L;

   if (focus_callback_ref == LUA_NOREF)
      /* no focus callback set */
      return;

   /* push callback function */
   hs_rload(L, focus_callback_ref);

   lua_pushboolean(L, focus);

   if (focus_data_ref == LUA_NOREF || focus_data_ref == LUA_REFNIL)
      lua_pushnil(L);
   else
      hs_rload(L, focus_data_ref);

   hs_call(L, 2, 0);
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * window
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

static int create_window(lua_State *L)
{
   /* return immediately if already called */
   if (window.created) return 0;
   
   lua_Integer x, y;
   hs_parse_args(L, hs_int(x), hs_int(y));

   if (!glfwInit()) {
      /* window creation failed :c */
      honey_fatal("failed to create window!");
      hs_throw_error(L, "failed to create window!");
   }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   window.window = glfwCreateWindow(x, y, "honey", NULL, NULL);
   glfwMakeContextCurrent(window.window);

   if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
      honey_fatal("failed to initialize GLAD");
      glfwTerminate();
      hs_throw_error(L, "failed to initialize GLAD");
   }

   /* bind resize/focus callbacks */
   glfwSetWindowSizeCallback(window.window, resize_callback);
   glfwSetWindowFocusCallback(window.window, focus_callback);
}


static int window_get_size(lua_State *L)
{
   int width, height;
   glfwGetWindowSize(window.window, &width, &height);
   lua_pushinteger(L, width);
   lua_pushinteger(L, height);
   return 2;
}


static int window_set_size(lua_State *L)
{
   lua_Integer width, height;
   hs_parse_args(L, hs_int(width), hs_int(height));
   glfwSetWindowSize(window.window, width, height);
   return 0;
}


static int window_set_resize_callback(lua_State *L)
{
   int cb, data;
   hs_parse_args(L, hs_func(cb), hs_any(data));

   lua_pushvalue(L, cb);
   resize_callback_ref = hs_rstore(L);

   lua_pushvalue(L, data);
   resize_data_ref = hs_rstore(L);

   return 0;
}


static int window_unset_resize_callback(lua_State *L)
{
   if (resize_callback_ref != LUA_NOREF)
      hs_rdel(L, resize_callback_ref);
   if (resize_data_ref != LUA_NOREF)
      hs_rdel(L, resize_callback_ref);

   resize_callback_ref = LUA_NOREF;
   resize_data_ref = LUA_NOREF;

   return 0;
}
