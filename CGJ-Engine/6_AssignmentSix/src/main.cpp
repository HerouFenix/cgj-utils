#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <typeinfo>


#include "../headers/matrices/Matrix4.h"

#include "../headers/camera/Camera.h"
#include "../headers/camera/ArcBallCamera.h"

#include "../headers/scene/SceneManager.h"
#include "../headers/drawing/Shader.h"
#include "../headers/drawing/Mesh.h"


#include "../headers/shapes/Tetromino.h"
#include "../headers/drawing/Renderer.h"

#include "../headers/scene/SceneGraph.h"
#include "../headers/scene/Scene.h"

#include <ctime>
#include <ratio>
#include <chrono>


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
Scene scene;


Shader shader("resources/shaders/Basic3D.shader");

const GLuint UBO_BP = 0;

bool ortho = false;
bool projChanged;

bool quaternionRotation = false;

// KEY PRESSED FLAGS
bool forwardKeyPressed = false;
bool backwardKeyPressed = false;
bool lockMouse = true;
bool firstMouse = true;
bool mouseMoved = false;

bool moveForward = false;
bool moveBackward = false;
bool moveLeft = false;
bool moveRight = false;

bool mouseRotating = true;
bool downMoved, upMoved = false;

bool cameraReset = false;
bool stopRotating = false;
bool automaticRotating = false;

bool animate = false;
bool goToInitial = false;

std::chrono::high_resolution_clock::time_point timeStartedLerping;
float animation_total = 3000.0f; //Animation speed in milliseconds


/////////////////////////////////////////////////////////////////////// SCENE
void moveCamera() {
	// ARCBALL CAMERA //

	if (forwardKeyPressed) {
		scene.GetSceneGraphs()[0]->camera.incrementRadius(-0.05f);
	}
	if (backwardKeyPressed) {
		scene.GetSceneGraphs()[0]->camera.incrementRadius(0.05f);
	}

	if (!stopRotating) {
		if (!quaternionRotation) {
			//std::cout << "EULER ROTATION \n";
			if (mouseMoved) {
				scene.GetSceneGraphs()[0]->camera.rotateCameraAroundHorizontal(xOffset);
				scene.GetSceneGraphs()[0]->camera.rotateCameraAroundVertical(yOffset);
				mouseMoved = false;
			}
		}

		else {
			//std::cout << "QUATERNION ROTATION \n";

			if (mouseMoved) {
				scene.GetSceneGraphs()[0]->camera.rotateCameraAroundQuaternionHorizontal(xOffset);
				scene.GetSceneGraphs()[0]->camera.rotateCameraAroundQuaternionVertical(yOffset);
				mouseMoved = false;
			}
		}
	}

	///////////////////////////////////////////////////////////////////////

	cameraReset = false;
	if (projChanged)
		!projChanged;
}

void moveFloor() {
	if (moveForward) {
		scene.GetSceneGraphs()[0]->GetRoot()->ApplyLocalTransform(Matrix4::translation(0, 0, -0.05));
	}
	if (moveBackward) {
		scene.GetSceneGraphs()[0]->GetRoot()->ApplyLocalTransform(Matrix4::translation(0, 0, 0.05));
	}
	if (moveLeft) {
		scene.GetSceneGraphs()[0]->GetRoot()->ApplyLocalTransform(Matrix4::translation(-0.05, 0, 0));
	}
	if (moveRight) {
		scene.GetSceneGraphs()[0]->GetRoot()->ApplyLocalTransform(Matrix4::translation(0.05, 0, 0));
	}
}

