#pragma once

#include "includes.h"
#include <GLFW/glfw3.h>

class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase() = default;

	bool initialize(int, int, std::string caption = "OpenGL Application");
	void run();

protected:
	virtual void render() = 0;

private:
	GLFWwindow* window_;
};
