#ifndef HONEY_AUDIO_H
#define HONEY_AUDIO_H

#include <lua.h>

extern const char *audio_engine_tname;

#define AUDIO_FUNCTIONS \
	X("engine_init", audio_engine_init) \
	X("engine_uninit", audio_engine_uninit) \
	X("engine_play_sound", audio_engine_play_sound) \

#define X(name, func) int func(lua_State *L);
AUDIO_FUNCTIONS
#undef X

#endif
