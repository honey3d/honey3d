#include <lua.h>
#include <lauxlib.h>
#include <nanovg.h>
#include <nanovg_gl.h>
#include "util/util.h"
#include "nvg.h"


const char *nvg_ctx_tname = "nvg.Context";
const char *nvg_color_tname = "nvg.Color";
const char *nvg_image_tname = "nvg.Image";
const char *nvg_paint_tname = "nvg.Paint";


void setup_nvg(lua_State *L, int honey_tbl)
{
	luaL_newmetatable(L, nvg_ctx_tname); lua_pop(L, 1);
	luaL_newmetatable(L, nvg_color_tname); lua_pop(L, 1);

	struct honey_tbl_t nvg[] = {
		#define X(name, func) H_FUNC(name, func),
		NVG_FUNCTIONS
		#undef X
		H_END,
	};
	create_table(L, nvg);

	lua_setfield(L, honey_tbl, "nvg");
}
