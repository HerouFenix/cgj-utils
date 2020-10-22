#include <iostream>
#include <sstream>
#include <iomanip>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../headers/matrices/Matrix4.h"

#include "../headers/camera/Camera.h"
#include "../headers/scene/SceneManager.h"
#include "../headers/drawing/VertexArray.h"
#include "../headers/drawing/VertexBufferLayout.h"

int window_width;
int window_height;

SceneManager sceneManager;
Camera camera;
bool ortho = true;
/////////////////////////////////////////////////////////////////////// SCENE

void drawScene_Tetramino()
{
	// CAMERA MOVEMENT //
	const float radius = 5.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	camera.createViewMatrix(Vector3(camX, 0, camZ), Vector3(0, 0, 0), Vector3(0, 1, 0));
	
	///////////////////////////////////////////////////////////////////////

	float view[16];
	Matrix4 viewM = camera.getView();
	viewM.getRowMajor(view);

	float proj[16];
	Matrix4 projM;
	if (ortho) {
		projM = camera.getOrthProj();
	}
	else {
		projM = camera.getPerspProj();
	}
	projM.getRowMajor(proj);


	Renderer renderer;

	Shader shader("resources/shaders/Basic.shader");

	VertexBufferLayout layout;
	layout.Push<float>(4);
	layout.Push<float>(4);

	VertexArray va;
	VertexBuffer vb(0, 4 * 8 * sizeof(float));
	for (int i = 0; i < sceneManager.getSize(); i++) {
		Vertex vertices[4];

		sceneManager.getPieceAt(i).getVertices(vertices);

		GLuint indices[4];
		

		vb.SubBufferData(0, 4 * 8 * sizeof(float), vertices);

		shader.Bind();
		va.Bind();
		va.AddBuffer(vb, layout);

		//Draw each square that makes up the piece using the transform matrices
		for (int j = 0; j < 4; j++) {
			// Draw Front Face
			sceneManager.getPieceAt(i).getIndices(indices);
			IndexBuffer ib(indices, 6);
			ib.Bind();

			float model[16];
			sceneManager.getPieceAt(i).getTransforms()[j].getRowMajor(model);
			shader.SetUniform4fv("Model", model);

			shader.SetUniform4fv("View", view);

			shader.SetUniform4fv("Projection", proj);

			shader.SetUniform1i("isBack", 0);

			renderer.Draw(va, ib, shader, sceneManager.getPieceAt(i).getMode());

			ib.Unbind();


			// Draw Back Face
			sceneManager.getPieceAt(i).getReverseIndices(indices);
			IndexBuffer ibBack(indices, 6);
			ibBack.Bind();

			shader.SetUniform4fv("Model", model);

			shader.SetUniform4fv("View", view);

			shader.SetUniform4fv("Projection", proj);

			shader.SetUniform1i("isBack", 1);

			renderer.Draw(va, ibBack, shader, sceneManager.getPieceAt(i).getMode());

			ibBack.Unbind();
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

void window_close_callback(GLFWwindow* win)
{
	std::cout << "Bye bye!" << std::endl;
}

void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	//std::cout << "key: " << key << " " << scancode << " " << action << " " << mods << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(win, GLFW_TRUE);
		window_close_callback(win);
	}

	// Change Perspective
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		ortho = !ortho;
	}
}

void setupCallbacks(GLFWwindow* win)
{
	glfwSetKeyCallback(win, key_callback);
	glfwSetWindowSizeCallback(win, window_size_callback);
	glfwSetWindowCloseCallback(win, window_close_callback);
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
	// CAMERA SETUP //
	camera.createViewMatrix(Vector3(5,0,5), Vector3(0,0,0), Vector3(0,1,0));
	camera.createOrthoProjectionMatrix(-1,1, -1, 1, 1, 10);
	camera.createPrespProjectionMatrix(15, 920/920, 1, 10);

	/////////////////////////////////////////////////////////////////////

	// DRAW SCENE //
	float squareDiagonal = sqrt(0.11 * 0.11 + 0.11 * 0.11);
	//int debugPiece = sceneManager.createDebugPiece();
	int sqPiece = sceneManager.createSQPiece();
	sceneManager.transformPiece(sqPiece, Matrix4::rotationZ(45, false, true));

	int lPiece = sceneManager.createLPiece();
	//sceneManager.transformPiece(lPiece, Matrix4::translation(-0.22, -0.11, 0));
	sceneManager.transformPiece(lPiece, Matrix4::rotationZ(-45, false, true));
	sceneManager.transformPiece(lPiece, Matrix4::translation(-(squareDiagonal + squareDiagonal / 2), squareDiagonal / 2, 0));

	int rlPiece = sceneManager.createRLPiece();
	//sceneManager.transformPiece(rlPiece, Matrix4::translation(0.11, -0.11, 0));
	sceneManager.transformPiece(rlPiece, Matrix4::rotationZ(-45, false, true));
	sceneManager.transformPiece(rlPiece, Matrix4::translation(0, -squareDiagonal, 0));

	int iPiece = sceneManager.createIPiece();
	//sceneManager.transformPiece(iPiece, Matrix4::translation(0.22, -0.11, 0));
	sceneManager.transformPiece(iPiece, Matrix4::rotationZ(45, false, true));
	sceneManager.transformPiece(iPiece, Matrix4::translation(squareDiagonal + squareDiagonal / 2, squareDiagonal / 2, 0));

	/////////////////////////////////////////////////////////////////////

	/*int tPiece = sceneManager.createTPiece();
	sceneManager.transformPiece(tPiece, Matrix4::translation(0.55, 0.11, 0));
	sceneManager.transformPiece(tPiece, Matrix4::rotationZ(45, false, true));

	int sPiece = sceneManager.createSPiece();
	sceneManager.transformPiece(sPiece, Matrix4::translation(0.44, 0.0, 0));
	sceneManager.transformPiece(sPiece, Matrix4::rotationZ(45, false, true));

	int rsPiece = sceneManager.createRSPiece();
	sceneManager.transformPiece(rsPiece, Matrix4::translation(0.55, -0.11, 0));
	sceneManager.transformPiece(rsPiece, Matrix4::rotationZ(45, false, true));
	*/


	int gl_major = 4, gl_minor = 3;
	int is_fullscreen = 0;
	int is_vsync = 1;
	GLFWwindow* win = setup(gl_major, gl_minor,
		920, 920, "Tetromino", is_fullscreen, is_vsync);
	run(win);
	exit(EXIT_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////// END