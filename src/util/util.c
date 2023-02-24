#include <lua.h>
#include <lauxlib.h>
#include "util.h"

void create_table(lua_State *L, struct honey_tbl_t *tbl)
{
	lua_createtable(L, 0, 0);
	int t = lua_gettop(L);

	for (struct honey_tbl_t *pair = tbl; pair->key != NULL; pair += 1) {
		if (pair->type == LUA_TNUMBER) {
			lua_pushinteger(L, pair->value.integer);
			lua_setfield(L, t, pair->key);
		}
		else if (pair->type == LUA_TFUNCTION) {
			lua_pushcfunction(L, pair->value.function);
			lua_setfield(L, t, pair->key);
		}
		else {
			/* bad type, ignore */
		}
	}
}

void append_table(lua_State *L, int tbl_a, int tbl_b)
{
	lua_pushnil(L);
	while(lua_next(L, tbl_b) != 0) {
		lua_pushvalue(L, -2); // key
		lua_pushvalue(L, -2); // value
		lua_settable(L, tbl_a);
		lua_pop(L, 1);
	}
}


const char *canary_tname = "honey.canary";

int gc_canary(lua_State *L);
int gc_canary_collect(lua_State *L);

void setup_util(lua_State *L, int honey_tbl)
{
	/* create gc_canary metatable */
	luaL_newmetatable(L, canary_tname);
	lua_pushcfunction(L, gc_canary_collect);
	lua_setfield(L, -2, "__gc");
	lua_pop(L, 1);

	struct honey_tbl_t util[] = {
		H_FUNC("gc_canary", gc_canary),
		H_END,
	};
	create_table(L, util);
	lua_setfield(L, honey_tbl, "util");
}


int gc_canary(lua_State *L)
{
	luaL_checktype(L, 1, LUA_TFUNCTION);
	int ref = luaL_ref(L, LUA_REGISTRYINDEX);
	int *canary = lua_newuserdata(L, sizeof(int));
	*canary = ref;
	luaL_getmetatable(L, canary_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int gc_canary_collect(lua_State *L)
{
	int *canary = luaL_checkudata(L, 1, canary_tname);
	lua_rawgeti(L, LUA_REGISTRYINDEX, *canary);
	lua_call(L, 0, 0);
	luaL_unref(L, LUA_REGISTRYINDEX, *canary);
	return 0;
}


static int h_traceback(lua_State *L)
{
   if (!lua_isstring(L, 1))
      /* 'message' is not a string, keep intact */
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


int h_call(lua_State *L, int nargs, int nret)
{
   int traceback_pos = lua_gettop(L) - nargs;
   lua_pushcfunction(L, h_traceback);
   lua_insert(L, traceback_pos);

   int result = lua_pcall(L, nargs, nret, traceback_pos);
   lua_remove(L, traceback_pos);
   return result;
}
