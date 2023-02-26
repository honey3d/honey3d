#ifndef HONEY_AUDIO_H
#define HONEY_AUDIO_H

#include <lua.h>
#include <miniaudio.h>


ma_sound_group * to_sound_group(lua_State *L, int index);
void ma_push_node(lua_State *L, ma_node *n);

#define AUDIO_METATABLES \
	X("ma.engine", ma_engine_tname) \
	X("ma.node", ma_node_tname) \
	X("ma.sound", ma_sound_tname) \
	X("ma.sound_group", ma_sound_group_tname) \

#define X(name, mt) extern const char *mt;
AUDIO_METATABLES
#undef X


#define AUDIO_FUNCTIONS \
	/* engine */ \
	X("engine_init", ma_engine_init_bind) \
	X("engine_uninit", ma_engine_uninit_bind) \
	X("engine_get_time", ma_engine_get_time_bind) \
	X("engine_set_time", ma_engine_set_time_bind) \
	X("engine_get_channels", ma_engine_get_channels_bind) \
	X("engine_get_sample_rate", ma_engine_get_sample_rate_bind) \
	X("engine_start", ma_engine_start_bind) \
	X("engine_stop", ma_engine_stop_bind) \
	X("engine_set_volume", ma_engine_set_volume_bind) \
	X("engine_set_gain_db", ma_engine_set_gain_db_bind) \
	X("engine_get_listener_count", ma_engine_get_listener_count_bind) \
	X("engine_find_closest_listener", ma_engine_find_closest_listener_bind) \
	X("engine_listener_set_position", ma_engine_listener_set_position_bind) \
	X("engine_listener_get_position", ma_engine_listener_get_position_bind) \
	X("engine_listener_set_direction", ma_engine_listener_set_direction_bind) \
	X("engine_listener_get_direction", ma_engine_listener_get_direction_bind) \
	X("engine_listener_set_velocity", ma_engine_listener_set_velocity_bind) \
	X("engine_listener_get_velocity", ma_engine_listener_get_velocity_bind) \
	X("engine_listener_set_cone", ma_engine_listener_set_cone_bind) \
	X("engine_listener_get_cone", ma_engine_listener_get_cone_bind) \
	X("engine_listener_set_world_up", ma_engine_listener_set_world_up_bind) \
	X("engine_listener_get_world_up", ma_engine_listener_get_world_up_bind) \
	X("engine_listener_set_enabled", ma_engine_listener_set_enabled_bind) \
	X("engine_listener_is_enabled", ma_engine_listener_is_enabled_bind) \
	X("engine_play_sound_ex", ma_engine_play_sound_ex_bind) \
	X("engine_play_sound", ma_engine_play_sound_bind) \
