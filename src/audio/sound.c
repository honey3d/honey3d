#include <lua.h>
#include <lauxlib.h>
#include <miniaudio.h>
#include "audio.h"


void push_sound(lua_State *L, ma_sound s) {
	ma_sound *su = lua_newuserdata(L, sizeof(ma_sound));
	*su = s;
	luaL_getmetatable(L, ma_sound_tname);
	lua_setmetatable(L, -2);
}


int ma_sound_init_from_file_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	const char * pFilePath = luaL_checkstring(L, 2);
	ma_uint32 flags = luaL_checkinteger(L, 3);
	ma_sound_group * pGroup = to_sound_group(L, 4);

	ma_sound *sound = lua_newuserdata(L, sizeof(ma_sound));
	int sound_index = lua_gettop(L);
	ma_result bind_result = ma_sound_init_from_file(pEngine, pFilePath, flags, pGroup, NULL, sound);
	lua_pushinteger(L, bind_result);
	lua_pushvalue(L, sound_index);
	lua_remove(L, sound_index);
	luaL_getmetatable(L, ma_sound_tname);
	lua_setmetatable(L, -2);
	return 2;
}


int ma_sound_init_copy_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_sound * pExistingSound = luaL_checkudata(L, 2, ma_sound_tname);
	ma_uint32 flags = luaL_checkinteger(L, 3);
	ma_sound_group * pGroup = to_sound_group(L, 4);
	ma_sound *sound = lua_newuserdata(L, sizeof(ma_sound));
	int sound_index = lua_gettop(L);
	ma_result bind_result = ma_sound_init_copy(pEngine, pExistingSound, flags, pGroup, sound);
	lua_pushinteger(L, bind_result);
	lua_pushvalue(L, sound_index);
	lua_remove(L, sound_index);
	luaL_getmetatable(L, ma_sound_tname);
	lua_setmetatable(L, -2);
	return 2;
}


int ma_sound_uninit_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_sound_uninit(pSound);
	return 0;
}


int ma_sound_start_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_result bind_result = ma_sound_start(pSound);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_stop_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_result bind_result = ma_sound_stop(pSound);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_set_volume_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float volume = luaL_checknumber(L, 2);
	ma_sound_set_volume(pSound, volume);
	return 0;
}


int ma_sound_get_volume_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float bind_result = ma_sound_get_volume(pSound);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_set_pan_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float pan = luaL_checknumber(L, 2);
	ma_sound_set_pan(pSound, pan);
	return 0;
}


int ma_sound_get_pan_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float bind_result = ma_sound_get_pan(pSound);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_set_pan_mode_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_pan_mode panMode = luaL_checkinteger(L, 2);
	ma_sound_set_pan_mode(pSound, panMode);
	return 0;
}


int ma_sound_get_pan_mode_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_pan_mode bind_result = ma_sound_get_pan_mode(pSound);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_set_pitch_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float pitch = luaL_checknumber(L, 2);
	ma_sound_set_pitch(pSound, pitch);
	return 0;
}


int ma_sound_get_pitch_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float bind_result = ma_sound_get_pitch(pSound);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_set_spatialization_enabled_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_bool32 enabled = lua_toboolean(L, 2);
	ma_sound_set_spatialization_enabled(pSound, enabled);
	return 0;
}


int ma_sound_is_spatialization_enabled_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_bool32 bind_result = ma_sound_is_spatialization_enabled(pSound);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_set_pinned_listener_index_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_uint32 listenerIndex = luaL_checkinteger(L, 2);
	ma_sound_set_pinned_listener_index(pSound, listenerIndex);
	return 0;
}


int ma_sound_get_pinned_listener_index_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_uint32 bind_result = ma_sound_get_pinned_listener_index(pSound);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_get_listener_index_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_uint32 bind_result = ma_sound_get_listener_index(pSound);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_get_direction_to_listener_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_vec3f bind_result = ma_sound_get_direction_to_listener(pSound);
	lua_pushinteger(L, bind_result.x);
	lua_pushinteger(L, bind_result.y);
	lua_pushinteger(L, bind_result.z);
	return 3;
}


int ma_sound_set_position_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float z = luaL_checknumber(L, 4);
	ma_sound_set_position(pSound, x, y, z);
	return 0;
}


int ma_sound_get_position_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_vec3f bind_result = ma_sound_get_position(pSound);
	lua_pushinteger(L, bind_result.x);
	lua_pushinteger(L, bind_result.y);
	lua_pushinteger(L, bind_result.z);
	return 3;
}


