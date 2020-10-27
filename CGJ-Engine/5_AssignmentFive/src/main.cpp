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
#include "../headers/camera/Quaternion.h"
#include <cassert>

const float Threshold = (float)1.0e-5;

int window_width;
int window_height;
float cursorX, cursorY;
float xOffset, yOffset;

SceneManager sceneManager;
Camera camera(Vector3(3, 0, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));
bool ortho = true;

// KEY PRESSED
bool forwardKeyPressed = false;
bool leftKeyPressed = false;
bool rightKeyPressed = false;
bool backwardKeyPressed = false;

bool upKeyPressed = false;
bool downKeyPressed = false;

bool lockMouse = true;
bool firstMouse = true;
bool mouseMoved = false;

/////////////////////////////////////////////////////////////////////// SCENE

void drawScene_Tetramino()
{
	const float radius = 20.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	Vector4 axis(0.0f, 1.0f, 0.0f, 0.0f);
	Quaternion qtr(-90.0f, axis);
	camera.rotateCamera(qtr);

	if (forwardKeyPressed) {
		camera.moveCameraForward(0.05);
	}
	if (backwardKeyPressed) {
		camera.moveCameraBackward(0.05);
	}

	///////////////////////////////////////////////////////////////////////

	float view[16];
	Matrix4 viewM = camera.getViewMatrix();
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

void window_close_callback(GLFWwindow* win)
{
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

void setupCamera() {
	// CAMERA SETUP //
	camera.setOrthoProjectionMatrix(-1, 1, -1, 1, 1, 10);
	camera.setPrespProjectionMatrix(15, window_width / window_height, 1, 10);

	//Set initial cursor position to be the middle of the screen
	cursorX = window_width / 2;
	cursorY = window_height / 2;
}

GLFWwindow* setup(int major, int minor,
	int winx, int winy, const char* title, int is_fullscreen, int is_vsync)
{
	GLFWwindow* win =
		setupGLFW(major, minor, winx, winy, title, is_fullscreen, is_vsync);
	setupGLEW();
	setupOpenGL(winx, winy);

	setupCamera();

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
	int gl_major = 4, gl_minor = 3;
	int is_fullscreen = 0;
	int is_vsync = 1;
	GLFWwindow* win = setup(gl_major, gl_minor,
		920, 920, "Tetromino", is_fullscreen, is_vsync);


	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "///////////TEST QUATERNIONS////////////////////" << std::endl;
	std::cout << std::endl;
	std::cout << "///////////TEST #1////////////////////" << std::endl;
	Vector4 axis ( 0.0f, 1.0f, 0.0f, 1.0f );
	Quaternion q  = Quaternion::fromAngleAxis(90.0f, axis);
	std::cout << "q" << q;

	Quaternion qi (0.0f, 7.0f, 0.0f, 0.0f);
	std::cout << "vi" << qi;

	Quaternion qe (0.0f, 0.0f, 0.0f, -7.0f);
	std::cout << "qe" << qe;

	Quaternion qinv = q.Inverse();
	qinv.clean(); 
	std::cout << "qinv" << qinv;

	Quaternion qf1 = (q * qi) * qinv;
	std::cout << "qf1" << qf1;

	assert(qf1 == qe);


	Quaternion qconj = q.Conjugate();
	std::cout << "qconj" << qconj;

	Quaternion qf2 = (q * qi) * qconj;
	std::cout << "qf2" << qf2;

	assert(qf2 == qe);

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "///////////TEST #2////////////////////" << std::endl;

	Vector4 axis2 = { 0.0f, 1.0f, 0.0f, 1.0f };
	Quaternion q2 = Quaternion::fromAngleAxis(90.0f, axis2);
	std::cout << "q" << q2;

	Vector4 vi2 = { 7.0f, 0.0f, 0.0f, 1.0f };
	std::cout << "vi" << vi2 << std::endl;

	Vector4 ve2 = { 0.0f, 0.0f, -7.0f, 1.0f };
	std::cout << "ve" << ve2 << std::endl;

	Matrix4 m2 = q2.GLRotationMatrix();
	m2.clean();
	std::cout << "M =" << m2;

	Vector4 vf2 = m2 * vi2;
	std::cout << "vf" << vf2 << std::endl;

	assert(vf2 == ve2);

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "///////////TEST #3////////////////////" << std::endl;
	Vector4 axis_x = { 1.0f, 0.0f, 0.0f, 1.0f };
	Vector4 axis_y = { 0.0f, 1.0f, 0.0f, 1.0f };
	Vector4 axis_z = { 0.0f, 0.0f, 1.0f, 1.0f };

	Quaternion qyaw900 = Quaternion::fromAngleAxis(900.0f, axis_y);
	std::cout << "qyaw900" << qyaw900;
	Quaternion qroll180 = Quaternion::fromAngleAxis(180.0f, axis_x);
	std::cout << "qroll180" << qroll180;
	Quaternion qpitch180 = Quaternion::fromAngleAxis(180.0f, axis_z);
	std::cout << "qpitch180" << qpitch180;
	Quaternion qrp = qpitch180 * qroll180;
	std::cout << "qrp" << qrp;
	Quaternion qpr = qroll180 * qpitch180;
	std::cout << "qpr" << qpr;

	Quaternion qi3 = { 0.0f, 1.0f, 0.0f, 0.0f }; // x-axis
	std::cout << "qi" << qi3;
	Quaternion qe3 = { 0.0f, -1.0f, 0.0f, 0.0f };
	std::cout << "qe" << qe3;

	Quaternion qfy = (qyaw900 * qi3) * (qyaw900.Inverse());
	std::cout << "qy" << qfy;
	assert(qe3 == qfy);

	Quaternion qfrp = (qrp * qi3) * (qrp.Inverse());
	std::cout << "qfrp" << qfrp;
	assert(qe3 == qfrp);

	Quaternion qfpr = (qpr * qi3) * (qpr.Inverse());
	std::cout << "qfpr" << qfpr;
	assert(qe3 == qfpr);


	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "///////////TEST #4////////////////////" << std::endl;

	float thetai = 45.0f;
	Vector4 axis_i = { 0.0f, 1.0f, 0.0f, 1.0f };
	Quaternion q4 = Quaternion::fromAngleAxis(thetai, axis_i);
	std::cout << thetai << " ";
	std::cout << "axis_i" << axis_i << std::endl;

	float thetaf;
	Vector4 axis_f;
	q4.toAngleAxis(thetaf, axis_f);
	std::cout << thetaf << " ";
	std::cout << "axis_f" << axis_f << std::endl;

	assert(fabs(thetai - thetaf) < Threshold && axis_i == axis_f);

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "///////////TEST #5////////////////////" << std::endl;

	Vector4 axis5 = { 0.0f, 1.0f, 0.0f, 1.0f };
	Quaternion q5 = Quaternion::fromAngleAxis(0.0f, axis5);
	std::cout << "q0" << q5;
	Quaternion q52 = Quaternion::fromAngleAxis(90.0f, axis5);
	std::cout << "q1" << q52;
	Quaternion qe5 = Quaternion::fromAngleAxis(30.0f, axis5);
	std::cout << "qe" << qe5;

	Quaternion qLerp0 = q5.Lerp(q52, 0.0f);
	std::cout << "lerp(0)" << qLerp0;
	assert(qLerp0 == q5);

	Quaternion qLerp1 = q5.Lerp(q52, 1.0f);
	std::cout << "lerp(1)" << qLerp1;
	assert(qLerp1 == q52);

	Quaternion qlerp = q5.Lerp(q2, 1 / 3.0f);
	std::cout << "lerp(1/3)" << qlerp;

	assert(!(qlerp == qe));

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "///////////TEST #6////////////////////" << std::endl;

	Vector4 axis6 = { 0.0f, 1.0f, 0.0f, 1.0f };
	Quaternion q6 = Quaternion::fromAngleAxis(0.0f, axis6);
	std::cout << "q0" << q6;
	Quaternion q62 = Quaternion::fromAngleAxis(90.0f, axis6);
	std::cout << "q1" << q62;
	Quaternion qe6 = Quaternion::fromAngleAxis(30.0f, axis6);
	std::cout << "qe" << q6;

	Quaternion qSlerp0 = q6.Slerp(q62, 0.0f);
	std::cout << "slerp(0)" << qSlerp0;
	assert(qSlerp0 == q6);

	Quaternion qSlerp1 = q6.Slerp(q62, 1.0f);
	std::cout << "slerp(1)" << qSlerp1;
	assert(qSlerp1 == q62);

	Quaternion qslerp = q6.Slerp(q62, 1 / 3.0f);
	std::cout << "slerp(1/3)" << qslerp;
	assert(qslerp == qe6);
	std::cout << std::endl;
	std::cout << std::endl;


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

	run(win);
	
	exit(EXIT_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////// END