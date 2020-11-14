#include "../../headers/drawing/VertexBuffer.h"
#include "../../headers/drawing/Renderer.h"
#include <iostream>


VertexBuffer::VertexBuffer()
{
	m_VboID = -1;
}

VertexBuffer::VertexBuffer(const void* data, GLuint size)
{
	GLCall(glGenBuffers(1, &m_VboID));

	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

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

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VboID));
}

void VertexBuffer::Unbind() const
{
	//std::cout << "Unbinding to: " << m_VboID << "\n";
	//std::cout << "Mode : " << mode << "  (" << GL_UNIFORM_BUFFER << ")" << "\n\n";

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

}

void VertexBuffer::SubBufferData(GLintptr offset, GLuint size, const void* data)
{
	Bind();
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
	Unbind();
}

GLuint VertexBuffer::getID() const
{
	return m_VboID;
}
