#include "Skybox.h"
#include <stb_image.h>

Skybox::Skybox(const SkyboxParameters &skyboxParameters)
{
	std::vector<std::string> faces;
	faces.push_back(skyboxParameters.right);
	faces.push_back(skyboxParameters.left);
	faces.push_back(skyboxParameters.top);
	faces.push_back(skyboxParameters.bottom);
	faces.push_back(skyboxParameters.back);
	faces.push_back(skyboxParameters.front);

	cubemap_.create_cubemap_from_files(faces);

	const GLchar* vertexShaderSource = R"END(
#version 330 core
layout (location = 0) in vec3 position;
out vec3 TexCoords;
uniform mat4 projection;
uniform mat4 view;
void main()
{
    vec4 finalPos = projection * view * vec4(position, 1.0f);
    gl_Position = finalPos.xyww;
    TexCoords = position;
}
)END";

	const GLchar* fragmentShaderSource = R"END(
#version 330 core
in vec3 TexCoords;
out vec4 color;
uniform samplerCube skybox;
void main()
{    
    color = texture(skybox, TexCoords);
}
)END";

	skyboxProgram_.create_program();
	skyboxProgram_.add_shader_from_source(vertexShaderSource, GL_VERTEX_SHADER);
	skyboxProgram_.add_shader_from_source(fragmentShaderSource, GL_FRAGMENT_SHADER);
	skyboxProgram_.link_program();

	// TODO: Use an IBO here
	GLfloat skyboxVertices[] =
	{
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		-1.0f, 1.0f, -1.0f,
		 1.0f, 1.0f, -1.0f,
		 1.0f, 1.0f,  1.0f,
		 1.0f, 1.0f,  1.0f,
		-1.0f, 1.0f,  1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	skyboxVAO_.create();
	skyboxVBO_.create();

	skyboxVAO_.bind();

	skyboxVBO_.bind();
	skyboxVBO_.add_data(&skyboxVertices, sizeof(skyboxVertices));
	skyboxVBO_.upload_data();

	skyboxVAO_.enable_attribute(0);
	skyboxVAO_.configure_attribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
	skyboxVAO_.unbind();
}

void Skybox::draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) const
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	skyboxProgram_.use();

	glm::mat4 view = glm::mat4(glm::mat3(viewMatrix));
	skyboxProgram_.set_uniform("projection", projectionMatrix);
	skyboxProgram_.set_uniform("view", view);

	skyboxVAO_.bind();

	cubemap_.bind();
	skyboxProgram_.set_uniform("skybox", 0);

	// TODO: Switch to indexed drawing 
	glDrawArrays(GL_TRIANGLES, 0, 36);

	skyboxVAO_.unbind();

	glDepthFunc(GL_LESS);
}
