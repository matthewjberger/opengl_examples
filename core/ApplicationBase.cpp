#include "ApplicationBase.h"

using namespace std;

ApplicationBase::ApplicationBase()
{
	window_ = nullptr;
}

bool ApplicationBase::initialize_all(int initialWidth, int initialHeight, string caption)
{
	// Load GLFW and Create a Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

	// Create Context and Load OpenGL Functions
	glfwMakeContextCurrent(window_);
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
		if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window_, true);
		}

		update();

		// Background Fill Color
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		render();

		// Flip Buffers and Draw
		glfwSwapBuffers(window_);
		glfwPollEvents();
	}

	cleanup();

	glfwTerminate();
}
