#include <lua.h>
#include <lauxlib.h>
#include <miniaudio.h>
#include "util/util.h"
#include "audio.h"


#define X(name, mt) const char *mt = name;
AUDIO_METATABLES
#undef X


void setup_audio(lua_State *L, int honey_tbl)
{
	#define X(n, mt) luaL_newmetatable(L, mt); lua_pop(L, 1);
	AUDIO_METATABLES
	#undef X

	struct honey_tbl_t audio[] = {
		#define X(name, func) H_FUNC(name, func),
		AUDIO_FUNCTIONS
		#undef X

		/* ma_result values */
		H_ENUM(MA_SUCCESS),

		H_END,
	};
	create_table(L, audio);
	lua_setfield(L, honey_tbl, "ma");
}
