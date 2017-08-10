#pragma once

#include "Application.h"

Application::Application() { }
Application::~Application() { }

void Application::update() { }

void Application::initialize()
{
	glfwSetWindowTitle(window_, "OpenGL Uniforms Example");

	const GLchar* vertexShaderSource = R"END(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos, 1.0);
}
)END";

	/*****************************************/
	// Declare a uniform in one of the shaders.
	// It is globally accessible across shaders
	// in the same program.
	const GLchar* fragmentShaderSource = R"END(
#version 330 core
out vec4 FragColor;
uniform vec4 color; // Declare a uniform value
void main()
{
    FragColor = color;
}
)END";
	/*****************************************/

	const float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	/* Boilerplate for creating a triangle */
	shaderProgram_.create_program();
	shaderProgram_.add_shader_from_source(vertexShaderSource, GL_VERTEX_SHADER);
	shaderProgram_.add_shader_from_source(fragmentShaderSource, GL_FRAGMENT_SHADER);
	shaderProgram_.link_program();
	vertexArray_.create();
	vertexBuffer_.create();
	vertexArray_.bind();
	vertexBuffer_.bind();
	vertexBuffer_.add_data(&vertices, sizeof(vertices));
	vertexBuffer_.upload_data(GL_STATIC_DRAW);
	vertexArray_.configure_attribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
	vertexArray_.enable_attribute(0);
	vertexBuffer_.unbind();
	vertexArray_.unbind();
}

void Application::render()
{
	glClearColor(0.4f, 0.58f, 0.92f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	shaderProgram_.use();

	/**********************************************************/
	// Update the uniform color according to the current time
	float timeValue = glfwGetTime();
	float greenValue = sin(timeValue) / 2.0f + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgram_.id(), "color");
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
	/**********************************************************/

	vertexArray_.bind();
	vertexArray_.draw_arrays(GL_TRIANGLES, 0, 3);
}

void Application::cleanup()
{
	vertexArray_.free();
	vertexBuffer_.free();
	shaderProgram_.delete_program();
}
