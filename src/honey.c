#include "honey.h"

static void default_honey_update_callback(float dt) {}
static void default_honey_draw_callback() {}

honey_window honey_setup(int screen_width, int screen_height, char* window_title) {
  honey_update_callback = &default_honey_update_callback;
  honey_draw_callback = &default_honey_draw_callback;
  
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

  honey_setup_keyboard();
  glfwSetKeyCallback(window, default_honey_keyboard_callback);

  // Enable blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  return window;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_set_update_callback(void (*update_callback)(float)) {
  honey_update_callback = update_callback;
}

void honey_set_draw_callback(void (*draw_callback)()) {
  honey_draw_callback = draw_callback;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void honey_run(honey_window window) {
  float prevTime = 0;
  float currentTime = 0;
  float dt;
  float draw_dt = 0;

  while(!glfwWindowShouldClose(window)) {
    currentTime = (float) glfwGetTime();
    dt = currentTime - prevTime;
    prevTime = currentTime;

    honey_update_callback(dt);
    honey_draw_callback();
  }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


