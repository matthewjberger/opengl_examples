#include <Application.h>

Application app;

void framebuffer_size_callback_global(GLFWwindow* window, int width, int height)
{
	app.framebuffer_size_callback(window, width, height);
}

void mouse_callback_global(GLFWwindow* window, double xPos, double yPos)
{
	app.mouse_callback(window, xPos, yPos);
}

void scroll_callback_global(GLFWwindow* window, double xOffset, double yOffset)
{
	app.scroll_callback(window, xOffset, yOffset);
}

void key_callback_global(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	app.key_callback(window, key, scancode, action, mods);
}

int main(int argc, char * argv[])
{
	if (app.initialize_all(800, 600))
	{
		// Add the global functions as callbacks
		glfwSetFramebufferSizeCallback(app.window(), framebuffer_size_callback_global);
		glfwSetCursorPosCallback(app.window(), mouse_callback_global);
		glfwSetScrollCallback(app.window(), scroll_callback_global);
		glfwSetKeyCallback(app.window(), key_callback_global);

		app.run();
	}
	return EXIT_SUCCESS;
}