void animateInitialToFinal() {

	auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::high_resolution_clock::now() - timeStartedLerping
		);
	float timeSinceStarted = dur.count();
	float percentageComplete;
	if (trunc(timeSinceStarted / animation_total) < 1.0f) {
		percentageComplete = timeSinceStarted / animation_total;
	}
	else {
		percentageComplete = 1.0f;
		animate = false;
		goToInitial = !goToInitial;
	}

	//SQUARE SHAPE //////////////////////////////////////////

		//translation
	Vector3 initialPos = Vector3(-0.11f, -0.11f, 0.0f);
	Vector3 finalPos(0.0f, 0.6f, 0.0f);
	Vector3 l = initialPos.Lerp(finalPos, percentageComplete);
	Matrix4 tr = (scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[0]->GetLocalTransform()).inverse()
		* Matrix4::translation(l.getX(), l.getY(), l.getZ());

	//rotations
	Matrix4 rot = scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[0]->GetLocalTransform().getRotation();
	Quaternion initialQuat(rot);
	Quaternion finalQuat(90.0f, { 0.0f, 0.0f, 1.0f, 1.0f });
	Quaternion q = initialQuat.Lerp(finalQuat, percentageComplete);
	Matrix4 tr_rot = rot.inverse() * q.GLRotationMatrix();

	scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[0]->ApplyLocalTransform(tr);
	scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[0]->ApplyLocalTransform(tr_rot);


	// I SHAPE ////////////////////////////////////////////

	//rotation
	rot = scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[3]->GetLocalTransform().getRotation();
	initialQuat = Quaternion(rot);
	finalQuat = Quaternion(0.0f, { 0.0f, 0.0f, 1.0f, 1.0f });
	q = initialQuat.Lerp(finalQuat, percentageComplete);
	tr_rot = rot.inverse() * q.GLRotationMatrix();

	//translation
	initialPos = Vector3(0.33f, 0.33f, 0.0f);
	finalPos = Vector3(0.0f, -0.3f, 0.0f);
	l = initialPos.Lerp(finalPos, percentageComplete);
	Vector3 p = scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[3]->GetLocalTransform().getTranslation();
	tr = (Matrix4::translation(p)).inverse()
		* Matrix4::translation(l.getX(), l.getY(), l.getZ());

	scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[3]->ApplyLocalTransform(tr);
	scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[3]->ApplyLocalTransform(tr_rot);


	// L SHAPE ////////////////////////////////////////////

	//rotation
	rot = scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[1]->GetLocalTransform().getRotation();
	initialQuat = Quaternion();
	finalQuat = Quaternion(70.0f, { 0.0f, 1.0f, 0.0f, 1.0f });
	q = initialQuat.Slerp(finalQuat, percentageComplete);
	tr_rot = rot.inverse() * q.GLRotationMatrix();
	//std::cout << scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[1]->pos << std::endl;

	//translation
	initialPos = Vector3(-0.33, -0.33f, 0.0f);
	finalPos = Vector3(-0.2f, -0.5f, 0.22);
	l = initialPos.Lerp(finalPos, percentageComplete);
	p = scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[1]->GetLocalTransform().getTranslation();
	tr = (Matrix4::translation(p)).inverse()
		* Matrix4::translation(l.getX(), l.getY(), l.getZ());

	scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[1]->ApplyLocalTransform(tr_rot);
	scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[1]->ApplyLocalTransform(tr);


	// REVERSE L SHAPE ////////////////////////////////////////////

	//rotation
	rot = scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[2]->GetLocalTransform().getRotation();
	initialQuat = Quaternion();
	finalQuat = Quaternion(-70.0f, { 0.0f, 1.0f, 0.0f, 1.0f });
	q = initialQuat.Slerp(finalQuat, percentageComplete);
	tr_rot = rot.inverse() * q.GLRotationMatrix();

	//translation
	initialPos = Vector3(0.33, -0.33f, 0.0f);
	finalPos = Vector3(0.2f, -0.5f, 0.22);
	l = initialPos.Lerp(finalPos, percentageComplete);
	p = scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[2]->GetLocalTransform().getTranslation();
	tr = (Matrix4::translation(p)).inverse()
		* Matrix4::translation(l.getX(), l.getY(), l.getZ());

	scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[2]->ApplyLocalTransform(tr_rot);
	scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[2]->ApplyLocalTransform(tr);
}

