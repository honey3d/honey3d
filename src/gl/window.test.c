#include <stdlib.h>
#include <lua.h>
#include <honeysuckle.h>
#include "test/honey-test.h"

#include "window.c"


void create_window_data_works()
{
	lua_State *L = luaL_newstate();
	struct window_data *wdata = create_window_data(L);

	lily_assert_ptr_equal(L, wdata->L);
	lily_assert_int_equal(wdata->framebuffer_size_callback, LUA_NOREF);
	lua_close(L);
	free(wdata);
}


void suite_window()
{
	lily_run_test(create_window_data_works);
}
