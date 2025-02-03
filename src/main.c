#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int main(void) {
  GLFWwindow *window;

  if (!glfwInit())
    return -1;

  window = glfwCreateWindow(1280, 720, "GLB Viewer", NULL, NULL);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
