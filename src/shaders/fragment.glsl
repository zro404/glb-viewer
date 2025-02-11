#version 330 core
out vec4 FragColor;

in vec4 vertexColor; // the input variable from the vertex shader

void main()
{
    FragColor = vertexColor;
}
