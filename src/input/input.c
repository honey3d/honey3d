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
    lua_createtable(L, 0, 121);

    lua_pushinteger(L, HONEY_KEY_UNKNOWN);
    lua_setfield(L, -2, "honey_key_unknown");
    
    lua_pushinteger(L, HONEY_KEY_SPACE);
    lua_setfield(L, -2, "honey_key_space");
    
    lua_pushinteger(L, HONEY_KEY_APOSTROPHE);
    lua_setfield(L, -2, "honey_key_apostrophe");
    
    lua_pushinteger(L, HONEY_KEY_COMMA);
    lua_setfield(L, -2, "honey_key_comma");
    
    lua_pushinteger(L, HONEY_KEY_MINUS);
    lua_setfield(L, -2, "honey_key_minus");
    
    lua_pushinteger(L, HONEY_KEY_PERIOD);
    lua_setfield(L, -2, "honey_key_period");
    
    lua_pushinteger(L, HONEY_KEY_SLASH);
    lua_setfield(L, -2, "honey_key_slash");
    
    lua_pushinteger(L, HONEY_KEY_0);
    lua_setfield(L, -2, "honey_key_0");
    
    lua_pushinteger(L, HONEY_KEY_1);
    lua_setfield(L, -2, "honey_key_1");
    
    lua_pushinteger(L, HONEY_KEY_2);
    lua_setfield(L, -2, "honey_key_2");
    
    lua_pushinteger(L, HONEY_KEY_3);
    lua_setfield(L, -2, "honey_key_3");
    
    lua_pushinteger(L, HONEY_KEY_4);
    lua_setfield(L, -2, "honey_key_4");
    
    lua_pushinteger(L, HONEY_KEY_5);
    lua_setfield(L, -2, "honey_key_5");
    
    lua_pushinteger(L, HONEY_KEY_6);
    lua_setfield(L, -2, "honey_key_6");
    
    lua_pushinteger(L, HONEY_KEY_7);
    lua_setfield(L, -2, "honey_key_7");
    
    lua_pushinteger(L, HONEY_KEY_8);
    lua_setfield(L, -2, "honey_key_8");
    
    lua_pushinteger(L, HONEY_KEY_9);
    lua_setfield(L, -2, "honey_key_9");
    
    lua_pushinteger(L, HONEY_KEY_SEMICOLON);
    lua_setfield(L, -2, "honey_key_semicolon");
    
    lua_pushinteger(L, HONEY_KEY_EQUAL);
    lua_setfield(L, -2, "honey_key_equal");
    
    lua_pushinteger(L, HONEY_KEY_A);
    lua_setfield(L, -2, "honey_key_a");
    
    lua_pushinteger(L, HONEY_KEY_B);
    lua_setfield(L, -2, "honey_key_b");
    
    lua_pushinteger(L, HONEY_KEY_C);
    lua_setfield(L, -2, "honey_key_c");
    
    lua_pushinteger(L, HONEY_KEY_D);
    lua_setfield(L, -2, "honey_key_d");
    
    lua_pushinteger(L, HONEY_KEY_E);
    lua_setfield(L, -2, "honey_key_e");
    
    lua_pushinteger(L, HONEY_KEY_F);
    lua_setfield(L, -2, "honey_key_f");
    
    lua_pushinteger(L, HONEY_KEY_G);
    lua_setfield(L, -2, "honey_key_g");
    
    lua_pushinteger(L, HONEY_KEY_H);
    lua_setfield(L, -2, "honey_key_h");
    
    lua_pushinteger(L, HONEY_KEY_I);
    lua_setfield(L, -2, "honey_key_i");
    
    lua_pushinteger(L, HONEY_KEY_J);
    lua_setfield(L, -2, "honey_key_j");
    
    lua_pushinteger(L, HONEY_KEY_K);
    lua_setfield(L, -2, "honey_key_k");
    
    lua_pushinteger(L, HONEY_KEY_L);
    lua_setfield(L, -2, "honey_key_l");
    
    lua_pushinteger(L, HONEY_KEY_M);
    lua_setfield(L, -2, "honey_key_m");
    
    lua_pushinteger(L, HONEY_KEY_N);
    lua_setfield(L, -2, "honey_key_n");
    
    lua_pushinteger(L, HONEY_KEY_O);
    lua_setfield(L, -2, "honey_key_o");
    
    lua_pushinteger(L, HONEY_KEY_P);
    lua_setfield(L, -2, "honey_key_p");
    
    lua_pushinteger(L, HONEY_KEY_Q);
    lua_setfield(L, -2, "honey_key_q");
    
    lua_pushinteger(L, HONEY_KEY_R);
    lua_setfield(L, -2, "honey_key_r");
    
    lua_pushinteger(L, HONEY_KEY_S);
    lua_setfield(L, -2, "honey_key_s");
    
    lua_pushinteger(L, HONEY_KEY_T);
    lua_setfield(L, -2, "honey_key_t");
    
    lua_pushinteger(L, HONEY_KEY_U);
    lua_setfield(L, -2, "honey_key_u");
    
    lua_pushinteger(L, HONEY_KEY_V);
    lua_setfield(L, -2, "honey_key_v");
    
    lua_pushinteger(L, HONEY_KEY_W);
    lua_setfield(L, -2, "honey_key_w");
    
    lua_pushinteger(L, HONEY_KEY_X);
    lua_setfield(L, -2, "honey_key_x");
    
    lua_pushinteger(L, HONEY_KEY_Y);
    lua_setfield(L, -2, "honey_key_y");
    
    lua_pushinteger(L, HONEY_KEY_Z);
    lua_setfield(L, -2, "honey_key_z");
    
    lua_pushinteger(L, HONEY_KEY_LEFT_BRACKET);
    lua_setfield(L, -2, "honey_key_left_bracket");
    
    lua_pushinteger(L, HONEY_KEY_BACKSLASH);
    lua_setfield(L, -2, "honey_key_backslash");
    
    lua_pushinteger(L, HONEY_KEY_RIGHT_BRACKET);
    lua_setfield(L, -2, "honey_key_right_bracket");
    
    lua_pushinteger(L, HONEY_KEY_GRAVE_ACCENT);
    lua_setfield(L, -2, "honey_key_grave_accent");
    
    lua_pushinteger(L, HONEY_KEY_WORLD_1);
    lua_setfield(L, -2, "honey_key_world_1");
    
    lua_pushinteger(L, HONEY_KEY_WORLD_2);
    lua_setfield(L, -2, "honey_key_world_2");
    
    lua_pushinteger(L, HONEY_KEY_ESCAPE);
    lua_setfield(L, -2, "honey_key_escape");
    
    lua_pushinteger(L, HONEY_KEY_ENTER);
    lua_setfield(L, -2, "honey_key_enter");
    
    lua_pushinteger(L, HONEY_KEY_TAB);
    lua_setfield(L, -2, "honey_key_tab");
    
    lua_pushinteger(L, HONEY_KEY_BACKSPACE);
    lua_setfield(L, -2, "honey_key_backspace");
    
    lua_pushinteger(L, HONEY_KEY_INSERT);
    lua_setfield(L, -2, "honey_key_insert");
    
    lua_pushinteger(L, HONEY_KEY_DELETE);
    lua_setfield(L, -2, "honey_key_delete");
    
    lua_pushinteger(L, HONEY_KEY_RIGHT);
    lua_setfield(L, -2, "honey_key_right");
    
    lua_pushinteger(L, HONEY_KEY_LEFT);
    lua_setfield(L, -2, "honey_key_left");
    
    lua_pushinteger(L, HONEY_KEY_DOWN);
    lua_setfield(L, -2, "honey_key_down");
    
    lua_pushinteger(L, HONEY_KEY_UP);
    lua_setfield(L, -2, "honey_key_up");
    
    lua_pushinteger(L, HONEY_KEY_PAGE_UP);
    lua_setfield(L, -2, "honey_key_page_up");
    
    lua_pushinteger(L, HONEY_KEY_PAGE_DOWN);
    lua_setfield(L, -2, "honey_key_page_down");
    
    lua_pushinteger(L, HONEY_KEY_HOME);
    lua_setfield(L, -2, "honey_key_home");
    
    lua_pushinteger(L, HONEY_KEY_END);
    lua_setfield(L, -2, "honey_key_end");
    
    lua_pushinteger(L, HONEY_KEY_CAPS_LOCK);
    lua_setfield(L, -2, "honey_key_caps_lock");
    
    lua_pushinteger(L, HONEY_KEY_SCROLL_LOCK);
    lua_setfield(L, -2, "honey_key_scroll_lock");
    
    lua_pushinteger(L, HONEY_KEY_NUM_LOCK);
    lua_setfield(L, -2, "honey_key_num_lock");
    
    lua_pushinteger(L, HONEY_KEY_PRINT_SCREEN);
    lua_setfield(L, -2, "honey_key_print_screen");
    
    lua_pushinteger(L, HONEY_KEY_PAUSE);
    lua_setfield(L, -2, "honey_key_pause");
    
    lua_pushinteger(L, HONEY_KEY_F1);
    lua_setfield(L, -2, "honey_key_f1");
    
    lua_pushinteger(L, HONEY_KEY_F2);
    lua_setfield(L, -2, "honey_key_f2");
    
    lua_pushinteger(L, HONEY_KEY_F3);
    lua_setfield(L, -2, "honey_key_f3");
    
    lua_pushinteger(L, HONEY_KEY_F4);
    lua_setfield(L, -2, "honey_key_f4");
    
    lua_pushinteger(L, HONEY_KEY_F5);
    lua_setfield(L, -2, "honey_key_f5");
    
    lua_pushinteger(L, HONEY_KEY_F6);
    lua_setfield(L, -2, "honey_key_f6");
    
    lua_pushinteger(L, HONEY_KEY_F7);
    lua_setfield(L, -2, "honey_key_f7");
    
    lua_pushinteger(L, HONEY_KEY_F8);
    lua_setfield(L, -2, "honey_key_f8");
    
    lua_pushinteger(L, HONEY_KEY_F9);
    lua_setfield(L, -2, "honey_key_f9");
    
    lua_pushinteger(L, HONEY_KEY_F10);
    lua_setfield(L, -2, "honey_key_f10");
    
    lua_pushinteger(L, HONEY_KEY_F11);
    lua_setfield(L, -2, "honey_key_f11");
    
    lua_pushinteger(L, HONEY_KEY_F12);
    lua_setfield(L, -2, "honey_key_f12");
    
    lua_pushinteger(L, HONEY_KEY_F13);
    lua_setfield(L, -2, "honey_key_f13");
    
    lua_pushinteger(L, HONEY_KEY_F14);
    lua_setfield(L, -2, "honey_key_f14");
    
    lua_pushinteger(L, HONEY_KEY_F15);
    lua_setfield(L, -2, "honey_key_f15");
    
    lua_pushinteger(L, HONEY_KEY_F16);
    lua_setfield(L, -2, "honey_key_f16");
    
    lua_pushinteger(L, HONEY_KEY_F17);
    lua_setfield(L, -2, "honey_key_f17");
    
    lua_pushinteger(L, HONEY_KEY_F18);
    lua_setfield(L, -2, "honey_key_f18");
    
    lua_pushinteger(L, HONEY_KEY_F19);
    lua_setfield(L, -2, "honey_key_f19");
    
    lua_pushinteger(L, HONEY_KEY_F20);
    lua_setfield(L, -2, "honey_key_f20");
    
    lua_pushinteger(L, HONEY_KEY_F21);
    lua_setfield(L, -2, "honey_key_f21");
    
    lua_pushinteger(L, HONEY_KEY_F22);
    lua_setfield(L, -2, "honey_key_f22");
    
    lua_pushinteger(L, HONEY_KEY_F23);
    lua_setfield(L, -2, "honey_key_f23");
    
    lua_pushinteger(L, HONEY_KEY_F24);
    lua_setfield(L, -2, "honey_key_f24");
    
    lua_pushinteger(L, HONEY_KEY_F25);
    lua_setfield(L, -2, "honey_key_f25");
    
    lua_pushinteger(L, HONEY_KEY_KP_0);
    lua_setfield(L, -2, "honey_key_kp_0");
    
    lua_pushinteger(L, HONEY_KEY_KP_1);
    lua_setfield(L, -2, "honey_key_kp_1");
    
    lua_pushinteger(L, HONEY_KEY_KP_2);
    lua_setfield(L, -2, "honey_key_kp_2");
    
    lua_pushinteger(L, HONEY_KEY_KP_3);
    lua_setfield(L, -2, "honey_key_kp_3");
    
    lua_pushinteger(L, HONEY_KEY_KP_4);
    lua_setfield(L, -2, "honey_key_kp_4");
    
    lua_pushinteger(L, HONEY_KEY_KP_5);
    lua_setfield(L, -2, "honey_key_kp_5");
    
    lua_pushinteger(L, HONEY_KEY_KP_6);
    lua_setfield(L, -2, "honey_key_kp_6");
    
    lua_pushinteger(L, HONEY_KEY_KP_7);
    lua_setfield(L, -2, "honey_key_kp_7");
    
    lua_pushinteger(L, HONEY_KEY_KP_8);
    lua_setfield(L, -2, "honey_key_kp_8");
    
    lua_pushinteger(L, HONEY_KEY_KP_9);
    lua_setfield(L, -2, "honey_key_kp_9");
    
    lua_pushinteger(L, HONEY_KEY_KP_DECIMAL);
    lua_setfield(L, -2, "honey_key_kp_decimal");
    
    lua_pushinteger(L, HONEY_KEY_KP_DIVIDE);
    lua_setfield(L, -2, "honey_key_kp_divide");
    
    lua_pushinteger(L, HONEY_KEY_KP_MULTIPLY);
    lua_setfield(L, -2, "honey_key_kp_multiply");
    
    lua_pushinteger(L, HONEY_KEY_KP_SUBTRACT);
    lua_setfield(L, -2, "honey_key_kp_subtract");
    
    lua_pushinteger(L, HONEY_KEY_KP_ADD);
    lua_setfield(L, -2, "honey_key_kp_add");
    
    lua_pushinteger(L, HONEY_KEY_KP_ENTER);
    lua_setfield(L, -2, "honey_key_kp_enter");
    
    lua_pushinteger(L, HONEY_KEY_KP_EQUAL);
    lua_setfield(L, -2, "honey_key_kp_equal");
    
    lua_pushinteger(L, HONEY_KEY_LEFT_SHIFT);
    lua_setfield(L, -2, "honey_key_left_shift");
    
    lua_pushinteger(L, HONEY_KEY_LEFT_CONTROL);
    lua_setfield(L, -2, "honey_key_left_control");
    
    lua_pushinteger(L, HONEY_KEY_LEFT_ALT);
    lua_setfield(L, -2, "honey_key_left_alt");
    
    lua_pushinteger(L, HONEY_KEY_LEFT_SUPER);
    lua_setfield(L, -2, "honey_key_left_super");
    
    lua_pushinteger(L, HONEY_KEY_RIGHT_SHIFT);
    lua_setfield(L, -2, "honey_key_right_shift");
    
    lua_pushinteger(L, HONEY_KEY_RIGHT_CONTROL);
    lua_setfield(L, -2, "honey_key_right_control");
    
    lua_pushinteger(L, HONEY_KEY_RIGHT_ALT);
    lua_setfield(L, -2, "honey_key_right_alt");
    
    lua_pushinteger(L, HONEY_KEY_RIGHT_SUPER);
    lua_setfield(L, -2, "honey_key_right_super");
    
    lua_pushinteger(L, HONEY_KEY_MENU);
    lua_setfield(L, -2, "honey_key_menu");
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
