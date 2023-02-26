#include <lua.h>
#include <lauxlib.h>
#include <miniaudio.h>
#include "audio.h"


ma_sound_group * to_sound_group(lua_State *L, int index)
{
	if (lua_isnil(L, index)) {
		return NULL;
	}
	return luaL_checkudata(L, index, ma_sound_group_tname);
}


int ma_sound_group_init_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint32 flags = luaL_checkinteger(L, 2);
	ma_sound_group * pParentGroup = to_sound_group(L, 3);
	ma_sound_group * pGroup = lua_newuserdata(L, sizeof(ma_sound_group));
	int gindex = lua_gettop(L);
	ma_result bind_result = ma_sound_group_init(pEngine, flags, pParentGroup, pGroup);
	lua_pushinteger(L, bind_result);
	lua_pushvalue(L, gindex);
	lua_remove(L, gindex);
	luaL_getmetatable(L, ma_sound_group_tname);
	lua_setmetatable(L, -2);
	return 2;
}


int ma_sound_group_uninit_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_sound_group_uninit(pGroup);
	return 0;
}


int ma_sound_group_start_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_result bind_result = ma_sound_group_start(pGroup);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_group_stop_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_result bind_result = ma_sound_group_stop(pGroup);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_group_set_volume_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float volume = luaL_checknumber(L, 2);
	ma_sound_group_set_volume(pGroup, volume);
	return 0;
}


int ma_sound_group_get_volume_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float bind_result = ma_sound_group_get_volume(pGroup);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_group_set_pan_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float pan = luaL_checknumber(L, 2);
	ma_sound_group_set_pan(pGroup, pan);
	return 0;
}


int ma_sound_group_get_pan_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float bind_result = ma_sound_group_get_pan(pGroup);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_group_set_pan_mode_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_pan_mode panMode = luaL_checkinteger(L, 2);
	ma_sound_group_set_pan_mode(pGroup, panMode);
	return 0;
}


int ma_sound_group_get_pan_mode_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_pan_mode bind_result = ma_sound_group_get_pan_mode(pGroup);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_group_set_pitch_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float pitch = luaL_checknumber(L, 2);
	ma_sound_group_set_pitch(pGroup, pitch);
	return 0;
}


int ma_sound_group_get_pitch_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float bind_result = ma_sound_group_get_pitch(pGroup);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_group_set_spatialization_enabled_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_bool32 enabled = lua_toboolean(L, 2);
	ma_sound_group_set_spatialization_enabled(pGroup, enabled);
	return 0;
}


int ma_sound_group_is_spatialization_enabled_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_bool32 bind_result = ma_sound_group_is_spatialization_enabled(pGroup);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_group_set_pinned_listener_index_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_uint32 listenerIndex = luaL_checkinteger(L, 2);
	ma_sound_group_set_pinned_listener_index(pGroup, listenerIndex);
	return 0;
}


int ma_sound_group_get_pinned_listener_index_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_uint32 bind_result = ma_sound_group_get_pinned_listener_index(pGroup);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_group_get_listener_index_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_uint32 bind_result = ma_sound_group_get_listener_index(pGroup);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_group_get_direction_to_listener_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_vec3f bind_result = ma_sound_group_get_direction_to_listener(pGroup);
	lua_pushnumber(L, bind_result.x);
	lua_pushnumber(L, bind_result.y);
	lua_pushnumber(L, bind_result.z);
	return 3;
}


int ma_sound_group_set_position_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float z = luaL_checknumber(L, 4);
	ma_sound_group_set_position(pGroup, x, y, z);
	return 0;
}


int ma_sound_group_get_position_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_vec3f bind_result = ma_sound_group_get_position(pGroup);
	lua_pushnumber(L, bind_result.x);
	lua_pushnumber(L, bind_result.y);
	lua_pushnumber(L, bind_result.z);
	return 3;
}


int ma_sound_group_set_direction_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float z = luaL_checknumber(L, 4);
	ma_sound_group_set_direction(pGroup, x, y, z);
	return 0;
}


int ma_sound_group_get_direction_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_vec3f bind_result = ma_sound_group_get_direction(pGroup);
	lua_pushnumber(L, bind_result.x);
	lua_pushnumber(L, bind_result.y);
	lua_pushnumber(L, bind_result.z);
	return 3;
}


int ma_sound_group_set_velocity_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float z = luaL_checknumber(L, 4);
	ma_sound_group_set_velocity(pGroup, x, y, z);
	return 0;
}


int ma_sound_group_get_velocity_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_vec3f bind_result = ma_sound_group_get_velocity(pGroup);
	lua_pushnumber(L, bind_result.x);
	lua_pushnumber(L, bind_result.y);
	lua_pushnumber(L, bind_result.z);
	return 3;
}


int ma_sound_group_set_attenuation_model_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_attenuation_model attenuationModel = luaL_checkinteger(L, 2);
	ma_sound_group_set_attenuation_model(pGroup, attenuationModel);
	return 0;
}


int ma_sound_group_get_attenuation_model_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_attenuation_model bind_result = ma_sound_group_get_attenuation_model(pGroup);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_group_set_positioning_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_positioning positioning = luaL_checkinteger(L, 2);
	ma_sound_group_set_positioning(pGroup, positioning);
	return 0;
}


int ma_sound_group_get_positioning_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_positioning bind_result = ma_sound_group_get_positioning(pGroup);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_group_set_rolloff_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float rolloff = luaL_checknumber(L, 2);
	ma_sound_group_set_rolloff(pGroup, rolloff);
	return 0;
}


