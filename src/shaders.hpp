#pragma once

#include "main.hpp"

class Shader {
	unsigned int ID;
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
};