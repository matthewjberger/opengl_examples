#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture()
{
	// Initialize variables
	width_ = 0;
	height_ = 0;
	textureID_ = -1;
	bindTarget_ = GL_TEXTURE_2D;
}

void Texture::bind(int textureID) const
{
	glActiveTexture(GL_TEXTURE0 + textureID);
	glBindTexture(bindTarget_, textureID_);
}

void Texture::unbind(int textureID) const
{
	glActiveTexture(GL_TEXTURE0 + textureID);
	glBindTexture(bindTarget_, 0);
}

void Texture::free() const
{
	glDeleteTextures(1, &textureID_);
}

bool Texture::create_texture_from_file(const std::string& path)
{
	bindTarget_ = GL_TEXTURE_2D;

	glGenTextures(1, &textureID_);
	bind();

	// Set default wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// Set default filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Flip the image upside down when loaded
	// so that it is considered right side up to OpenGL
	stbi_set_flip_vertically_on_load(true);

	int width, height, numberOfChannels;
	unsigned char* image = stbi_load(path.c_str(), &width, &height, &numberOfChannels, 0);
	if (!image)
	{
		// TODO: Log an error here
		std::string errorMessage = "Couldn't load image " + path;
		return false;
	}

	GLenum pixelFormat;
	switch (numberOfChannels)
	{
	case 1:  pixelFormat = GL_RED;  break;
	case 3:  pixelFormat = GL_RGB;  break;
	case 4:  pixelFormat = GL_RGBA; break;
	default: pixelFormat = GL_RGB;  break;
	}

	// TODO: Log an error here
	if (width < 0 || height < 0) return false;
	width_ = width;
	height_ = height;

	glTexImage2D(GL_TEXTURE_2D, 0, pixelFormat, width_, height_, 0, pixelFormat, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image);
	stbi_set_flip_vertically_on_load(false);

	return true;
}

bool Texture::create_cubemap_from_files(const std::vector<std::string> faces)
{
	bindTarget_ = GL_TEXTURE_CUBE_MAP;

	glGenTextures(1, &textureID_);
	bind();

	// Set default wrapping parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// Set default filtering options
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (unsigned int i = 0; i < faces.size(); i++)
	{
		std::string path = faces[i];
		int width, height, numberOfChannels;
		unsigned char* image = stbi_load(path.c_str(), &width, &height, &numberOfChannels, 0);
		if (!image)
		{
			// TODO: Log an error here
			std::string errorMessage = "Couldn't load image " + path;
			return false;
		}

		GLenum pixelFormat;
		switch (numberOfChannels)
		{
		case 1:  pixelFormat = GL_RED;  break;
		case 3:  pixelFormat = GL_RGB;  break;
		case 4:  pixelFormat = GL_RGBA; break;
		default: pixelFormat = GL_RGB;  break;
		}

		// TODO: Log an error here
		if (width < 0 || height < 0) return false;
		width_ = width;
		height_ = height;

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, pixelFormat, width_, height_, 0, pixelFormat, GL_UNSIGNED_BYTE, image);
		stbi_image_free(image);
	}

	return true;
}

glm::vec2 Texture::dimensions() const
{
	return glm::vec2(width_, height_);
}

GLuint Texture::id() const
{
	return textureID_;
}
