#include "Camera.h"

Camera::Camera(
	GLFWwindow* window,
	glm::vec3 position,
	glm::vec3 up, float yaw,
	float pitch) :
CameraBase(position, up, yaw, pitch)
{
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	lastX_ = windowWidth / 2.0f;
	lastY_ = windowHeight / 2.0f;
	firstMouse_ = true;
}

void Camera::handle_keystates(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		process_keyboard(CAMERA_FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		process_keyboard(CAMERA_BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		process_keyboard(CAMERA_LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		process_keyboard(CAMERA_RIGHT, deltaTime);
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
	// Reversed because Y-Coordinates go from bottom to top
	float yOffset = lastY_ - yPos;

	lastX_ = xPos;
	lastY_ = yPos;

	process_mouse_motion(xOffset, yOffset);
}
