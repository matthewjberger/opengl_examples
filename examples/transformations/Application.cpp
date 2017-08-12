#pragma once

#include "Application.h"

Application::Application() { }
Application::~Application() { }
void Application::update() { }

void Application::initialize()
{
	glfwSetWindowTitle(window_, "OpenGL Transformations Example");

	/* Boilerplate for drawing a rectangle using indices */

	glm::vec3 quadVertices[] =
	{
		glm::vec3(-0.5f,  0.5f, 0.0f),
		glm::vec3(0.5f,  0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f)
	};

    glm::vec2 quadUVCoords[] =
    {
      glm::vec2(0.0f, 1.0f),
      glm::vec2(1.0f, 1.0f),
      glm::vec2(0.0f, 0.0f),
      glm::vec2(1.0f, 0.0f)
    };

    GLuint indices[] =
    {
        1, 2, 0,
        2, 1, 3
    };

	shaderProgram_.create_program();
	shaderProgram_.add_shader_from_file("resources/shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	shaderProgram_.add_shader_from_file("resources/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
	shaderProgram_.link_program();

	vertexArray_.create();
	vertexBuffer_.create();
	elementBuffer_.create(GL_ELEMENT_ARRAY_BUFFER);

	vertexArray_.bind();

	vertexBuffer_.bind();
	for (int i = 0; i < 4; i++)
	{
		vertexBuffer_.add_data(&quadVertices[i], sizeof(glm::vec3));
		vertexBuffer_.add_data(&quadUVCoords[i], sizeof(glm::vec2));
	}
	vertexBuffer_.upload_data();

	elementBuffer_.bind();
	elementBuffer_.add_data(&indices, sizeof(indices));
	elementBuffer_.upload_data();

	vertexArray_.configure_attribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) + sizeof(glm::vec2), nullptr);
	vertexArray_.enable_attribute(0);

	vertexArray_.configure_attribute(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) + sizeof(glm::vec2), reinterpret_cast<GLvoid*>(sizeof(glm::vec3)));
	vertexArray_.enable_attribute(1);

	vertexBuffer_.unbind();
	vertexArray_.unbind();

	texture_.create_from_file("resources/iceberg.png");
}

void Application::render()
{
	/**********************************************/
	/* Build model, view, and projection matrices */
	static glm::mat4 projectionMatrix = glm::perspective(45.0f, 3.0f / 4.0f, 0.1f, 100.0f);
	static glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	static glm::mat4 modelMatrix = glm::mat4(1.0f);
	static glm::mat4 mvpMatrix;
	/**********************************************/

	glClearColor(0.4f, 0.58f, 0.92f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	shaderProgram_.use();
	vertexArray_.bind();

	/*******************************************/
	/* Manipulate the model matrix in some way */
	/* and then create the MVP matrix          */
	// Rotate the quad
	modelMatrix = glm::rotate(modelMatrix, glm::radians(60.0f) * deltaTime_, glm::vec3(0.0f, 1.0f, 0.0f));

	// Compute the mvp matrix and assign it to the uniform in the shader
	// The order matters here. Right multiply projection * view * model
	mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
	shaderProgram_.set_uniform("mvpMatrix", mvpMatrix);
	/*******************************************/

	texture_.bind();
	vertexArray_.draw_elements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Application::cleanup()
{
	vertexArray_.free();
	vertexBuffer_.free();
	elementBuffer_.free();
}
