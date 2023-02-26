#include <lua.h>
#include <lauxlib.h>
#include <miniaudio.h>
#include "audio.h"


#define GET_PARAM(param) \
do { \
	lua_getfield(L, conf_tbl, #param); \
	if (!lua_isnil(L, -1)) { \
		config.param = lua_tointeger(L, -1); \
	} \
	lua_pop(L, 1); \
} while (0)

int ma_engine_init_bind(lua_State *L)
{
	luaL_checktype(L, 1, LUA_TTABLE);
	const int conf_tbl = 1;
	ma_engine_config config = ma_engine_config_init();
	GET_PARAM(listenerCount);
	GET_PARAM(sampleRate);
	GET_PARAM(gainSmoothTimeInFrames);
	GET_PARAM(gainSmoothTimeInMilliseconds);

	ma_engine *engine = lua_newuserdata(L, sizeof(ma_engine));
	int engine_index = lua_gettop(L);
	ma_result result = ma_engine_init(&config, engine);
	lua_pushinteger(L, result);
	lua_pushvalue(L, engine_index);
	lua_remove(L, engine_index);
	return 2;
}


int ma_engine_uninit_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_engine_uninit(pEngine);
	return 0;
}


int ma_engine_get_endpoint_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_node* bind_result = ma_engine_get_endpoint(pEngine);
	ma_push_node(L, bind_result);
	return 1;
}


int ma_engine_get_time_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint64 bind_result = ma_engine_get_time(pEngine);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_engine_set_time_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint64 globalTime = luaL_checkinteger(L, 2);
	ma_result bind_result = ma_engine_set_time(pEngine, globalTime);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_engine_get_channels_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint32 bind_result = ma_engine_get_channels(pEngine);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_engine_get_sample_rate_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint32 bind_result = ma_engine_get_sample_rate(pEngine);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_engine_start_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_result bind_result = ma_engine_start(pEngine);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_engine_stop_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_result bind_result = ma_engine_stop(pEngine);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_engine_set_volume_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	float volume = luaL_checknumber(L, 2);
	ma_result bind_result = ma_engine_set_volume(pEngine, volume);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_engine_set_gain_db_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	float gainDB = luaL_checknumber(L, 2);
	ma_result bind_result = ma_engine_set_gain_db(pEngine, gainDB);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_engine_get_listener_count_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint32 bind_result = ma_engine_get_listener_count(pEngine);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_engine_find_closest_listener_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	float absolutePosX = luaL_checknumber(L, 2);
	float absolutePosY = luaL_checknumber(L, 3);
	float absolutePosZ = luaL_checknumber(L, 4);
	ma_uint32 bind_result = ma_engine_find_closest_listener(pEngine, absolutePosX, absolutePosY, absolutePosZ);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_engine_listener_set_position_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint32 listenerIndex = luaL_checkinteger(L, 2);
	float x = luaL_checknumber(L, 3);
	float y = luaL_checknumber(L, 4);
	float z = luaL_checknumber(L, 5);
	ma_engine_listener_set_position(pEngine, listenerIndex, x, y, z);
	return 0;
}


int ma_engine_listener_get_position_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint32 listenerIndex = luaL_checkinteger(L, 2);
	ma_vec3f bind_result = ma_engine_listener_get_position(pEngine, listenerIndex);
	lua_pushnumber(L, bind_result.x);
	lua_pushnumber(L, bind_result.y);
	lua_pushnumber(L, bind_result.z);
	return 3;
}


int ma_engine_listener_set_direction_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint32 listenerIndex = luaL_checkinteger(L, 2);
	float x = luaL_checknumber(L, 3);
	float y = luaL_checknumber(L, 4);
	float z = luaL_checknumber(L, 5);
	ma_engine_listener_set_direction(pEngine, listenerIndex, x, y, z);
	return 0;
}


int ma_engine_listener_get_direction_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint32 listenerIndex = luaL_checkinteger(L, 2);
	ma_vec3f bind_result = ma_engine_listener_get_direction(pEngine, listenerIndex);
	lua_pushnumber(L, bind_result.x);
	lua_pushnumber(L, bind_result.y);
	lua_pushnumber(L, bind_result.z);
	return 3;
}


