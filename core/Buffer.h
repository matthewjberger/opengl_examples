#pragma once

#include "includes.h"
#include <vector>

class Buffer
{
public:

	Buffer();
	~Buffer() = default;

	void create(GLuint type = GL_ARRAY_BUFFER, GLint size = 0);
	void free();
	void bind() const;
	void unbind() const;
	void add_data(void* newData, GLuint dataSize);
	void upload_data(GLenum drawingHint = GL_STATIC_DRAW);
	bool update_buffer(const GLvoid* data, GLsizeiptr size, GLintptr offset) const;

private:
	GLuint buffer_;
	GLuint type_;
	std::vector<GLbyte> data_;
	bool uploaded_;
};
