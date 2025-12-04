#include "main.h"
#ifndef Shaders
typedef unsigned int Shaderprogram;

Shaderprogram createShaderProgram();

void shaderSetVec3(Shaderprogram *program, char *name, float x, float y, float z);
#endif // !Shaders
