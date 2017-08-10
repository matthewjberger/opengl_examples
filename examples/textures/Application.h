#pragma once

#include "ApplicationBase.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "Buffer.h"

class Application : public ApplicationBase
{
public:
	Application();
	~Application();

	void initialize() override;
	void cleanup() override;
	void update() override;
	void render() override;

private:
	GLuint textureId_;
	VertexArray vertexArray_;
	Buffer vertexBuffer_;
	ShaderProgram shaderProgram_;
};
