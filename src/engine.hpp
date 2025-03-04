#pragma once

#include "main.hpp"

class Engine {
	GLFWwindow* window;
public:
	Engine();
	GLFWwindow* getWindow();
};
