#ifndef HONEY_INPUT_H
#define HONEY_INPUT_H

/** @file input.h
 *
 * @brief Wrap GLFW input functions for honey.
 */

#include "../common.h"

#define HONEY_KEY_UNKNOWN 0
#define HONEY_KEY_SPACE 1
#define HONEY_KEY_APOSTROPHE 2
#define HONEY_KEY_COMMA 3
#define HONEY_KEY_MINUS 4
#define HONEY_KEY_PERIOD 5
#define HONEY_KEY_SLASH 6
#define HONEY_KEY_0 7
#define HONEY_KEY_1 8
#define HONEY_KEY_2 9
#define HONEY_KEY_3 10
#define HONEY_KEY_4 11
#define HONEY_KEY_5 12
#define HONEY_KEY_6 13
#define HONEY_KEY_7 14
#define HONEY_KEY_8 15
#define HONEY_KEY_9 16
#define HONEY_KEY_SEMICOLON 17
#define HONEY_KEY_EQUAL 18
#define HONEY_KEY_A 19
#define HONEY_KEY_B 20
#define HONEY_KEY_C 21
#define HONEY_KEY_D 22
#define HONEY_KEY_E 23
#define HONEY_KEY_F 24
#define HONEY_KEY_G 25
#define HONEY_KEY_H 26
#define HONEY_KEY_I 27
#define HONEY_KEY_J 28
#define HONEY_KEY_K 29
#define HONEY_KEY_L 30
#define HONEY_KEY_M 31
#define HONEY_KEY_N 32
#define HONEY_KEY_O 33
#define HONEY_KEY_P 34
#define HONEY_KEY_Q 35
#define HONEY_KEY_R 36
#define HONEY_KEY_S 37
#define HONEY_KEY_T 38
#define HONEY_KEY_U 39
#define HONEY_KEY_V 40
#define HONEY_KEY_W 41
#define HONEY_KEY_X 42
#define HONEY_KEY_Y 43
#define HONEY_KEY_Z 44
#define HONEY_KEY_LEFT_BRACKET 45
#define HONEY_KEY_BACKSLASH 46
#define HONEY_KEY_RIGHT_BRACKET 47
#define HONEY_KEY_GRAVE_ACCENT 48
#define HONEY_KEY_WORLD_1 49
#define HONEY_KEY_WORLD_2 50
#define HONEY_KEY_ESCAPE 51
#define HONEY_KEY_ENTER 52
#define HONEY_KEY_TAB 53
#define HONEY_KEY_BACKSPACE 54
#define HONEY_KEY_INSERT 55
#define HONEY_KEY_DELETE 56
#define HONEY_KEY_RIGHT 57
#define HONEY_KEY_LEFT 58
#define HONEY_KEY_DOWN 59
#define HONEY_KEY_UP 60
#define HONEY_KEY_PAGE_UP 61
#define HONEY_KEY_PAGE_DOWN 62
#define HONEY_KEY_HOME 63
#define HONEY_KEY_END 64
#define HONEY_KEY_CAPS_LOCK 65
#define HONEY_KEY_SCROLL_LOCK 66
#define HONEY_KEY_NUM_LOCK 67
#define HONEY_KEY_PRINT_SCREEN 68
#define HONEY_KEY_PAUSE 69
#define HONEY_KEY_F1 70
#define HONEY_KEY_F2 71
#define HONEY_KEY_F3 72
#define HONEY_KEY_F4 73
#define HONEY_KEY_F5 74
#define HONEY_KEY_F6 75
#define HONEY_KEY_F7 76
#define HONEY_KEY_F8 77
#define HONEY_KEY_F9 78
#define HONEY_KEY_F10 79
#define HONEY_KEY_F11 80
#define HONEY_KEY_F12 81
#define HONEY_KEY_F13 82
#define HONEY_KEY_F14 83
#define HONEY_KEY_F15 84
#define HONEY_KEY_F16 85
#define HONEY_KEY_F17 86
#define HONEY_KEY_F18 87
#define HONEY_KEY_F19 88
#define HONEY_KEY_F20 89
#define HONEY_KEY_F21 90
#define HONEY_KEY_F22 91
#define HONEY_KEY_F23 92
#define HONEY_KEY_F24 93
#define HONEY_KEY_F25 94
#define HONEY_KEY_KP_0 95
#define HONEY_KEY_KP_1 96
#define HONEY_KEY_KP_2 97
#define HONEY_KEY_KP_3 98
#define HONEY_KEY_KP_4 99
#define HONEY_KEY_KP_5 100
#define HONEY_KEY_KP_6 101
#define HONEY_KEY_KP_7 102
#define HONEY_KEY_KP_8 103
#define HONEY_KEY_KP_9 104
#define HONEY_KEY_KP_DECIMAL 105
#define HONEY_KEY_KP_DIVIDE 106
#define HONEY_KEY_KP_MULTIPLY 107
#define HONEY_KEY_KP_SUBTRACT 108
#define HONEY_KEY_KP_ADD 109
#define HONEY_KEY_KP_ENTER 110
#define HONEY_KEY_KP_EQUAL 111
#define HONEY_KEY_LEFT_SHIFT 112
#define HONEY_KEY_LEFT_CONTROL 113
#define HONEY_KEY_LEFT_ALT 114
#define HONEY_KEY_LEFT_SUPER 115
#define HONEY_KEY_RIGHT_SHIFT 116
#define HONEY_KEY_RIGHT_CONTROL 117
#define HONEY_KEY_RIGHT_ALT 118
#define HONEY_KEY_RIGHT_SUPER 119
#define HONEY_KEY_MENU 120