int ma_sound_set_direction_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float z = luaL_checknumber(L, 4);
	ma_sound_set_direction(pSound, x, y, z);
	return 0;
}


int ma_sound_get_direction_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_vec3f bind_result = ma_sound_get_direction(pSound);
	lua_pushinteger(L, bind_result.x);
	lua_pushinteger(L, bind_result.y);
	lua_pushinteger(L, bind_result.z);
	return 3;
}


int ma_sound_set_velocity_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float z = luaL_checknumber(L, 4);
	ma_sound_set_velocity(pSound, x, y, z);
	return 0;
}


int ma_sound_get_velocity_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_vec3f bind_result = ma_sound_get_velocity(pSound);
	lua_pushinteger(L, bind_result.x);
	lua_pushinteger(L, bind_result.y);
	lua_pushinteger(L, bind_result.z);
	return 3;
}


int ma_sound_set_attenuation_model_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_attenuation_model attenuationModel = luaL_checkinteger(L, 2);
	ma_sound_set_attenuation_model(pSound, attenuationModel);
	return 0;
}


int ma_sound_get_attenuation_model_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_attenuation_model bind_result = ma_sound_get_attenuation_model(pSound);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_set_positioning_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_positioning positioning = luaL_checkinteger(L, 2);
	ma_sound_set_positioning(pSound, positioning);
	return 0;
}


int ma_sound_get_positioning_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_positioning bind_result = ma_sound_get_positioning(pSound);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_set_rolloff_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float rolloff = luaL_checknumber(L, 2);
	ma_sound_set_rolloff(pSound, rolloff);
	return 0;
}


int ma_sound_get_rolloff_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float bind_result = ma_sound_get_rolloff(pSound);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_set_min_gain_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float minGain = luaL_checknumber(L, 2);
	ma_sound_set_min_gain(pSound, minGain);
	return 0;
}


int ma_sound_get_min_gain_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float bind_result = ma_sound_get_min_gain(pSound);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_set_max_gain_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float maxGain = luaL_checknumber(L, 2);
	ma_sound_set_max_gain(pSound, maxGain);
	return 0;
}


int ma_sound_get_max_gain_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float bind_result = ma_sound_get_max_gain(pSound);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_set_min_distance_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float minDistance = luaL_checknumber(L, 2);
	ma_sound_set_min_distance(pSound, minDistance);
	return 0;
}


int ma_sound_get_min_distance_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float bind_result = ma_sound_get_min_distance(pSound);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_set_max_distance_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float maxDistance = luaL_checknumber(L, 2);
	ma_sound_set_max_distance(pSound, maxDistance);
	return 0;
}


int ma_sound_get_max_distance_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float bind_result = ma_sound_get_max_distance(pSound);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_set_cone_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float innerAngleInRadians = luaL_checknumber(L, 2);
	float outerAngleInRadians = luaL_checknumber(L, 3);
	float outerGain = luaL_checknumber(L, 4);
	ma_sound_set_cone(pSound, innerAngleInRadians, outerAngleInRadians, outerGain);
	return 0;
}


int ma_sound_get_cone_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float innerAngleInRadians, outerAngleInRadians, outerGain;
	ma_sound_get_cone(pSound, &innerAngleInRadians, &outerAngleInRadians, &outerGain);
	lua_pushnumber(L, innerAngleInRadians);
	lua_pushnumber(L, outerAngleInRadians);
	lua_pushnumber(L, outerGain);
	return 3;
}


int ma_sound_set_doppler_factor_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float dopplerFactor = luaL_checknumber(L, 2);
	ma_sound_set_doppler_factor(pSound, dopplerFactor);
	return 0;
}


int ma_sound_get_doppler_factor_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float bind_result = ma_sound_get_doppler_factor(pSound);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_set_directional_attenuation_factor_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float directionalAttenuationFactor = luaL_checknumber(L, 2);
	ma_sound_set_directional_attenuation_factor(pSound, directionalAttenuationFactor);
	return 0;
}


int ma_sound_get_directional_attenuation_factor_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float bind_result = ma_sound_get_directional_attenuation_factor(pSound);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_set_fade_in_pcm_frames_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float volumeBeg = luaL_checknumber(L, 2);
	float volumeEnd = luaL_checknumber(L, 3);
	ma_uint64 fadeLengthInFrames = luaL_checkinteger(L, 4);
	ma_sound_set_fade_in_pcm_frames(pSound, volumeBeg, volumeEnd, fadeLengthInFrames);
	return 0;
}


