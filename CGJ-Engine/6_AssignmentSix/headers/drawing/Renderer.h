#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"



#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
	static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const GLenum mode = GL_TRIANGLES);
	static void DrawObject(const GLuint VaoId, GLsizei size, Shader& shader,float* model);
	static void clear();
};


