#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "include/stb_image.h"

#include "include/glad.h"
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>
#include <cglm/call.h>

#include "include/shader.h"

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

void processInput(GLFWwindow* window, float dt) {
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

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "hello, world!", NULL, NULL);
  if (window == NULL) {
    fprintf(stderr, "ERROR: failed to create GLFW window!\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
  glfwSetCursorPosCallback(window, mouseCallback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    fprintf(stderr, "ERROR: failed to initialize GLAD!\n");
    glfwTerminate();
    return 2;
  }

  /* load box texture */
  unsigned int boxTex;
  glGenTextures(1, &boxTex);
  glBindTexture(GL_TEXTURE_2D, boxTex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int imgWidth, imgHeight, imgChannels;
  unsigned char* imageData = stbi_load("container.jpg", &imgWidth, &imgHeight, &imgChannels, 0);
  if (imageData == NULL) {
    fprintf(stderr, "ERROR: failed to load 'container.jpg'\n");
    return 1;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(imageData);

  /* load happy face texture */
  unsigned int happyTex;
  glGenTextures(1, &happyTex);
  glBindTexture(GL_TEXTURE_2D, happyTex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  imageData = stbi_load("happy.png", &imgWidth, &imgHeight, &imgChannels, 0);
  if (imageData == NULL) {
    fprintf(stderr, "ERROR: failed to load 'happy.png'\n");
    return 1;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(imageData);
  
  honey_shader shader;
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

  unsigned int vertexBufferObject, vertexArrayObject, elementBufferObject;
  glGenVertexArrays(1, &vertexArrayObject);
  glGenBuffers(1, &vertexBufferObject);
  glGenBuffers(1, &elementBufferObject);
  glBindVertexArray(vertexArrayObject);

  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  honey_shader_set_int(shader, "boxTexture", 0);
  honey_shader_set_int(shader, "happyTexture", 1);

  mat4 model, view, projection;
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

  float prevTime = 0;
  float currentTime = 0;
  float dt = 0;

  while(!glfwWindowShouldClose(window)) {
    currentTime = (float) glfwGetTime();
    dt = currentTime - prevTime;
    prevTime = currentTime;

    processInput(window, dt);

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
    
    glm_rotate_x(model, glm_rad(10*dt), model);
    honey_shader_set_matrix_4fv(shader, "model", (float*) model);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, boxTex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, happyTex);

    honey_shader_use(shader);
    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &vertexArrayObject);
  glDeleteBuffers(1, &vertexArrayObject);
  honey_shader_delete(shader);

  glfwTerminate();

  return 0;
}

/*
           ,d88b.d88b,
           88888888888
           `Y8888888Y'
             `Y888Y'
               `Y'
*/
