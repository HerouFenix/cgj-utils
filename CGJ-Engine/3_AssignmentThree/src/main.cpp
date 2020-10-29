#include <iostream>
#include <sstream>
#include <iomanip>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../headers/matrices/Matrix4.h"

#include "../headers/scene/SceneManager.h"
#include "../headers/drawing/VertexArray.h"
#include "../headers/drawing/VertexBufferLayout.h"

int window_width;
int window_height;

SceneManager sceneManager;
VertexArray va;
IndexBuffer ib;
Shader shader("resources/shaders/Basic.shader");
/////////////////////////////////////////////////////////////////////// SCENE

// All pieces share the same "main" or "central" square
void drawScene_Tetramino()
{
	shader.Bind();
	va.Bind();
	ib.Bind();

	float colours[4];
	shader.SetUniform1i("isUniformColour", 1);

	for (int i = 0; i < sceneManager.getSize(); i++) {
		sceneManager.getPieceAt(i).getColours(colours);
		shader.SetUniform4fvec("uniformColour", colours);

		//Draw each square that makes up the piece using the transform matrices
		for (int j = 0; j < 4; j++) {
			float matrix[16];
			sceneManager.getPieceAt(i).getTransforms()[j].getRowMajor(matrix);
			shader.SetUniform4fv("Matrix", matrix);
			Renderer::Draw(va, ib, shader, sceneManager.getPieceAt(i).getMode());
		}
	}
}
///////////////////////////////////////////////////////////////////// CALLBACKS



void window_size_callback(GLFWwindow* win, int winx, int winy)
{
	glViewport(0, 0, winx, winy);
}

void glfw_error_callback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

///////////////////////////////////////////////////////////////////////// SETUP

GLFWwindow* setupWindow(int winx, int winy, const char* title,
	int is_fullscreen, int is_vsync)
{
	window_width = winx;
	window_height = winy;

	GLFWmonitor* monitor = is_fullscreen ? glfwGetPrimaryMonitor() : 0;
	GLFWwindow* win = glfwCreateWindow(winx, winy, title, monitor, 0);

	if (!win)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(win);
	glfwSwapInterval(is_vsync);

	return win;
}

void setupCallbacks(GLFWwindow* win)
{
	glfwSetWindowSizeCallback(win, window_size_callback);
}

GLFWwindow* setupGLFW(int gl_major, int gl_minor,
	int winx, int winy, const char* title, int is_fullscreen, int is_vsync)
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	GLFWwindow* win = setupWindow(winx, winy, title, is_fullscreen, is_vsync);
	setupCallbacks(win);

#if _DEBUG
	std::cout << "GLFW " << glfwGetVersionString() << std::endl;
#endif
	return win;
}

void setupGLEW()
{
	glewExperimental = GL_TRUE;
	// Allow extension entry points to be loaded even if the extension isn't 
	// present in the driver's extensions string.
	GLenum result = glewInit();
	if (result != GLEW_OK)
	{
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
	// You might get GL_INVALID_ENUM when loading GLEW.
}

void checkOpenGLInfo()
{
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cerr << "OpenGL Renderer: " << renderer << " (" << vendor << ")" << std::endl;
	std::cerr << "OpenGL version " << version << std::endl;
	std::cerr << "GLSL version " << glslVersion << std::endl;
}

void setupOpenGL(int winx, int winy)
{
#if _DEBUG
	checkOpenGLInfo();
#endif
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glViewport(0, 0, winx, winy);
}


void setupShaderProgram() {
	shader.SetupShader();
}

void setupBufferObjects() {
	va.CreateVertexArray();

	Vector4 vertices[4];

	vertices[0] = Vector4(0 - 0.05f, 0 - 0.05f, 0, 1.0f);
	vertices[1] = Vector4(0 + 0.05f, 0 - 0.05f, 0, 1.0f);
	vertices[2] = Vector4(0 + 0.05f, 0 + 0.05f, 0, 1.0f);
	vertices[3] = Vector4(0 - 0.05f, 0 + 0.05f, 0, 1.0f);

	VertexBufferLayout layout;
	layout.Push<Vector4>(1); // One Vector 4 for each vertex's position

	VertexBuffer vb(vertices, sizeof(vertices));
	va.AddBuffer(vb, layout);

	GLuint indices[4] = { 0,1,2,3 };
	ib.BuildIndexBuffer(indices, 4);
}


GLFWwindow* setup(int major, int minor,
	int winx, int winy, const char* title, int is_fullscreen, int is_vsync)
{
	GLFWwindow* win =
		setupGLFW(major, minor, winx, winy, title, is_fullscreen, is_vsync);
	setupGLEW();
	setupOpenGL(winx, winy);

	//setupBufferObjects();	//Create buffer objects

#ifdef ERROR_CALLBACK
	setupErrorCallback();
#endif
	setupBufferObjects();
	setupShaderProgram();
	return win;
}


void destroyBufferObjects()
{
	va.~VertexArray();
}
void destroyShaderProgram()
{
	shader.~Shader();
}

void window_close_callback(GLFWwindow* win)
{
	destroyShaderProgram();
	destroyBufferObjects();
}
////////////////////////////////////////////////////////////////////////// RUN

void run(GLFWwindow* win)
{
	double last_time = glfwGetTime();
	while (!glfwWindowShouldClose(win))
	{
		double time = glfwGetTime();
		double elapsed_time = time - last_time;
		last_time = time;

		// Double Buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		drawScene_Tetramino();

		glfwSwapBuffers(win);
		glfwPollEvents();

	}
	glfwDestroyWindow(win);
	glfwTerminate();
}




////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char* argv[])
{
	// DRAW SCENE //
	float squareDiagonal = sqrt(0.11 * 0.11 + 0.11 * 0.11);

	int sqPiece = sceneManager.createSQPiece();
	sceneManager.transformPiece(sqPiece, Matrix4::rotationZ(45, false, true));

	int lPiece = sceneManager.createLPiece();
	//sceneManager.transformPiece(lPiece, Matrix4::translation(-0.22, -0.11, 0));
	sceneManager.transformPiece(lPiece, Matrix4::rotationZ(-45, false, true));
	sceneManager.transformPiece(lPiece, Matrix4::translation(-(squareDiagonal+squareDiagonal/2), squareDiagonal/2, 0));

	int rlPiece = sceneManager.createRLPiece();
	//sceneManager.transformPiece(rlPiece, Matrix4::translation(0.11, -0.11, 0));
	sceneManager.transformPiece(rlPiece, Matrix4::rotationZ(-45, false, true));
	sceneManager.transformPiece(rlPiece, Matrix4::translation(0, -squareDiagonal, 0));

	int iPiece = sceneManager.createIPiece();
	//sceneManager.transformPiece(iPiece, Matrix4::translation(0.22, -0.11, 0));
	sceneManager.transformPiece(iPiece, Matrix4::rotationZ(45, false, true));
	sceneManager.transformPiece(iPiece, Matrix4::translation(squareDiagonal + squareDiagonal/2, squareDiagonal/2, 0));

	/////////////////////////////////////////////////////////////////////

	int gl_major = 4, gl_minor = 3;
	int is_fullscreen = 0;
	int is_vsync = 1;
	GLFWwindow* win = setup(gl_major, gl_minor,
		920, 920, "Tetromino", is_fullscreen, is_vsync);
	run(win);
	exit(EXIT_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////// END