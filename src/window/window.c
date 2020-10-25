#include "window.h"

bool honey_setup_window(lua_State* L)
{
    honey_window_information* info = malloc(sizeof(honey_window_information));
    if (info == NULL) {
        fprintf(stderr, "[honey] ERROR: failed to allocate memory for window information!\n");
        return false;
    }
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    info->window = glfwCreateWindow(640, 480, "honey", NULL, NULL);
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
        { "internal", HONEY_LIGHTUSERDATA, { .pointer = info } },
        { "set_fullscreen", HONEY_FUNC, { .function = honey_window_set_fullscreen } },
    };

    honey_lua_create_table(L, window_elements, 2);
    return true;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int honey_window_set_fullscreen(lua_State* L)
{
    if (!honey_lua_validate_types(L, 1, HONEY_BOOL))
        lua_error(L);

    bool fullscreen = lua_toboolean(L, 1);

    lua_getglobal(L, "honey");
    lua_getfield(L, -1, "window");
    lua_getfield(L, -1, "internal");
    honey_window_information* info = lua_touserdata(L, -1);
    lua_pop(L, 2);

    if (fullscreen) {
        glfwGetWindowSize(info->window, &(info->width), &(info->height));
        
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(info->window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else {
        glfwSetWindowMonitor(info->window, NULL, 20, 20, info->width, info->height, 0);
    }
    return 0;
}
