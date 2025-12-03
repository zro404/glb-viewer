#include "main.h"
#include "parser.h"
#include "shader.h"
#include "texture.h"
#include <stdlib.h>

static float width = 800.0f;
static float height = 600.0f;

void framebuffer_size_callback(GLFWwindow *_, int new_width, int new_height) {
  width = new_width;
  height = new_height;
  glViewport(0, 0, new_width, new_height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Filename required!\n");
    return -1;
  }

  VertexArray va = parseSTL(argv[1]);

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "GLB Viewer", NULL, NULL);
  if (window == NULL) {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    return -1;
  }

  glViewport(0, 0, (int)width, (int)height);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, va.size * 9 * sizeof(float), va.vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Compile Shaderprogram
  Shaderprogram shaderProgram = createShaderProgram();

  glEnable(GL_DEPTH_TEST);

  Texture tex = Texture_new("assets/texture_01.png");

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);

    mat4 model = GLM_MAT4_IDENTITY;
    glm_rotate(model, (float)glfwGetTime() * glm_rad(50.0f), (vec3){0.5f, 1.0f, 0.0f});
    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model[0]);

    mat4 view = GLM_MAT4_IDENTITY;
    glm_translate(view, (vec3){0.0f, 0.0f, -10.0f});
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view[0]);

    mat4 projection = GLM_MAT4_IDENTITY;
    glm_perspective(glm_rad(45.0f), width / height, 0.1f, 100.0f, projection);
    int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection[0]);

    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, tex.texture);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  free(va.vertices);
  glfwTerminate();
  return 0;
}
