#ifndef SHADERS_H_
#define SHADERS_H_
#include "main.h"

typedef unsigned int Shader_t;

Shader_t Shader_Load(char *source, uint type);
unsigned int Shader_Compile(Shader_t vertex_shader, Shader_t fragment_shader);

#endif // SHADERS_H_
