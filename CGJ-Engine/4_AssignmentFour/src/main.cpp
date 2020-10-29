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
float cursorX, cursorY;
float xOffset, yOffset;

SceneManager sceneManager;
VertexArray va;
IndexBuffer ib;
IndexBuffer ibBack;

Shader shader("resources/shaders/Basic.shader");

Camera camera(Vector3(3, 0, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));
float view[16];
float proj[16];
bool ortho = true;
bool projChanged;

// KEY PRESSED FLAGS
bool forwardKeyPressed = false;
bool leftKeyPressed = false;
bool rightKeyPressed = false;
bool backwardKeyPressed = false;

bool upKeyPressed = false;
bool downKeyPressed = false;

bool lockMouse = true;
bool firstMouse = true;
bool mouseMoved = false;

bool cameraInverted = false;
bool cameraReset = false;

/////////////////////////////////////////////////////////////////////// SCENE
void moveCamera() {
	// CAMERA MOVEMENT //
	if (mouseMoved) {
		camera.rotateCamera(xOffset, yOffset);
		mouseMoved = false;
	}

	if (forwardKeyPressed) {
		camera.moveCameraForward(0.05);
	}
	if (backwardKeyPressed) {
		camera.moveCameraBackward(0.05);
	}
	if (leftKeyPressed) {
		camera.moveCameraLeft(0.05);
	}
	if (rightKeyPressed) {
		camera.moveCameraRight(0.05);
	}

	if (upKeyPressed) {
		camera.moveCameraUp(0.05);
	}

	if (downKeyPressed) {
		camera.moveCameraDown(0.05);
	}


	///////////////////////////////////////////////////////////////////////
	// Get the updated view matrix
	Matrix4 viewM = camera.getViewMatrix();
	viewM.getRowMajor(view);
	cameraReset = false;
	cameraInverted = false;
}

void drawScene_Tetramino()
{
	bool cameraMoved = (mouseMoved || cameraInverted || cameraReset || forwardKeyPressed || backwardKeyPressed || leftKeyPressed || rightKeyPressed || upKeyPressed || downKeyPressed);

	if (cameraMoved)
		moveCamera();

	if (projChanged) {
		Matrix4 projM;
		if (ortho) {
			projM = camera.getOrthProj();
		}
		else {
			projM = camera.getPerspProj();
		}
		projM.getRowMajor(proj);

		projChanged = false;
	}

	shader.Bind();
	va.Bind();

	float colours[4];
	shader.SetUniform1i("isUniformColour", 1);

	for (int i = 0; i < sceneManager.getSize(); i++) {
		sceneManager.getPieceAt(i).getColours(colours);
		shader.SetUniform4fvec("uniformColour", colours);
		GLuint indices[4];

		//Draw each square that makes up the piece using the transform matrices
		for (int j = 0; j < 4; j++) {
			float model[16];
			sceneManager.getPieceAt(i).getTransforms()[j].getRowMajor(model);
			shader.SetUniform4fv("Model", model);
			shader.SetUniform4fv("View", view);
			shader.SetUniform4fv("Projection", proj);

			// Draw Front Face			
			ib.Bind();

			shader.SetUniform1i("isBack", 0);
			Renderer::Draw(va, ib, shader, sceneManager.getPieceAt(i).getMode());

			ib.Unbind();

			// Draw Back Face			
			ibBack.Bind();

			shader.SetUniform1i("isBack", 1);
			Renderer::Draw(va, ibBack, shader, sceneManager.getPieceAt(i).getMode());

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

void window_close_callback(GLFWwindow* win)
{
	shader.~Shader();
	va.~VertexArray();
	std::cout << "Bye bye!" << std::endl;
}

void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	//std::cout << "key: " << key << " " << scancode << " " << action << " " << mods << std::endl;

	// Key Presses
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_P:
			ortho = !ortho;
			projChanged = true;
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(win, GLFW_TRUE);
			window_close_callback(win);
			break;
		case GLFW_KEY_A:
			leftKeyPressed = true;
			break;
		case GLFW_KEY_D:
			rightKeyPressed = true;
			break;
		case GLFW_KEY_W:
			forwardKeyPressed = true;
			break;
		case GLFW_KEY_S:
			backwardKeyPressed = true;
			break;
		case GLFW_KEY_SPACE:
			upKeyPressed = true;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			downKeyPressed = true;
			break;
		case GLFW_KEY_F:
			lockMouse = !lockMouse;
			if (lockMouse) {
				firstMouse = true;
			}
			break;
		case GLFW_KEY_I:
			camera.invertCamera();
			cameraInverted = true;
			break;
		case GLFW_KEY_R:
			camera.resetCamera();
			cameraReset = true;
			break;
		}
	}
	else if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_A:
			leftKeyPressed = false;
			break;
		case GLFW_KEY_D:
			rightKeyPressed = false;
			break;
		case GLFW_KEY_W:
			forwardKeyPressed = false;
			break;
		case GLFW_KEY_S:
			backwardKeyPressed = false;
			break;
		case GLFW_KEY_SPACE:
			upKeyPressed = false;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			downKeyPressed = false;
			break;
		}
	}

}

