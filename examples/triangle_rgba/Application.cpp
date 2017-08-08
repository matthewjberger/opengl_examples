#pragma once

#include "Application.h"

Application::Application() { }
Application::~Application() { }
void Application::update() { }

void Application::initialize()
{
	glfwSetWindowTitle(window_, "OpenGL Triangle Example");

	const GLchar* vertexShaderSource = R"END(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; // Specify a vertex attribute for color
out vec3 color;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	color = aColor; // pass the color along to the fragment shader
}
)END";

	const GLchar* fragmentShaderSource = R"END(
#version 330 core
out vec4 FragColor;
in vec3 color;
void main()
{
   // Set the fragment color to the color passed from the vertex shader
   FragColor = vec4(color, 1.0);
}
)END";

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	shaderProgram_ = glCreateProgram();
	glAttachShader(shaderProgram_, vertexShader);
	glAttachShader(shaderProgram_, fragmentShader);
	glLinkProgram(shaderProgram_);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Specify vertex and color information for the triangle
	float vertices[] = {
		 // Positions        // Colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom Left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // Top
	};

	glGenVertexArrays(1, &VAO_);
	glGenBuffers(1, &VBO_);

	glBindVertexArray(VAO_);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* Specify the layout of the data in the buffer. */
	// The first vertex attribute will be the position in this case.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);

	// The second vertex attribute will be the color in this case.
	// Note that this data is found after the position data (3 floats in size) and is 3 floats long.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Application::render()
{
	glClearColor(0.4f, 0.58f, 0.92f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgram_);
	glBindVertexArray(VAO_);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Application::cleanup()
{
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &VBO_);
}
