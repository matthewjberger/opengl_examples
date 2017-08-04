#pragma once

#include "includes.h"
#include <GLFW/glfw3.h>

class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase() = default;

	bool initialize_all(int, int, std::string caption = "OpenGL Application");
	void run();

protected:
	virtual void initialize() = 0;
	virtual void update() = 0;
	virtual void cleanup() = 0;
	virtual void render() = 0;

	GLFWwindow* window_;
};