void mouse_callback(GLFWwindow* win, double xPos, double yPos) {
	/*
		1. Calculate the mouse's offset since the last frame.
		2. Add the offset values to the camera's yaw and pitch values.
		3. Add some constraints to the minimum/maximum pitch values.
		4. Calculate the direction vector.
	*/

	if (firstMouse) // initially set to true
	{
		cursorX = xPos;
		cursorY = yPos;
		firstMouse = false;
	}

	xOffset = xPos - cursorX;
	yOffset = cursorY - yPos; // reversed since y-coordinates range from bottom to top

	cursorX = xPos;
	cursorY = yPos;

	mouseMoved = true;
}

void setupCallbacks(GLFWwindow* win)
{
	glfwSetKeyCallback(win, key_callback);
	glfwSetCursorPosCallback(win, mouse_callback);
	glfwSetWindowSizeCallback(win, window_size_callback);
	glfwSetWindowCloseCallback(win, window_close_callback);
}

///////////////////////////////////////////////////////////////////////// SETUP

GLFWwindow* setupWindow(int winx, int winy, const char* title,
	int is_fullscreen, int is_vsync)
{
	window_width = winx;
	window_height = winy;

	cursorX = window_width / 2;
	cursorY = window_height / 2;

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

	GLuint backIndices[4] = { 0,3,2,1 };
	ibBack.BuildIndexBuffer(backIndices, 4);
}

void setupCamera() {
	// CAMERA SETUP //
	camera.setOrthoProjectionMatrix(-1, 1, -1, 1, 1, 10);
	camera.setPrespProjectionMatrix(15, window_width / window_height, 1, 10);

	//Set initial cursor position to be the middle of the screen
	cursorX = window_width / 2;
	cursorY = window_height / 2;

	Matrix4 viewM = camera.getViewMatrix();
	viewM.getRowMajor(view);


	Matrix4 projM;
	if (ortho) {
		projM = camera.getOrthProj();
	}
	else {
		projM = camera.getPerspProj();
	}
	projM.getRowMajor(proj);

	projChanged = false;
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
	setupBufferObjects();
	setupShaderProgram();
	setupCamera();
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

		if (lockMouse) {
			glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //Tell GLFW that it should hide the cursorand capture it.Capturing a cursor means that, once the application has focus, the mouse cursor stays within the center of the window(unless the application loses focus or quits)
		}
		else {
			glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

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

	int gl_major = 4, gl_minor = 3;
	int is_fullscreen = 0;
	int is_vsync = 1;
	GLFWwindow* win = setup(gl_major, gl_minor,
		920, 920, "Tetromino", is_fullscreen, is_vsync);
	run(win);
	exit(EXIT_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////// END