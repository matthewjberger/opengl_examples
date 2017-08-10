#pragma once

#include "Application.h"

Application::Application() { }
Application::~Application() { }
void Application::update() { }

void Application::initialize()
{
	glfwSetWindowTitle(window_, "OpenGL Triangle Example");

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
   FragColor = vec4(1.0f, 0.49f, 0.31f, 1.0f);
}
)END";

	/* Create a vertex shader */
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);           // Create an empty shader object of the type GL_VERTEX_SHADER
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr); // Store the shader source in the shader
	glCompileShader(vertexShader);                                 // Compile the vertex shader. This can fail if the shader source is invalid.

	/* Create a vertex shader (Same process as vertex shader) */
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	// Create a shader program
	shaderProgram_ = glCreateProgram();             // Create the shader program
	glAttachShader(shaderProgram_, vertexShader);   // Attach the vertex shader
	glAttachShader(shaderProgram_, fragmentShader); // Attach the fragment shader
	glLinkProgram(shaderProgram_);                  // Link the shaders into a an executable that will run on the gpu.

	// Delete the compiled shader objects.
	// These are useless now that the shader program has been linked.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Specify vertices for the triangle
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // Left
		 0.5f, -0.5f, 0.0f, // Right
		 0.0f,  0.5f, 0.0f  // Top
	};

	// Generate a Vertex Array Object.
	// A VAO is used to supply input to the vertex shader.
	glGenVertexArrays(1, &VAO_);

	// Generate a Vertex Buffer Object.
	// A VBO is used to store vertex data.
	glGenBuffers(1, &VBO_);

	// Bind the Vertex Array Object
	glBindVertexArray(VAO_);

	// Bind the Vertex Buffer Object.
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);

	// Create a new data store for the buffer object, using the vertex data for the triangle.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Specify the location and data format of the of generic vertex attributes at index 0
	// Effectively, this specifies a single vertex attribute
	// A vertex attribute is used to communicate from 'outside' to the vertex shader.
	// These values are provided per vertex.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));

	// This enables the vertex attribute we specified at index 0
	glEnableVertexAttribArray(0);

	// Unbind the VBO and then the VAO so that no buffers are bound
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Uncomment this call to draw in wireframe.
}

void Application::render()
{
	// Set the clear color
	glClearColor(0.4f, 0.58f, 0.92f, 1.0f);

	// Clear the screen to the set clear color
	glClear(GL_COLOR_BUFFER_BIT);

	// Use the shader program we created
	glUseProgram(shaderProgram_);

	// Bind the vertex array object
	glBindVertexArray(VAO_);

	// Draw the triangle using the
	// data specified in the VBO
	// that is specified in the VAO
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Application::cleanup()
{
	// Delete the VAO and VBO explicitly
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &VBO_);
}
