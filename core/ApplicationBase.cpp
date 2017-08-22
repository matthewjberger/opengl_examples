#include "ApplicationBase.h"

using namespace std;

ApplicationBase::ApplicationBase()
{
	window_ = nullptr;
	deltaTime_ = 0.0f;
	lastFrame_ = 0.0f;
}

bool ApplicationBase::initialize_all(int initialWidth, int initialHeight, string caption)
{
	// Load GLFW and Create a Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window_ = glfwCreateWindow(initialWidth, initialHeight, caption.c_str(), nullptr, nullptr);

	// Check for Valid Context
	if (window_ == nullptr)
	{
		fprintf(stderr, "Failed to Create OpenGL Context");
		return false;
	}

	// Create Context
	glfwMakeContextCurrent(window_);

	// Capture the mouse
	glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Load OpenGL Functions
	gladLoadGL();
	fprintf(stderr, "OpenGL %p\n", glGetString(GL_VERSION));

	initialize();

	return true;
}

void ApplicationBase::run()
{
	// Rendering Loop
	while (glfwWindowShouldClose(window_) == false)
	{
		// Calculate delta time
		float currentFrame = glfwGetTime();
		deltaTime_ = currentFrame - lastFrame_;
		lastFrame_ = currentFrame;

		update();

		// Enable depth testing
		glEnable(GL_DEPTH_TEST);

		// Background Fill Color
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		render();

		// Flip Buffers and Draw
		glfwSwapBuffers(window_);
		glfwPollEvents();
	}

	cleanup();

	glfwTerminate();
}

void ApplicationBase::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	on_framebuffer_size_callback(window, width, height);
}

void ApplicationBase::mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	on_mouse_callback(window, xPos, yPos);
}

void ApplicationBase::scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	on_scroll_callback(window, xOffset, yOffset);
}

void ApplicationBase::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window_, true);
		return;
	}

	on_key_callback(window, key, scancode, action, mods);
}
