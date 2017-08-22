#pragma once

#include "ApplicationBase.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "ShaderProgram.h"
#include "Texture.h"

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
	VertexArray vertexArray_;
	Buffer vertexBuffer_;
	Buffer elementBuffer_;
	ShaderProgram shaderProgram_;
	Texture texture_;
};