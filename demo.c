#include "include/honey.h"

honey_window window;

unsigned int screen_width = 640;
unsigned int screen_height = 480;

honey_camera camera;
float cameraSpeed = 3.0;
float camera_roll_speed = 1.0;
const float cameraMouseSensitivity = 0.1;

honey_mesh cube;
mat4 model;
honey_shader cube_shader;
honey_texture container;
honey_texture happy_face;

honey_mesh light_cube;
vec3 light_color = { 1, 0, 0 };
mat4 light_model;
honey_shader light_shader;

bool wireframe = false;

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

void toggle_wireframe(void* data, int action) {
  if (action == HONEY_KEY_PRESS) { wireframe = !wireframe; }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void update(float dt) {
  glfwPollEvents();

  glm_rotate_x(model, glm_rad(10*dt), model);
  
  if (honey_key_down(HONEY_KEY_ESCAPE)) {
    glfwSetWindowShouldClose(window, true);
  }

  if (honey_key_down(HONEY_KEY_W)) {
    vec3 step;
    glm_vec3_scale(camera.look_direction, cameraSpeed*dt, step);
    glm_vec3_add(camera.position, step, camera.position);
  }
  if (honey_key_down(HONEY_KEY_S)) {
    vec3 step;
    glm_vec3_scale(camera.look_direction, -cameraSpeed*dt, step);
    glm_vec3_add(camera.position, step, camera.position);
  }
  if (honey_key_down(HONEY_KEY_A)) {
    vec3 step;
    glm_vec3_scale(camera.right, cameraSpeed*dt, step);
    glm_vec3_add(camera.position, step, camera.position);
  }
  if (honey_key_down(HONEY_KEY_D)) {
    vec3 step;
    glm_vec3_scale(camera.right, -cameraSpeed*dt, step);
    glm_vec3_add(camera.position, step, camera.position);
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
  honey_shader_set_mat4(cube_shader, "view", camera.view);
  honey_shader_set_mat4(light_shader, "view", camera.view);    
  honey_shader_set_mat4(cube_shader, "model", model);
  honey_shader_set_mat4(light_shader, "model", light_model);
    
  honey_texture_use(container, 0);
  honey_texture_use(happy_face, 1);

  honey_mesh_draw(cube, cube_shader);
  honey_mesh_draw(light_cube, light_shader);
    
  glfwSwapBuffers(window);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int main() {
  window = honey_setup(screen_width, screen_height, "hello, world!");

  honey_set_resize_callback(window, framebufferResizeCallback);
  honey_set_mouse_move_callback(window, mouseCallback);

  honey_key_bind(HONEY_KEY_F, toggle_wireframe, NULL);

  /* load container texture */
  if (honey_texture_new(&container, "container.jpg", false) != TEXTURE_OK) {
    return 1;
  }

  /* load happy face texture */
  if (honey_texture_new(&happy_face, "happy.png", true) != TEXTURE_OK) {
    return 1;
  }
  
  if (honey_shader_load(&cube_shader, "demo.vs", "demo.fs") != SHADER_OK) {
    return 1;
  }

  if (honey_shader_load(&light_shader, "light.vs", "light.fs") != SHADER_OK) {
    return 1;
  }

  honey_shader_set_vec3(light_shader, "light_color", light_color);

  if (honey_mesh_new_textured_cube(&cube, 1, 1, 1) != MESH_OK) {
    fprintf(stderr, "Failed to load cube\n");
    return 1;
  }

  if (honey_mesh_new_cube(&light_cube, 0.5, 0.5, 0.5) != MESH_OK) {
    return 1;
  }

  glm_mat4_identity(light_model);
  glm_translate(light_model, (vec3){4, 5, 0});
  honey_shader_set_mat4(light_shader, "model", light_model);

  honey_shader_set_int(cube_shader, "box_texture", 0);
  honey_shader_set_int(cube_shader, "happy_texture", 1);
  honey_shader_set_vec3(cube_shader, "light_color", light_color);

  glm_mat4_identity(model);
  //glm_rotate_x(model, glm_rad(-55), model);
  honey_shader_set_mat4(cube_shader, "model", model);

  vec3 camera_pos = { -4, 0, 0 };
  vec3 camera_angle = { 0, 0, 0 };
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

  honey_shader_set_mat4(cube_shader, "view", camera.view);
  honey_shader_set_mat4(cube_shader, "projection", camera.projection);
  honey_shader_set_mat4(light_shader, "projection", camera.projection);

  glEnable(GL_DEPTH_TEST);

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  honey_set_update_callback(&update);
  honey_set_draw_callback(&draw);

  honey_run(window);

  honey_mesh_delete(cube);
  honey_shader_delete(cube_shader);

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