\
	/* sound */ \
	X("sound_init_from_file", ma_sound_init_from_file_bind) \
	X("sound_init_copy", ma_sound_init_copy_bind) \
	X("sound_uninit", ma_sound_uninit_bind) \
	X("sound_start", ma_sound_start_bind) \
	X("sound_stop", ma_sound_stop_bind) \
	X("sound_set_volume", ma_sound_set_volume_bind) \
	X("sound_get_volume", ma_sound_get_volume_bind) \
	X("sound_set_pan", ma_sound_set_pan_bind) \
	X("sound_get_pan", ma_sound_get_pan_bind) \
	X("sound_set_pan_mode", ma_sound_set_pan_mode_bind) \
	X("sound_get_pan_mode", ma_sound_get_pan_mode_bind) \
	X("sound_set_pitch", ma_sound_set_pitch_bind) \
	X("sound_get_pitch", ma_sound_get_pitch_bind) \
	X("sound_set_spatialization_enabled", ma_sound_set_spatialization_enabled_bind) \
	X("sound_is_spatialization_enabled", ma_sound_is_spatialization_enabled_bind) \
	X("sound_set_pinned_listener_index", ma_sound_set_pinned_listener_index_bind) \
	X("sound_get_pinned_listener_index", ma_sound_get_pinned_listener_index_bind) \
	X("sound_get_listener_index", ma_sound_get_listener_index_bind) \
	X("sound_get_direction_to_listener", ma_sound_get_direction_to_listener_bind) \
	X("sound_set_position", ma_sound_set_position_bind) \
	X("sound_get_position", ma_sound_get_position_bind) \
	X("sound_set_direction", ma_sound_set_direction_bind) \
	X("sound_get_direction", ma_sound_get_direction_bind) \
	X("sound_set_velocity", ma_sound_set_velocity_bind) \
	X("sound_get_velocity", ma_sound_get_velocity_bind) \
	X("sound_set_attenuation_model", ma_sound_set_attenuation_model_bind) \
	X("sound_get_attenuation_model", ma_sound_get_attenuation_model_bind) \
	X("sound_set_positioning", ma_sound_set_positioning_bind) \
	X("sound_get_positioning", ma_sound_get_positioning_bind) \
	X("sound_set_rolloff", ma_sound_set_rolloff_bind) \
	X("sound_get_rolloff", ma_sound_get_rolloff_bind) \
	X("sound_set_min_gain", ma_sound_set_min_gain_bind) \
	X("sound_get_min_gain", ma_sound_get_min_gain_bind) \
	X("sound_set_max_gain", ma_sound_set_max_gain_bind) \
	X("sound_get_max_gain", ma_sound_get_max_gain_bind) \
	X("sound_set_min_distance", ma_sound_set_min_distance_bind) \
	X("sound_get_min_distance", ma_sound_get_min_distance_bind) \
	X("sound_set_max_distance", ma_sound_set_max_distance_bind) \
	X("sound_get_max_distance", ma_sound_get_max_distance_bind) \
	X("sound_set_cone", ma_sound_set_cone_bind) \
	X("sound_get_cone", ma_sound_get_cone_bind) \
	X("sound_set_doppler_factor", ma_sound_set_doppler_factor_bind) \
	X("sound_get_doppler_factor", ma_sound_get_doppler_factor_bind) \
	X("sound_set_directional_attenuation_factor", ma_sound_set_directional_attenuation_factor_bind) \
	X("sound_get_directional_attenuation_factor", ma_sound_get_directional_attenuation_factor_bind) \
	X("sound_set_fade_in_pcm_frames", ma_sound_set_fade_in_pcm_frames_bind) \
	X("sound_set_fade_in_milliseconds", ma_sound_set_fade_in_milliseconds_bind) \
	X("sound_get_current_fade_volume", ma_sound_get_current_fade_volume_bind) \
	X("sound_set_start_time_in_pcm_frames", ma_sound_set_start_time_in_pcm_frames_bind) \
	X("sound_set_start_time_in_milliseconds", ma_sound_set_start_time_in_milliseconds_bind) \
	X("sound_set_stop_time_in_pcm_frames", ma_sound_set_stop_time_in_pcm_frames_bind) \
	X("sound_set_stop_time_in_milliseconds", ma_sound_set_stop_time_in_milliseconds_bind) \
	X("sound_is_playing", ma_sound_is_playing_bind) \
	X("sound_get_time_in_pcm_frames", ma_sound_get_time_in_pcm_frames_bind) \
	X("sound_set_looping", ma_sound_set_looping_bind) \
	X("sound_is_looping", ma_sound_is_looping_bind) \
	X("sound_at_end", ma_sound_at_end_bind) \
	X("sound_seek_to_pcm_frame", ma_sound_seek_to_pcm_frame_bind) \
	X("sound_get_data_format", ma_sound_get_data_format_bind) \
	X("sound_get_cursor_in_pcm_frames", ma_sound_get_cursor_in_pcm_frames_bind) \
	X("sound_get_length_in_pcm_frames", ma_sound_get_length_in_pcm_frames_bind) \
	X("sound_get_cursor_in_seconds", ma_sound_get_cursor_in_seconds_bind) \
	X("sound_get_length_in_seconds", ma_sound_get_length_in_seconds_bind) \
