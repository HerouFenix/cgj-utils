#pragma once
#include <GL\glew.h>
class VertexBuffer
{
private:
	GLuint m_VboID;
	GLenum mode;
public:
	VertexBuffer();
	VertexBuffer(const void* data, GLuint size);
	VertexBuffer(const void* data, GLuint size, GLuint UBO_BP , GLenum bufferMode, GLenum draw);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void SubBufferData(GLintptr offset, GLuint size, const void* data);

	GLuint getID() const;
};