int ma_sound_set_fade_in_milliseconds_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float volumeBeg = luaL_checknumber(L, 2);
	float volumeEnd = luaL_checknumber(L, 3);
	ma_uint64 fadeLengthInMilliseconds = luaL_checkinteger(L, 4);
	ma_sound_set_fade_in_milliseconds(pSound, volumeBeg, volumeEnd, fadeLengthInMilliseconds);
	return 0;
}


int ma_sound_get_current_fade_volume_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float bind_result = ma_sound_get_current_fade_volume(pSound);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_set_start_time_in_pcm_frames_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_uint64 absoluteGlobalTimeInFrames = luaL_checkinteger(L, 2);
	ma_sound_set_start_time_in_pcm_frames(pSound, absoluteGlobalTimeInFrames);
	return 0;
}


int ma_sound_set_start_time_in_milliseconds_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_uint64 absoluteGlobalTimeInMilliseconds = luaL_checkinteger(L, 2);
	ma_sound_set_start_time_in_milliseconds(pSound, absoluteGlobalTimeInMilliseconds);
	return 0;
}


int ma_sound_set_stop_time_in_pcm_frames_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_uint64 absoluteGlobalTimeInFrames = luaL_checkinteger(L, 2);
	ma_sound_set_stop_time_in_pcm_frames(pSound, absoluteGlobalTimeInFrames);
	return 0;
}


int ma_sound_set_stop_time_in_milliseconds_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_uint64 absoluteGlobalTimeInMilliseconds = luaL_checkinteger(L, 2);
	ma_sound_set_stop_time_in_milliseconds(pSound, absoluteGlobalTimeInMilliseconds);
	return 0;
}


int ma_sound_is_playing_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_bool32 bind_result = ma_sound_is_playing(pSound);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_get_time_in_pcm_frames_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_uint64 bind_result = ma_sound_get_time_in_pcm_frames(pSound);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_set_looping_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_bool32 isLooping = luaL_checkinteger(L, 2);
	ma_sound_set_looping(pSound, isLooping);
	return 0;
}


int ma_sound_is_looping_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_bool32 bind_result = ma_sound_is_looping(pSound);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_at_end_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_bool32 bind_result = ma_sound_at_end(pSound);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_seek_to_pcm_frame_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_uint64 frameIndex = luaL_checkinteger(L, 2);
	ma_result bind_result = ma_sound_seek_to_pcm_frame(pSound, frameIndex);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_get_data_format_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_format format;
	ma_uint32 channels;
	ma_uint32 sampleRate;
	ma_channel channelMap;
	size_t channelMapCap = 0;
	ma_result bind_result = ma_sound_get_data_format(pSound, &format, &channels, &sampleRate, &channelMap, channelMapCap);
	lua_pushinteger(L, bind_result);
	lua_pushinteger(L, format);
	lua_pushinteger(L, channels);
	lua_pushinteger(L, sampleRate);
	lua_pushinteger(L, channelMap);
	return 5;
}


int ma_sound_get_cursor_in_pcm_frames_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_uint64 cursor;
	ma_result bind_result = ma_sound_get_cursor_in_pcm_frames(pSound, &cursor);
	lua_pushinteger(L, bind_result);
	lua_pushinteger(L, cursor);
	return 2;
}


int ma_sound_get_length_in_pcm_frames_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	ma_uint64 length;
	ma_result bind_result = ma_sound_get_length_in_pcm_frames(pSound, &length);
	lua_pushinteger(L, bind_result);
	lua_pushinteger(L, length);
	return 2;
}


int ma_sound_get_cursor_in_seconds_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float cursor;
	ma_result bind_result = ma_sound_get_cursor_in_seconds(pSound, &cursor);
	lua_pushinteger(L, bind_result);
	lua_pushnumber(L, cursor);
	return 2;
}


int ma_sound_get_length_in_seconds_bind(lua_State *L)
{
	ma_sound * pSound = luaL_checkudata(L, 1, ma_sound_tname);
	float length;
	ma_result bind_result = ma_sound_get_length_in_seconds(pSound, &length);
	lua_pushinteger(L, bind_result);
	lua_pushnumber(L, length);
	return 2;
}