#define HONEY_N_KEYS 121

#define HONEY_KEY_PRESS GLFW_PRESS
#define HONEY_KEY_RELEASE GLFW_RELEASE

unsigned int honey_key_states[HONEY_N_KEYS];
static void (*honey_key_callbacks[HONEY_N_KEYS])(void*, int);
static void* honey_key_callbacks_data[HONEY_N_KEYS];
static void (*honey_keyboard_callback)(honey_window window, int key, int scancode, int action, int mods);

/** @brief Initializes Honey's internal keyboard states.
 * 
 * This function is called by honey_setup, so you shouldn't need
 * to manually call it in most cases.
 */
void honey_setup_keyboard();

/* @brief Place a lua table containing the enum values for GLFW keys on the stack. 
 * 
 * @param L The lua state to place the table on the top of the stack.
 *
 * @returns Nothing.
 */
void honey_setup_input(lua_State* L);

/** @brief Check if a key is down.
 *
 * This function accepts a single integer as input and returns TRUE if the integer
 * refers to a valid key and is pressed down, and false otherwise.
 *
 * @param[in] L The lua state.
 * 
 * @return 1 on success and 0 on failure.
 */
int honey_key_down(lua_State* L);

/** @brief Bind a callback to a key.
 *
 * The callback must have signature (void*, int), where the first argument is supplied by the 
 * void* supplied with this function, and the int is one of HONEY_KEY_PRESS or HONEY_KEY_RELEASE,
 * depending on the action that triggered the callback.
 *
 * @param[in] key The key to bind the callback to.
 * @param[in] callback The callback function to bind.
 * @param[in] data Data to pass to the callback function upon triggering.
 */
void honey_key_bind(int key, void (*callback)(void*, int), void* data);

/** @brief Unbind a key callback.
 *
 * THIS FUNCTION DOES NOT FREE MEMORY! If you allocated any, be sure to free it yourself!
 *
 * @param[in] key The key to unbind a callback from.
 */
void honey_key_unbind(int key);

/** @brief Unbind all key callbacks.
 *
 * THIS FUNCTION DOES NOT FREE MEMORY! If you allocated any, be sure to free it yourself!
 */
void honey_key_unbind_all();

void default_honey_keyboard_callback(honey_window window, int key, int scancode, int action, int mods);

#endif
