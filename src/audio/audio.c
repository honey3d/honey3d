#include <lua.h>
#include <honeysuckle.h>

#define STB_VORBIS_HEADER_ONLY
#include <stb_vorbis.c>
#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>
#undef STB_VORBIS_HEADER_ONLY
#include <stb_vorbis.c>

/* stb_vorbis defines this for some reason? */
#undef L

#include "audio.h"


int audio_engine_init(lua_State *L);
int audio_engine_uninit(lua_State *L);
int audio_engine_play_sound(lua_State *L);


void setup_audio(lua_State *L, int honey_tbl)
{
	hs_create_table(L,
		hs_str_cfunc("engine_init", audio_engine_init),
		hs_str_cfunc("engine_uninit", audio_engine_uninit),
		hs_str_cfunc("engine_play_sound", audio_engine_play_sound),

		/* ma_result values */
		hs_str_int("MA_SUCCESS", MA_SUCCESS),
	);
	lua_setfield(L, honey_tbl, "audio");
}


int audio_engine_init(lua_State *L)
{
	ma_engine *engine = malloc(sizeof(ma_engine));
	if (engine == NULL)
		hs_throw_error(L, "failed to allocate memory for engine");
	
	ma_result result = ma_engine_init(NULL, engine);
	if (result != MA_SUCCESS)
		hs_throw_error(L, "failed to initialize audio engine: %d", result);
	
	lua_pushlightuserdata(L, engine);
	return 1;
}


int audio_engine_uninit(lua_State *L)
{
	ma_engine *engine;
	void *engine_ptr;
	hs_parse_args(L, hs_light(engine_ptr));
	engine = engine_ptr;

	ma_engine_uninit(engine);
	free(engine);
	return 0;
}


int audio_engine_play_sound(lua_State *L)
{
	ma_engine *engine;
	void *engine_ptr;
	char *filename;
	hs_parse_args(L, hs_light(engine_ptr), hs_str(filename));
	engine = engine_ptr;

	ma_engine_play_sound(engine, filename, NULL);
	return 0;
}
