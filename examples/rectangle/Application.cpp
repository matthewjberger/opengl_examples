#pragma once

#include "Application.h"

Application::Application() { }
Application::~Application() { }
void Application::update() { }

void Application::initialize()
{
	glfwSetWindowTitle(window_, "OpenGL Rectangle Example");

	/* In modern OpenGL, a rectangle cannot be rendered directly.
	 * It must be rendered using two triangles. The two points on those
	 * triangles that overlapped would normally be duplicated in the VBO.
	 * To reuse existing vertices and prevent duplicating vertex data,
	 * we can use indexed rendering. With indexed rendering,
	 * a list of vertices is given, and a list of indices specifies
	 * the order to use those vertices in. This way,
	 * vertices can be reused an arbitrary number of times
	 * without duplicating data.
	 */


	 // The vertex shader source code
	const GLchar* vertexShaderSource = R"END(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)END";

	// The fragment shader source code
	const GLchar* fragmentShaderSource = R"END(
#version 330 core
out vec4 FragColor;
void main()
{
   FragColor = vec4(0.0f, 1.00f, 0.0f, 1.0f);
}
)END";

	// Vertex Shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	// Fragment Shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Link shaders into exe to run on the gpu
	shaderProgram_ = glCreateProgram();
	glAttachShader(shaderProgram_, vertexShader);
	glAttachShader(shaderProgram_, fragmentShader);
	glLinkProgram(shaderProgram_);

	// Delete unused shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Specify vertices for the rectangle
	float vertices[] = {
		 0.5f,  0.5f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f  // top left
	};

	// Describe the vertex order using indices
	unsigned int indices[] = {
		// Start from 0
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};

	// Create VAO, VBO, and Element Buffer Object (EBO)
	glGenVertexArrays(1, &VAO_);
	glGenBuffers(1, &VBO_);
	glGenBuffers(1, &EBO_);
	glBindVertexArray(VAO_);

	// Fill the VBO with data
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Fill the EBO with data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Application::render()
{
	glClearColor(0.4f, 0.58f, 0.92f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram_);
	glBindVertexArray(VAO_);

	// glDrawElements is used for indexed rendering,
	// rather than glDrawArrays
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Application::cleanup()
{
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &VBO_);
	glDeleteBuffers(1, &EBO_);
}
