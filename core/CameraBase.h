#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

enum CameraDirection {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class CameraBase
{
public:
	explicit CameraBase(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

	void process_keyboard(CameraDirection direction, float deltaTime);
	void process_mouse_motion(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void process_mouse_scroll(float yoffset);

	glm::mat4 view_matrix() const;

protected:
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// Angles
	float Yaw;
	float Pitch;

	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

private:
	void calculate_vectors();
};
