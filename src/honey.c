#include "honey.h"

void honey_print_help()
{
    printf("usage: honey [OPTIONS] SCRIPT_DIR\n"
           "  -v        Enable verbose logging\n"
           "  -h        Show this help message and exit\n"
           "  -l LOG    Log to LOG instead of stdout\n");
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

bool honey_parse_options(honey_options* options, int argc, char** argv)
{
    honey_options opts;
    opts.verbose = false;
    opts.script_directory = NULL;
    opts.logfile = NULL;

    opterr = 0;
    int c;

    while ((c = getopt(argc, argv, "vhl:")) != -1) {
        switch (c) {
        case 'v':
            opts.verbose = true;
            break;

        case 'h':
            honey_print_help();
            return false;

        case 'l':
            opts.logfile = optarg;
            break;

        case '?':
            fprintf(stderr, "unknown option: '%c'\n", optopt);
            honey_print_help();
            return false;

        default:
            return false;
        }
    }

    if (optind < argc) {
        opts.script_directory = argv[optind];
    }

    *options = opts;

    return true;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

static int honey_lua_clear_color(lua_State* L)
{
    float* color_array;
    bool color, depth, stencil;
    honey_lua_parse_arguments(L, 4,
                              HONEY_USERDATA, &color_array,
                              HONEY_BOOLEAN, &color,
                              HONEY_BOOLEAN, &depth,
                              HONEY_BOOLEAN, &stencil);
    float r = color_array[0];
    float g = color_array[1];
    float b = color_array[2];
    float a = color_array[3];

    int clear_flags = 0;
    if (color)
        clear_flags = clear_flags | GL_COLOR_BUFFER_BIT;
    if (depth)
        clear_flags = clear_flags | GL_DEPTH_BUFFER_BIT;
    if (stencil)
        clear_flags = clear_flags | GL_STENCIL_BUFFER_BIT;

    glClearColor(r, g, b, a);
    glClear(clear_flags);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_lua_enable_depth_test(lua_State* L)
{
    bool enable;
    honey_lua_parse_arguments(L, 1, HONEY_BOOLEAN, &enable);
    if (enable)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
    return 0;
}

int honey_lua_set_viewport_size(lua_State* L)
{
    int width, height;
    honey_lua_parse_arguments(L, 2,
                              HONEY_INTEGER, &width,
                              HONEY_INTEGER, &height);
    glViewport(0,0,width,height);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    
bool honey_setup(lua_State** L)
{
    /* set up lua and honey lua bindings */
    *L = luaL_newstate();
    luaL_openlibs(*L);

    lua_createtable(*L, 0, 1);

    if (!honey_setup_window(*L))
        return false;
    lua_setfield(*L, -2, "window");

    honey_setup_input(*L);
    lua_setfield(*L, -2, "input");

    honey_setup_cglm(*L);
    lua_setfield(*L, -2, "cglm");

    honey_setup_shader(*L);
    lua_setfield(*L, -2, "shader");

    honey_setup_mesh(*L);
    lua_setfield(*L, -2, "mesh");

    honey_setup_primitives(*L);
    lua_setfield(*L, -2, "primitives");

    honey_setup_texture(*L);
    lua_setfield(*L, -2, "texture");

    lua_pushcfunction(*L, honey_exit);
    lua_setfield(*L, -2, "exit");

    lua_pushcfunction(*L, honey_set_framebuffer);
    lua_setfield(*L, -2, "set_framebuffer");

    lua_pushcfunction(*L, honey_lua_clear_color);
    lua_setfield(*L, -2, "clear_color");

    lua_pushcfunction(*L, honey_lua_enable_depth_test);
    lua_setfield(*L, -2, "enable_depth_test");

    lua_pushcfunction(*L, honey_lua_set_viewport_size);
    lua_setfield(*L, -2, "set_viewport_size");

    lua_setglobal(*L, "honey");

    return true;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

bool honey_run(lua_State* L, honey_options opts) {
    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_window_info_ref);
    honey_window_information* info = lua_touserdata(L, -1);
    honey_window window = info->window;

    chdir(opts.script_directory);
    
    if (luaL_loadfile(L, "main.lua") == 0) {
        if (!honey_lua_pcall(L, 0, 1) == 0) {
            const char* error = lua_tostring(L, -1);
            fprintf(stderr, "[honey] ERROR: %s\n", error);
            return false;
        }
    }
    else {
        
        fprintf(stderr,
                "[honey] ERROR: failed to load main.lua: %s!\n",
                lua_tostring(L, -1));
        return false;
    }

    int update_callback = honey_get_callback(L, "update");
    int draw_callback   = honey_get_callback(L, "draw");
    
    float prevTime = 0;
    float currentTime = 0;
    float dt;
    float drawTime = 0;
    
    while (!glfwWindowShouldClose(window)) {
        currentTime = (float) glfwGetTime();
        dt = currentTime - prevTime;
        prevTime = currentTime;
        drawTime += dt;
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

        if (drawTime > 0.016) {
            drawTime -= 0.016;
        
            if (draw_callback != LUA_NOREF) {
                lua_rawgeti(L, LUA_REGISTRYINDEX, draw_callback);
                int result = honey_lua_pcall(L, 0, 0);
                if (result != 0) {
                    const char* error = lua_tostring(L, -1);
                    fprintf(stderr, "[honey] ERROR: %s\n", error);
                    glfwSetWindowShouldClose(window, true);
                }
            }

            glfwSwapBuffers(window);
        }
    }

    lua_close(L);
    
    glfwTerminate();
    return true;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_get_callback(lua_State* L, char* callback)
{
    lua_getglobal(L, "honey");
    lua_getfield(L, -1, callback);

    int ref = LUA_NOREF;
    
    if (lua_isfunction(L, -1))
        ref = luaL_ref(L, LUA_REGISTRYINDEX);
    else
        lua_pop(L, 1);
    lua_pop(L, 1);

    return ref;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_set_framebuffer(lua_State* L)
{
    int framebuffer;
    honey_lua_parse_arguments(L, 1, HONEY_INTEGER, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    return 0;
}
