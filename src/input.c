#include "input.h"

int honey_mouse_movement_callback_ref = LUA_NOREF;
int honey_mouse_movement_callback_data_ref = LUA_NOREF;

static void honey_glfw_mouse_movement_callback(honey_window window,
                                               double x_pos, double y_pos);
static void honey_glfw_keyboard_callback(honey_window window,
                                         int key, int scancode,
                                         int action, int mods);

void honey_setup_keyboard()
{
    memset(honey_key_states, 0, sizeof(honey_key_states));
    memset(honey_key_callbacks, LUA_NOREF, sizeof(honey_key_callbacks));
    memset(honey_key_callbacks_data, LUA_NOREF, sizeof(honey_key_callbacks_data));
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_setup_input(lua_State* L)
{
    honey_setup_keyboard();

    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_window_info_ref);
    honey_window_information* info = lua_touserdata(L, -1);
    lua_pop(L, 1);

    glfwSetKeyCallback(info->window, honey_glfw_keyboard_callback);
    glfwSetCursorPosCallback(info->window, honey_glfw_mouse_movement_callback);
    
    honey_lua_create_table(L, 2,
			   HONEY_TABLE, "key", HONEY_N_KEYS+4,

			   /* key table */
			   HONEY_INTEGER, "unknown", HONEY_KEY_UNKNOWN,
			   HONEY_INTEGER, "space", HONEY_KEY_SPACE,
			   HONEY_INTEGER, "apostrophe", HONEY_KEY_APOSTROPHE,
			   HONEY_INTEGER, "comma", HONEY_KEY_COMMA,
			   HONEY_INTEGER, "minus", HONEY_KEY_MINUS,
			   HONEY_INTEGER, "period", HONEY_KEY_PERIOD,
			   HONEY_INTEGER, "slash", HONEY_KEY_SLASH,
			   HONEY_INTEGER, "0", HONEY_KEY_0,
			   HONEY_INTEGER, "1", HONEY_KEY_1,
			   HONEY_INTEGER, "2", HONEY_KEY_2,
			   HONEY_INTEGER, "3", HONEY_KEY_3,
			   HONEY_INTEGER, "4", HONEY_KEY_4,
			   HONEY_INTEGER, "5", HONEY_KEY_5,
			   HONEY_INTEGER, "6", HONEY_KEY_6,
			   HONEY_INTEGER, "7", HONEY_KEY_7,
			   HONEY_INTEGER, "8", HONEY_KEY_8,
			   HONEY_INTEGER, "9", HONEY_KEY_9,
			   HONEY_INTEGER, "semicolon", HONEY_KEY_SEMICOLON,
			   HONEY_INTEGER, "equal", HONEY_KEY_EQUAL,
			   HONEY_INTEGER, "a", HONEY_KEY_A,
			   HONEY_INTEGER, "b", HONEY_KEY_B,
			   HONEY_INTEGER, "c", HONEY_KEY_C,
			   HONEY_INTEGER, "d", HONEY_KEY_D,
			   HONEY_INTEGER, "e", HONEY_KEY_E,
			   HONEY_INTEGER, "f", HONEY_KEY_F,
			   HONEY_INTEGER, "g", HONEY_KEY_G,
			   HONEY_INTEGER, "h", HONEY_KEY_H,
			   HONEY_INTEGER, "i", HONEY_KEY_I,
			   HONEY_INTEGER, "j", HONEY_KEY_J,
			   HONEY_INTEGER, "k", HONEY_KEY_K,
			   HONEY_INTEGER, "l", HONEY_KEY_L,
			   HONEY_INTEGER, "m", HONEY_KEY_M,
			   HONEY_INTEGER, "n", HONEY_KEY_N,
			   HONEY_INTEGER, "o", HONEY_KEY_O,
			   HONEY_INTEGER, "p", HONEY_KEY_P,
			   HONEY_INTEGER, "q", HONEY_KEY_Q,
			   HONEY_INTEGER, "r", HONEY_KEY_R,
			   HONEY_INTEGER, "s", HONEY_KEY_S,
			   HONEY_INTEGER, "t", HONEY_KEY_T,
			   HONEY_INTEGER, "u", HONEY_KEY_U,
			   HONEY_INTEGER, "v", HONEY_KEY_V,
			   HONEY_INTEGER, "w", HONEY_KEY_W,
			   HONEY_INTEGER, "x", HONEY_KEY_X,
			   HONEY_INTEGER, "y", HONEY_KEY_Y,
			   HONEY_INTEGER, "z", HONEY_KEY_Z,
			   HONEY_INTEGER, "left_bracket",  HONEY_KEY_LEFT_BRACKET,
			   HONEY_INTEGER, "backslash",  HONEY_KEY_BACKSLASH,
			   HONEY_INTEGER, "right_bracket",  HONEY_KEY_RIGHT_BRACKET,
			   HONEY_INTEGER, "grave_accent",  HONEY_KEY_GRAVE_ACCENT,
			   HONEY_INTEGER, "world_1",  HONEY_KEY_WORLD_1,
			   HONEY_INTEGER, "world_2",  HONEY_KEY_WORLD_2,
			   HONEY_INTEGER, "escape",  HONEY_KEY_ESCAPE,
			   HONEY_INTEGER, "enter",  HONEY_KEY_ENTER,
			   HONEY_INTEGER, "tab",  HONEY_KEY_TAB,
			   HONEY_INTEGER, "backspace",  HONEY_KEY_BACKSPACE,
			   HONEY_INTEGER, "insert",  HONEY_KEY_INSERT,
			   HONEY_INTEGER, "delete",  HONEY_KEY_DELETE,
			   HONEY_INTEGER, "right",  HONEY_KEY_RIGHT,
			   HONEY_INTEGER, "left",  HONEY_KEY_LEFT,
			   HONEY_INTEGER, "down",  HONEY_KEY_DOWN,
			   HONEY_INTEGER, "up",  HONEY_KEY_UP,
			   HONEY_INTEGER, "page_up",  HONEY_KEY_PAGE_UP,
			   HONEY_INTEGER, "page_down",  HONEY_KEY_PAGE_DOWN,
			   HONEY_INTEGER, "home",  HONEY_KEY_HOME,
			   HONEY_INTEGER, "end",  HONEY_KEY_END,
			   HONEY_INTEGER, "caps_lock",  HONEY_KEY_CAPS_LOCK,
			   HONEY_INTEGER, "scroll_lock",  HONEY_KEY_SCROLL_LOCK,
			   HONEY_INTEGER, "num_lock",  HONEY_KEY_NUM_LOCK,
			   HONEY_INTEGER, "print_screen",  HONEY_KEY_PRINT_SCREEN,
			   HONEY_INTEGER, "pause",  HONEY_KEY_PAUSE,
			   HONEY_INTEGER, "f1",  HONEY_KEY_F1,
			   HONEY_INTEGER, "f2",  HONEY_KEY_F2,
			   HONEY_INTEGER, "f3",  HONEY_KEY_F3,
			   HONEY_INTEGER, "f4",  HONEY_KEY_F4,
			   HONEY_INTEGER, "f5",  HONEY_KEY_F5,
			   HONEY_INTEGER, "f6",  HONEY_KEY_F6,
			   HONEY_INTEGER, "f7",  HONEY_KEY_F7,
			   HONEY_INTEGER, "f8",  HONEY_KEY_F8,
			   HONEY_INTEGER, "f9",  HONEY_KEY_F9,
			   HONEY_INTEGER, "f10",  HONEY_KEY_F10,
			   HONEY_INTEGER, "f11",  HONEY_KEY_F11,
			   HONEY_INTEGER, "f12",  HONEY_KEY_F12,
			   HONEY_INTEGER, "f13",  HONEY_KEY_F13,
			   HONEY_INTEGER, "f14",  HONEY_KEY_F14,
			   HONEY_INTEGER, "f15",  HONEY_KEY_F15,
			   HONEY_INTEGER, "f16",  HONEY_KEY_F16,
			   HONEY_INTEGER, "f17",  HONEY_KEY_F17,
			   HONEY_INTEGER, "f18",  HONEY_KEY_F18,
			   HONEY_INTEGER, "f19",  HONEY_KEY_F19,
			   HONEY_INTEGER, "f20",  HONEY_KEY_F20,
			   HONEY_INTEGER, "f21",  HONEY_KEY_F21,
			   HONEY_INTEGER, "f22",  HONEY_KEY_F22,
			   HONEY_INTEGER, "f23",  HONEY_KEY_F23,
			   HONEY_INTEGER, "f24",  HONEY_KEY_F24,
			   HONEY_INTEGER, "f25",  HONEY_KEY_F25,
			   HONEY_INTEGER, "kp_0",  HONEY_KEY_KP_0,
			   HONEY_INTEGER, "kp_1",  HONEY_KEY_KP_1,
			   HONEY_INTEGER, "kp_2",  HONEY_KEY_KP_2,
			   HONEY_INTEGER, "kp_3",  HONEY_KEY_KP_3,
			   HONEY_INTEGER, "kp_4",  HONEY_KEY_KP_4,
			   HONEY_INTEGER, "kp_5",  HONEY_KEY_KP_5,
			   HONEY_INTEGER, "kp_6",  HONEY_KEY_KP_6,
			   HONEY_INTEGER, "kp_7",  HONEY_KEY_KP_7,
			   HONEY_INTEGER, "kp_8",  HONEY_KEY_KP_8,
			   HONEY_INTEGER, "kp_9",  HONEY_KEY_KP_9,
			   HONEY_INTEGER, "kp_decimal",  HONEY_KEY_KP_DECIMAL,
			   HONEY_INTEGER, "kp_divide",  HONEY_KEY_KP_DIVIDE,
			   HONEY_INTEGER, "kp_multiply",  HONEY_KEY_KP_MULTIPLY,
			   HONEY_INTEGER, "kp_subtract",  HONEY_KEY_KP_SUBTRACT,
			   HONEY_INTEGER, "kp_add",  HONEY_KEY_KP_ADD,
			   HONEY_INTEGER, "kp_enter",  HONEY_KEY_KP_ENTER,
			   HONEY_INTEGER, "kp_equal",  HONEY_KEY_KP_EQUAL,
			   HONEY_INTEGER, "left_shift",  HONEY_KEY_LEFT_SHIFT,
			   HONEY_INTEGER, "left_control",  HONEY_KEY_LEFT_CONTROL,
			   HONEY_INTEGER, "left_alt",  HONEY_KEY_LEFT_ALT,
			   HONEY_INTEGER, "left_super",  HONEY_KEY_LEFT_SUPER,
			   HONEY_INTEGER, "right_shift",  HONEY_KEY_RIGHT_SHIFT,
			   HONEY_INTEGER, "right_control",  HONEY_KEY_RIGHT_CONTROL,
			   HONEY_INTEGER, "right_alt",  HONEY_KEY_RIGHT_ALT,
			   HONEY_INTEGER, "right_super",  HONEY_KEY_RIGHT_SUPER,
			   HONEY_INTEGER, "menu",  HONEY_KEY_MENU,
			   HONEY_FUNCTION, "is_down",  .function = honey_key_down,
			   HONEY_FUNCTION, "bind",  .function = honey_key_bind,
			   HONEY_FUNCTION, "unbind",  .function = honey_key_unbind,
			   HONEY_FUNCTION, "unbind_all",  .function = honey_key_unbind_all,

			   HONEY_TABLE, "mouse", 4,

			   /* mouse table */
			   HONEY_TABLE, "mode", 3,
			   HONEY_INTEGER, "normal", HONEY_MOUSE_MODE_NORMAL,
			   HONEY_INTEGER, "hidden", HONEY_MOUSE_MODE_HIDDEN,
			   HONEY_INTEGER, "captured", HONEY_MOUSE_MODE_CAPTURED,
			   HONEY_FUNCTION, "set_mode", honey_mouse_set_mode,
			   HONEY_FUNCTION, "bind_movement", honey_mouse_movement_bind,
			   HONEY_FUNCTION, "unbind_movement", honey_mouse_movement_unbind);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_key_down(lua_State* L)
{
    int key;
    honey_lua_parse_arguments(L, 1, 1, HONEY_INTEGER, &key);

    if (key < 0 || key >= HONEY_N_KEYS)
        lua_pushboolean(L, false);
    else
        lua_pushboolean(L, honey_key_states[key]);

    return 1;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_key_bind(lua_State* L)
{
    int key;

    int choice = honey_lua_parse_arguments
	(L, 2,
	 2, HONEY_INTEGER, &key, HONEY_FUNCTION,
	 3, HONEY_INTEGER, &key, HONEY_FUNCTION, HONEY_ANY);

    lua_pushvalue(L, 2);
    int callback = luaL_ref(L, LUA_REGISTRYINDEX);
    int data = LUA_NOREF;
    if (choice == 1) { /* callback data provided */
	lua_pushvalue(L, 3);
	data = luaL_ref(L, LUA_REGISTRYINDEX);
    }

    /* avoid potential memory leak */
    lua_pushcfunction(L, honey_key_unbind);
    lua_pushinteger(L, key);
    honey_lua_pcall(L, 1, 0);

    if (key >= 0 && key < HONEY_N_KEYS) {
        honey_key_callbacks[key] = callback;
        honey_key_callbacks_data[key] = data;
    }

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_key_unbind(lua_State* L)
{
    int key;
    honey_lua_parse_arguments
	(L, 1,
	 1, HONEY_INTEGER, &key);
        
    if (key >=0 && key < HONEY_N_KEYS) {
	luaL_unref(L, LUA_REGISTRYINDEX, honey_key_callbacks[key]);
	luaL_unref(L, LUA_REGISTRYINDEX, honey_key_callbacks_data[key]);
		   
        honey_key_callbacks[key] = LUA_NOREF;
        honey_key_callbacks_data[key] = LUA_NOREF;
    }
    else
	honey_lua_throw_error(L,
			      "'%d' is not a valid keycode",
			      key);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_key_unbind_all(lua_State* L)
{
    for (int i=0; i<HONEY_N_KEYS; i++) {
	luaL_unref(L, LUA_REGISTRYINDEX, honey_key_callbacks[i]);
	luaL_unref(L, LUA_REGISTRYINDEX, honey_key_callbacks_data[i]);
	
        honey_key_callbacks[i] = LUA_NOREF;
        honey_key_callbacks_data[i] = LUA_NOREF;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_mouse_set_mode(lua_State* L)
{
    int cursor_mode;

    honey_lua_parse_arguments
	(L, 1,
	 1, HONEY_INTEGER, &cursor_mode);

    if (honey_window_info_ref == LUA_NOREF ||
        honey_window_info_ref == LUA_REFNIL) {
        lua_pushstring(L, "ERROR: no window set!");
        lua_error(L);
    }
    
    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_window_info_ref);
    honey_window_information* info = lua_touserdata(L, -1);

    glfwSetInputMode(info->window, GLFW_CURSOR, cursor_mode);

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_mouse_movement_bind(lua_State* L)
{
    honey_lua_parse_arguments
	(L, 1,
	 2, HONEY_FUNCTION, HONEY_ANY);

    honey_mouse_movement_unbind(L); /* avoid memory leaks! */
    
    lua_pushvalue(L, 1);
    honey_mouse_movement_callback_ref = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_pushvalue(L, 2);
    honey_mouse_movement_callback_data_ref = luaL_ref(L, LUA_REGISTRYINDEX);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_mouse_movement_unbind(lua_State* L)
{
    int callback = honey_mouse_movement_callback_ref;
    int data = honey_mouse_movement_callback_data_ref;

    if (callback != LUA_NOREF || callback != LUA_REFNIL)
	luaL_unref(L, LUA_REGISTRYINDEX, callback);

    if (data != LUA_NOREF || data != LUA_REFNIL)
	luaL_unref(L, LUA_REGISTRYINDEX, data);

    honey_mouse_movement_callback_ref = LUA_NOREF;
    honey_mouse_movement_callback_data_ref = LUA_NOREF;
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void honey_glfw_mouse_movement_callback(honey_window window,
                                               double x_pos, double y_pos)
{
    int callback = honey_mouse_movement_callback_ref;
    int data = honey_mouse_movement_callback_data_ref;
    lua_State* L = glfwGetWindowUserPointer(window);
    
    if (callback == LUA_NOREF || callback == LUA_REFNIL)
        return;

    lua_rawgeti(L, LUA_REGISTRYINDEX, callback);
    lua_pushnumber(L, x_pos);
    lua_pushnumber(L, y_pos);

    if (data == LUA_NOREF || data == LUA_REFNIL)
        lua_pushnil(L);
    else
        lua_rawgeti(L, LUA_REGISTRYINDEX, data);

    honey_lua_pcall(L, 3, 0);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void execute_lua_key_callback(lua_State* L, int callback, int action, int data)
{
    if (callback != LUA_NOREF) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, callback);
        lua_pushinteger(L, action);
        if (data != LUA_REFNIL)
            lua_rawgeti(L, LUA_REGISTRYINDEX, data);
        else
            lua_pushnil(L);
        honey_lua_pcall(L, 2, 0);
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static void honey_glfw_keyboard_callback(honey_window window,
                                         int key, int scancode,
                                         int action, int mods)
{
    int callback, data;
    lua_State* L = glfwGetWindowUserPointer(window);
    switch (key) {
    case GLFW_KEY_UNKNOWN:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_UNKNOWN] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_UNKNOWN] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_UNKNOWN];
        data = honey_key_callbacks_data[HONEY_KEY_UNKNOWN];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_SPACE:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_SPACE] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_SPACE] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_SPACE];
        data = honey_key_callbacks_data[HONEY_KEY_SPACE];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_APOSTROPHE:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_APOSTROPHE] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_APOSTROPHE] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_APOSTROPHE];
        data = honey_key_callbacks_data[HONEY_KEY_APOSTROPHE];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_COMMA:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_COMMA] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_COMMA] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_COMMA];
        data = honey_key_callbacks_data[HONEY_KEY_COMMA];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_MINUS:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_MINUS] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_MINUS] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_MINUS];
        data = honey_key_callbacks_data[HONEY_KEY_MINUS];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_PERIOD:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_PERIOD] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_PERIOD] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_PERIOD];
        data = honey_key_callbacks_data[HONEY_KEY_PERIOD];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_SLASH:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_SLASH] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_SLASH] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_SLASH];
        data = honey_key_callbacks_data[HONEY_KEY_SLASH];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_0:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_0] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_0] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_0];
        data = honey_key_callbacks_data[HONEY_KEY_0];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_1:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_1] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_1] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_1];
        data = honey_key_callbacks_data[HONEY_KEY_1];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_2:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_2] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_2] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_2];
        data = honey_key_callbacks_data[HONEY_KEY_2];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_3:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_3] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_3] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_3];
        data = honey_key_callbacks_data[HONEY_KEY_3];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_4:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_4] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_4] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_4];
        data = honey_key_callbacks_data[HONEY_KEY_4];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_5:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_5] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_5] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_5];
        data = honey_key_callbacks_data[HONEY_KEY_5];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_6:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_6] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_6] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_6];
        data = honey_key_callbacks_data[HONEY_KEY_6];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_7:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_7] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_7] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_7];
        data = honey_key_callbacks_data[HONEY_KEY_7];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_8:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_8] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_8] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_8];
        data = honey_key_callbacks_data[HONEY_KEY_8];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_9:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_9] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_9] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_9];
        data = honey_key_callbacks_data[HONEY_KEY_9];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_SEMICOLON:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_SEMICOLON] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_SEMICOLON] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_SEMICOLON];
        data = honey_key_callbacks_data[HONEY_KEY_SEMICOLON];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_EQUAL:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_EQUAL] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_EQUAL] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_EQUAL];
        data = honey_key_callbacks_data[HONEY_KEY_EQUAL];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_A:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_A] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_A] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_A];
        data = honey_key_callbacks_data[HONEY_KEY_A];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_B:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_B] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_B] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_B];
        data = honey_key_callbacks_data[HONEY_KEY_B];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_C:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_C] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_C] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_C];
        data = honey_key_callbacks_data[HONEY_KEY_C];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_D:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_D] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_D] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_D];
        data = honey_key_callbacks_data[HONEY_KEY_D];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_E:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_E] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_E] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_E];
        data = honey_key_callbacks_data[HONEY_KEY_E];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F];
        data = honey_key_callbacks_data[HONEY_KEY_F];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_G:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_G] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_G] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_G];
        data = honey_key_callbacks_data[HONEY_KEY_G];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_H:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_H] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_H] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_H];
        data = honey_key_callbacks_data[HONEY_KEY_H];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_I:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_I] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_I] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_I];
        data = honey_key_callbacks_data[HONEY_KEY_I];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_J:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_J] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_J] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_J];
        data = honey_key_callbacks_data[HONEY_KEY_J];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_K:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_K] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_K] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_K];
        data = honey_key_callbacks_data[HONEY_KEY_K];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_L:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_L] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_L] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_L];
        data = honey_key_callbacks_data[HONEY_KEY_L];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_M:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_M] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_M] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_M];
        data = honey_key_callbacks_data[HONEY_KEY_M];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_N:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_N] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_N] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_N];
        data = honey_key_callbacks_data[HONEY_KEY_N];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_O:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_O] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_O] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_O];
        data = honey_key_callbacks_data[HONEY_KEY_O];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_P:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_P] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_P] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_P];
        data = honey_key_callbacks_data[HONEY_KEY_P];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_Q:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_Q] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_Q] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_Q];
        data = honey_key_callbacks_data[HONEY_KEY_Q];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_R:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_R] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_R] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_R];
        data = honey_key_callbacks_data[HONEY_KEY_R];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_S:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_S] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_S] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_S];
        data = honey_key_callbacks_data[HONEY_KEY_S];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_T:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_T] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_T] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_T];
        data = honey_key_callbacks_data[HONEY_KEY_T];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_U:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_U] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_U] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_U];
        data = honey_key_callbacks_data[HONEY_KEY_U];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_V:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_V] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_V] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_V];
        data = honey_key_callbacks_data[HONEY_KEY_V];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_W:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_W] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_W] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_W];
        data = honey_key_callbacks_data[HONEY_KEY_W];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_X:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_X] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_X] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_X];
        data = honey_key_callbacks_data[HONEY_KEY_X];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_Y:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_Y] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_Y] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_Y];
        data = honey_key_callbacks_data[HONEY_KEY_Y];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_Z:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_Z] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_Z] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_Z];
        data = honey_key_callbacks_data[HONEY_KEY_Z];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_LEFT_BRACKET:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_LEFT_BRACKET] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_LEFT_BRACKET] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_LEFT_BRACKET];
        data = honey_key_callbacks_data[HONEY_KEY_LEFT_BRACKET];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_BACKSLASH:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_BACKSLASH] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_BACKSLASH] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_BACKSLASH];
        data = honey_key_callbacks_data[HONEY_KEY_BACKSLASH];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_RIGHT_BRACKET:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_RIGHT_BRACKET] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_RIGHT_BRACKET] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_RIGHT_BRACKET];
        data = honey_key_callbacks_data[HONEY_KEY_RIGHT_BRACKET];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_GRAVE_ACCENT:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_GRAVE_ACCENT] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_GRAVE_ACCENT] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_GRAVE_ACCENT];
        data = honey_key_callbacks_data[HONEY_KEY_GRAVE_ACCENT];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_WORLD_1:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_WORLD_1] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_WORLD_1] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_WORLD_1];
        data = honey_key_callbacks_data[HONEY_KEY_WORLD_1];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_WORLD_2:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_WORLD_2] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_WORLD_2] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_WORLD_2];
        data = honey_key_callbacks_data[HONEY_KEY_WORLD_2];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_ESCAPE:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_ESCAPE] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_ESCAPE] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_ESCAPE];
        data = honey_key_callbacks_data[HONEY_KEY_ESCAPE];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_ENTER:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_ENTER] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_ENTER] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_ENTER];
        data = honey_key_callbacks_data[HONEY_KEY_ENTER];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_TAB:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_TAB] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_TAB] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_TAB];
        data = honey_key_callbacks_data[HONEY_KEY_TAB];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_BACKSPACE:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_BACKSPACE] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_BACKSPACE] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_BACKSPACE];
        data = honey_key_callbacks_data[HONEY_KEY_BACKSPACE];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_INSERT:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_INSERT] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_INSERT] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_INSERT];
        data = honey_key_callbacks_data[HONEY_KEY_INSERT];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_DELETE:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_DELETE] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_DELETE] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_DELETE];
        data = honey_key_callbacks_data[HONEY_KEY_DELETE];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_RIGHT:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_RIGHT] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_RIGHT] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_RIGHT];
        data = honey_key_callbacks_data[HONEY_KEY_RIGHT];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_LEFT:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_LEFT] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_LEFT] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_LEFT];
        data = honey_key_callbacks_data[HONEY_KEY_LEFT];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_DOWN:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_DOWN] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_DOWN] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_DOWN];
        data = honey_key_callbacks_data[HONEY_KEY_DOWN];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_UP:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_UP] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_UP] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_UP];
        data = honey_key_callbacks_data[HONEY_KEY_UP];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_PAGE_UP:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_PAGE_UP] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_PAGE_UP] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_PAGE_UP];
        data = honey_key_callbacks_data[HONEY_KEY_PAGE_UP];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_PAGE_DOWN:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_PAGE_DOWN] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_PAGE_DOWN] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_PAGE_DOWN];
        data = honey_key_callbacks_data[HONEY_KEY_PAGE_DOWN];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_HOME:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_HOME] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_HOME] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_HOME];
        data = honey_key_callbacks_data[HONEY_KEY_HOME];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_END:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_END] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_END] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_END];
        data = honey_key_callbacks_data[HONEY_KEY_END];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_CAPS_LOCK:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_CAPS_LOCK] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_CAPS_LOCK] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_CAPS_LOCK];
        data = honey_key_callbacks_data[HONEY_KEY_CAPS_LOCK];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_SCROLL_LOCK:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_SCROLL_LOCK] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_SCROLL_LOCK] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_SCROLL_LOCK];
        data = honey_key_callbacks_data[HONEY_KEY_SCROLL_LOCK];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_NUM_LOCK:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_NUM_LOCK] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_NUM_LOCK] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_NUM_LOCK];
        data = honey_key_callbacks_data[HONEY_KEY_NUM_LOCK];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_PRINT_SCREEN:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_PRINT_SCREEN] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_PRINT_SCREEN] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_PRINT_SCREEN];
        data = honey_key_callbacks_data[HONEY_KEY_PRINT_SCREEN];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_PAUSE:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_PAUSE] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_PAUSE] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_PAUSE];
        data = honey_key_callbacks_data[HONEY_KEY_PAUSE];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F1:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F1] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F1] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F1];
        data = honey_key_callbacks_data[HONEY_KEY_F1];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F2:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F2] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F2] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F2];
        data = honey_key_callbacks_data[HONEY_KEY_F2];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F3:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F3] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F3] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F3];
        data = honey_key_callbacks_data[HONEY_KEY_F3];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F4:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F4] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F4] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F4];
        data = honey_key_callbacks_data[HONEY_KEY_F4];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F5:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F5] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F5] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F5];
        data = honey_key_callbacks_data[HONEY_KEY_F5];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F6:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F6] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F6] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F6];
        data = honey_key_callbacks_data[HONEY_KEY_F6];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F7:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F7] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F7] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F7];
        data = honey_key_callbacks_data[HONEY_KEY_F7];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F8:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F8] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F8] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F8];
        data = honey_key_callbacks_data[HONEY_KEY_F8];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F9:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F9] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F9] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F9];
        data = honey_key_callbacks_data[HONEY_KEY_F9];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F10:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F10] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F10] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F10];
        data = honey_key_callbacks_data[HONEY_KEY_F10];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F11:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F11] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F11] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F11];
        data = honey_key_callbacks_data[HONEY_KEY_F11];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F12:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F12] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F12] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F12];
        data = honey_key_callbacks_data[HONEY_KEY_F12];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F13:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F13] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F13] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F13];
        data = honey_key_callbacks_data[HONEY_KEY_F13];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F14:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F14] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F14] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F14];
        data = honey_key_callbacks_data[HONEY_KEY_F14];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F15:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F15] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F15] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F15];
        data = honey_key_callbacks_data[HONEY_KEY_F15];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F16:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F16] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F16] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F16];
        data = honey_key_callbacks_data[HONEY_KEY_F16];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F17:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F17] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F17] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F17];
        data = honey_key_callbacks_data[HONEY_KEY_F17];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F18:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F18] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F18] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F18];
        data = honey_key_callbacks_data[HONEY_KEY_F18];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F19:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F19] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F19] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F19];
        data = honey_key_callbacks_data[HONEY_KEY_F19];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F20:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F20] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F20] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F20];
        data = honey_key_callbacks_data[HONEY_KEY_F20];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F21:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F21] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F21] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F21];
        data = honey_key_callbacks_data[HONEY_KEY_F21];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F22:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F22] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F22] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F22];
        data = honey_key_callbacks_data[HONEY_KEY_F22];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F23:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F23] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F23] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F23];
        data = honey_key_callbacks_data[HONEY_KEY_F23];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F24:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F24] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F24] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F24];
        data = honey_key_callbacks_data[HONEY_KEY_F24];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_F25:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_F25] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_F25] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_F25];
        data = honey_key_callbacks_data[HONEY_KEY_F25];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_KP_0:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_0] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_0] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_KP_0];
        data = honey_key_callbacks_data[HONEY_KEY_KP_0];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_KP_1:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_1] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_1] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_KP_1];
        data = honey_key_callbacks_data[HONEY_KEY_KP_1];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_KP_2:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_2] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_2] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_KP_2];
        data = honey_key_callbacks_data[HONEY_KEY_KP_2];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_KP_3:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_3] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_3] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_KP_3];
        data = honey_key_callbacks_data[HONEY_KEY_KP_3];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_KP_4:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_4] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_4] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_KP_4];
        data = honey_key_callbacks_data[HONEY_KEY_KP_4];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_KP_5:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_5] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_5] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_KP_5];
        data = honey_key_callbacks_data[HONEY_KEY_KP_5];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_KP_6:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_6] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_6] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_KP_6];
        data = honey_key_callbacks_data[HONEY_KEY_KP_6];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_KP_7:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_7] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_7] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_KP_7];
        data = honey_key_callbacks_data[HONEY_KEY_KP_7];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_KP_8:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_8] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_8] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_KP_8];
        data = honey_key_callbacks_data[HONEY_KEY_KP_8];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_KP_9:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_9] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_9] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_KP_9];
        data = honey_key_callbacks_data[HONEY_KEY_KP_9];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_KP_DECIMAL:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_DECIMAL] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_DECIMAL] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_KP_DECIMAL];
        data = honey_key_callbacks_data[HONEY_KEY_KP_DECIMAL];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_KP_DIVIDE:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_DIVIDE] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_DIVIDE] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_KP_DIVIDE];
        data = honey_key_callbacks_data[HONEY_KEY_KP_DIVIDE];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_KP_MULTIPLY:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_MULTIPLY] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_MULTIPLY] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_KP_MULTIPLY];
        data = honey_key_callbacks_data[HONEY_KEY_KP_MULTIPLY];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_KP_SUBTRACT:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_SUBTRACT] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_SUBTRACT] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_KP_SUBTRACT];
        data = honey_key_callbacks_data[HONEY_KEY_KP_SUBTRACT];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_KP_ADD:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_ADD] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_ADD] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_KP_ADD];
        data = honey_key_callbacks_data[HONEY_KEY_KP_ADD];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_KP_ENTER:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_ENTER] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_ENTER] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_KP_ENTER];
        data = honey_key_callbacks_data[HONEY_KEY_KP_ENTER];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_KP_EQUAL:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_KP_EQUAL] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_KP_EQUAL] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_KP_EQUAL];
        data = honey_key_callbacks_data[HONEY_KEY_KP_EQUAL];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_LEFT_SHIFT:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_LEFT_SHIFT] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_LEFT_SHIFT] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_LEFT_SHIFT];
        data = honey_key_callbacks_data[HONEY_KEY_LEFT_SHIFT];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_LEFT_CONTROL:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_LEFT_CONTROL] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_LEFT_CONTROL] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_LEFT_CONTROL];
        data = honey_key_callbacks_data[HONEY_KEY_LEFT_CONTROL];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_LEFT_ALT:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_LEFT_ALT] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_LEFT_ALT] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_LEFT_ALT];
        data = honey_key_callbacks_data[HONEY_KEY_LEFT_ALT];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_LEFT_SUPER:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_LEFT_SUPER] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_LEFT_SUPER] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_LEFT_SUPER];
        data = honey_key_callbacks_data[HONEY_KEY_LEFT_SUPER];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_RIGHT_SHIFT:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_RIGHT_SHIFT] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_RIGHT_SHIFT] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_RIGHT_SHIFT];
        data = honey_key_callbacks_data[HONEY_KEY_RIGHT_SHIFT];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_RIGHT_CONTROL:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_RIGHT_CONTROL] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_RIGHT_CONTROL] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_RIGHT_CONTROL];
        data = honey_key_callbacks_data[HONEY_KEY_RIGHT_CONTROL];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_RIGHT_ALT:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_RIGHT_ALT] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_RIGHT_ALT] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_RIGHT_ALT];
        data = honey_key_callbacks_data[HONEY_KEY_RIGHT_ALT];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_RIGHT_SUPER:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_RIGHT_SUPER] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_RIGHT_SUPER] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_RIGHT_SUPER];
        data = honey_key_callbacks_data[HONEY_KEY_RIGHT_SUPER];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    case GLFW_KEY_MENU:
        if (action == HONEY_KEY_PRESS)   { honey_key_states[HONEY_KEY_MENU] = 1; }
        if (action == HONEY_KEY_RELEASE) { honey_key_states[HONEY_KEY_MENU] = 0; }
        callback = honey_key_callbacks[HONEY_KEY_MENU];
        data = honey_key_callbacks_data[HONEY_KEY_MENU];
        execute_lua_key_callback(L, callback, action, data);
        break;
        
    default:
        /* do nothing */
        break;
    }
}
