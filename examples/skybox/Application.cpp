#pragma once

#include "Application.h"

Application::Application() { camera_ = nullptr; }
Application::~Application() { delete camera_; }

void Application::initialize()
{
	camera_ = new Camera(window_,  glm::vec3(0.0f, 0.0f, 2.0f));

	glfwSetWindowTitle(window_, "OpenGL Skybox Example");

	float skyboxVertices[] = {
		// positions
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

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	vertexArray_.create();
	vertexBuffer_.create();

	vertexArray_.bind();
	vertexBuffer_.bind();

	vertexBuffer_.add_data(skyboxVertices, sizeof skyboxVertices);
	vertexBuffer_.upload_data(GL_STATIC_DRAW);

	vertexArray_.configure_attribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	vertexArray_.enable_attribute(0);

	std::vector<std::string> faces
	{
		"resources/skybox/right.tga",
		"resources/skybox/left.tga",
		"resources/skybox/top.tga",
		"resources/skybox/bottom.tga",
		"resources/skybox/back.tga",
		"resources/skybox/front.tga"
	};

	glGenTextures(1, &cubemapTexture_);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture_);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		stbi_image_free(data);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

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

	skyboxShader_.create_program();
	skyboxShader_.add_shader_from_source(vertexShaderSource, GL_VERTEX_SHADER);
	skyboxShader_.add_shader_from_source(fragmentShaderSource, GL_FRAGMENT_SHADER);
	skyboxShader_.link_program();
	skyboxShader_.use();
	skyboxShader_.set_uniform("skybox", 0);
}

void Application::render()
{
	static glm::mat4 projectionMatrix = glm::perspective(45.0f, 3.0f / 4.0f, 0.1f, 100.0f);
	glClearColor(0.4f, 0.58f, 0.92f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glDepthFunc(GL_LEQUAL);
	skyboxShader_.use();
	glm::mat4 viewMatrix = glm::mat4(glm::mat3(camera_->view_matrix()));
	skyboxShader_.set_uniform("view", viewMatrix);
	skyboxShader_.set_uniform("projection", projectionMatrix);

	vertexArray_.bind();
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture_);
	vertexArray_.draw_arrays(GL_TRIANGLES, 0, 36);
	glDepthFunc(GL_LESS);
}

void Application::update()
{
	camera_->handle_keystates(window_, deltaTime_);
}

void Application::on_mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	camera_->mouse_callback(window, xPos, yPos);
}

void Application::on_scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	camera_->process_mouse_scroll(yOffset);
}

void Application::cleanup()
{
	vertexArray_.free();
	vertexBuffer_.free();
}
