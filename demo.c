#include "include/honey.h"

honey_window window;

unsigned int screen_width = 640;
unsigned int screen_height = 480;

honey_camera camera;
float cameraSpeed = 3.0;
float camera_roll_speed = 1.0;
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

  float yaw = glm_deg(camera.angle[1]) + xOffset;
  float pitch = glm_deg(camera.angle[0]) - yOffset;

  if (pitch > 89) { pitch = 89; }
  if (pitch < -89) { pitch = -89; }

  camera.angle[0] = glm_rad(pitch);
  camera.angle[1] = glm_rad(yaw);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void print_vec3(vec3 v) {
  printf("(%f, %f, %f)\n", v[0], v[1], v[2]);
}

void update(float dt) {
  glfwPollEvents();

  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  print_vec3(camera.look_direction);
  print_vec3(camera.up);
  print_vec3(camera.right);

  //glm_rotate_x(model, glm_rad(10*dt), model);
  
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
    glm_vec3_scale(camera.look_direction, cameraSpeed*dt, step);
    glm_vec3_add(camera.position, step, camera.position);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    vec3 step;
    glm_vec3_scale(camera.look_direction, -cameraSpeed*dt, step);
    glm_vec3_add(camera.position, step, camera.position);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    vec3 step;
    glm_vec3_scale(camera.right, cameraSpeed*dt, step);
    glm_vec3_add(camera.position, step, camera.position);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    vec3 step;
    glm_vec3_scale(camera.right, -cameraSpeed*dt, step);
    glm_vec3_add(camera.position, step, camera.position);
  }
  if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
    camera.angle[2] += camera_roll_speed*dt;
  }
  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
    camera.angle[2] -= camera_roll_speed*dt;
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

  honey_camera_calculate_view(&camera);
  honey_shader_set_mat4(shader, "view", camera.view);
    
  honey_shader_set_mat4(shader, "model", model);
    
  honey_texture_use(container, 0);
  honey_texture_use(happy_face, 1);

  honey_mesh_draw(cube, shader);
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

  if (honey_mesh_new_textured_cube(&cube, 1, 1, 1) != MESH_OK) {
    fprintf(stderr, "Failed to load cube\n");
    return 1;
  }

  honey_shader_set_int(shader, "box_texture", 0);
  honey_shader_set_int(shader, "happy_texture", 1);

  glm_mat4_identity(model);
  //glm_rotate_x(model, glm_rad(-55), model);
  honey_shader_set_mat4(shader, "model", model);

  vec3 camera_pos = { 4, 0, 0 };
  vec3 camera_angle = { 0, glm_rad(180), 0 };
  float camera_near = 0.1;
  float camera_far = 100;
  float camera_fov = glm_rad(45);
  float camera_aspect_ratio = ((float) screen_width)/screen_height;
  honey_camera_new_perspective(&camera,
                               camera_pos,
                               camera_angle,
                               camera_aspect_ratio,
                               camera_near, camera_far,
                               camera_fov);

  honey_shader_set_mat4(shader, "view", camera.view);
  honey_shader_set_mat4(shader, "projection", camera.projection);

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
