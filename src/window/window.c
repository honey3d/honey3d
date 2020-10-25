#include "window.h"

int honey_window_info_ref = LUA_NOREF;

bool honey_setup_window(lua_State* L)
{
    honey_window_information* info = lua_newuserdata(L, sizeof(honey_window_information));
    honey_window_info_ref = luaL_ref(L, LUA_REGISTRYINDEX);
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    info->window = glfwCreateWindow(HONEY_WINDOW_DEFAULT_WIDTH,
                                    HONEY_WINDOW_DEFAULT_HEIGHT,
                                    "honey", NULL, NULL);

    info->width = HONEY_WINDOW_DEFAULT_WIDTH;
    info->height = HONEY_WINDOW_DEFAULT_WIDTH;
    info->fullscreen = false;
    
    if (info->window == NULL) {
        fprintf(stderr, "[honey] ERROR: failed to create window!\n");
        glfwTerminate();
        return false;
    }
    /* store lua state in window, so it's accessible from GLFW callbacks */
    glfwSetWindowUserPointer(info->window, L);
    glfwMakeContextCurrent(info->window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        fprintf(stderr, "[honey] ERROR: failed to initialize GLAD!\n");
        glfwTerminate();
        return false;
    }

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    honey_lua_element window_elements[] = {
        { "set_fullscreen", HONEY_FUNC, { .function = honey_window_set_fullscreen } },
        { "set_title",      HONEY_FUNC, { .function = honey_window_set_title } },
        { "get_size",       HONEY_FUNC, { .function = honey_window_get_size } },
        { "set_size",       HONEY_FUNC, { .function = honey_window_set_size } },
    };

    honey_lua_create_table(L, window_elements, 4);
    return true;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_window_set_fullscreen(lua_State* L)
{
    if (!honey_lua_validate_types(L, 1, HONEY_BOOL))
        lua_error(L);

    bool fullscreen = lua_toboolean(L, 1);

    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_window_info_ref);
    honey_window_information* info = lua_touserdata(L, -1);

    if (fullscreen) {
        glfwGetWindowSize(info->window, &(info->width), &(info->height));
        
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(info->window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        info->fullscreen = true;
    }
    else {
        glfwSetWindowMonitor(info->window, NULL, 20, 20, info->width, info->height, 0);
        info->fullscreen = false;
    }
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_window_set_title(lua_State* L)
{
    if (!honey_lua_validate_types(L, 1, HONEY_STRING))
        lua_error(L);

    const char* title = lua_tostring(L, 1);

    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_window_info_ref);
    honey_window_information* info = lua_touserdata(L, -1);
    
    glfwSetWindowTitle(info->window, title);
    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_window_get_size(lua_State* L)
{
    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_window_info_ref);
    honey_window_information* info = lua_touserdata(L, -1);
                 
    int width, height;
    glfwGetWindowSize(info->window, &width, &height);
    lua_pushinteger(L, width);
    lua_pushinteger(L, height);
    return 2;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_window_set_size(lua_State* L)
{
    if (!honey_lua_validate_types(L, 2, HONEY_INT, HONEY_INT))
        lua_error(L);

    int width = lua_tointeger(L, 1);
    int height = lua_tointeger(L, 2);

    lua_rawgeti(L, LUA_REGISTRYINDEX, honey_window_info_ref);
    honey_window_information* info = lua_touserdata(L, -1);

    glfwSetWindowSize(info->window, width, height);
    return 0;
}
