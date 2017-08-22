#include "Camera.h"

Camera::Camera(float windowWidth, float windowHeight)
{
	lastX_ = windowWidth / 2.0f;
	lastY_ = windowHeight / 2.0f;
	firstMouse_ = true;
}

void Camera::handle_keystates(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		process_keyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		process_keyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		process_keyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		process_keyboard(RIGHT, deltaTime);
}

void Camera::mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse_)
	{
		lastX_ = xPos;
		lastY_ = yPos;
		firstMouse_ = false;
	}

	float xOffset = xPos - lastX_;
	float yOffset = lastY_ - yPos; // reversed since y-coordinates go from bottom to top

	lastX_ = xPos;
	lastY_ = yPos;

	process_mouse_motion(xOffset, yOffset);
}
