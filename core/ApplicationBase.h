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

	void framebuffer_size_callback(GLFWwindow*, int, int);
	void mouse_callback(GLFWwindow*, double, double);
	void scroll_callback(GLFWwindow*, double, double);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	GLFWwindow* window() const { return window_; }

protected:
	virtual void initialize() = 0;
	virtual void update() = 0;
	virtual void cleanup() = 0;
	virtual void render() = 0;

	virtual void on_framebuffer_size_callback(GLFWwindow*, int, int) {}
	virtual void on_mouse_callback(GLFWwindow*, double, double) {}
	virtual void on_scroll_callback(GLFWwindow*, double, double) {}
	virtual void on_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {}

	GLFWwindow* window_;
	float deltaTime_;
	float lastFrame_;
};
