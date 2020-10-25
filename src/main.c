#include "honey.h"

int main(int argc, char** argv)
{
    honey_options opts;
    if (!honey_parse_options(&opts, argc, argv)) {
        return 0;
    }

    honey_window window;
    lua_State* L;

    if (!honey_setup(&L, &window))
        return 1;

    char* script;
    honey_result res = honey_format_string(&script,
                                           "%s/main.lua",
                                           opts.script_directory);
    if (res != HONEY_OK) {
        fprintf(stderr, "[honey] FATAL: could not allocate space for script filename!");
        return 1;
    }
    
    if (luaL_loadfile(L, script) == 0) {
        if (!honey_lua_pcall(L, 0, 1) == 0) {
            const char* error = lua_tostring(L, -1);
            fprintf(stderr, "[honey] ERROR: %s\n", error);
            return 1;
        }
    }
    else {
        fprintf(stderr, "ERROR: failed to open %s!\n", script);
        return 1;
    }

    int update_callback = honey_get_callback(L, "update");
    int draw_callback   = honey_get_callback(L, "draw");
    
    float prevTime = 0;
    float currentTime = 0;
    float dt;
    
    while (!glfwWindowShouldClose(window)) {
        currentTime = (float) glfwGetTime();
        dt = currentTime - prevTime;
        prevTime = currentTime;
        glfwPollEvents();

        if (update_callback != LUA_NOREF) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, update_callback);
            lua_pushnumber(L, dt);
            int result = honey_lua_pcall(L, 1, 0);
            if (result != 0) {
                const char* error = lua_tostring(L, -1);
                fprintf(stderr, "[honey] ERROR: %s\n", error);
                glfwSetWindowShouldClose(window, true);
            }
        }

        if (draw_callback != LUA_NOREF) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, draw_callback);
            int result = honey_lua_pcall(L, 0, 0);
            if (result != 0) {
                const char* error = lua_tostring(L, -1);
                fprintf(stderr, "[honey] ERROR: %s\n", error);
                glfwSetWindowShouldClose(window, true);
            }
        }
    }

    lua_close(L);
    
    glfwTerminate();
    return 0;
}
