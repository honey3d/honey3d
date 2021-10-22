#ifndef MOCK_GLFW_H
#define MOCK_GLFW_H

void glfwGetVersion(int *major, int *minor, int *rev);
int glfwInit();
void glfwTerminate();
int glfwGetError(const char **description);

#endif
