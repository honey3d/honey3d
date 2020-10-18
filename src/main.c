#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <unistd.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "glad.h"
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>
#include <cglm/call.h>

#include "input.h"

struct options {
    bool verbose;
    bool run;
    bool has_update;
    bool has_draw;
    char* scriptdir;
};

bool has_function(lua_State* L, char* field)
{
    lua_getglobal(L, "honey");
    lua_getfield(L, -1, field);
    if (lua_isfunction(L, -1))
	return true;
    return false;
}

bool parse_options(struct options* opt, int argc, char** argv)
{
    opt->verbose = false;
    opt->run = false;

    opterr = 0;
    int c;

    while ((c = getopt(argc, argv, "vh")) != -1) {
	switch (c) {
	case 'v':
	    opt->verbose = true;
	    break;

	case 'h':
	    // print help
	    break;

	case '?':
	    if (isprint (optopt))
		fprintf (stderr, "Unknown option `-%c'.\n", optopt);
	    else
		fprintf (stderr,
			 "Unknown option character `\\x%x'.\n",
			 optopt);
	    return false;

	default:
	    return false;
	}
    }

    if (optind < argc) {
	opt->run = true;
	opt->scriptdir = argv[optind];
    }

    return true;
}

GLFWwindow* setup_window(int width, int height, char* title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
	fprintf(stderr, "ERROR: failed to create window!\n");
	glfwTerminate();
	return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
	fprintf(stderr, "ERROR: failed to initialize GLAD!\n");
	glfwTerminate();
	return NULL;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return window;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main(int argc, char** argv)
{
    struct options opt;
    if (!parse_options(&opt, argc, argv)) {
	fprintf(stderr, "ERROR: failed to parse command line options!\n");
	return 1;
    }

    if (!opt.run)
	return 0;
        
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_createtable(L, 0, 1);

    lua_createtable(L, 0, 1);
    
    honey_setup_input(L);
    lua_setfield(L, -2, "key");

    lua_setfield(L, -2, "input");

    lua_setglobal(L, "honey");
    
    GLFWwindow* window = setup_window(480, 320, "honey-engine");

    size_t dirlen  = strlen(opt.scriptdir) + 10;
    char* scriptfile = malloc(sizeof(char) * dirlen);
    if (scriptfile == NULL) {
	fprintf(stderr, "ERROR: failed to allocate memory for script file string!\n");
	return 1;
    }

    snprintf(scriptfile, dirlen, "%s/main.lua", opt.scriptdir);
    
    if (luaL_loadfile(L, scriptfile) == 0) {
	if (lua_pcall(L, 0, 1, 0) == 0) {
	    lua_pop(L, lua_gettop(L));
	}
    }
    else {
	fprintf(stderr, "ERROR: failed to open %s!\n", scriptfile);
	return 1;
    }

    opt.has_update = has_function(L, "update");
    opt.has_draw = has_function(L, "draw");

    float prevTime = 0;
    float currentTime = 0;
    float dt;
    
    while (!glfwWindowShouldClose(window)) {
	currentTime = (float) glfwGetTime();
	dt = currentTime - prevTime;
	prevTime = currentTime;
	glfwPollEvents();

	lua_getglobal(L, "honey");

	if (opt.has_update) {
	    lua_getfield(L, -1, "update");
	    if (lua_isfunction(L, -1)) {
		lua_pushnumber(L, dt);
		int result = lua_pcall(L, 1, 0, 0);
		if (result != 0) {
		    glfwSetWindowShouldClose(window, true);
		}
	    }
	    else {
		lua_pop(L, 1);
	    }
	}

	if (opt.has_draw) {
	    lua_getfield(L, -1, "draw");
	    if (lua_isfunction(L, -1)) {
		int result = lua_pcall(L, 0, 0, 0);
		if (result != 0) {
		    glfwSetWindowShouldClose(window, true);
		}
	    }
	    else {
		lua_pop(L, 1);
	    }
	}

	lua_pop(L, 1);
    }

    lua_close(L);
    
    glfwTerminate();
    return 0;
}
