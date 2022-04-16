#include <string.h>
#include <stdlib.h>
#include <honeysuckle.h>

struct settings
{
   bool debug;
   int debug_level;
   char *logfile;
} global_settings;

void set_logfile(const char* filename, void *s)
{
   struct settings *settings = (struct settings *) s;
   settings->logfile = malloc(sizeof(char) * strlen(filename));
   strcpy(settings->logfile, filename);
}

int process(lua_State *L)
{
   int table_index;
   hs_parse_args(L, hs_tbl(table_index));
   hs_process_table(L, table_index,
		    hs_process_bool("debug",
				    hs_pt_set_boolean,
				    &(global_settings.debug)),
		    hs_process_int("level",
				   hs_pt_set_integer,
				   &(global_settings.debug_level)),
		    hs_process_str("logfile",
				   set_logfile,
				   &global_settings));
   return 0;
}

int main()
{
   lua_State *L = luaL_newstate();
   luaL_openlibs(L);

   lua_pushcfunction(L, process);
   lua_setglobal(L, "configure");

   global_settings.debug = false;
   global_settings.debug_level = 0;
   global_settings.logfile = "nil";

   printf("settings: [ %d, %d, '%s' ]\n",
	  global_settings.debug,
	  global_settings.debug_level,
	  global_settings.logfile);

   luaL_dostring(L, "configure{debug=true, level=6, logfile='output.log'}");

   printf("settings: [ %d, %d, '%s' ]\n",
	  global_settings.debug,
	  global_settings.debug_level,
	  global_settings.logfile);
   return 0;
}
