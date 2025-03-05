#pragma once

#include "main.hpp"

class Engine {
	GLFWwindow* window;
	bool wireframeMode;
public:
	Engine();
	GLFWwindow* getWindow();
	void toggleWireframe();
};
