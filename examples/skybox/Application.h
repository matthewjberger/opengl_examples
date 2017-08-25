#pragma once

#include "ApplicationBase.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Camera.h"

class Application : public ApplicationBase
{
public:
	Application();
	~Application();

	void initialize() override;
	void cleanup() override;
	void update() override;
	void render() override;

	void on_mouse_callback(GLFWwindow*, double, double) override;
	void on_scroll_callback(GLFWwindow*, double, double) override;

private:
	Camera* camera_;
	ShaderProgram skyboxShader_;
	VertexArray vertexArray_;
	Buffer vertexBuffer_;
	unsigned int cubemapTexture_;
};
