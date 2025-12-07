#include "shader.h"

const char *vertexShaderSource =
    "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aNormal;\n"
    // "layout (location = 2) in vec2 aTexCoord;\n"
    // "out vec2 TexCoord;\n"
    "out vec3 Normal;\n"
    "out vec3 FragPos;\n"

    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "   FragPos = vec3(model * vec4(aPos, 1.0));\n"
    "   Normal = mat3(transpose(inverse(model))) * aNormal;\n"
    "   gl_Position = projection * view * vec4(FragPos, 1.0);\n"
    "}\0";

const char *fragmentShaderSource =
    "#version 460 core\n"
    "out vec4 FragColor;\n"
    "in vec3 Normal;\n"
    "in vec3 FragPos;\n"
    "uniform sampler2D ourTexture;\n"
    "uniform vec3 objectColor;\n"
    "uniform vec3 lightColor;\n"
    "uniform vec3 lightPos;\n"
    "uniform vec3 viewPos;\n"
    "void main()\n"
    "{\n"
    "   float ambientStrength = 0.3;\n"
    "   vec3 ambient = ambientStrength * lightColor;\n"

    "   vec3 norm = normalize(Normal);\n"
    "   vec3 lightDir = normalize(lightPos - FragPos);\n"
    "   float diff = max(dot(norm, lightDir), 0.0);\n"
    "   vec3 diffuse = diff * lightColor;\n"

    "   float specularStrength = 0.5;\n"
    "   vec3 viewDir = normalize(viewPos - FragPos);\n"
    "   vec3 reflectDir = reflect(lightDir, norm);\n"
    "   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);\n"
    "   vec3 specular = specularStrength * spec * lightColor;\n"

    "   vec3 result = (ambient + diffuse + specular) * objectColor;\n"
    "   FragColor = vec4(result, 1.0f);\n"
    "}\0";

Shaderprogram createShaderProgram() {
  int success;
  char infoLog[512];

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("ERROR compiling Vertex shader: %s\n", infoLog);
    return -1;
  }

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    printf("ERROR compiling Fragment shader: %s\n", infoLog);
    return -1;
  }

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("ERROR linking shaders: %s\n", infoLog);
    return -1;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}

void shaderSetVec3(Shaderprogram *program, char *name, float x, float y,
                   float z) {
  int loc = glGetUniformLocation(*program, name);
  glUniform3f(loc, x, y, z);
}
