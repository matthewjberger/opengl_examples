#pragma once

#include "Application.h"
// This is defined in Texture.cpp already
// but normally you would need this line
// in order to use stb_image.
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Application::Application() { }
Application::~Application() { }
void Application::update() { }

void Application::initialize()
{
	glfwSetWindowTitle(window_, "OpenGL Textures Example");

	GLfloat vertices[] = {
		// Positions        // Texture Coordinates
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.5f, 1.0f
	};

	/*****************************/
	/* Texture Creation */

	// Generate a texture id
	glGenTextures(1, &textureId_);

	// Bind the texture id so subsequent GL_TEXTURE_2D operations affect the texture
	glBindTexture(GL_TEXTURE_2D, textureId_);

	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load the image
	int width, height, numberOfChannels;
	unsigned char *data = stbi_load("resources/blue.jpg", &width, &height, &numberOfChannels, 0);

	// Load the image data into the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	// Generate mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free the unused image data
	stbi_image_free(data);
	/*****************************/

	/* Boilerplate for creating a triangle */
	shaderProgram_.create_program();
	shaderProgram_.add_shader_from_file("resources/shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
	shaderProgram_.add_shader_from_file("resources/shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
	shaderProgram_.link_program();
	vertexArray_.create();
	vertexBuffer_.create();
	vertexArray_.bind();
	vertexBuffer_.bind();
	vertexBuffer_.add_data(&vertices, sizeof(vertices));
	vertexBuffer_.upload_data(GL_STATIC_DRAW);
	/*********************************************************/
	/* Create a vertex attribute for the texture coordinates */
	// Specify how the data is laid out in the buffer
	vertexArray_.configure_attribute(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void*>(nullptr));
	vertexArray_.configure_attribute(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));

	// Enable the vertex attributes
	vertexArray_.enable_attribute(0); // position
	vertexArray_.enable_attribute(1); // texture coordinates
	/*********************************************************/
	vertexBuffer_.unbind();
	vertexArray_.unbind();
}

void Application::render()
{
	glClearColor(0.4f, 0.58f, 0.92f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Bind the texture before the draw call to
	// automatically assign the texture
	// to the fragment shader's sampler.
	glBindTexture(GL_TEXTURE_2D, textureId_);

	shaderProgram_.use();
	vertexArray_.bind();
	vertexArray_.draw_arrays(GL_TRIANGLES, 0, 3);
}

void Application::cleanup()
{
	vertexArray_.free();
	vertexBuffer_.free();
	shaderProgram_.delete_program();
}
