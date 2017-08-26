#ifndef TEXTURE_H
#define TEXTURE_H

#include "Includes.h"

class Texture
{
public:

	Texture();
	~Texture() = default;

	bool create_texture_from_file(const std::string& path);
	bool create_cubemap_from_files(const std::vector<std::string> faces);
	void bind(int textureID = 0) const;
	void unbind(int textureID = 0) const;

	GLuint id() const;
	glm::vec2 dimensions() const;

private:

	void free() const;

	GLint width_, height_;
	GLuint textureID_;
	GLenum bindTarget_;
};
#endif
