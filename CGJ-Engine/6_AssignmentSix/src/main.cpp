#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../headers/matrices/Matrix4.h"

#include "../headers/camera/Camera.h"
#include "../headers/camera/ArcBallCamera.h"

#include "../headers/scene/SceneManager.h"
#include "../headers/drawing/Shader.h"
#include "../headers/drawing/Mesh.h"

#include "../headers/quaternions/Quaternion.h"

#include "../headers/shapes/Tetromino.h"
#include "../headers/drawing/Renderer.h"

#include "../headers/scene/SceneGraph.h"


#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2

GLuint VaoId, ProgramId;
std::vector <Vertex> Vertices;
std::vector <Texcoord> Texcoords;
std::vector <Normal> Normals;

Mesh mesh;

int window_width;
int window_height;
float cursorX, cursorY;
float xOffset, yOffset;

const float Threshold = (float)1.0e-5;

SceneManager sceneManager;

Shader shader("resources/shaders/Basic3D.shader");

const GLuint UBO_BP = 0;

bool ortho = false;
bool projChanged;

bool quaternionRotation = false;

SceneGraph sceneGraph;

// KEY PRESSED FLAGS
bool forwardKeyPressed = false;
bool backwardKeyPressed = false;
bool lockMouse = true;
bool firstMouse = true;
bool mouseMoved = false;

bool keyRotationX = false;
bool keyRotationY = false;
bool keyRotationZ = false;
bool mouseRotating = true;
bool downMoved, upMoved = false;

bool cameraReset = false;
bool stopRotating = false;
bool automaticRotating = false;

/////////////////////////////////////////////////////////////////////// SCENE
void moveCamera() {
	// ARCBALL CAMERA //

	if (forwardKeyPressed) {
		sceneGraph.camera.incrementRadius(-0.05f);
	}
	if (backwardKeyPressed) {
		sceneGraph.camera.incrementRadius(0.05f);
	}

	if (!stopRotating) {
		if (!quaternionRotation) {
			//std::cout << "EULER ROTATION \n";
			if (keyRotationX) {
				if (downMoved) {
					sceneGraph.camera.rotateCameraAroundVertical(-1);
				}
				else if (upMoved) {
					sceneGraph.camera.rotateCameraAroundVertical(1);
				}
			}
			else if (keyRotationY) {
				if (downMoved) {
					sceneGraph.camera.rotateCameraAroundHorizontal(-1);
				}
				else if (upMoved) {
					sceneGraph.camera.rotateCameraAroundHorizontal(1);
				}
			}
			else if (keyRotationZ) {
				if (downMoved) {
					sceneGraph.camera.rotateCameraAroundZ(-1);
				}
				else if (upMoved) {
					sceneGraph.camera.rotateCameraAroundZ(1);
				}
			}
			else if (mouseRotating)
				if (mouseMoved) {
					sceneGraph.camera.rotateCameraAroundHorizontal(xOffset);
					sceneGraph.camera.rotateCameraAroundVertical(yOffset);
					mouseMoved = false;
				}
		}

		else {
			//std::cout << "QUATERNION ROTATION \n";
			if (keyRotationX) {
				if (downMoved) {
					sceneGraph.camera.rotateCameraAroundQuaternionVertical(-1);
				}
				else if (upMoved) {
					sceneGraph.camera.rotateCameraAroundQuaternionVertical(1);
				}
			}
			else if (keyRotationY) {
				if (downMoved) {
					sceneGraph.camera.rotateCameraAroundQuaternionHorizontal(-1);
				}
				else if (upMoved) {
					sceneGraph.camera.rotateCameraAroundQuaternionHorizontal(1);
				}
			}
			else if (keyRotationZ) {
				if (downMoved) {
					sceneGraph.camera.rotateCameraAroundQuaternionZ(-1);
				}
				else if (upMoved) {
					sceneGraph.camera.rotateCameraAroundQuaternionZ(1);
				}
			}
			else if (mouseRotating)
				if (mouseMoved) {
					sceneGraph.camera.rotateCameraAroundQuaternionHorizontal(xOffset);
					sceneGraph.camera.rotateCameraAroundQuaternionVertical(yOffset);
					mouseMoved = false;
				}
		}
	}

	///////////////////////////////////////////////////////////////////////

	cameraReset = false;
	if (projChanged)
		!projChanged;
}

