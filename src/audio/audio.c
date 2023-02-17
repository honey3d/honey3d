#include <lua.h>
#include <lauxlib.h>

#define STB_VORBIS_HEADER_ONLY
#include <stb_vorbis.c>
#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>
#undef STB_VORBIS_HEADER_ONLY
#include <stb_vorbis.c>

/* stb_vorbis defines this for some reason? */
#undef L

#include "util/util.h"
#include "audio.h"


const char *audio_engine_tname = "audio.Engine";


void setup_audio(lua_State *L, int honey_tbl)
{
	luaL_newmetatable(L, audio_engine_tname); lua_pop(L, 1);

	struct honey_tbl_t audio[] = {
		#define X(name, func) H_FUNC(name, func),
		AUDIO_FUNCTIONS
		#undef X

		/* ma_result values */
		H_ENUM(MA_SUCCESS),

		H_END,
	};
	create_table(L, audio);
	lua_setfield(L, honey_tbl, "audio");
}


int audio_engine_init(lua_State *L)
{
	ma_engine *engine = lua_newuserdata(L, sizeof(ma_engine));
	ma_result result = ma_engine_init(NULL, engine);
	if (result != MA_SUCCESS)
		luaL_error(L, "failed to initialize audio engine: %d", result);

	luaL_getmetatable(L, audio_engine_tname);
	lua_setmetatable(L, -2);
	return 1;
}


int audio_engine_uninit(lua_State *L)
{
	ma_engine *engine = luaL_checkudata(L, 1, audio_engine_tname);
	ma_engine_uninit(engine);
	return 0;
}


int audio_engine_play_sound(lua_State *L)
{
	ma_engine *engine = luaL_checkudata(L, 1, audio_engine_tname);
	char *filename = luaL_checkstring(L, 2);
	ma_engine_play_sound(engine, filename, NULL);
	return 0;
}
