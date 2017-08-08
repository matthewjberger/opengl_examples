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

	const GLchar* fragmentShaderSource = R"END(
out vec4 FragColor;
uniform vec4 color; // Uniforms are global
void main()
{
    FragColor = color;
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

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	glGenVertexArrays(1, &VAO_);
	glGenBuffers(1, &VBO_);

	glBindVertexArray(VAO_);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

	// Update the uniform color
	float timeValue = glfwGetTime();
	float greenValue = sin(timeValue) / 2.0f + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgram_, "color");
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

	glBindVertexArray(VAO_);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Application::cleanup()
{
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &VBO_);
}