void drawScene_Tetramino()
{
	bool cameraMoved = (mouseMoved || projChanged || cameraReset || forwardKeyPressed || backwardKeyPressed || downMoved || upMoved);

	if (cameraMoved)
		moveCamera();

	glBindVertexArray(VaoId);
	shader.Bind();

	shader.SetUniform1i("isUniformColour", 1);

	sceneGraph.DrawSceneGraph(ortho);

	/// ///////////////////////////////////////////////////
	/*
	for (int i = 0; i < sceneManager.getSize(); i++) {
		shader.Bind();
		float colours[4];
		sceneManager.getPieceAt(i).getColours(colours);
		shader.SetUniform4fvec("uniformColour", colours);
		shader.UnBind();

		//Draw each square that makes up the piece using the transform matrices
		for (int j = 0; j < 4; j++) {
			float model[16];
			sceneManager.getPieceAt(i).getTransforms()[j].getRowMajor(model);
			Renderer::DrawObject((GLsizei)Vertices.size(), shader, model);
		}
	}
	*/
	/// ///////////////////////////////////////////////////

	shader.UnBind();
	glBindVertexArray(0);
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

void destroyBufferObjects()
{
	glBindVertexArray(VaoId);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(TEXCOORDS);
	glDisableVertexAttribArray(NORMALS);
	glDeleteVertexArrays(1, &VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void window_close_callback(GLFWwindow* win)
{
	shader.~Shader();
	destroyBufferObjects();
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
		case GLFW_KEY_X:
			keyRotationX = true;
			keyRotationY = false;
			keyRotationZ = false;
			mouseRotating = false;
			break;
		case GLFW_KEY_Y:
			keyRotationX = false;
			keyRotationY = true;
			keyRotationZ = false;
			mouseRotating = false;
			break;
		case GLFW_KEY_Z:
			keyRotationX = false;
			keyRotationY = false;
			keyRotationZ = true;
			mouseRotating = false;
			break;
		case GLFW_KEY_M:
			keyRotationX = false;
			keyRotationY = false;
			keyRotationZ = false;
			mouseRotating = true;
			break;
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(win, GLFW_TRUE);
			window_close_callback(win);
			break;
		case GLFW_KEY_W:
			forwardKeyPressed = true;
			break;
		case GLFW_KEY_S:
			backwardKeyPressed = true;
			break;
		case GLFW_KEY_R:
			sceneGraph.camera.resetCamera();
			cameraReset = true;
			break;
		case GLFW_KEY_G:
			quaternionRotation = !quaternionRotation;
			break;
		case GLFW_KEY_F:
			lockMouse = !lockMouse;
			if (lockMouse) {
				firstMouse = true;
			}
			break;
		case GLFW_KEY_SPACE:
			stopRotating = !stopRotating;
			break;
		case GLFW_KEY_UP:
			upMoved = true;
			break;
		case GLFW_KEY_DOWN:
			downMoved = true;
			break;

		}
	}
	else if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_W:
			forwardKeyPressed = false;
			break;
		case GLFW_KEY_S:
			backwardKeyPressed = false;
			break;
		case GLFW_KEY_UP:
			upMoved = false;
			break;
		case GLFW_KEY_DOWN:
			downMoved = false;
			break;
		}
	}

}

void mouse_callback(GLFWwindow* win, double xPos, double yPos) {
	if (firstMouse) // initially set to true
	{
		cursorX = (float)xPos;
		cursorY = (float)yPos;
		firstMouse = false;
	}

	xOffset = (float)xPos - cursorX;
	yOffset = cursorY - (float)yPos; // reversed since y-coordinates range from bottom to top

	cursorX = (float)xPos;
	cursorY = (float)yPos;

	mouseMoved = true;
}

void setupCallbacks(GLFWwindow* win)
{
	glfwSetKeyCallback(win, key_callback);
	glfwSetCursorPosCallback(win, mouse_callback);
	glfwSetWindowCloseCallback(win, window_close_callback);
	glfwSetWindowSizeCallback(win, window_size_callback);
}

///////////////////////////////////////////////////////////////////////// SETUP

GLFWwindow* setupWindow(int winx, int winy, const char* title,
	int is_fullscreen, int is_vsync)
{
	window_width = winx;
	window_height = winy;

	cursorX = (float)window_width / 2;
	cursorY = (float)window_height / 2;

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
	shader.SetupShader(mesh.getTexcoordsLoaded(), mesh.getNormalsLoaded());
	shader.SetUniformBlock("SharedMatrices", UBO_BP);
}

