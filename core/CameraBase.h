#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

enum CameraDirection {
	CAMERA_FORWARD,
	CAMERA_BACKWARD,
	CAMERA_LEFT,
	CAMERA_RIGHT
};

class CameraBase
{
public:
	explicit CameraBase(
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = CAMERA_YAW,
		float pitch = CAMERA_PITCH);

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

	// Camera default settings
	static constexpr float CAMERA_YAW = -90.0f;
	static constexpr float CAMERA_PITCH = 0.0f;
	static constexpr float CAMERA_SPEED = 2.5f;
	static constexpr float CAMERA_SENSITIVITY = 0.1f;
	static constexpr float CAMERA_ZOOM = 45.0f;

private:
	void calculate_vectors();
};
