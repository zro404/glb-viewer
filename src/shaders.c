#include "shaders.h"
#include <stdio.h>

Shader_t Shader_Load(char *source, uint type) {
  FILE *fptr = fopen(source, "r");
  if (fptr == NULL) {
    printf("Failed to open file: %s\n", source);
  }
  fseek(fptr, 0, SEEK_END);
  long fsize = ftell(fptr);
  fseek(fptr, 0, SEEK_SET); /* same as rewind(f); */

  char *shader_src = malloc(fsize + 1);
  fread(shader_src, fsize, 1, fptr);
  fclose(fptr);

  shader_src[fsize] = 0;

  const char *shader_src_const = shader_src;

  unsigned int shader;
  shader = glCreateShader(type);
  glShaderSource(shader, 1, &shader_src_const, NULL);
  glCompileShader(shader);

  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
  }
  return shader;
}

unsigned int Shader_Compile(Shader_t vertexShader, Shader_t fragmentShader) {
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // check for linking errors
  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}