void animateFinalToInitial() {
	auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::high_resolution_clock::now() - timeStartedLerping
		);
	float timeSinceStarted = dur.count();
	float percentageComplete;
	if (trunc(timeSinceStarted / animation_total) < 1.0f) {
		percentageComplete = timeSinceStarted / animation_total;
	}
	else {
		percentageComplete = 1.0f;
		animate = false;
		goToInitial = !goToInitial;
	}

	//SQUARE SHAPE //////////////////////////////////////////

	//translation
	Vector3 initialPos = Vector3(0.0f, 0.6f, 0.0f);
	Vector3 finalPos(-0.11f, -0.11f, 0.0f);
	Vector3 l = initialPos.Lerp(finalPos, percentageComplete);
	Matrix4 tr = (scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[0]->GetLocalTransform()).inverse()
		* Matrix4::translation(l.getX(), l.getY(), l.getZ());

	//rotations
	Matrix4 rot = scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[0]->GetLocalTransform().getRotation();
	Quaternion initialQuat = Quaternion (90.0f, { 0.0f, 0.0f, 1.0f, 1.0f });;
	Quaternion finalQuat = Quaternion();
	Quaternion q = initialQuat.Lerp(finalQuat, percentageComplete);
	Matrix4 tr_rot = rot.inverse() * q.GLRotationMatrix();

	scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[0]->ApplyLocalTransform(tr_rot);
	scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[0]->ApplyLocalTransform(tr);
	


	// I SHAPE ////////////////////////////////////////////

	//rotation
	rot = scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[3]->GetLocalTransform().getRotation();
	initialQuat = Quaternion();
	finalQuat = Quaternion(90.0f, { 0.0f, 0.0f, 1.0f, 1.0f });
	q = initialQuat.Lerp(finalQuat, percentageComplete);
	tr_rot = rot.inverse() * q.GLRotationMatrix();

	//translation
	initialPos = Vector3(0.0f, -0.3f, 0.0f);
	finalPos = Vector3(0.33f, 0.33f, 0.0f);
	l = initialPos.Lerp(finalPos, percentageComplete);
	Vector3 p = scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[3]->GetLocalTransform().getTranslation();
	tr = (Matrix4::translation(p)).inverse()
		* Matrix4::translation(l.getX(), l.getY(), l.getZ());

	scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[3]->ApplyLocalTransform(tr_rot);
	scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[3]->ApplyLocalTransform(tr);


	// L SHAPE ////////////////////////////////////////////

	//rotation
	rot = scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[1]->GetLocalTransform().getRotation();
	initialQuat = Quaternion(70.0f, { 0.0f, 1.0f, 0.0f, 1.0f });
	finalQuat = Quaternion();
	q = initialQuat.Slerp(finalQuat, percentageComplete);
	tr_rot = rot.inverse() * q.GLRotationMatrix();
	//std::cout << scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[1]->pos << std::endl;

	//translation
	initialPos = Vector3(-0.2f, -0.5f, 0.22);
	finalPos = Vector3(-0.33, -0.33f, 0.0f);
	l = initialPos.Lerp(finalPos, percentageComplete);
	p = scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[1]->GetLocalTransform().getTranslation();
	tr = (Matrix4::translation(p)).inverse()
		* Matrix4::translation(l.getX(), l.getY(), l.getZ());

	scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[1]->ApplyLocalTransform(tr_rot);
	scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[1]->ApplyLocalTransform(tr);
	
	//std::cout << scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[1]->GetLocalTransform() << std::endl;


	// REVERSE L SHAPE ////////////////////////////////////////////

	//rotation
	rot = scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[2]->GetLocalTransform().getRotation();
	initialQuat = Quaternion(-70.0f, { 0.0f, 1.0f, 0.0f, 1.0f }); 
	finalQuat = Quaternion();
	q = initialQuat.Slerp(finalQuat, percentageComplete);
	tr_rot = rot.inverse() * q.GLRotationMatrix();

	//translation
	initialPos = Vector3(0.2f, -0.5f, 0.22);
	finalPos = Vector3(0.33, -0.33f, 0.0f);
	l = initialPos.Lerp(finalPos, percentageComplete);
	p = scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[2]->GetLocalTransform().getTranslation();
	tr = (Matrix4::translation(p)).inverse()
		* Matrix4::translation(l.getX(), l.getY(), l.getZ());

	scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[2]->ApplyLocalTransform(tr_rot);
	scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[2]->ApplyLocalTransform(tr);
}


