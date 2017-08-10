#pragma once

#include "includes.h"

class VertexArray
{
public:

	VertexArray();
	~VertexArray() = default;

	void create();
	void free() const;
	void bind() const;
	static void unbind();
	void enable_attribute(GLint location = 0) const;
	void disable_attribute(GLint location = 0) const;
	void configure_attribute(GLuint index, GLint size, GLenum type,
		GLboolean normalized, GLsizei stride, const GLvoid* pointer) const;
	void draw_arrays(const GLenum mode, const GLint first, const GLsizei count) const;
	void draw_elements(const GLenum mode, const GLsizei count, const GLenum type, const void * indices) const;

private:

	GLuint vertexArray;
};
