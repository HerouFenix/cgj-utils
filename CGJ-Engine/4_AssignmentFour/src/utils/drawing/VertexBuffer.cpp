#include "../../headers/drawing/VertexBuffer.h"
#include "../../headers/drawing/Renderer.h"
#include <iostream>


VertexBuffer::VertexBuffer()
{
}

VertexBuffer::VertexBuffer(const void* data, GLuint size)
{
	GLCall(glGenBuffers(1, &m_VboID));

	mode = GL_ARRAY_BUFFER;

	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

	Unbind();

}

VertexBuffer::VertexBuffer(const void* data, GLuint size, GLuint UBO_BP, GLenum bufferMode, GLenum draw)
{
	GLCall(glGenBuffers(1, &m_VboID));

	mode = bufferMode;

	Bind();
	GLCall(glBufferData(mode, size, data, draw));
	GLCall(glBindBufferBase(mode, UBO_BP, m_VboID));
	Unbind();
}


VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_VboID));
}

void VertexBuffer::Bind() const
{
	//std::cout << "Binding to: " << m_VboID << "\n";
	//std::cout << "Mode : " << mode << "  (" << GL_UNIFORM_BUFFER << ")" << "\n\n";

	GLCall(glBindBuffer(mode, m_VboID));
}

void VertexBuffer::Unbind() const
{
	//std::cout << "Unbinding to: " << m_VboID << "\n";
	//std::cout << "Mode : " << mode << "  (" << GL_UNIFORM_BUFFER << ")" << "\n\n";

	GLCall(glBindBuffer(mode, 0));

}

void VertexBuffer::SubBufferData(GLintptr offset, GLuint size, const void* data)
{
	Bind();
	GLCall(glBufferSubData(mode, offset, size, data));
	Unbind();
}

GLuint VertexBuffer::getID() const
{
	return m_VboID;
}
