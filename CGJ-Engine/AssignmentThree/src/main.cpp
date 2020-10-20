#include <iostream>
#include <sstream>
#include <iomanip>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../headers/vectors/Vector3.h"
#include "../headers/vectors/Vector2.h"
#include "../headers/vectors/Vector4.h"

#include "../headers/matrices/Matrix3.h"
#include "../headers/matrices/Matrix2.h"
#include "../headers/matrices/Matrix4.h"


#include "../headers/scene/SceneManager.h"
#include "../headers/drawing/VertexArray.h"
#include "../headers/drawing/VertexBufferLayout.h"


SceneManager sceneManager;


/////////////////////////////////////////////////////////////////////// SCENE

void drawScene_Tetramino()
{


	Renderer renderer;

	Shader shader("resources/shaders/Basic.shader");

	GLuint indices[] = {0, 1, 2, 3};
	IndexBuffer ib(indices, 4);

	GLuint indices_back[] = { 3, 2, 1, 0 };
	IndexBuffer ib_back(indices_back, 4);

	VertexBufferLayout layout;
	layout.Push<float>(4);
	layout.Push<float>(4);

	VertexArray va;
	VertexBuffer vb(0, 4 * 8 * sizeof(float));
	for (int i = 0; i < sceneManager.getSize(); i++) {
		Vertex vertices[4];
		sceneManager.getPieceAt(i).getVertices(vertices);
		vb.SubBufferData(0, 4 * 8 * sizeof(float), vertices);
		shader.Bind();
		va.Bind();
		ib.Bind();
		va.AddBuffer(vb, layout);
		for (int j = 0; j < 4; j++) {
			float matrix[16];
			sceneManager.getPieceAt(i).getTransforms()[j].getRowMajor(matrix);
			shader.SetUniform4fv("Matrix", matrix);
			shader.SetUniform1i("isBack", 0);
			renderer.Draw(va, ib, shader);
			shader.SetUniform1i("isBack", 1);
			renderer.Draw(va, ib_back, shader);
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

GLFWwindow* setup(int major, int minor,
	int winx, int winy, const char* title, int is_fullscreen, int is_vsync)
{
	GLFWwindow* win =
		setupGLFW(major, minor, winx, winy, title, is_fullscreen, is_vsync);
	setupGLEW();
	setupOpenGL(winx, winy);
#ifdef ERROR_CALLBACK
	setupErrorCallback();
#endif
	//createShaderProgram();
	return win;
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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// DRAW SCENE //

	int sqPiece = sceneManager.createSQPiece();
	sceneManager.transformPiece(sqPiece, Matrix4::rotationZ(45, false, true));

	int lPiece = sceneManager.createLPiece();
	sceneManager.transformPiece(lPiece, Matrix4::translation(-0.22, -0.11, 0));
	sceneManager.transformPiece(lPiece, Matrix4::rotationZ(-45, false, true));

	int rlPiece = sceneManager.createRLPiece();
	sceneManager.transformPiece(rlPiece, Matrix4::translation(0.11, -0.11, 0));
	sceneManager.transformPiece(rlPiece, Matrix4::rotationZ(-45, false, true));

	int iPiece = sceneManager.createIPiece();
	sceneManager.transformPiece(iPiece, Matrix4::translation(0.22, -0.11, 0));
	sceneManager.transformPiece(iPiece, Matrix4::rotationZ(45, false, true));

	/////////////////////////////////////////////////////////////////////

	int tPiece = sceneManager.createTPiece();
	sceneManager.transformPiece(tPiece, Matrix4::translation(0.55, 0.11, 0));
	sceneManager.transformPiece(tPiece, Matrix4::rotationZ(45, false, true));

	int sPiece = sceneManager.createSPiece();
	sceneManager.transformPiece(sPiece, Matrix4::translation(0.44, 0.0, 0));
	sceneManager.transformPiece(sPiece, Matrix4::rotationZ(45, false, true));

	int rsPiece = sceneManager.createRSPiece();
	sceneManager.transformPiece(rsPiece, Matrix4::translation(0.55, -0.11, 0));
	sceneManager.transformPiece(rsPiece, Matrix4::rotationZ(45, false, true));



	int gl_major = 4, gl_minor = 3;
	int is_fullscreen = 0;
	int is_vsync = 1;
	GLFWwindow* win = setup(gl_major, gl_minor,
		920, 920, "Tetromino", is_fullscreen, is_vsync);
	run(win);
	exit(EXIT_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////// END