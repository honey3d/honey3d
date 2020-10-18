#ifndef HONEY_INPUT_H
#define HONEY_INPUT_H

#include <lua.h>

/* @brief Place a lua table containing the enum values for GLFW keys on the stack. */
void honey_setup_input(lua_State* L)
{

    lua_createtable(L, 0, 121);

    lua_pushinteger(L, 0);
    lua_setfield(L, -2, "unknown");

    lua_pushinteger(L, 1);
    lua_setfield(L, -2, "space");

    lua_pushinteger(L, 2);
    lua_setfield(L, -2, "apostrophe");

    lua_pushinteger(L, 3);
    lua_setfield(L, -2, "comma");

    lua_pushinteger(L, 4);
    lua_setfield(L, -2, "minus");

    lua_pushinteger(L, 5);
    lua_setfield(L, -2, "period");

    lua_pushinteger(L, 6);
    lua_setfield(L, -2, "slash");

    lua_pushinteger(L, 7);
    lua_setfield(L, -2, "0");

    lua_pushinteger(L, 8);
    lua_setfield(L, -2, "1");

    lua_pushinteger(L, 9);
    lua_setfield(L, -2, "2");

    lua_pushinteger(L, 10);
    lua_setfield(L, -2, "3");

    lua_pushinteger(L, 11);
    lua_setfield(L, -2, "4");

    lua_pushinteger(L, 12);
    lua_setfield(L, -2, "5");

    lua_pushinteger(L, 13);
    lua_setfield(L, -2, "6");

    lua_pushinteger(L, 14);
    lua_setfield(L, -2, "7");

    lua_pushinteger(L, 15);
    lua_setfield(L, -2, "8");

    lua_pushinteger(L, 16);
    lua_setfield(L, -2, "9");

    lua_pushinteger(L, 17);
    lua_setfield(L, -2, "semicolon");

    lua_pushinteger(L, 18);
    lua_setfield(L, -2, "equal");

    lua_pushinteger(L, 19);
    lua_setfield(L, -2, "a");

    lua_pushinteger(L, 20);
    lua_setfield(L, -2, "b");

    lua_pushinteger(L, 21);
    lua_setfield(L, -2, "c");

    lua_pushinteger(L, 22);
    lua_setfield(L, -2, "d");

    lua_pushinteger(L, 23);
    lua_setfield(L, -2, "e");

    lua_pushinteger(L, 24);
    lua_setfield(L, -2, "f");

    lua_pushinteger(L, 25);
    lua_setfield(L, -2, "g");

    lua_pushinteger(L, 26);
    lua_setfield(L, -2, "h");

    lua_pushinteger(L, 27);
    lua_setfield(L, -2, "i");

    lua_pushinteger(L, 28);
    lua_setfield(L, -2, "j");

    lua_pushinteger(L, 29);
    lua_setfield(L, -2, "k");

    lua_pushinteger(L, 30);
    lua_setfield(L, -2, "l");

    lua_pushinteger(L, 31);
    lua_setfield(L, -2, "m");

    lua_pushinteger(L, 32);
    lua_setfield(L, -2, "n");

    lua_pushinteger(L, 33);
    lua_setfield(L, -2, "o");

    lua_pushinteger(L, 34);
    lua_setfield(L, -2, "p");

    lua_pushinteger(L, 35);
    lua_setfield(L, -2, "q");

    lua_pushinteger(L, 36);
    lua_setfield(L, -2, "r");

    lua_pushinteger(L, 37);
    lua_setfield(L, -2, "s");

    lua_pushinteger(L, 38);
    lua_setfield(L, -2, "t");

    lua_pushinteger(L, 39);
    lua_setfield(L, -2, "u");

    lua_pushinteger(L, 40);
    lua_setfield(L, -2, "v");

    lua_pushinteger(L, 41);
    lua_setfield(L, -2, "w");

    lua_pushinteger(L, 42);
    lua_setfield(L, -2, "x");

    lua_pushinteger(L, 43);
    lua_setfield(L, -2, "y");

    lua_pushinteger(L, 44);
    lua_setfield(L, -2, "z");

    lua_pushinteger(L, 45);
    lua_setfield(L, -2, "left_bracket");

    lua_pushinteger(L, 46);
    lua_setfield(L, -2, "backslash");

    lua_pushinteger(L, 47);
    lua_setfield(L, -2, "right_bracket");

    lua_pushinteger(L, 48);
    lua_setfield(L, -2, "grave_accent");

    lua_pushinteger(L, 49);
    lua_setfield(L, -2, "world_1");

    lua_pushinteger(L, 50);
    lua_setfield(L, -2, "world_2");

    lua_pushinteger(L, 51);
    lua_setfield(L, -2, "escape");

    lua_pushinteger(L, 52);
    lua_setfield(L, -2, "enter");

    lua_pushinteger(L, 53);
    lua_setfield(L, -2, "tab");

    lua_pushinteger(L, 54);
    lua_setfield(L, -2, "backspace");

    lua_pushinteger(L, 55);
    lua_setfield(L, -2, "insert");

    lua_pushinteger(L, 56);
    lua_setfield(L, -2, "delete");

    lua_pushinteger(L, 57);
    lua_setfield(L, -2, "right");

    lua_pushinteger(L, 58);
    lua_setfield(L, -2, "left");

    lua_pushinteger(L, 59);
    lua_setfield(L, -2, "down");

    lua_pushinteger(L, 60);
    lua_setfield(L, -2, "up");

    lua_pushinteger(L, 61);
    lua_setfield(L, -2, "page_up");

    lua_pushinteger(L, 62);
    lua_setfield(L, -2, "page_down");

    lua_pushinteger(L, 63);
    lua_setfield(L, -2, "home");

    lua_pushinteger(L, 64);
    lua_setfield(L, -2, "end");

    lua_pushinteger(L, 65);
    lua_setfield(L, -2, "caps_lock");

    lua_pushinteger(L, 66);
    lua_setfield(L, -2, "scroll_lock");

    lua_pushinteger(L, 67);
    lua_setfield(L, -2, "num_lock");

    lua_pushinteger(L, 68);
    lua_setfield(L, -2, "print_screen");

    lua_pushinteger(L, 69);
    lua_setfield(L, -2, "pause");

    lua_pushinteger(L, 70);
    lua_setfield(L, -2, "f1");

    lua_pushinteger(L, 71);
    lua_setfield(L, -2, "f2");

    lua_pushinteger(L, 72);
    lua_setfield(L, -2, "f3");

    lua_pushinteger(L, 73);
    lua_setfield(L, -2, "f4");

    lua_pushinteger(L, 74);
    lua_setfield(L, -2, "f5");

    lua_pushinteger(L, 75);
    lua_setfield(L, -2, "f6");

    lua_pushinteger(L, 76);
    lua_setfield(L, -2, "f7");

    lua_pushinteger(L, 77);
    lua_setfield(L, -2, "f8");

    lua_pushinteger(L, 78);
    lua_setfield(L, -2, "f9");

    lua_pushinteger(L, 79);
    lua_setfield(L, -2, "f10");

    lua_pushinteger(L, 80);
    lua_setfield(L, -2, "f11");

    lua_pushinteger(L, 81);
    lua_setfield(L, -2, "f12");

    lua_pushinteger(L, 82);
    lua_setfield(L, -2, "f13");

    lua_pushinteger(L, 83);
    lua_setfield(L, -2, "f14");

    lua_pushinteger(L, 84);
    lua_setfield(L, -2, "f15");

    lua_pushinteger(L, 85);
    lua_setfield(L, -2, "f16");

    lua_pushinteger(L, 86);
    lua_setfield(L, -2, "f17");

    lua_pushinteger(L, 87);
    lua_setfield(L, -2, "f18");

    lua_pushinteger(L, 88);
    lua_setfield(L, -2, "f19");

    lua_pushinteger(L, 89);
    lua_setfield(L, -2, "f20");

    lua_pushinteger(L, 90);
    lua_setfield(L, -2, "f21");

    lua_pushinteger(L, 91);
    lua_setfield(L, -2, "f22");

    lua_pushinteger(L, 92);
    lua_setfield(L, -2, "f23");

    lua_pushinteger(L, 93);
    lua_setfield(L, -2, "f24");

    lua_pushinteger(L, 94);
    lua_setfield(L, -2, "f25");

    lua_pushinteger(L, 95);
    lua_setfield(L, -2, "kp_0");

    lua_pushinteger(L, 96);
    lua_setfield(L, -2, "kp_1");

    lua_pushinteger(L, 97);
    lua_setfield(L, -2, "kp_2");

    lua_pushinteger(L, 98);
    lua_setfield(L, -2, "kp_3");

    lua_pushinteger(L, 99);
    lua_setfield(L, -2, "kp_4");

    lua_pushinteger(L, 100);
    lua_setfield(L, -2, "kp_5");

    lua_pushinteger(L, 101);
    lua_setfield(L, -2, "kp_6");

    lua_pushinteger(L, 102);
    lua_setfield(L, -2, "kp_7");

    lua_pushinteger(L, 103);
    lua_setfield(L, -2, "kp_8");

    lua_pushinteger(L, 104);
    lua_setfield(L, -2, "kp_9");

    lua_pushinteger(L, 105);
    lua_setfield(L, -2, "kp_decimal");

    lua_pushinteger(L, 106);
    lua_setfield(L, -2, "kp_divide");

    lua_pushinteger(L, 107);
    lua_setfield(L, -2, "kp_multiply");

    lua_pushinteger(L, 108);
    lua_setfield(L, -2, "kp_subtract");

    lua_pushinteger(L, 109);
    lua_setfield(L, -2, "kp_add");

    lua_pushinteger(L, 110);
    lua_setfield(L, -2, "kp_enter");

    lua_pushinteger(L, 111);
    lua_setfield(L, -2, "kp_equal");

    lua_pushinteger(L, 112);
    lua_setfield(L, -2, "left_shift");

    lua_pushinteger(L, 113);
    lua_setfield(L, -2, "left_control");

    lua_pushinteger(L, 114);
    lua_setfield(L, -2, "left_alt");

    lua_pushinteger(L, 115);
    lua_setfield(L, -2, "left_super");

    lua_pushinteger(L, 116);
    lua_setfield(L, -2, "right_shift");

    lua_pushinteger(L, 117);
    lua_setfield(L, -2, "right_control");

    lua_pushinteger(L, 118);
    lua_setfield(L, -2, "right_alt");

    lua_pushinteger(L, 119);
    lua_setfield(L, -2, "right_super");

    lua_pushinteger(L, 120);
    lua_setfield(L, -2, "menu");
}

#endif
