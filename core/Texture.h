#ifndef TEXTURE_H
#define TEXTURE_H

#include "includes.h"

class Texture
{
public:

	Texture();
	~Texture() = default;

	bool create_from_file(const std::string& path, bool generateMipMaps = true, GLenum target = GL_TEXTURE_2D);
	void create_from_data(int width, int height, const unsigned char* data, GLenum pixelFormat, bool generateMipMaps = true, GLenum bindTarget = GL_TEXTURE_2D);
	void bind() const;
	void unbind() const;

	GLuint id() const;
	std::string path() const;
	glm::vec2 dimensions() const;

private:

	void free() const;

	GLint width_, height_, channels_;
	GLuint textureID_;
	std::string path_;
	GLenum bindTarget_;
};
#endif
