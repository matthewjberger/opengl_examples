#include "CameraBase.h"
#include <glm/gtc/matrix_transform.inl>

CameraBase::CameraBase(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(CAMERA_SPEED), MouseSensitivity(CAMERA_SENSITIVITY), Zoom(CAMERA_ZOOM)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	calculate_vectors();
}

glm::mat4 CameraBase::view_matrix() const
{
	return glm::lookAt(Position, Position + Front, Up);
}

float CameraBase::zoom() const
{
	return Zoom;
}

void CameraBase::process_keyboard(CameraDirection direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == CAMERA_FORWARD)  Position += Front * velocity;
	if (direction == CAMERA_BACKWARD) Position -= Front * velocity;
	if (direction == CAMERA_LEFT)     Position -= Right * velocity;
	if (direction == CAMERA_RIGHT)    Position += Right * velocity;
}

void CameraBase::process_mouse_motion(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)  Pitch = 89.0f;
		if (Pitch < -89.0f) Pitch = -89.0f;
	}

	calculate_vectors();
}

void CameraBase::process_mouse_scroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f) Zoom -= yoffset;
	if (Zoom <= 1.0f)  Zoom = 1.0f;
	if (Zoom >= 45.0f) Zoom = 45.0f;
}

void CameraBase::calculate_vectors()
{
	Front = glm::normalize(glm::vec3(
		cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)),
		sin(glm::radians(Pitch)),
		sin(glm::radians(Yaw)) * cos(glm::radians(Pitch))));
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}
