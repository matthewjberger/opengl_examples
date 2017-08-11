#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture()
{
    // Initialize variables
    width_ = 0;
    height_ = 0;
    channels_ = 0;
    bindTarget_ = 0;
	textureID_ = -1;
}

void Texture::bind() const
{
    glBindTexture(bindTarget_, textureID_);
}

void Texture::unbind() const
{
    glBindTexture(bindTarget_, 0);
}

void Texture::create_from_data(int width, int height, const unsigned char* data, GLenum pixelFormat,  bool generateMipMaps, GLenum bindTarget)
{
	bindTarget_ = bindTarget;
    glGenTextures(1, &textureID_);

    // TODO: Log an error here
    if (width < 0 || height < 0) return;

    width_ = width;
    height_ = height;

    bind();
    glTexImage2D(bindTarget_, 0, pixelFormat, width_, height_, 0, pixelFormat, GL_UNSIGNED_BYTE, data);

	// Set default wrapping parameters
    glTexParameteri(bindTarget_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(bindTarget_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(bindTarget_, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// Set default filtering options
    glTexParameteri(bindTarget_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(bindTarget_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(generateMipMaps) glGenerateMipmap(GL_TEXTURE_2D);
    unbind();
}

void Texture::free() const
{
    glDeleteTextures(1, &textureID_);
}

bool Texture::create_from_file(const std::string& path, bool generateMipMaps, GLenum target)
{
    path_ = path;

	// Flip the image upside down when loaded
	// so that it is considered right side up to OpenGL
	stbi_set_flip_vertically_on_load(true);

    int width, height;
    unsigned char* image = stbi_load(path.c_str(), &width, &height, &channels_, 0);
    if (!image)
    {
        std::string errorMessage = "Couldn't load image " + path;
        return false;
    }

    GLenum pixelFormat = GL_RGB;
    switch (channels_)
    {
        case 1: pixelFormat = GL_RED;   break;
        case 2: pixelFormat = GL_RG;    break;
        case 3: pixelFormat = GL_RGB;   break;
        case 4: pixelFormat = GL_RGBA;  break;
    }

    create_from_data(width, height, image, pixelFormat, generateMipMaps, target);
    stbi_image_free(image);

	stbi_set_flip_vertically_on_load(false);

    return true;
}

std::string Texture::path() const
{
    return path_;
}

glm::vec2 Texture::dimensions() const
{
    return glm::vec2(width_, height_);
}

GLuint Texture::id() const
{
    return textureID_;
}
