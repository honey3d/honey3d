#include "input.h"

void honey_setup_keyboard()
{
    memset(honey_key_states, 0, sizeof(honey_key_states));
    memset(honey_key_callbacks, 0, sizeof(honey_key_callbacks));
    memset(honey_key_callbacks_data, 0, sizeof(honey_key_callbacks_data));

    honey_keyboard_callback = &default_honey_keyboard_callback;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_setup_input(lua_State* L)
{
    honey_lua_element elements[] = {
	{ "honey_key_unknown", HONEY_INT, { HONEY_KEY_UNKNOWN } },
	{ "honey_key_space", HONEY_INT, { HONEY_KEY_SPACE } },
	{ "honey_key_apostrophe", HONEY_INT, { HONEY_KEY_APOSTROPHE } },
	{ "honey_key_comma", HONEY_INT, { HONEY_KEY_COMMA } },
	{ "honey_key_minus", HONEY_INT, { HONEY_KEY_MINUS } },
	{ "honey_key_period", HONEY_INT, { HONEY_KEY_PERIOD } },
	{ "honey_key_slash", HONEY_INT, { HONEY_KEY_SLASH } },
	{ "honey_key_0", HONEY_INT, { HONEY_KEY_0 } },
	{ "honey_key_1", HONEY_INT, { HONEY_KEY_1 } },
	{ "honey_key_2", HONEY_INT, { HONEY_KEY_2 } },
	{ "honey_key_3", HONEY_INT, { HONEY_KEY_3 } },
	{ "honey_key_4", HONEY_INT, { HONEY_KEY_4 } },
	{ "honey_key_5", HONEY_INT, { HONEY_KEY_5 } },
	{ "honey_key_6", HONEY_INT, { HONEY_KEY_6 } },
	{ "honey_key_7", HONEY_INT, { HONEY_KEY_7 } },
	{ "honey_key_8", HONEY_INT, { HONEY_KEY_8 } },
	{ "honey_key_9", HONEY_INT, { HONEY_KEY_9 } },
	{ "honey_key_semicolon", HONEY_INT, { HONEY_KEY_SEMICOLON } },
	{ "honey_key_equal", HONEY_INT, { HONEY_KEY_EQUAL } },
	{ "honey_key_a", HONEY_INT, { HONEY_KEY_A } },
	{ "honey_key_b", HONEY_INT, { HONEY_KEY_B } },
	{ "honey_key_c", HONEY_INT, { HONEY_KEY_C } },
	{ "honey_key_d", HONEY_INT, { HONEY_KEY_D } },
	{ "honey_key_e", HONEY_INT, { HONEY_KEY_E } },
	{ "honey_key_f", HONEY_INT, { HONEY_KEY_F } },
	{ "honey_key_g", HONEY_INT, { HONEY_KEY_G } },
	{ "honey_key_h", HONEY_INT, { HONEY_KEY_H } },
	{ "honey_key_i", HONEY_INT, { HONEY_KEY_I } },
	{ "honey_key_j", HONEY_INT, { HONEY_KEY_J } },
	{ "honey_key_k", HONEY_INT, { HONEY_KEY_K } },
	{ "honey_key_l", HONEY_INT, { HONEY_KEY_L } },
	{ "honey_key_m", HONEY_INT, { HONEY_KEY_M } },
	{ "honey_key_n", HONEY_INT, { HONEY_KEY_N } },
	{ "honey_key_o", HONEY_INT, { HONEY_KEY_O } },
	{ "honey_key_p", HONEY_INT, { HONEY_KEY_P } },
	{ "honey_key_q", HONEY_INT, { HONEY_KEY_Q } },
	{ "honey_key_r", HONEY_INT, { HONEY_KEY_R } },
	{ "honey_key_s", HONEY_INT, { HONEY_KEY_S } },
	{ "honey_key_t", HONEY_INT, { HONEY_KEY_T } },
	{ "honey_key_u", HONEY_INT, { HONEY_KEY_U } },
	{ "honey_key_v", HONEY_INT, { HONEY_KEY_V } },
	{ "honey_key_w", HONEY_INT, { HONEY_KEY_W } },
	{ "honey_key_x", HONEY_INT, { HONEY_KEY_X } },
	{ "honey_key_y", HONEY_INT, { HONEY_KEY_Y } },
	{ "honey_key_z", HONEY_INT, { HONEY_KEY_Z } },
	{ "honey_key_left_bracket", HONEY_INT, { HONEY_KEY_LEFT_BRACKET } },
	{ "honey_key_backslash", HONEY_INT, { HONEY_KEY_BACKSLASH } },
	{ "honey_key_right_bracket", HONEY_INT, { HONEY_KEY_RIGHT_BRACKET } },
	{ "honey_key_grave_accent", HONEY_INT, { HONEY_KEY_GRAVE_ACCENT } },
	{ "honey_key_world_1", HONEY_INT, { HONEY_KEY_WORLD_1 } },
	{ "honey_key_world_2", HONEY_INT, { HONEY_KEY_WORLD_2 } },
	{ "honey_key_escape", HONEY_INT, { HONEY_KEY_ESCAPE } },
	{ "honey_key_enter", HONEY_INT, { HONEY_KEY_ENTER } },
	{ "honey_key_tab", HONEY_INT, { HONEY_KEY_TAB } },
	{ "honey_key_backspace", HONEY_INT, { HONEY_KEY_BACKSPACE } },
	{ "honey_key_insert", HONEY_INT, { HONEY_KEY_INSERT } },
	{ "honey_key_delete", HONEY_INT, { HONEY_KEY_DELETE } },
	{ "honey_key_right", HONEY_INT, { HONEY_KEY_RIGHT } },
	{ "honey_key_left", HONEY_INT, { HONEY_KEY_LEFT } },
	{ "honey_key_down", HONEY_INT, { HONEY_KEY_DOWN } },
	{ "honey_key_up", HONEY_INT, { HONEY_KEY_UP } },
	{ "honey_key_page_up", HONEY_INT, { HONEY_KEY_PAGE_UP } },
	{ "honey_key_page_down", HONEY_INT, { HONEY_KEY_PAGE_DOWN } },
	{ "honey_key_home", HONEY_INT, { HONEY_KEY_HOME } },
	{ "honey_key_end", HONEY_INT, { HONEY_KEY_END } },
	{ "honey_key_caps_lock", HONEY_INT, { HONEY_KEY_CAPS_LOCK } },
	{ "honey_key_scroll_lock", HONEY_INT, { HONEY_KEY_SCROLL_LOCK } },
	{ "honey_key_num_lock", HONEY_INT, { HONEY_KEY_NUM_LOCK } },
	{ "honey_key_print_screen", HONEY_INT, { HONEY_KEY_PRINT_SCREEN } },
	{ "honey_key_pause", HONEY_INT, { HONEY_KEY_PAUSE } },
	{ "honey_key_f1", HONEY_INT, { HONEY_KEY_F1 } },
	{ "honey_key_f2", HONEY_INT, { HONEY_KEY_F2 } },
	{ "honey_key_f3", HONEY_INT, { HONEY_KEY_F3 } },
	{ "honey_key_f4", HONEY_INT, { HONEY_KEY_F4 } },
	{ "honey_key_f5", HONEY_INT, { HONEY_KEY_F5 } },
	{ "honey_key_f6", HONEY_INT, { HONEY_KEY_F6 } },
	{ "honey_key_f7", HONEY_INT, { HONEY_KEY_F7 } },
	{ "honey_key_f8", HONEY_INT, { HONEY_KEY_F8 } },
	{ "honey_key_f9", HONEY_INT, { HONEY_KEY_F9 } },
	{ "honey_key_f10", HONEY_INT, { HONEY_KEY_F10 } },
	{ "honey_key_f11", HONEY_INT, { HONEY_KEY_F11 } },
	{ "honey_key_f12", HONEY_INT, { HONEY_KEY_F12 } },
	{ "honey_key_f13", HONEY_INT, { HONEY_KEY_F13 } },
	{ "honey_key_f14", HONEY_INT, { HONEY_KEY_F14 } },
	{ "honey_key_f15", HONEY_INT, { HONEY_KEY_F15 } },
	{ "honey_key_f16", HONEY_INT, { HONEY_KEY_F16 } },
	{ "honey_key_f17", HONEY_INT, { HONEY_KEY_F17 } },
	{ "honey_key_f18", HONEY_INT, { HONEY_KEY_F18 } },
	{ "honey_key_f19", HONEY_INT, { HONEY_KEY_F19 } },
	{ "honey_key_f20", HONEY_INT, { HONEY_KEY_F20 } },
	{ "honey_key_f21", HONEY_INT, { HONEY_KEY_F21 } },
	{ "honey_key_f22", HONEY_INT, { HONEY_KEY_F22 } },
	{ "honey_key_f23", HONEY_INT, { HONEY_KEY_F23 } },
	{ "honey_key_f24", HONEY_INT, { HONEY_KEY_F24 } },
	{ "honey_key_f25", HONEY_INT, { HONEY_KEY_F25 } },
	{ "honey_key_kp_0", HONEY_INT, { HONEY_KEY_KP_0 } },
	{ "honey_key_kp_1", HONEY_INT, { HONEY_KEY_KP_1 } },
	{ "honey_key_kp_2", HONEY_INT, { HONEY_KEY_KP_2 } },
	{ "honey_key_kp_3", HONEY_INT, { HONEY_KEY_KP_3 } },
	{ "honey_key_kp_4", HONEY_INT, { HONEY_KEY_KP_4 } },
	{ "honey_key_kp_5", HONEY_INT, { HONEY_KEY_KP_5 } },
	{ "honey_key_kp_6", HONEY_INT, { HONEY_KEY_KP_6 } },
	{ "honey_key_kp_7", HONEY_INT, { HONEY_KEY_KP_7 } },
	{ "honey_key_kp_8", HONEY_INT, { HONEY_KEY_KP_8 } },
	{ "honey_key_kp_9", HONEY_INT, { HONEY_KEY_KP_9 } },
	{ "honey_key_kp_decimal", HONEY_INT, { HONEY_KEY_KP_DECIMAL } },
	{ "honey_key_kp_divide", HONEY_INT, { HONEY_KEY_KP_DIVIDE } },
	{ "honey_key_kp_multiply", HONEY_INT, { HONEY_KEY_KP_MULTIPLY } },
	{ "honey_key_kp_subtract", HONEY_INT, { HONEY_KEY_KP_SUBTRACT } },
	{ "honey_key_kp_add", HONEY_INT, { HONEY_KEY_KP_ADD } },
	{ "honey_key_kp_enter", HONEY_INT, { HONEY_KEY_KP_ENTER } },
	{ "honey_key_kp_equal", HONEY_INT, { HONEY_KEY_KP_EQUAL } },
	{ "honey_key_left_shift", HONEY_INT, { HONEY_KEY_LEFT_SHIFT } },
	{ "honey_key_left_control", HONEY_INT, { HONEY_KEY_LEFT_CONTROL } },
	{ "honey_key_left_alt", HONEY_INT, { HONEY_KEY_LEFT_ALT } },
	{ "honey_key_left_super", HONEY_INT, { HONEY_KEY_LEFT_SUPER } },
	{ "honey_key_right_shift", HONEY_INT, { HONEY_KEY_RIGHT_SHIFT } },
	{ "honey_key_right_control", HONEY_INT, { HONEY_KEY_RIGHT_CONTROL } },
	{ "honey_key_right_alt", HONEY_INT, { HONEY_KEY_RIGHT_ALT } },
	{ "honey_key_right_super", HONEY_INT, { HONEY_KEY_RIGHT_SUPER } },
	{ "honey_key_menu", HONEY_INT, { HONEY_KEY_MENU } }
    };

    honey_lua_create_table(L, elements, HONEY_N_KEYS);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

bool honey_key_down(int key)
{
    if (key < 0 || key >= HONEY_N_KEYS) {
	return false;
    }
    return (bool) honey_key_states[key];
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_key_bind(int key,
		    void (*callback)(void*, int),
		    void* data)
{
    if (key >= 0 && key < HONEY_N_KEYS) {
	honey_key_callbacks[key] = callback;
	honey_key_callbacks_data[key] = data;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_key_unbind(int key)
{
    if (key >=0 && key < HONEY_N_KEYS) {
	honey_key_callbacks[key] = NULL;
	honey_key_callbacks_data[key] = NULL;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_key_unbind_all()
{
    for (int i=0; i<HONEY_N_KEYS; i++) {
	honey_key_callbacks[i] = NULL;
	honey_key_callbacks_data[i] = NULL;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void default_honey_keyboard_callback(honey_window window, int key, int scancode, int action, int mods)
{
    if (key >= 0 && key < HONEY_N_KEYS) {
	if (action == HONEY_KEY_PRESS)   { honey_key_states[key] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[key] = 0; }
	if (honey_key_callbacks[key] != NULL) {
	    honey_key_callbacks[key](honey_key_callbacks_data[key], action);
	}
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
