#include "include/honey.h"

honey_window window;

unsigned int screen_width = 640;
unsigned int screen_height = 480;

honey_camera camera;
float cameraSpeed = 3.0;
float camera_roll_speed = 1.0;
const float cameraMouseSensitivity = 0.1;

honey_mesh light_cube;
vec3 ambient_color = { 0.3, 0.3, 0.3 };
honey_point_light light;

honey_directional_light sun;

mat4 light_model;
honey_shader light_shader;

honey_model suzanne;
mat4 suzanne_model;
honey_texture suzanne_tex;

honey_model sphere;
honey_shader sphere_shader;
mat4 model;
honey_texture sphere_tex;

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
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (wireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  honey_camera_calculate_view(&camera);
  honey_shader_set_mat4(sphere_shader, "view", camera.view);
  honey_shader_set_mat4(sphere_shader, "model", model);
  mat4 normal4;
  mat3 normal;
  glm_mat4_copy(model, normal4);
  glm_mat4_inv_fast(normal4, normal4);
  glm_mat4_pick3t(normal4, normal);
  honey_shader_set_mat3(sphere_shader, "normal_mat", normal);

  honey_shader_set_mat4(light_shader, "view", camera.view);    
  honey_shader_set_mat4(light_shader, "model", light_model);
    
  honey_texture_use(sphere_tex, 0);

  //honey_mesh_draw(cube, sphere_shader);
  honey_model_draw(&sphere, sphere_shader);
  honey_mesh_draw(light_cube, light_shader);
    
  glfwSwapBuffers(window);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int main() {
  window = honey_setup(screen_width, screen_height, "hello, world!");

  honey_set_resize_callback(window, framebufferResizeCallback);
  honey_set_mouse_move_callback(window, mouseCallback);

  honey_key_bind(HONEY_KEY_F, toggle_wireframe, NULL);

  /* load model */
  honey_texture_new(&sphere_tex, "sphere-tex.png", true);
  honey_model_load(&sphere, "sphere.obj");
  
  honey_error result = honey_shader_load(&sphere_shader, "demo.vs", "cel.fs");
  if (result != HONEY_OK) {
    char error_message[3*HONEY_ERROR_DATA_STRING_LENGTH];
    honey_human_readable_error(error_message, result);
    fprintf(stderr, "%s\n", error_message);
    return 1;
  }

  honey_shader_load(&light_shader, "light.vs", "light.fs");

  honey_mesh_new_cube(&light_cube, 0.1,0.1,0.1);

  sun.direction[0] = 0;
  sun.direction[1] = -1;
  sun.direction[0] = 0;

  sun.color[0] = 1;
  sun.color[1] = 1;
  sun.color[2] = 1;

  glm_mat4_identity(model);

  vec3 camera_pos = { -4, 0, 0 };
  vec3 camera_angle = { 0, 0, 0 };
  float camera_near = 0.1;
  float camera_far = 1000;
  float camera_fov = glm_rad(100);
  float camera_aspect_ratio = ((float) screen_width)/screen_height;
  honey_camera_new_perspective(&camera,
                               camera_pos,
                               camera_angle,
                               camera_aspect_ratio,
                               camera_near, camera_far,
                               camera_fov);

  /* set sphere_shader uniforms */
  honey_shader_set_int(sphere_shader, "tex", 0);

  honey_shader_set_int (sphere_shader, "n_point_lights", 1);
  honey_shader_set_int (sphere_shader, "n_directional_lights", 1);
  
  honey_point_light_new(&light,
                        2, 2, 2,   /* position */
                        1, 1, 1,   /* color */
                        1, 0, 0);  /* attenuation */

  glm_mat4_identity(light_model);
  glm_translate(light_model, light.position);

  honey_shader_set_point_light(sphere_shader, 0, light);
  honey_shader_set_directional_light(sphere_shader, 0, sun);
  honey_shader_set_vec3(sphere_shader, "ambient_color", ambient_color);

  honey_shader_set_mat4(sphere_shader, "model", model);
  mat4 normal4;
  mat3 normal;
  glm_mat4_copy(model, normal4);
  glm_mat4_inv_fast(normal4, normal4);
  glm_mat4_pick3t(normal4, normal);
  honey_shader_set_mat3(sphere_shader, "normal_mat", normal);
  honey_shader_set_mat4(sphere_shader, "view", camera.view);
  honey_shader_set_mat4(sphere_shader, "projection", camera.projection);

  /* set light_shader uniforms */
  honey_shader_set_vec3(light_shader, "light_color", light.color);

  honey_shader_set_mat4(light_shader, "model", light_model);
  honey_shader_set_mat4(light_shader, "view", camera.view);
  honey_shader_set_mat4(light_shader, "projection", camera.projection);

  glEnable(GL_DEPTH_TEST);

  /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  honey_set_update_callback(&update);
  honey_set_draw_callback(&draw);

  honey_run(window);

  honey_model_delete(&sphere);
  honey_shader_delete(sphere_shader);

  honey_mesh_delete(light_cube);
  honey_shader_delete(light_shader);

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