void setupBufferObjects() {
	GLuint VboVertices, VboTexcoords, VboNormals;

	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	{
		glGenBuffers(1, &VboVertices);
		glBindBuffer(GL_ARRAY_BUFFER, VboVertices);
		glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(VERTICES);
		glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

		if (mesh.getTexcoordsLoaded())
		{
			glGenBuffers(1, &VboTexcoords);
			glBindBuffer(GL_ARRAY_BUFFER, VboTexcoords);
			glBufferData(GL_ARRAY_BUFFER, Texcoords.size() * sizeof(Texcoord), &Texcoords[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(TEXCOORDS);
			glVertexAttribPointer(TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Texcoord), 0);
		}
		if (mesh.getNormalsLoaded())
		{
			glGenBuffers(1, &VboNormals);
			glBindBuffer(GL_ARRAY_BUFFER, VboNormals);
			glBufferData(GL_ARRAY_BUFFER, Normals.size() * sizeof(Normal), &Normals[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(NORMALS);
			glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(Normal), 0);
		}

	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboVertices);
	glDeleteBuffers(1, &VboTexcoords);
	glDeleteBuffers(1, &VboNormals);

	// CAMERA
	sceneGraph.camera.SetupCamera(UBO_BP);
}

void setupCamera() {
	// ARC BALL CAMERA SETUP //
	sceneGraph.camera.setOrthoProjectionMatrix(-2.0f, 2.0f, -2.0f, 2.0f, 1.0f, 10.0f);
	sceneGraph.camera.setPrespProjectionMatrix(50, ((GLfloat)window_width / (GLfloat)window_height), 1.0f, 25.0f);

	//Set initial cursor position to be the middle of the screen
	cursorX = (float)window_width / 2;
	cursorY = (float)window_height / 2;

	sceneGraph.camera.RenderCamera(ortho);

	projChanged = false;
}

void setupScene() {

	Tetromino_SQ sqPiece;
	SceneNode* root = sceneGraph.AddNode(&mesh, &shader, sqPiece);

	Tetromino_L lPiece;
	SceneNode* childL = sceneGraph.AddNode(&mesh, &shader, lPiece);

	root->ApplyLocalTransform(Matrix4::scaling(0.1, 0.1, 0.1));

	root->ApplyLocalTransform(Matrix4::translation(-0.11, -0.11, 0));

	childL->ApplyLocalTransform(Matrix4::translation(-0.22, -0.22, 0));

	
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

	mesh.CreateMesh("resources/models/cube.obj");
	Vertices = mesh.getVertices();
	Normals = mesh.getNormals();
	Texcoords = mesh.getTexCoords();

	setupBufferObjects();
	setupShaderProgram();
	setupCamera();
	setupScene();
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
	/*
	float squareDiagonal = sqrt(0.11f * 0.11f + 0.11f * 0.11f);

	int sqPiece = sceneManager.createSQPiece();
	sceneManager.transformPiece(sqPiece, Matrix4::scaling(0.1, 0.1, 0.1));
	sceneManager.transformPiece(sqPiece, Matrix4::translation(-0.11,-0.11,0));

	
	int lPiece = sceneManager.createLPiece();
	sceneManager.transformPiece(lPiece, Matrix4::scaling(0.1, 0.1, 0.1));
	sceneManager.transformPiece(lPiece, Matrix4::translation(-0.33, -0.33, 0));

	
	int rlPiece = sceneManager.createRLPiece();
	sceneManager.transformPiece(rlPiece, Matrix4::scaling(0.1, 0.1, 0.1));
	sceneManager.transformPiece(rlPiece, Matrix4::translation(0.33, -0.33, 0));

	
	int iPiece = sceneManager.createIPiece();
	sceneManager.transformPiece(iPiece, Matrix4::scaling(0.1, 0.1, 0.1));
	sceneManager.transformPiece(iPiece, Matrix4::rotationZ(-90, false, true));
	sceneManager.transformPiece(iPiece, Matrix4::translation(-0.33, 0.33, 0));
	*/

	ArcBallCamera arcBall(5);
	sceneGraph.SetCamera(arcBall);

	int gl_major = 4, gl_minor = 3;
	int is_fullscreen = 0;
	int is_vsync = 1;
	GLFWwindow* win = setup(gl_major, gl_minor,
		920, 920, "Tetromino 3D", is_fullscreen, is_vsync);
	run(win);
	exit(EXIT_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////// END