#include "include/honey.h"

honey_window honey_setup(int screen_width, int screen_height, char* window_title) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  honey_window window = glfwCreateWindow(screen_width, screen_height, window_title, NULL, NULL);
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

  return window;
}

  
