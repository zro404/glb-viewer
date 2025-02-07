#ifndef SHADERS_H_
#define SHADERS_H_
#include "main.h"

typedef struct {
  unsigned int shaderProgram;
  unsigned int VAO;
  unsigned int VBO;
} ShaderData;

void Shader_Load(ShaderData *shader_data);

#endif // SHADERS_H_
