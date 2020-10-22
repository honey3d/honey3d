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
    honey_setup_keyboard();

    honey_lua_element keyElements[] = {
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

    honey_lua_element inputElements[] = {
	{ "key", HONEY_TABLE, { .table={ HONEY_N_KEYS, keyElements } } },
	{ "is_down", HONEY_FUNC, { .function = honey_key_down } }
    };

    honey_lua_create_table(L, inputElements, 2);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_key_down(lua_State* L)
{
    if (!lua_isnumber(L, 1))
	return 0;

    int key = lua_tointeger(L, 1);
    if (key < 0 || key >= HONEY_N_KEYS)
	lua_pushboolean(L, false);
    else
	lua_pushboolean(L, honey_key_states[key]);

    printf("check key %d: %d\n", key, honey_key_states[key]);
    
    return 1;
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
    switch (key) {
    case GLFW_KEY_UNKNOWN:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_UNKNOWN] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_UNKNOWN] = 0; }
	if (honey_key_callbacks[HONEY_KEY_UNKNOWN] != NULL) {
	    honey_key_callbacks[HONEY_KEY_UNKNOWN](honey_key_callbacks_data[HONEY_KEY_UNKNOWN],
						   action);
	}
	break;
    case GLFW_KEY_SPACE:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_SPACE] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_SPACE] = 0; }
	if (honey_key_callbacks[HONEY_KEY_SPACE] != NULL) {
	    honey_key_callbacks[HONEY_KEY_SPACE] (honey_key_callbacks_data[HONEY_KEY_SPACE],
						  action);
	}
	break;
    case GLFW_KEY_APOSTROPHE:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_APOSTROPHE] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_APOSTROPHE] = 0; }
	if (honey_key_callbacks[HONEY_KEY_APOSTROPHE] != NULL) {
	    honey_key_callbacks[HONEY_KEY_APOSTROPHE] (honey_key_callbacks_data[HONEY_KEY_APOSTROPHE],
						       action);
	}
	break;
    case GLFW_KEY_COMMA:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_COMMA] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_COMMA] = 0; }
	if (honey_key_callbacks[HONEY_KEY_COMMA] != NULL) {
	    honey_key_callbacks[HONEY_KEY_COMMA] (honey_key_callbacks_data[HONEY_KEY_COMMA],
						  action);
	}
	break;
    case GLFW_KEY_MINUS:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_MINUS] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_MINUS] = 0; }
	if (honey_key_callbacks[HONEY_KEY_MINUS] != NULL) {
	    honey_key_callbacks[HONEY_KEY_MINUS] (honey_key_callbacks_data[HONEY_KEY_MINUS],
						  action);
	}
	break;
    case GLFW_KEY_PERIOD:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_PERIOD] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_PERIOD] = 0; }
	if (honey_key_callbacks[HONEY_KEY_PERIOD] != NULL) {
	    honey_key_callbacks[HONEY_KEY_PERIOD] (honey_key_callbacks_data[HONEY_KEY_PERIOD],
						   action);
	}
	break;
    case GLFW_KEY_SLASH:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_SLASH] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_SLASH] = 0; }
	if (honey_key_callbacks[HONEY_KEY_SLASH] != NULL) {
	    honey_key_callbacks[HONEY_KEY_SLASH] (honey_key_callbacks_data[HONEY_KEY_SLASH],
						  action);
	}
	break;
    case GLFW_KEY_0:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_0] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_0] = 0; }
	if (honey_key_callbacks[HONEY_KEY_0] != NULL) {
	    honey_key_callbacks[HONEY_KEY_0] (honey_key_callbacks_data[HONEY_KEY_0],
					      action);
	}
	break;
    case GLFW_KEY_1:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_1] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_1] = 0; }
	if (honey_key_callbacks[HONEY_KEY_1] != NULL) {
	    honey_key_callbacks[HONEY_KEY_1] (honey_key_callbacks_data[HONEY_KEY_1],
					      action);
	}
	break;
    case GLFW_KEY_2:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_2] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_2] = 0; }
	if (honey_key_callbacks[HONEY_KEY_2] != NULL) {
	    honey_key_callbacks[HONEY_KEY_2] (honey_key_callbacks_data[HONEY_KEY_2],
					      action);
	}
	break;
    case GLFW_KEY_3:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_3] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_3] = 0; }
	if (honey_key_callbacks[HONEY_KEY_3] != NULL) {
	    honey_key_callbacks[HONEY_KEY_3] (honey_key_callbacks_data[HONEY_KEY_3],
					      action);
	}
	break;
    case GLFW_KEY_4:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_4] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_4] = 0; }
	if (honey_key_callbacks[HONEY_KEY_4] != NULL) {
	    honey_key_callbacks[HONEY_KEY_4] (honey_key_callbacks_data[HONEY_KEY_4],
					      action);
	}
	break;
    case GLFW_KEY_5:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_5] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_5] = 0; }
	if (honey_key_callbacks[HONEY_KEY_5] != NULL) {
	    honey_key_callbacks[HONEY_KEY_5] (honey_key_callbacks_data[HONEY_KEY_5],
					      action);
	}
	break;
    case GLFW_KEY_6:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_6] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_6] = 0; }
	if (honey_key_callbacks[HONEY_KEY_6] != NULL) {
	    honey_key_callbacks[HONEY_KEY_6] (honey_key_callbacks_data[HONEY_KEY_6],
					      action);
	}
	break;
    case GLFW_KEY_7:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_7] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_7] = 0; }
	if (honey_key_callbacks[HONEY_KEY_7] != NULL) {
	    honey_key_callbacks[HONEY_KEY_7] (honey_key_callbacks_data[HONEY_KEY_7],
					      action);
	}
	break;
    case GLFW_KEY_8:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_8] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_8] = 0; }
	if (honey_key_callbacks[HONEY_KEY_8] != NULL) {
	    honey_key_callbacks[HONEY_KEY_8] (honey_key_callbacks_data[HONEY_KEY_8],
					      action);
	}
	break;
    case GLFW_KEY_9:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_9] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_9] = 0; }
	if (honey_key_callbacks[HONEY_KEY_9] != NULL) {
	    honey_key_callbacks[HONEY_KEY_9] (honey_key_callbacks_data[HONEY_KEY_9],
					      action);
	}
	break;
    case GLFW_KEY_SEMICOLON:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_SEMICOLON] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_SEMICOLON] = 0; }
	if (honey_key_callbacks[HONEY_KEY_SEMICOLON] != NULL) {
	    honey_key_callbacks[HONEY_KEY_SEMICOLON] (honey_key_callbacks_data[HONEY_KEY_SEMICOLON],
						      action);
	}
	break;
    case GLFW_KEY_EQUAL:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_EQUAL] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_EQUAL] = 0; }
	if (honey_key_callbacks[HONEY_KEY_EQUAL] != NULL) {
	    honey_key_callbacks[HONEY_KEY_EQUAL] (honey_key_callbacks_data[HONEY_KEY_EQUAL],
						  action);
	}
	break;
    case GLFW_KEY_A:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_A] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_A] = 0; }
	if (honey_key_callbacks[HONEY_KEY_A] != NULL) {
	    honey_key_callbacks[HONEY_KEY_A] (honey_key_callbacks_data[HONEY_KEY_A],
					      action);
	}
	break;
    case GLFW_KEY_B:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_B] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_B] = 0; }
	if (honey_key_callbacks[HONEY_KEY_B] != NULL) {
	    honey_key_callbacks[HONEY_KEY_B] (honey_key_callbacks_data[HONEY_KEY_B],
					      action);
	}
	break;
    case GLFW_KEY_C:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_C] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_C] = 0; }
	if (honey_key_callbacks[HONEY_KEY_C] != NULL) {
	    honey_key_callbacks[HONEY_KEY_C] (honey_key_callbacks_data[HONEY_KEY_C],
					      action);
	}
	break;
    case GLFW_KEY_D:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_D] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_D] = 0; }
	if (honey_key_callbacks[HONEY_KEY_D] != NULL) {
	    honey_key_callbacks[HONEY_KEY_D] (honey_key_callbacks_data[HONEY_KEY_D],
					      action);
	}
	break;
    case GLFW_KEY_E:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_E] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_E] = 0; }
	if (honey_key_callbacks[HONEY_KEY_E] != NULL) {
	    honey_key_callbacks[HONEY_KEY_E] (honey_key_callbacks_data[HONEY_KEY_E],
					      action);
	}
	break;
    case GLFW_KEY_F:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F] (honey_key_callbacks_data[HONEY_KEY_F],
					      action);
	}
	break;
    case GLFW_KEY_G:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_G] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_G] = 0; }
	if (honey_key_callbacks[HONEY_KEY_G] != NULL) {
	    honey_key_callbacks[HONEY_KEY_G] (honey_key_callbacks_data[HONEY_KEY_G],
					      action);
	}
	break;
    case GLFW_KEY_H:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_H] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_H] = 0; }
	if (honey_key_callbacks[HONEY_KEY_H] != NULL) {
	    honey_key_callbacks[HONEY_KEY_H] (honey_key_callbacks_data[HONEY_KEY_H],
					      action);
	}
	break;
    case GLFW_KEY_I:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_I] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_I] = 0; }
	if (honey_key_callbacks[HONEY_KEY_I] != NULL) {
	    honey_key_callbacks[HONEY_KEY_I] (honey_key_callbacks_data[HONEY_KEY_I],
					      action);
	}
	break;
    case GLFW_KEY_J:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_J] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_J] = 0; }
	if (honey_key_callbacks[HONEY_KEY_J] != NULL) {
	    honey_key_callbacks[HONEY_KEY_J] (honey_key_callbacks_data[HONEY_KEY_J],
					      action);
	}
	break;
    case GLFW_KEY_K:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_K] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_K] = 0; }
	if (honey_key_callbacks[HONEY_KEY_K] != NULL) {
	    honey_key_callbacks[HONEY_KEY_K] (honey_key_callbacks_data[HONEY_KEY_K],
					      action);
	}
	break;
    case GLFW_KEY_L:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_L] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_L] = 0; }
	if (honey_key_callbacks[HONEY_KEY_L] != NULL) {
	    honey_key_callbacks[HONEY_KEY_L] (honey_key_callbacks_data[HONEY_KEY_L],
					      action);
	}
	break;
    case GLFW_KEY_M:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_M] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_M] = 0; }
	if (honey_key_callbacks[HONEY_KEY_M] != NULL) {
	    honey_key_callbacks[HONEY_KEY_M] (honey_key_callbacks_data[HONEY_KEY_M],
					      action);
	}
	break;
    case GLFW_KEY_N:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_N] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_N] = 0; }
	if (honey_key_callbacks[HONEY_KEY_N] != NULL) {
	    honey_key_callbacks[HONEY_KEY_N] (honey_key_callbacks_data[HONEY_KEY_N],
					      action);
	}
	break;
    case GLFW_KEY_O:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_O] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_O] = 0; }
	if (honey_key_callbacks[HONEY_KEY_O] != NULL) {
	    honey_key_callbacks[HONEY_KEY_O] (honey_key_callbacks_data[HONEY_KEY_O],
					      action);
	}
	break;
    case GLFW_KEY_P:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_P] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_P] = 0; }
	if (honey_key_callbacks[HONEY_KEY_P] != NULL) {
	    honey_key_callbacks[HONEY_KEY_P] (honey_key_callbacks_data[HONEY_KEY_P],
					      action);
	}
	break;
    case GLFW_KEY_Q:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_Q] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_Q] = 0; }
	if (honey_key_callbacks[HONEY_KEY_Q] != NULL) {
	    honey_key_callbacks[HONEY_KEY_Q] (honey_key_callbacks_data[HONEY_KEY_Q],
					      action);
	}
	break;
    case GLFW_KEY_R:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_R] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_R] = 0; }
	if (honey_key_callbacks[HONEY_KEY_R] != NULL) {
	    honey_key_callbacks[HONEY_KEY_R] (honey_key_callbacks_data[HONEY_KEY_R],
					      action);
	}
	break;
    case GLFW_KEY_S:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_S] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_S] = 0; }
	if (honey_key_callbacks[HONEY_KEY_S] != NULL) {
	    honey_key_callbacks[HONEY_KEY_S] (honey_key_callbacks_data[HONEY_KEY_S],
					      action);
	}
	break;
    case GLFW_KEY_T:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_T] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_T] = 0; }
	if (honey_key_callbacks[HONEY_KEY_T] != NULL) {
	    honey_key_callbacks[HONEY_KEY_T] (honey_key_callbacks_data[HONEY_KEY_T],
					      action);
	}
	break;
    case GLFW_KEY_U:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_U] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_U] = 0; }
	if (honey_key_callbacks[HONEY_KEY_U] != NULL) {
	    honey_key_callbacks[HONEY_KEY_U] (honey_key_callbacks_data[HONEY_KEY_U],
					      action);
	}
	break;
    case GLFW_KEY_V:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_V] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_V] = 0; }
	if (honey_key_callbacks[HONEY_KEY_V] != NULL) {
	    honey_key_callbacks[HONEY_KEY_V] (honey_key_callbacks_data[HONEY_KEY_V],
					      action);
	}
	break;
    case GLFW_KEY_W:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_W] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_W] = 0; }
	if (honey_key_callbacks[HONEY_KEY_W] != NULL) {
	    honey_key_callbacks[HONEY_KEY_W] (honey_key_callbacks_data[HONEY_KEY_W],
					      action);
	}
	break;
    case GLFW_KEY_X:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_X] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_X] = 0; }
	if (honey_key_callbacks[HONEY_KEY_X] != NULL) {
	    honey_key_callbacks[HONEY_KEY_X] (honey_key_callbacks_data[HONEY_KEY_X],
					      action);
	}
	break;
    case GLFW_KEY_Y:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_Y] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_Y] = 0; }
	if (honey_key_callbacks[HONEY_KEY_Y] != NULL) {
	    honey_key_callbacks[HONEY_KEY_Y] (honey_key_callbacks_data[HONEY_KEY_Y],
					      action);
	}
	break;
    case GLFW_KEY_Z:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_Z] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_Z] = 0; }
	if (honey_key_callbacks[HONEY_KEY_Z] != NULL) {
	    honey_key_callbacks[HONEY_KEY_Z] (honey_key_callbacks_data[HONEY_KEY_Z],
					      action);
	}
	break;
    case GLFW_KEY_LEFT_BRACKET:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_LEFT_BRACKET] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_LEFT_BRACKET] = 0; }
	if (honey_key_callbacks[HONEY_KEY_LEFT_BRACKET] != NULL) {
	    honey_key_callbacks[HONEY_KEY_LEFT_BRACKET] (honey_key_callbacks_data[HONEY_KEY_LEFT_BRACKET],
							 action);
	}
	break;
    case GLFW_KEY_BACKSLASH:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_BACKSLASH] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_BACKSLASH] = 0; }
	if (honey_key_callbacks[HONEY_KEY_BACKSLASH] != NULL) {
	    honey_key_callbacks[HONEY_KEY_BACKSLASH] (honey_key_callbacks_data[HONEY_KEY_BACKSLASH],
						      action);
	}
	break;
    case GLFW_KEY_RIGHT_BRACKET:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_RIGHT_BRACKET] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_RIGHT_BRACKET] = 0; }
	if (honey_key_callbacks[HONEY_KEY_RIGHT_BRACKET] != NULL) {
	    honey_key_callbacks[HONEY_KEY_RIGHT_BRACKET] (honey_key_callbacks_data[HONEY_KEY_RIGHT_BRACKET],
							  action);
	}
	break;
    case GLFW_KEY_GRAVE_ACCENT:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_GRAVE_ACCENT] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_GRAVE_ACCENT] = 0; }
	if (honey_key_callbacks[HONEY_KEY_GRAVE_ACCENT] != NULL) {
	    honey_key_callbacks[HONEY_KEY_GRAVE_ACCENT] (honey_key_callbacks_data[HONEY_KEY_GRAVE_ACCENT],
							 action);
	}
	break;
    case GLFW_KEY_WORLD_1:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_WORLD_1] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_WORLD_1] = 0; }
	if (honey_key_callbacks[HONEY_KEY_WORLD_1] != NULL) {
	    honey_key_callbacks[HONEY_KEY_WORLD_1] (honey_key_callbacks_data[HONEY_KEY_WORLD_1],
						    action);
	}
	break;
    case GLFW_KEY_WORLD_2:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_WORLD_2] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_WORLD_2] = 0; }
	if (honey_key_callbacks[HONEY_KEY_WORLD_2] != NULL) {
	    honey_key_callbacks[HONEY_KEY_WORLD_2] (honey_key_callbacks_data[HONEY_KEY_WORLD_2],
						    action);
	}
	break;
    case GLFW_KEY_ESCAPE:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_ESCAPE] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_ESCAPE] = 0; }
	if (honey_key_callbacks[HONEY_KEY_ESCAPE] != NULL) {
	    honey_key_callbacks[HONEY_KEY_ESCAPE] (honey_key_callbacks_data[HONEY_KEY_ESCAPE],
						   action);
	}
	break;
    case GLFW_KEY_ENTER:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_ENTER] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_ENTER] = 0; }
	if (honey_key_callbacks[HONEY_KEY_ENTER] != NULL) {
	    honey_key_callbacks[HONEY_KEY_ENTER] (honey_key_callbacks_data[HONEY_KEY_ENTER],
						  action);
	}
	break;
    case GLFW_KEY_TAB:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_TAB] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_TAB] = 0; }
	if (honey_key_callbacks[HONEY_KEY_TAB] != NULL) {
	    honey_key_callbacks[HONEY_KEY_TAB] (honey_key_callbacks_data[HONEY_KEY_TAB],
						action);
	}
	break;
    case GLFW_KEY_BACKSPACE:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_BACKSPACE] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_BACKSPACE] = 0; }
	if (honey_key_callbacks[HONEY_KEY_BACKSPACE] != NULL) {
	    honey_key_callbacks[HONEY_KEY_BACKSPACE] (honey_key_callbacks_data[HONEY_KEY_BACKSPACE],
						      action);
	}
	break;
    case GLFW_KEY_INSERT:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_INSERT] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_INSERT] = 0; }
	if (honey_key_callbacks[HONEY_KEY_INSERT] != NULL) {
	    honey_key_callbacks[HONEY_KEY_INSERT] (honey_key_callbacks_data[HONEY_KEY_INSERT],
						   action);
	}
	break;
    case GLFW_KEY_DELETE:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_DELETE] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_DELETE] = 0; }
	if (honey_key_callbacks[HONEY_KEY_DELETE] != NULL) {
	    honey_key_callbacks[HONEY_KEY_DELETE] (honey_key_callbacks_data[HONEY_KEY_DELETE],
						   action);
	}
	break;
    case GLFW_KEY_RIGHT:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_RIGHT] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_RIGHT] = 0; }
	if (honey_key_callbacks[HONEY_KEY_RIGHT] != NULL) {
	    honey_key_callbacks[HONEY_KEY_RIGHT] (honey_key_callbacks_data[HONEY_KEY_RIGHT],
						  action);
	}
	break;
    case GLFW_KEY_LEFT:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_LEFT] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_LEFT] = 0; }
	if (honey_key_callbacks[HONEY_KEY_LEFT] != NULL) {
	    honey_key_callbacks[HONEY_KEY_LEFT] (honey_key_callbacks_data[HONEY_KEY_LEFT],
						 action);
	}
	break;
    case GLFW_KEY_DOWN:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_DOWN] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_DOWN] = 0; }
	if (honey_key_callbacks[HONEY_KEY_DOWN] != NULL) {
	    honey_key_callbacks[HONEY_KEY_DOWN] (honey_key_callbacks_data[HONEY_KEY_DOWN],
						 action);
	}
	break;
    case GLFW_KEY_UP:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_UP] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_UP] = 0; }
	if (honey_key_callbacks[HONEY_KEY_UP] != NULL) {
	    honey_key_callbacks[HONEY_KEY_UP] (honey_key_callbacks_data[HONEY_KEY_UP],
					       action);
	}
	break;
    case GLFW_KEY_PAGE_UP:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_PAGE_UP] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_PAGE_UP] = 0; }
	if (honey_key_callbacks[HONEY_KEY_PAGE_UP] != NULL) {
	    honey_key_callbacks[HONEY_KEY_PAGE_UP] (honey_key_callbacks_data[HONEY_KEY_PAGE_UP],
						    action);
	}
	break;
    case GLFW_KEY_PAGE_DOWN:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_PAGE_DOWN] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_PAGE_DOWN] = 0; }
	if (honey_key_callbacks[HONEY_KEY_PAGE_DOWN] != NULL) {
	    honey_key_callbacks[HONEY_KEY_PAGE_DOWN] (honey_key_callbacks_data[HONEY_KEY_PAGE_DOWN],
						      action);
	}
	break;
    case GLFW_KEY_HOME:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_HOME] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_HOME] = 0; }
	if (honey_key_callbacks[HONEY_KEY_HOME] != NULL) {
	    honey_key_callbacks[HONEY_KEY_HOME] (honey_key_callbacks_data[HONEY_KEY_HOME],
						 action);
	}
	break;
    case GLFW_KEY_END:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_END] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_END] = 0; }
	if (honey_key_callbacks[HONEY_KEY_END] != NULL) {
	    honey_key_callbacks[HONEY_KEY_END] (honey_key_callbacks_data[HONEY_KEY_END],
						action);
	}
	break;
    case GLFW_KEY_CAPS_LOCK:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_CAPS_LOCK] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_CAPS_LOCK] = 0; }
	if (honey_key_callbacks[HONEY_KEY_CAPS_LOCK] != NULL) {
	    honey_key_callbacks[HONEY_KEY_CAPS_LOCK] (honey_key_callbacks_data[HONEY_KEY_CAPS_LOCK],
						      action);
	}
	break;
    case GLFW_KEY_SCROLL_LOCK:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_SCROLL_LOCK] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_SCROLL_LOCK] = 0; }
	if (honey_key_callbacks[HONEY_KEY_SCROLL_LOCK] != NULL) {
	    honey_key_callbacks[HONEY_KEY_SCROLL_LOCK] (honey_key_callbacks_data[HONEY_KEY_SCROLL_LOCK],
							action);
	}
	break;
    case GLFW_KEY_NUM_LOCK:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_NUM_LOCK] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_NUM_LOCK] = 0; }
	if (honey_key_callbacks[HONEY_KEY_NUM_LOCK] != NULL) {
	    honey_key_callbacks[HONEY_KEY_NUM_LOCK] (honey_key_callbacks_data[HONEY_KEY_NUM_LOCK],
						     action);
	}
	break;
    case GLFW_KEY_PRINT_SCREEN:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_PRINT_SCREEN] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_PRINT_SCREEN] = 0; }
	if (honey_key_callbacks[HONEY_KEY_PRINT_SCREEN] != NULL) {
	    honey_key_callbacks[HONEY_KEY_PRINT_SCREEN] (honey_key_callbacks_data[HONEY_KEY_PRINT_SCREEN],
							 action);
	}
	break;
    case GLFW_KEY_PAUSE:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_PAUSE] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_PAUSE] = 0; }
	if (honey_key_callbacks[HONEY_KEY_PAUSE] != NULL) {
	    honey_key_callbacks[HONEY_KEY_PAUSE] (honey_key_callbacks_data[HONEY_KEY_PAUSE],
						  action);
	}
	break;
    case GLFW_KEY_F1:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F1] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F1] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F1] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F1] (honey_key_callbacks_data[HONEY_KEY_F1],
					       action);
	}
	break;
    case GLFW_KEY_F2:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F2] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F2] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F2] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F2] (honey_key_callbacks_data[HONEY_KEY_F2],
					       action);
	}
	break;
    case GLFW_KEY_F3:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F3] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F3] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F3] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F3] (honey_key_callbacks_data[HONEY_KEY_F3],
					       action);
	}
	break;
    case GLFW_KEY_F4:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F4] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F4] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F4] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F4] (honey_key_callbacks_data[HONEY_KEY_F4],
					       action);
	}
	break;
    case GLFW_KEY_F5:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F5] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F5] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F5] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F5] (honey_key_callbacks_data[HONEY_KEY_F5],
					       action);
	}
	break;
    case GLFW_KEY_F6:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F6] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F6] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F6] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F6] (honey_key_callbacks_data[HONEY_KEY_F6],
					       action);
	}
	break;
    case GLFW_KEY_F7:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F7] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F7] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F7] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F7] (honey_key_callbacks_data[HONEY_KEY_F7],
					       action);
	}
	break;
    case GLFW_KEY_F8:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F8] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F8] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F8] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F8] (honey_key_callbacks_data[HONEY_KEY_F8],
					       action);
	}
	break;
    case GLFW_KEY_F9:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F9] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F9] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F9] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F9] (honey_key_callbacks_data[HONEY_KEY_F9],
					       action);
	}
	break;
    case GLFW_KEY_F10:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F10] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F10] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F10] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F10] (honey_key_callbacks_data[HONEY_KEY_F10],
						action);
	}
	break;
    case GLFW_KEY_F11:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F11] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F11] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F11] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F11] (honey_key_callbacks_data[HONEY_KEY_F11],
						action);
	}
	break;
    case GLFW_KEY_F12:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F12] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F12] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F12] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F12] (honey_key_callbacks_data[HONEY_KEY_F12],
						action);
	}
	break;
    case GLFW_KEY_F13:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F13] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F13] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F13] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F13] (honey_key_callbacks_data[HONEY_KEY_F13],
						action);
	}
	break;
    case GLFW_KEY_F14:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F14] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F14] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F14] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F14] (honey_key_callbacks_data[HONEY_KEY_F14],
						action);
	}
	break;
    case GLFW_KEY_F15:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F15] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F15] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F15] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F15] (honey_key_callbacks_data[HONEY_KEY_F15],
						action);
	}
	break;
    case GLFW_KEY_F16:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F16] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F16] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F16] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F16] (honey_key_callbacks_data[HONEY_KEY_F16],
						action);
	}
	break;
    case GLFW_KEY_F17:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F17] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F17] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F17] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F17] (honey_key_callbacks_data[HONEY_KEY_F17],
						action);
	}
	break;
    case GLFW_KEY_F18:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F18] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F18] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F18] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F18] (honey_key_callbacks_data[HONEY_KEY_F18],
						action);
	}
	break;
    case GLFW_KEY_F19:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F19] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F19] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F19] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F19] (honey_key_callbacks_data[HONEY_KEY_F19],
						action);
	}
	break;
    case GLFW_KEY_F20:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F20] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F20] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F20] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F20] (honey_key_callbacks_data[HONEY_KEY_F20],
						action);
	}
	break;
    case GLFW_KEY_F21:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F21] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F21] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F21] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F21] (honey_key_callbacks_data[HONEY_KEY_F21],
						action);
	}
	break;
    case GLFW_KEY_F22:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F22] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F22] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F22] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F22] (honey_key_callbacks_data[HONEY_KEY_F22],
						action);
	}
	break;
    case GLFW_KEY_F23:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F23] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F23] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F23] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F23] (honey_key_callbacks_data[HONEY_KEY_F23],
						action);
	}
	break;
    case GLFW_KEY_F24:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F24] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F24] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F24] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F24] (honey_key_callbacks_data[HONEY_KEY_F24],
						action);
	}
	break;
    case GLFW_KEY_F25:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F25] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F25] = 0; }
	if (honey_key_callbacks[HONEY_KEY_F25] != NULL) {
	    honey_key_callbacks[HONEY_KEY_F25] (honey_key_callbacks_data[HONEY_KEY_F25],
						action);
	}
	break;
    case GLFW_KEY_KP_0:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_0] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_0] = 0; }
	if (honey_key_callbacks[HONEY_KEY_KP_0] != NULL) {
	    honey_key_callbacks[HONEY_KEY_KP_0] (honey_key_callbacks_data[HONEY_KEY_KP_0],
						 action);
	}
	break;
    case GLFW_KEY_KP_1:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_1] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_1] = 0; }
	if (honey_key_callbacks[HONEY_KEY_KP_1] != NULL) {
	    honey_key_callbacks[HONEY_KEY_KP_1] (honey_key_callbacks_data[HONEY_KEY_KP_1],
						 action);
	}
	break;
    case GLFW_KEY_KP_2:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_2] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_2] = 0; }
	if (honey_key_callbacks[HONEY_KEY_KP_2] != NULL) {
	    honey_key_callbacks[HONEY_KEY_KP_2] (honey_key_callbacks_data[HONEY_KEY_KP_2],
						 action);
	}
	break;
    case GLFW_KEY_KP_3:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_3] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_3] = 0; }
	if (honey_key_callbacks[HONEY_KEY_KP_3] != NULL) {
	    honey_key_callbacks[HONEY_KEY_KP_3] (honey_key_callbacks_data[HONEY_KEY_KP_3],
						 action);
	}
	break;
    case GLFW_KEY_KP_4:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_4] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_4] = 0; }
	if (honey_key_callbacks[HONEY_KEY_KP_4] != NULL) {
	    honey_key_callbacks[HONEY_KEY_KP_4] (honey_key_callbacks_data[HONEY_KEY_KP_4],
						 action);
	}
	break;
    case GLFW_KEY_KP_5:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_5] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_5] = 0; }
	if (honey_key_callbacks[HONEY_KEY_KP_5] != NULL) {
	    honey_key_callbacks[HONEY_KEY_KP_5] (honey_key_callbacks_data[HONEY_KEY_KP_5],
						 action);
	}
	break;
    case GLFW_KEY_KP_6:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_6] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_6] = 0; }
	if (honey_key_callbacks[HONEY_KEY_KP_6] != NULL) {
	    honey_key_callbacks[HONEY_KEY_KP_6] (honey_key_callbacks_data[HONEY_KEY_KP_6],
						 action);
	}
	break;
    case GLFW_KEY_KP_7:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_7] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_7] = 0; }
	if (honey_key_callbacks[HONEY_KEY_KP_7] != NULL) {
	    honey_key_callbacks[HONEY_KEY_KP_7] (honey_key_callbacks_data[HONEY_KEY_KP_7],
						 action);
	}
	break;
    case GLFW_KEY_KP_8:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_8] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_8] = 0; }
	if (honey_key_callbacks[HONEY_KEY_KP_8] != NULL) {
	    honey_key_callbacks[HONEY_KEY_KP_8] (honey_key_callbacks_data[HONEY_KEY_KP_8],
						 action);
	}
	break;
    case GLFW_KEY_KP_9:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_9] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_9] = 0; }
	if (honey_key_callbacks[HONEY_KEY_KP_9] != NULL) {
	    honey_key_callbacks[HONEY_KEY_KP_9] (honey_key_callbacks_data[HONEY_KEY_KP_9],
						 action);
	}
	break;
    case GLFW_KEY_KP_DECIMAL:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_DECIMAL] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_DECIMAL] = 0; }
	if (honey_key_callbacks[HONEY_KEY_KP_DECIMAL] != NULL) {
	    honey_key_callbacks[HONEY_KEY_KP_DECIMAL] (honey_key_callbacks_data[HONEY_KEY_KP_DECIMAL],
						       action);
	}
	break;
    case GLFW_KEY_KP_DIVIDE:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_DIVIDE] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_DIVIDE] = 0; }
	if (honey_key_callbacks[HONEY_KEY_KP_DIVIDE] != NULL) {
	    honey_key_callbacks[HONEY_KEY_KP_DIVIDE] (honey_key_callbacks_data[HONEY_KEY_KP_DIVIDE],
						      action);
	}
	break;
    case GLFW_KEY_KP_MULTIPLY:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_MULTIPLY] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_MULTIPLY] = 0; }
	if (honey_key_callbacks[HONEY_KEY_KP_MULTIPLY] != NULL) {
	    honey_key_callbacks[HONEY_KEY_KP_MULTIPLY] (honey_key_callbacks_data[HONEY_KEY_KP_MULTIPLY],
							action);
	}
	break;
    case GLFW_KEY_KP_SUBTRACT:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_SUBTRACT] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_SUBTRACT] = 0; }
	if (honey_key_callbacks[HONEY_KEY_KP_SUBTRACT] != NULL) {
	    honey_key_callbacks[HONEY_KEY_KP_SUBTRACT] (honey_key_callbacks_data[HONEY_KEY_KP_SUBTRACT],
							action);
	}
	break;
    case GLFW_KEY_KP_ADD:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_ADD] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_ADD] = 0; }
	if (honey_key_callbacks[HONEY_KEY_KP_ADD] != NULL) {
	    honey_key_callbacks[HONEY_KEY_KP_ADD] (honey_key_callbacks_data[HONEY_KEY_KP_ADD],
						   action);
	}
	break;
    case GLFW_KEY_KP_ENTER:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_ENTER] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_ENTER] = 0; }
	if (honey_key_callbacks[HONEY_KEY_KP_ENTER] != NULL) {
	    honey_key_callbacks[HONEY_KEY_KP_ENTER] (honey_key_callbacks_data[HONEY_KEY_KP_ENTER],
						     action);
	}
	break;
    case GLFW_KEY_KP_EQUAL:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_EQUAL] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_EQUAL] = 0; }
	if (honey_key_callbacks[HONEY_KEY_KP_EQUAL] != NULL) {
	    honey_key_callbacks[HONEY_KEY_KP_EQUAL] (honey_key_callbacks_data[HONEY_KEY_KP_EQUAL],
						     action);
	}
	break;
    case GLFW_KEY_LEFT_SHIFT:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_LEFT_SHIFT] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_LEFT_SHIFT] = 0; }
	if (honey_key_callbacks[HONEY_KEY_LEFT_SHIFT] != NULL) {
	    honey_key_callbacks[HONEY_KEY_LEFT_SHIFT] (honey_key_callbacks_data[HONEY_KEY_LEFT_SHIFT],
						       action);
	}
	break;
    case GLFW_KEY_LEFT_CONTROL:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_LEFT_CONTROL] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_LEFT_CONTROL] = 0; }
	if (honey_key_callbacks[HONEY_KEY_LEFT_CONTROL] != NULL) {
	    honey_key_callbacks[HONEY_KEY_LEFT_CONTROL] (honey_key_callbacks_data[HONEY_KEY_LEFT_CONTROL],
							 action);
	}
	break;
    case GLFW_KEY_LEFT_ALT:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_LEFT_ALT] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_LEFT_ALT] = 0; }
	if (honey_key_callbacks[HONEY_KEY_LEFT_ALT] != NULL) {
	    honey_key_callbacks[HONEY_KEY_LEFT_ALT] (honey_key_callbacks_data[HONEY_KEY_LEFT_ALT],
						     action);
	}
	break;
    case GLFW_KEY_LEFT_SUPER:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_LEFT_SUPER] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_LEFT_SUPER] = 0; }
	if (honey_key_callbacks[HONEY_KEY_LEFT_SUPER] != NULL) {
	    honey_key_callbacks[HONEY_KEY_LEFT_SUPER] (honey_key_callbacks_data[HONEY_KEY_LEFT_SUPER],
						       action);
	}
	break;
    case GLFW_KEY_RIGHT_SHIFT:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_RIGHT_SHIFT] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_RIGHT_SHIFT] = 0; }
	if (honey_key_callbacks[HONEY_KEY_RIGHT_SHIFT] != NULL) {
	    honey_key_callbacks[HONEY_KEY_RIGHT_SHIFT] (honey_key_callbacks_data[HONEY_KEY_RIGHT_SHIFT],
							action);
	}
	break;
    case GLFW_KEY_RIGHT_CONTROL:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_RIGHT_CONTROL] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_RIGHT_CONTROL] = 0; }
	if (honey_key_callbacks[HONEY_KEY_RIGHT_CONTROL] != NULL) {
	    honey_key_callbacks[HONEY_KEY_RIGHT_CONTROL] (honey_key_callbacks_data[HONEY_KEY_RIGHT_CONTROL],
							  action);
	}
	break;
    case GLFW_KEY_RIGHT_ALT:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_RIGHT_ALT] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_RIGHT_ALT] = 0; }
	if (honey_key_callbacks[HONEY_KEY_RIGHT_ALT] != NULL) {
	    honey_key_callbacks[HONEY_KEY_RIGHT_ALT] (honey_key_callbacks_data[HONEY_KEY_RIGHT_ALT],
						      action);
	}
	break;
    case GLFW_KEY_RIGHT_SUPER:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_RIGHT_SUPER] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_RIGHT_SUPER] = 0; }
	if (honey_key_callbacks[HONEY_KEY_RIGHT_SUPER] != NULL) {
	    honey_key_callbacks[HONEY_KEY_RIGHT_SUPER] (honey_key_callbacks_data[HONEY_KEY_RIGHT_SUPER],
							action);
	}
	break;
    case GLFW_KEY_MENU:
	if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_MENU] = 1; }
	if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_MENU] = 0; }
	if (honey_key_callbacks[HONEY_KEY_MENU] != NULL) {
	    honey_key_callbacks[HONEY_KEY_MENU] (honey_key_callbacks_data[HONEY_KEY_MENU],
						 action);
	}
	break;
    default:
	/* do nothing */
	break;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