\
	/* sound group */ \
	X("sound_group_init", ma_sound_group_init_bind) \
	X("sound_group_uninit", ma_sound_group_uninit_bind) \
	X("sound_group_start", ma_sound_group_start_bind) \
	X("sound_group_stop", ma_sound_group_stop_bind) \
	X("sound_group_set_volume", ma_sound_group_set_volume_bind) \
	X("sound_group_get_volume", ma_sound_group_get_volume_bind) \
	X("sound_group_set_pan", ma_sound_group_set_pan_bind) \
	X("sound_group_get_pan", ma_sound_group_get_pan_bind) \
	X("sound_group_set_pan_mode", ma_sound_group_set_pan_mode_bind) \
	X("sound_group_get_pan_mode", ma_sound_group_get_pan_mode_bind) \
	X("sound_group_set_pitch", ma_sound_group_set_pitch_bind) \
	X("sound_group_get_pitch", ma_sound_group_get_pitch_bind) \
	X("sound_group_set_spatialization_enabled", ma_sound_group_set_spatialization_enabled_bind) \
	X("sound_group_is_spatialization_enabled", ma_sound_group_is_spatialization_enabled_bind) \
	X("sound_group_set_pinned_listener_index", ma_sound_group_set_pinned_listener_index_bind) \
	X("sound_group_get_pinned_listener_index", ma_sound_group_get_pinned_listener_index_bind) \
	X("sound_group_get_listener_index", ma_sound_group_get_listener_index_bind) \
	X("sound_group_get_direction_to_listener", ma_sound_group_get_direction_to_listener_bind) \
	X("sound_group_set_position", ma_sound_group_set_position_bind) \
	X("sound_group_get_position", ma_sound_group_get_position_bind) \
	X("sound_group_set_direction", ma_sound_group_set_direction_bind) \
	X("sound_group_get_direction", ma_sound_group_get_direction_bind) \
	X("sound_group_set_velocity", ma_sound_group_set_velocity_bind) \
	X("sound_group_get_velocity", ma_sound_group_get_velocity_bind) \
	X("sound_group_set_attenuation_model", ma_sound_group_set_attenuation_model_bind) \
	X("sound_group_get_attenuation_model", ma_sound_group_get_attenuation_model_bind) \
	X("sound_group_set_positioning", ma_sound_group_set_positioning_bind) \
	X("sound_group_get_positioning", ma_sound_group_get_positioning_bind) \
	X("sound_group_set_rolloff", ma_sound_group_set_rolloff_bind) \
	X("sound_group_get_rolloff", ma_sound_group_get_rolloff_bind) \
	X("sound_group_set_min_gain", ma_sound_group_set_min_gain_bind) \
	X("sound_group_get_min_gain", ma_sound_group_get_min_gain_bind) \
	X("sound_group_set_max_gain", ma_sound_group_set_max_gain_bind) \
	X("sound_group_get_max_gain", ma_sound_group_get_max_gain_bind) \
	X("sound_group_set_min_distance", ma_sound_group_set_min_distance_bind) \
	X("sound_group_get_min_distance", ma_sound_group_get_min_distance_bind) \
	X("sound_group_set_max_distance", ma_sound_group_set_max_distance_bind) \
	X("sound_group_get_max_distance", ma_sound_group_get_max_distance_bind) \
	X("sound_group_set_cone", ma_sound_group_set_cone_bind) \
	X("sound_group_get_cone", ma_sound_group_get_cone_bind) \
	X("sound_group_set_doppler_factor", ma_sound_group_set_doppler_factor_bind) \
	X("sound_group_get_doppler_factor", ma_sound_group_get_doppler_factor_bind) \
	X("sound_group_set_directional_attenuation_factor", ma_sound_group_set_directional_attenuation_factor_bind) \
	X("sound_group_get_directional_attenuation_factor", ma_sound_group_get_directional_attenuation_factor_bind) \
	X("sound_group_set_fade_in_pcm_frames", ma_sound_group_set_fade_in_pcm_frames_bind) \
	X("sound_group_set_fade_in_milliseconds", ma_sound_group_set_fade_in_milliseconds_bind) \
	X("sound_group_get_current_fade_volume", ma_sound_group_get_current_fade_volume_bind) \
	X("sound_group_set_start_time_in_pcm_frames", ma_sound_group_set_start_time_in_pcm_frames_bind) \
	X("sound_group_set_start_time_in_milliseconds", ma_sound_group_set_start_time_in_milliseconds_bind) \
	X("sound_group_set_stop_time_in_pcm_frames", ma_sound_group_set_stop_time_in_pcm_frames_bind) \
	X("sound_group_set_stop_time_in_milliseconds", ma_sound_group_set_stop_time_in_milliseconds_bind) \
	X("sound_group_is_playing", ma_sound_group_is_playing_bind) \
	X("sound_group_get_time_in_pcm_frames", ma_sound_group_get_time_in_pcm_frames_bind) \


#define X(name, func) int func(lua_State *L);
AUDIO_FUNCTIONS
#undef X

#endif