void drawScene_Tetramino()
{
	bool cameraMoved = (mouseMoved || projChanged || cameraReset || forwardKeyPressed || backwardKeyPressed);

	if (cameraMoved)
		moveCamera();

	bool floorMoved = (moveForward || moveBackward || moveLeft || moveRight);
	if (floorMoved) {
		moveFloor();
	}
	/*
	if (animate) {

		//L shape

		if (scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[1]->GetWorldTransform()[0][0] > 0) {
			scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[1]->ApplyLocalTransform(Matrix4::rotationZ(1.00f, false));
		}
		else {
			animate_checklist[0] = true;
		}
		if (scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[1]->GetWorldTransform()[1][3] < -0.4f) {
			scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[1]->ApplyLocalTransform(Matrix4::translation(0.0f, 0.005f, 0.0f));
		}
		else {
			animate_checklist[1] = true;
		}
		if (scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[1]->GetWorldTransform()[0][0] > -0.05f) {
			scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[1]->ApplyLocalTransform(Matrix4::rotationY(1.00f, false));
		}
		else {
			animate_checklist[2] = true;
		}
		//Reversed-L shape

		if (scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[2]->GetWorldTransform()[0][0] > 0) {
			scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[2]->ApplyLocalTransform(Matrix4::rotationZ(-1.00f, false));
		}
		else {
			animate_checklist[3] = true;
		}
		if (scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[2]->GetWorldTransform()[1][3] < -0.4f) {
			scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[2]->ApplyLocalTransform(Matrix4::translation(0.0f, 0.005f, 0.0f));
		}
		else {
			animate_checklist[4] = true;
		}
		if (scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[2]->GetWorldTransform()[0][0] > -0.05f) {
			scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[2]->ApplyLocalTransform(Matrix4::rotationY(1.00f, false));
		}
		else {
			animate_checklist[5] = true;
		}

		//I shape

		if (scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[3]->GetWorldTransform()[1][3] < 0.4) {
			scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[3]->ApplyLocalTransform(Matrix4::translation(0.0f, 0.05f, 0.0f));
		}
		else {
			animate_checklist[6] = true;
		}
		if (scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[3]->GetWorldTransform()[0][0] < 1) {
			scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[3]->ApplyLocalTransform(Matrix4::rotationZ(-1.00f, false));
		}
		else {
			animate_checklist[7] = true;
		}
		if (scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[3]->GetWorldTransform()[0][3] > 0) {
			scene.GetSceneGraphs()[0]->GetRoot()->GetChildNodes()[1]->GetChildNodes()[3]->ApplyLocalTransform(Matrix4::translation(-0.035f, 0.0f, 0.0f));
		}
		else {
			animate_checklist[8] = true;
		}

		bool done = true;
		for(bool b: animate_checklist)
		{
			if (b == false) {
				done = false;
				break;
			}
		}
		if (done) {
			animate = false;
		}

	}
	*/

	if (animate) {

		if (!goToInitial) {// If in initial -> animate to final position
			animateInitialToFinal();
		}
		else { // else animate back to initial position
			animateFinalToInitial();
		}
	}

	glBindVertexArray(VaoId);
	shader.Bind();

	shader.SetUniform1i("isUniformColour", 1);

	scene.DrawSceneGraphs(ortho);

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
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(win, GLFW_TRUE);
			window_close_callback(win);
			break;
		case GLFW_KEY_UP:
			forwardKeyPressed = true;
			break;
		case GLFW_KEY_DOWN:
			backwardKeyPressed = true;
			break;
		case GLFW_KEY_W:
			moveForward = true;
			break;
		case GLFW_KEY_S:
			moveBackward = true;
			break;
		case GLFW_KEY_A:
			moveLeft = true;
			break;
		case GLFW_KEY_D:
			moveRight = true;
			break;
		case GLFW_KEY_R:
			scene.GetSceneGraphs()[0]->camera.resetCamera();
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
		case GLFW_KEY_C: {
			animate = !animate;
			timeStartedLerping = std::chrono::high_resolution_clock::now();
			break;
		}
			
		}
	}
	else if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_UP:
			forwardKeyPressed = false;
			break;
		case GLFW_KEY_DOWN:
			backwardKeyPressed = false;
			break;
		case GLFW_KEY_W:
			moveForward = false;
			break;
		case GLFW_KEY_S:
			moveBackward = false;
			break;
		case GLFW_KEY_A:
			moveLeft = false;
			break;
		case GLFW_KEY_D:
			moveRight = false;
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
}

void setupCamera() {
	// ARC BALL CAMERA SETUP //
	ArcBallCamera c(5);

	c.setOrthoProjectionMatrix(-2.0f, 2.0f, -2.0f, 2.0f, 1.0f, 10.0f);
	c.setPrespProjectionMatrix(50, ((GLfloat)window_width / (GLfloat)window_height), 1.0f, 25.0f);

	//Set initial cursor position to be the middle of the screen
	cursorX = (float)window_width / 2;
	cursorY = (float)window_height / 2;

	scene.GetSceneGraphs()[0]->SetCamera(c);
	scene.GetSceneGraphs()[0]->camera.SetupCamera(UBO_BP);
	scene.GetSceneGraphs()[0]->camera.RenderCamera(ortho);

	projChanged = false;
}

void setupScene() {
	scene.SetupTetrominoSceneGraph(scene.GetSceneGraphs()[0], &mesh, &shader);
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
	scene.CreateSceneGraph();

	int gl_major = 4, gl_minor = 3;
	int is_fullscreen = 0;
	int is_vsync = 1;
	GLFWwindow* win = setup(gl_major, gl_minor,
		920, 920, "Tetromino 3D", is_fullscreen, is_vsync);
	run(win);

	exit(EXIT_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////// END