int ma_sound_group_get_rolloff_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float bind_result = ma_sound_group_get_rolloff(pGroup);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_group_set_min_gain_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float minGain = luaL_checknumber(L, 2);
	ma_sound_group_set_min_gain(pGroup, minGain);
	return 0;
}


int ma_sound_group_get_min_gain_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float bind_result = ma_sound_group_get_min_gain(pGroup);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_group_set_max_gain_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float maxGain = luaL_checknumber(L, 2);
	ma_sound_group_set_max_gain(pGroup, maxGain);
	return 0;
}


int ma_sound_group_get_max_gain_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float bind_result = ma_sound_group_get_max_gain(pGroup);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_group_set_min_distance_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float minDistance = luaL_checknumber(L, 2);
	ma_sound_group_set_min_distance(pGroup, minDistance);
	return 0;
}


int ma_sound_group_get_min_distance_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float bind_result = ma_sound_group_get_min_distance(pGroup);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_group_set_max_distance_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float maxDistance = luaL_checknumber(L, 2);
	ma_sound_group_set_max_distance(pGroup, maxDistance);
	return 0;
}


int ma_sound_group_get_max_distance_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float bind_result = ma_sound_group_get_max_distance(pGroup);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_group_set_cone_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float innerAngleInRadians = luaL_checknumber(L, 2);
	float outerAngleInRadians = luaL_checknumber(L, 3);
	float outerGain = luaL_checknumber(L, 4);
	ma_sound_group_set_cone(pGroup, innerAngleInRadians, outerAngleInRadians, outerGain);
	return 0;
}


int ma_sound_group_get_cone_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float InnerAngleInRadians, OuterAngleInRadians, OuterGain;
	ma_sound_group_get_cone(pGroup, &InnerAngleInRadians, &OuterAngleInRadians, &OuterGain);
	lua_pushnumber(L, InnerAngleInRadians);
	lua_pushnumber(L, OuterAngleInRadians);
	lua_pushnumber(L, OuterGain);
	return 3;
}


int ma_sound_group_set_doppler_factor_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float dopplerFactor = luaL_checknumber(L, 2);
	ma_sound_group_set_doppler_factor(pGroup, dopplerFactor);
	return 0;
}


int ma_sound_group_get_doppler_factor_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float bind_result = ma_sound_group_get_doppler_factor(pGroup);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_group_set_directional_attenuation_factor_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float directionalAttenuationFactor = luaL_checknumber(L, 2);
	ma_sound_group_set_directional_attenuation_factor(pGroup, directionalAttenuationFactor);
	return 0;
}


int ma_sound_group_get_directional_attenuation_factor_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float bind_result = ma_sound_group_get_directional_attenuation_factor(pGroup);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_group_set_fade_in_pcm_frames_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float volumeBeg = luaL_checknumber(L, 2);
	float volumeEnd = luaL_checknumber(L, 3);
	ma_uint64 fadeLengthInFrames = luaL_checkinteger(L, 4);
	ma_sound_group_set_fade_in_pcm_frames(pGroup, volumeBeg, volumeEnd, fadeLengthInFrames);
	return 0;
}


int ma_sound_group_set_fade_in_milliseconds_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float volumeBeg = luaL_checknumber(L, 2);
	float volumeEnd = luaL_checknumber(L, 3);
	ma_uint64 fadeLengthInMilliseconds = luaL_checkinteger(L, 4);
	ma_sound_group_set_fade_in_milliseconds(pGroup, volumeBeg, volumeEnd, fadeLengthInMilliseconds);
	return 0;
}


int ma_sound_group_get_current_fade_volume_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	float bind_result = ma_sound_group_get_current_fade_volume(pGroup);
	lua_pushnumber(L, bind_result);
	return 1;
}


int ma_sound_group_set_start_time_in_pcm_frames_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_uint64 absoluteGlobalTimeInFrames = luaL_checkinteger(L, 2);
	ma_sound_group_set_start_time_in_pcm_frames(pGroup, absoluteGlobalTimeInFrames);
	return 0;
}


int ma_sound_group_set_start_time_in_milliseconds_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_uint64 absoluteGlobalTimeInMilliseconds = luaL_checkinteger(L, 2);
	ma_sound_group_set_start_time_in_milliseconds(pGroup, absoluteGlobalTimeInMilliseconds);
	return 0;
}


int ma_sound_group_set_stop_time_in_pcm_frames_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_uint64 absoluteGlobalTimeInFrames = luaL_checkinteger(L, 2);
	ma_sound_group_set_stop_time_in_pcm_frames(pGroup, absoluteGlobalTimeInFrames);
	return 0;
}


int ma_sound_group_set_stop_time_in_milliseconds_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_uint64 absoluteGlobalTimeInMilliseconds = luaL_checkinteger(L, 2);
	ma_sound_group_set_stop_time_in_milliseconds(pGroup, absoluteGlobalTimeInMilliseconds);
	return 0;
}


int ma_sound_group_is_playing_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_bool32 bind_result = ma_sound_group_is_playing(pGroup);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_sound_group_get_time_in_pcm_frames_bind(lua_State *L)
{
	ma_sound_group * pGroup = luaL_checkudata(L, 1, ma_sound_group_tname);
	ma_uint64 bind_result = ma_sound_group_get_time_in_pcm_frames(pGroup);
	lua_pushinteger(L, bind_result);
	return 1;
}