int ma_engine_listener_set_velocity_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint32 listenerIndex = luaL_checkinteger(L, 2);
	float x = luaL_checknumber(L, 3);
	float y = luaL_checknumber(L, 4);
	float z = luaL_checknumber(L, 5);
	ma_engine_listener_set_velocity(pEngine, listenerIndex, x, y, z);
	return 0;
}


int ma_engine_listener_get_velocity_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint32 listenerIndex = luaL_checkinteger(L, 2);
	ma_vec3f bind_result = ma_engine_listener_get_velocity(pEngine, listenerIndex);
	lua_pushnumber(L, bind_result.x);
	lua_pushnumber(L, bind_result.y);
	lua_pushnumber(L, bind_result.z);
	return 3;
}


int ma_engine_listener_set_cone_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint32 listenerIndex = luaL_checkinteger(L, 2);
	float innerAngleInRadians = luaL_checknumber(L, 3);
	float outerAngleInRadians = luaL_checknumber(L, 4);
	float outerGain = luaL_checknumber(L, 5);
	ma_engine_listener_set_cone(pEngine, listenerIndex, innerAngleInRadians, outerAngleInRadians, outerGain);
	return 0;
}


int ma_engine_listener_get_cone_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint32 listenerIndex = luaL_checkinteger(L, 2);
	float innerAngleInRadians, outerAngleInRadians, outerGain;
	ma_engine_listener_get_cone(pEngine, listenerIndex, &innerAngleInRadians, &outerAngleInRadians, &outerGain);
	lua_pushnumber(L, innerAngleInRadians);
	lua_pushnumber(L, outerAngleInRadians);
	lua_pushnumber(L, outerGain);
	return 3;
}


int ma_engine_listener_set_world_up_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint32 listenerIndex = luaL_checkinteger(L, 2);
	float x = luaL_checknumber(L, 3);
	float y = luaL_checknumber(L, 4);
	float z = luaL_checknumber(L, 5);
	ma_engine_listener_set_world_up(pEngine, listenerIndex, x, y, z);
	return 0;
}


int ma_engine_listener_get_world_up_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint32 listenerIndex = luaL_checkinteger(L, 2);
	ma_vec3f bind_result = ma_engine_listener_get_world_up(pEngine, listenerIndex);
	lua_pushnumber(L, bind_result.x);
	lua_pushnumber(L, bind_result.y);
	lua_pushnumber(L, bind_result.z);
	return 3;
}


int ma_engine_listener_set_enabled_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint32 listenerIndex = luaL_checkinteger(L, 2);
	ma_bool32 isEnabled = luaL_checkinteger(L, 3);
	ma_engine_listener_set_enabled(pEngine, listenerIndex, isEnabled);
	return 0;
}


int ma_engine_listener_is_enabled_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	ma_uint32 listenerIndex = luaL_checkinteger(L, 2);
	ma_bool32 bind_result = ma_engine_listener_is_enabled(pEngine, listenerIndex);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_engine_play_sound_ex_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	const char * pFilePath = luaL_checkstring(L, 2);
	ma_node * pNode = luaL_checkudata(L, 3, ma_node_tname);
	ma_uint32 nodeInputBusIndex = luaL_checkinteger(L, 4);
	ma_result bind_result = ma_engine_play_sound_ex(pEngine, pFilePath, pNode, nodeInputBusIndex);
	lua_pushinteger(L, bind_result);
	return 1;
}


int ma_engine_play_sound_bind(lua_State *L)
{
	ma_engine * pEngine = luaL_checkudata(L, 1, ma_engine_tname);
	const char * pFilePath = luaL_checkstring(L, 2);
	ma_sound_group * pGroup = to_sound_group(L, 3);
	ma_result bind_result = ma_engine_play_sound(pEngine, pFilePath, pGroup);
	lua_pushinteger(L, bind_result);
	return 1;
}
