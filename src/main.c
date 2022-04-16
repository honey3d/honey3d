#include <stdio.h>
#include <honeysuckle.h>

#include "logging/logging.h"
#include "options/honey_options.h"
#include "gl/honey_gl.h"

static int get_func(lua_State *L, char *name);
static void loop(lua_State *L, int update, int draw);


int main(int argc, char **argv)
{
   /* process command-line options */
   struct honey_options options;
   if (!parse_options(&options, argc, argv))
      return 1;
   if (options.display_help)
      /* help displayed, exit */
      return 0;

   honey_info("options:\n"
	      "  main script: %s\n"
	      "  log level: %s\n",
	      options.main_script,
	      honey_log_level_str(options.log_level));

   /* setup lua environment */
   honey_debug("initialize lua_State\n");
   lua_State *L = luaL_newstate();
   luaL_openlibs(L);

   honey_debug("load honey bindings\n");
   lua_createtable(L, 0, 1);
   int index = lua_gettop(L);

   setup_window(L, index);

   lua_setglobal(L, "honey");

   /* load main script */
   honey_debug("loading '%s'\n", options.main_script);

   if (luaL_loadfile(L, options.main_script) != 0) {
      const char *error = lua_tostring(L, -1);
      honey_fatal("%s\n", error);
      return 1;
   }

   if (hs_call(L, 0, 0) != 0) {
      honey_debug("stack size: %d\n", lua_gettop(L));
      const char *error = lua_tostring(L, -1);
      honey_fatal("error loading main file: %s\n", error);
      goto close; /* sorry */
   }

   /* ensure window exists */
   if (!window.created) {
      lua_getglobal(L, "honey");
      lua_getfield(L, -1, "window");
      lua_getfield(L, -1, "createWindow");
      lua_pushinteger(L, 640);
      lua_pushinteger(L, 480);
      hs_call(L, 2, 0);
      lua_pop(L, 2);
   }

   /* load main callback functions */
   int update = get_func(L, "update");
   if (update) honey_info("honey.update: %s\n", lua_tostring(L, update));
   else honey_info("honey.update: (nil)\n");
   int draw   = get_func(L, "draw");
   if (draw) honey_info("honey.draw: %s\n", lua_tostring(L, draw));
   else honey_info("honey.draw: (nil)\n");

   /* main loop */
   while(!glfwWindowShouldClose(window.window))
      loop(L, update, draw);

 close:
   lua_close(L);
   glfwTerminate();
   
   return 0;
}


static int get_func(lua_State *L, char *name)
{
   lua_getglobal(L, "honey");
   int index = lua_gettop(L);
   lua_getfield(L, -1, name);

   if (lua_isfunction(L, -1)) {
      lua_remove(L, index);
      return lua_gettop(L);
   }
   else {
      lua_pop(L, 2);
      return 0;
   }
}
			

static void loop(lua_State *L, int update, int draw)
{
   static float prev_time = 0;
   static float draw_time = 0;

   float current_time = (float) glfwGetTime();
   float dt = current_time - prev_time;
   prev_time = current_time;

   draw_time += dt;
   glfwPollEvents();

   if (update) {
      lua_pushvalue(L, update);
      lua_pushnumber(L, dt);
      if (!hs_call(L, 1, 0)) {
	 /* error! */
	 const char *error = lua_tostring(L, -1);
	 honey_fatal("unhandled error: %s\n", error);
	 glfwSetWindowShouldClose(window.window, 1);
      }
   }

   /* cap framerate at 60fps */
   if (draw && draw_time > 0.016) {
      draw_time -= 0.016;
      lua_pushvalue(L, draw);
      if(!hs_call(L, 0, 0)) {
	 /* error! */
	 const char *error = lua_tostring(L, -1);
	 honey_fatal("unhandled error: %s\n", error);
	 glfwSetWindowShouldClose(window.window, 1);
      }
   }
}
   
