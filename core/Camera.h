#pragma once

#include "CameraBase.h"
#include "Includes.h"

class Camera : public CameraBase
{
public:
	Camera(float,float);
	~Camera() = default;

	void handle_keystates(GLFWwindow*, float);
	void mouse_callback(GLFWwindow*, double, double);

private:
	float lastX_;
	float lastY_;
	bool firstMouse_;
};
