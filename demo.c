#include "include/honey.h"

honey_window window;

unsigned int screen_width = 640;
unsigned int screen_height = 480;

vec3 cameraPosition, cameraFacing, cameraUp;

vec3 cameraPosition = { 0, 0, 3 };
vec3 cameraFacing = { 0, 0, -1 };
vec3 cameraUp = { 0, 1, 0 };
float cameraSpeed = 2.0;
float cameraPitch = 0;
float cameraYaw = 0;
const float cameraMouseSensitivity = 0.1;

honey_mesh cube;
honey_shader shader;
honey_texture container;
honey_texture happy_face;

mat4 model, view, projection;

bool wireframe = false;
bool fKeyDown = false;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  screen_width = width;
  screen_height = height;
}

void mouseCallback(GLFWwindow* window, double x, double y) {
  static float prevX, prevY;
  static bool firstMouse = true;

  if (firstMouse) {
    prevX = x;
    prevY = y;
    firstMouse = false;
  }

  float xOffset = x - prevX;
  float yOffset = y - prevY;
  prevX = x;
  prevY = y;

  xOffset *= cameraMouseSensitivity;
  yOffset *= cameraMouseSensitivity;

  cameraYaw += xOffset;
  cameraPitch -= yOffset;

  if (cameraPitch > 89) { cameraPitch = 89; }
  if (cameraPitch < -89) { cameraPitch = -89; }

  cameraFacing[0] = cos(glm_rad(cameraYaw))*cos(glm_rad(cameraPitch));
  cameraFacing[1] = sin(glm_rad(cameraPitch));
  cameraFacing[2] = sin(glm_rad(cameraYaw)) * cos(glm_rad(cameraPitch));
  glm_vec3_normalize(cameraFacing);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void update(float dt) {
  glfwPollEvents();

  glm_rotate_x(model, glm_rad(10*dt), model);
  
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
    if (!fKeyDown) {
      wireframe = !wireframe;
      fKeyDown = true;
    }
  }
  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE) {
    fKeyDown = false;
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    vec3 step;
    glm_vec3_scale(cameraFacing, cameraSpeed*dt, step);
    glm_vec3_add(cameraPosition, step, cameraPosition);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    vec3 step;
    glm_vec3_scale(cameraFacing, -cameraSpeed*dt, step);
    glm_vec3_add(cameraPosition, step, cameraPosition);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    vec3 direction, step;
    glm_vec3_cross(cameraFacing, cameraUp, direction);
    glm_vec3_normalize(direction);
    glm_vec3_scale(direction, -cameraSpeed*dt, step);
    glm_vec3_add(cameraPosition, step, cameraPosition);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    vec3 direction, step;
    glm_vec3_cross(cameraFacing, cameraUp, direction);
    glm_vec3_normalize(direction);
    glm_vec3_scale(direction, cameraSpeed*dt, step);
    glm_vec3_add(cameraPosition, step, cameraPosition);
  }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void draw() {
  glClearColor(0.4f, 0.4f, 0.4f, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (wireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  glm_perspective_default(((float)screen_width)/screen_height, projection);
  honey_shader_set_matrix_4fv(shader, "projection", (float*) projection);

  vec3 cameraDirection;
  glm_vec3_add(cameraPosition, cameraFacing, cameraDirection);
  glm_lookat(cameraPosition, cameraDirection, cameraUp, view);
  honey_shader_set_matrix_4fv(shader, "view", (float*) view);
    
  honey_shader_set_matrix_4fv(shader, "model", (float*) model);
    
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, container.texture_id);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, happy_face.texture_id);

  honey_mesh_draw(cube, shader);
    
  glfwSwapBuffers(window);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int main() {
  window = honey_setup(screen_width, screen_height, "hello, world!");

  honey_set_resize_callback(window, framebufferResizeCallback);
  honey_set_mouse_move_callback(window, mouseCallback);

  /* load container texture */
  if (honey_texture_new(&container, "container.jpg", false) != TEXTURE_OK) {
    return 1;
  }

  /* load happy face texture */
  if (honey_texture_new(&happy_face, "happy.png", true) != TEXTURE_OK) {
    return 1;
  }
  
  if (honey_shader_load(&shader, "demo.vs", "demo.fs") != SHADER_OK) {
    return 1;
  }

  /* create triangle */
  float vertices[] = {
    /* positions           colors          tex coords */
    -0.5, -0.5,  0.5,     1.0, 0.0, 0.0,    0.0, 0.0,
    0.5,  -0.5,  0.5,     0.0, 1.0, 0.0,    1.0, 0.0,
    -0.5,  0.5,  0.5,     0.0, 0.0, 1.0,    0.0, 1.0,
    0.5,   0.5,  0.5,     1.0, 1.0, 1.0,    1.0, 1.0, 
    -0.5, -0.5, -0.5,     1.0, 0.0, 0.0,    0.0, 0.0,
    0.5,  -0.5, -0.5,     0.0, 1.0, 0.0,    1.0, 0.0,
    -0.5,  0.5, -0.5,     0.0, 0.0, 1.0,    0.0, 1.0,
    0.5,   0.5, -0.5,     1.0, 1.0, 1.0,    1.0, 1.0 };

  unsigned int indices[] = { 0, 1, 2,
                             1, 2, 3,
                             4, 5, 6,
                             5, 6, 7,
                             0, 2, 4,
                             2, 4, 6,
                             1, 3, 5,
                             3, 5, 7,
                             2, 3, 6,
                             3, 6, 7,
                             0, 1, 4,
                             1, 4, 5 };

  unsigned int attribute_sizes[] = { 3, 3, 2 }; /* position, color, texture coordinate */
  enum honey_mesh_result result = honey_mesh_new(&cube,
                                                 vertices, 8, 3, attribute_sizes,
                                                 indices,
                                                 sizeof(indices)/sizeof(unsigned int));
  if (result != MESH_OK) {
    fprintf(stderr, "Failed to load cube\n");
    return 1;
  }

  honey_shader_set_int(shader, "boxTexture", 0);
  honey_shader_set_int(shader, "happyTexture", 1);

  glm_mat4_identity(model);
  glm_rotate_x(model, glm_rad(-55), model);
  honey_shader_set_matrix_4fv(shader, "model", (float*) model);

  glm_lookat(cameraPosition, cameraFacing, cameraUp, view);
  honey_shader_set_matrix_4fv(shader, "view", (float*) view);

  glm_mat4_identity(projection);
  /* glm_perspective(glm_rad(90), float(screen_width)/screen_height, 0.1, 100); */
  glm_perspective_default(((float)screen_width)/screen_height, projection);
  honey_shader_set_matrix_4fv(shader, "projection", (float*) projection);

  glEnable(GL_DEPTH_TEST);

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  honey_set_update_callback(&update);
  honey_set_draw_callback(&draw);

  honey_run(window);

  honey_mesh_delete(cube);
  honey_shader_delete(shader);

  honey_quit();

  return 0;
}

/*
           ,d88b.d88b,
           88888888888
           `Y8888888Y'
             `Y888Y'
               `Y'
*/
