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
	{ "unknown", HONEY_INT, { HONEY_KEY_UNKNOWN } },
	{ "space", HONEY_INT, { HONEY_KEY_SPACE } },
	{ "apostrophe", HONEY_INT, { HONEY_KEY_APOSTROPHE } },
	{ "comma", HONEY_INT, { HONEY_KEY_COMMA } },
	{ "minus", HONEY_INT, { HONEY_KEY_MINUS } },
	{ "period", HONEY_INT, { HONEY_KEY_PERIOD } },
	{ "slash", HONEY_INT, { HONEY_KEY_SLASH } },
	{ "0", HONEY_INT, { HONEY_KEY_0 } },
	{ "1", HONEY_INT, { HONEY_KEY_1 } },
	{ "2", HONEY_INT, { HONEY_KEY_2 } },
	{ "3", HONEY_INT, { HONEY_KEY_3 } },
	{ "4", HONEY_INT, { HONEY_KEY_4 } },
	{ "5", HONEY_INT, { HONEY_KEY_5 } },
	{ "6", HONEY_INT, { HONEY_KEY_6 } },
	{ "7", HONEY_INT, { HONEY_KEY_7 } },
	{ "8", HONEY_INT, { HONEY_KEY_8 } },
	{ "9", HONEY_INT, { HONEY_KEY_9 } },
	{ "semicolon", HONEY_INT, { HONEY_KEY_SEMICOLON } },
	{ "equal", HONEY_INT, { HONEY_KEY_EQUAL } },
	{ "a", HONEY_INT, { HONEY_KEY_A } },
	{ "b", HONEY_INT, { HONEY_KEY_B } },
	{ "c", HONEY_INT, { HONEY_KEY_C } },
	{ "d", HONEY_INT, { HONEY_KEY_D } },
	{ "e", HONEY_INT, { HONEY_KEY_E } },
	{ "f", HONEY_INT, { HONEY_KEY_F } },
	{ "g", HONEY_INT, { HONEY_KEY_G } },
	{ "h", HONEY_INT, { HONEY_KEY_H } },
	{ "i", HONEY_INT, { HONEY_KEY_I } },
	{ "j", HONEY_INT, { HONEY_KEY_J } },
	{ "k", HONEY_INT, { HONEY_KEY_K } },
	{ "l", HONEY_INT, { HONEY_KEY_L } },
	{ "m", HONEY_INT, { HONEY_KEY_M } },
	{ "n", HONEY_INT, { HONEY_KEY_N } },
	{ "o", HONEY_INT, { HONEY_KEY_O } },
	{ "p", HONEY_INT, { HONEY_KEY_P } },
	{ "q", HONEY_INT, { HONEY_KEY_Q } },
	{ "r", HONEY_INT, { HONEY_KEY_R } },
	{ "s", HONEY_INT, { HONEY_KEY_S } },
	{ "t", HONEY_INT, { HONEY_KEY_T } },
	{ "u", HONEY_INT, { HONEY_KEY_U } },
	{ "v", HONEY_INT, { HONEY_KEY_V } },
	{ "w", HONEY_INT, { HONEY_KEY_W } },
	{ "x", HONEY_INT, { HONEY_KEY_X } },
	{ "y", HONEY_INT, { HONEY_KEY_Y } },
	{ "z", HONEY_INT, { HONEY_KEY_Z } },
	{ "left_bracket", HONEY_INT, { HONEY_KEY_LEFT_BRACKET } },
	{ "backslash", HONEY_INT, { HONEY_KEY_BACKSLASH } },
	{ "right_bracket", HONEY_INT, { HONEY_KEY_RIGHT_BRACKET } },
	{ "grave_accent", HONEY_INT, { HONEY_KEY_GRAVE_ACCENT } },
	{ "world_1", HONEY_INT, { HONEY_KEY_WORLD_1 } },
	{ "world_2", HONEY_INT, { HONEY_KEY_WORLD_2 } },
	{ "escape", HONEY_INT, { HONEY_KEY_ESCAPE } },
	{ "enter", HONEY_INT, { HONEY_KEY_ENTER } },
	{ "tab", HONEY_INT, { HONEY_KEY_TAB } },
	{ "backspace", HONEY_INT, { HONEY_KEY_BACKSPACE } },
	{ "insert", HONEY_INT, { HONEY_KEY_INSERT } },
	{ "delete", HONEY_INT, { HONEY_KEY_DELETE } },
	{ "right", HONEY_INT, { HONEY_KEY_RIGHT } },
	{ "left", HONEY_INT, { HONEY_KEY_LEFT } },
	{ "down", HONEY_INT, { HONEY_KEY_DOWN } },
	{ "up", HONEY_INT, { HONEY_KEY_UP } },
	{ "page_up", HONEY_INT, { HONEY_KEY_PAGE_UP } },
	{ "page_down", HONEY_INT, { HONEY_KEY_PAGE_DOWN } },
	{ "home", HONEY_INT, { HONEY_KEY_HOME } },
	{ "end", HONEY_INT, { HONEY_KEY_END } },
	{ "caps_lock", HONEY_INT, { HONEY_KEY_CAPS_LOCK } },
	{ "scroll_lock", HONEY_INT, { HONEY_KEY_SCROLL_LOCK } },
	{ "num_lock", HONEY_INT, { HONEY_KEY_NUM_LOCK } },
	{ "print_screen", HONEY_INT, { HONEY_KEY_PRINT_SCREEN } },
	{ "pause", HONEY_INT, { HONEY_KEY_PAUSE } },
	{ "f1", HONEY_INT, { HONEY_KEY_F1 } },
	{ "f2", HONEY_INT, { HONEY_KEY_F2 } },
	{ "f3", HONEY_INT, { HONEY_KEY_F3 } },
	{ "f4", HONEY_INT, { HONEY_KEY_F4 } },
	{ "f5", HONEY_INT, { HONEY_KEY_F5 } },
	{ "f6", HONEY_INT, { HONEY_KEY_F6 } },
	{ "f7", HONEY_INT, { HONEY_KEY_F7 } },
	{ "f8", HONEY_INT, { HONEY_KEY_F8 } },
	{ "f9", HONEY_INT, { HONEY_KEY_F9 } },
	{ "f10", HONEY_INT, { HONEY_KEY_F10 } },
	{ "f11", HONEY_INT, { HONEY_KEY_F11 } },
	{ "f12", HONEY_INT, { HONEY_KEY_F12 } },
	{ "f13", HONEY_INT, { HONEY_KEY_F13 } },
	{ "f14", HONEY_INT, { HONEY_KEY_F14 } },
	{ "f15", HONEY_INT, { HONEY_KEY_F15 } },
	{ "f16", HONEY_INT, { HONEY_KEY_F16 } },
	{ "f17", HONEY_INT, { HONEY_KEY_F17 } },
	{ "f18", HONEY_INT, { HONEY_KEY_F18 } },
	{ "f19", HONEY_INT, { HONEY_KEY_F19 } },
	{ "f20", HONEY_INT, { HONEY_KEY_F20 } },
	{ "f21", HONEY_INT, { HONEY_KEY_F21 } },
	{ "f22", HONEY_INT, { HONEY_KEY_F22 } },
	{ "f23", HONEY_INT, { HONEY_KEY_F23 } },
	{ "f24", HONEY_INT, { HONEY_KEY_F24 } },
	{ "f25", HONEY_INT, { HONEY_KEY_F25 } },
	{ "kp_0", HONEY_INT, { HONEY_KEY_KP_0 } },
	{ "kp_1", HONEY_INT, { HONEY_KEY_KP_1 } },
	{ "kp_2", HONEY_INT, { HONEY_KEY_KP_2 } },
	{ "kp_3", HONEY_INT, { HONEY_KEY_KP_3 } },
	{ "kp_4", HONEY_INT, { HONEY_KEY_KP_4 } },
	{ "kp_5", HONEY_INT, { HONEY_KEY_KP_5 } },
	{ "kp_6", HONEY_INT, { HONEY_KEY_KP_6 } },
	{ "kp_7", HONEY_INT, { HONEY_KEY_KP_7 } },
	{ "kp_8", HONEY_INT, { HONEY_KEY_KP_8 } },
	{ "kp_9", HONEY_INT, { HONEY_KEY_KP_9 } },
	{ "kp_decimal", HONEY_INT, { HONEY_KEY_KP_DECIMAL } },
	{ "kp_divide", HONEY_INT, { HONEY_KEY_KP_DIVIDE } },
	{ "kp_multiply", HONEY_INT, { HONEY_KEY_KP_MULTIPLY } },
	{ "kp_subtract", HONEY_INT, { HONEY_KEY_KP_SUBTRACT } },
	{ "kp_add", HONEY_INT, { HONEY_KEY_KP_ADD } },
	{ "kp_enter", HONEY_INT, { HONEY_KEY_KP_ENTER } },
	{ "kp_equal", HONEY_INT, { HONEY_KEY_KP_EQUAL } },
	{ "left_shift", HONEY_INT, { HONEY_KEY_LEFT_SHIFT } },
	{ "left_control", HONEY_INT, { HONEY_KEY_LEFT_CONTROL } },
	{ "left_alt", HONEY_INT, { HONEY_KEY_LEFT_ALT } },
	{ "left_super", HONEY_INT, { HONEY_KEY_LEFT_SUPER } },
	{ "right_shift", HONEY_INT, { HONEY_KEY_RIGHT_SHIFT } },
	{ "right_control", HONEY_INT, { HONEY_KEY_RIGHT_CONTROL } },
	{ "right_alt", HONEY_INT, { HONEY_KEY_RIGHT_ALT } },
	{ "right_super", HONEY_INT, { HONEY_KEY_RIGHT_SUPER } },
	{ "menu", HONEY_INT, { HONEY_KEY_MENU } },
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
