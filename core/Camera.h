#pragma once

#include "CameraBase.h"
#include "Includes.h"

// An implementation of the abstract CameraBase class using GLFW
class Camera : public CameraBase
{
public:
	explicit Camera(
		GLFWwindow* window,
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = CAMERA_YAW,
		float pitch = CAMERA_PITCH);
	~Camera() = default;

	void handle_keystates(GLFWwindow* window, float deltaTime);
	void mouse_callback(GLFWwindow* window, double, double);

private:
	float lastX_;
	float lastY_;
	bool firstMouse_;
};
