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
    
bool honey_setup(lua_State** L, honey_window* window)
{
    /* set up glfw */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    *window = glfwCreateWindow(640, 480, "honey", NULL, NULL);
    if (*window == NULL) {
        fprintf(stderr, "[honey] ERROR: failed to create window!\n");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(*window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        fprintf(stderr, "[honey] ERROR: failed to initialize GLAD!\n");
        glfwTerminate();
        return false;
    }

    honey_setup_keyboard();
    glfwSetKeyCallback(*window, default_honey_keyboard_callback);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  

    /* set up lua and honey lua bindings */
    *L = luaL_newstate();
    luaL_openlibs(*L);
    glfwSetWindowUserPointer(*window, *L);

    lua_createtable(*L, 0, 1);

    honey_setup_input(*L);
    lua_setfield(*L, -2, "input");

    lua_setglobal(*L, "honey");

    return true;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_run(honey_window window) {
    /*float prevTime = 0;
    float currentTime = 0;
    float dt;
    float draw_dt = 0;

    while(!glfwWindowShouldClose(window)) {
        currentTime = (float) glfwGetTime();
        dt = currentTime - prevTime;
        prevTime = currentTime;

        honey_update_callback(dt);
        honey_draw_callback();
        }*/
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
