#pragma once

#include "Includes.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "ShaderProgram.h"
#include "Texture.h"

struct SkyboxParameters
{
	std::string left;
	std::string right;
	std::string top;
	std::string bottom;
	std::string front;
	std::string back;
};

class Skybox
{
public:
	explicit Skybox(const SkyboxParameters &skyboxParameters);
	~Skybox() = default;

	void draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) const;

private:
	VertexArray skyboxVAO_;
	Buffer skyboxVBO_;
	ShaderProgram skyboxProgram_;
	Texture cubemap_;
};