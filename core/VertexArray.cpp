#include "VertexArray.h"

VertexArray::VertexArray()
{
    vertexArray = 0;
}

void VertexArray::create()
{
    glGenVertexArrays(1, &vertexArray);
}

void VertexArray::free() const
{
    glDeleteVertexArrays(1, &vertexArray);
}

void VertexArray::bind() const
{
    glBindVertexArray(vertexArray);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}

void VertexArray::enable_attribute(GLint location) const
{
	bind();
    glEnableVertexAttribArray(location);
}

void VertexArray::disable_attribute(GLint location) const
{
	bind();
    glDisableVertexAttribArray(location);
}

void VertexArray::configure_attribute(GLuint index, GLint size, GLenum type,
                              GLboolean normalized, GLsizei stride, const GLvoid* pointer) const
{
	bind();
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void VertexArray::draw_arrays(const GLenum mode, const GLint first, const GLsizei count) const
{
	bind();
	glDrawArrays(mode, first, count);
}

void VertexArray::draw_elements(const GLenum mode, const GLsizei count, const GLenum type, const void * indices) const
{
	bind();
	glDrawElements(mode, count, type, indices);
}

