
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../headers/matrices/Matrix4.h"
#include "../headers/camera/Camera.h"
#include "../headers/camera/ArcBallCamera.h"

#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2
bool TexcoordsLoaded, NormalsLoaded;

GLuint VaoId, ProgramId;
GLint ModelMatrix_UId, ViewMatrix_UId, ProjectionMatrix_UId, Color_UId;

int window_width;
int window_height;
float cursorX, cursorY;
float xOffset, yOffset;

Camera camera(Vector3(5, 5, 5), Vector3(0, 0, 0), Vector3(0, 1, 0));
ArcBallCamera arcBall(5);

float view[16];
float proj[16];
bool ortho = false;
bool projChanged;

bool quaternionRotation = false;

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


/////////////////////////////////////////////////////////////////////// SHADERs

const std::string read(const std::string& filename)
{
	std::ifstream ifile(filename);
	std::string shader_string, line;
	while (std::getline(ifile, line))
	{
		shader_string += line + "\n";
	}
	return shader_string;
}

const GLuint checkCompilation(const GLuint shader_id, const std::string& filename)
{
	GLint compiled;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
		GLchar* const log = new char[length];
		glGetShaderInfoLog(shader_id, length, &length, log);
		std::cerr << "[" << filename << "] " << std::endl << log;
		delete[] log;
		exit(EXIT_FAILURE);
	}
	return compiled;
}

void checkLinkage(const GLuint program_id) {
	GLint linked;
	glGetProgramiv(program_id, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE)
	{
		GLint length;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length);
		GLchar* const log = new char[length];
		glGetProgramInfoLog(program_id, length, &length, log);
		std::cerr << "[LINK] " << std::endl << log << std::endl;
		delete[] log;
		exit(EXIT_FAILURE);
	}
}

const GLuint addShader(const GLuint program_id, const GLenum shader_type, const std::string& filename)
{
	const GLuint shader_id = glCreateShader(shader_type);
	const std::string scode = read(filename);
	const GLchar* code = scode.c_str();
	glShaderSource(shader_id, 1, &code, 0);
	glCompileShader(shader_id);
	checkCompilation(shader_id, filename);
	glAttachShader(program_id, shader_id);
	return shader_id;
}

void createShaderProgram(std::string& vs_file, std::string& fs_file)
{
	ProgramId = glCreateProgram();

	GLuint VertexShaderId = addShader(ProgramId, GL_VERTEX_SHADER, vs_file);
	GLuint FragmentShaderId = addShader(ProgramId, GL_FRAGMENT_SHADER, fs_file);

	glBindAttribLocation(ProgramId, VERTICES, "inPosition");
	if (TexcoordsLoaded)
		glBindAttribLocation(ProgramId, TEXCOORDS, "inTexcoord");
	if (NormalsLoaded)
		glBindAttribLocation(ProgramId, NORMALS, "inNormal");

	glLinkProgram(ProgramId);
	checkLinkage(ProgramId);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);
	glDeleteShader(VertexShaderId);
	glDeleteShader(FragmentShaderId);

	ModelMatrix_UId = glGetUniformLocation(ProgramId, "ModelMatrix");
	ViewMatrix_UId = glGetUniformLocation(ProgramId, "ViewMatrix");
	ProjectionMatrix_UId = glGetUniformLocation(ProgramId, "ProjectionMatrix");
	Color_UId = glGetUniformLocation(ProgramId, "ourColor");
}

void destroyShaderProgram()
{
	glUseProgram(0);
	glDeleteProgram(ProgramId);
}

////////////////////////////////////////////////////////////////////////// MESH

typedef struct {
	GLfloat x, y, z;
} Vertex;

typedef struct {
	GLfloat u, v;
} Texcoord;

typedef struct {
	GLfloat nx, ny, nz;
} Normal;

std::vector <Vertex> Vertices, vertexData;
std::vector <Texcoord> Texcoords, texcoordData;
std::vector <Normal> Normals, normalData;

std::vector <unsigned int> vertexIdx, texcoordIdx, normalIdx;

void parseVertex(std::stringstream& sin)
{
	Vertex v;
	sin >> v.x >> v.y >> v.z;
	vertexData.push_back(v);
}

void parseTexcoord(std::stringstream& sin)
{
	Texcoord t;
	sin >> t.u >> t.v;
	texcoordData.push_back(t);
}

void parseNormal(std::stringstream& sin)
{
	Normal n;
	sin >> n.nx >> n.ny >> n.nz;
	normalData.push_back(n);
}

void parseFace(std::stringstream& sin)
{
	std::string token;
	if (normalData.empty() && texcoordData.empty())
	{
		for (int i = 0; i < 3; i++)
		{
			sin >> token;
			vertexIdx.push_back(std::stoi(token));
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			std::getline(sin, token, '/');
			if (token.size() > 0) vertexIdx.push_back(std::stoi(token));
			std::getline(sin, token, '/');
			if (token.size() > 0) texcoordIdx.push_back(std::stoi(token));
			std::getline(sin, token, ' ');
			if (token.size() > 0) normalIdx.push_back(std::stoi(token));
		}
	}
}

void parseLine(std::stringstream& sin)
{
	std::string s;
	sin >> s;
	if (s.compare("v") == 0) parseVertex(sin);
	else if (s.compare("vt") == 0) parseTexcoord(sin);
	else if (s.compare("vn") == 0) parseNormal(sin);
	else if (s.compare("f") == 0) parseFace(sin);
}

void loadMeshData(std::string& filename)
{
	std::ifstream ifile(filename);
	std::string line;
	while (std::getline(ifile, line)) {
		std::stringstream sline(line);
		parseLine(sline);
	}
	TexcoordsLoaded = (texcoordIdx.size() > 0);
	NormalsLoaded = (normalIdx.size() > 0);
}

void processMeshData()
{
	for (unsigned int i = 0; i < vertexIdx.size(); i++) {
		unsigned int vi = vertexIdx[i];
		Vertex v = vertexData[vi - 1];
		Vertices.push_back(v);
		if (TexcoordsLoaded)
		{
			unsigned int ti = texcoordIdx[i];
			Texcoord t = texcoordData[ti - 1];
			Texcoords.push_back(t);
		}
		if (NormalsLoaded)
		{
			unsigned int ni = normalIdx[i];
			Normal n = normalData[ni - 1];
			Normals.push_back(n);
		}
	}
}

void freeMeshData()
{
	vertexData.clear();
	texcoordData.clear();
	normalData.clear();
	vertexIdx.clear();
	texcoordIdx.clear();
	normalIdx.clear();
}

const void createMesh(std::string& filename)
{
	loadMeshData(filename);
	processMeshData();
	freeMeshData();
}

/////////////////////////////////////////////////////////////////////// VAOs & VBOs

void createBufferObjects()
{
	GLuint VboVertices, VboTexcoords, VboNormals;

	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	{
		glGenBuffers(1, &VboVertices);
		glBindBuffer(GL_ARRAY_BUFFER, VboVertices);
		glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(VERTICES);
		glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

		if (TexcoordsLoaded)
		{
			glGenBuffers(1, &VboTexcoords);
			glBindBuffer(GL_ARRAY_BUFFER, VboTexcoords);
			glBufferData(GL_ARRAY_BUFFER, Texcoords.size() * sizeof(Texcoord), &Texcoords[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(TEXCOORDS);
			glVertexAttribPointer(TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Texcoord), 0);
		}
		if (NormalsLoaded)
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

/////////////////////////////////////////////////////////////////////// SCENE

void move_camera() {

	// ARCBALL CAMERA //

	if (forwardKeyPressed) {
		arcBall.incrementRadius(-0.05f);
	}
	if (backwardKeyPressed) {
		arcBall.incrementRadius(0.05f);
	}

	if (!stopRotating) {
		if (!quaternionRotation) {
			//std::cout << "EULER ROTATION \n";
			if (keyRotationX) {
				if (downMoved) {
					arcBall.rotateCameraAroundVertical(-1);
				}
				else if (upMoved) {
					arcBall.rotateCameraAroundVertical(1);
				}
			}
			else if (keyRotationY) {
				if (downMoved) {
					arcBall.rotateCameraAroundHorizontal(-1);
				}
				else if (upMoved) {
					arcBall.rotateCameraAroundHorizontal(1);
				}
			}
			else if (keyRotationZ) {
				if (downMoved) {
					arcBall.rotateCameraAroundZ(-1);
				}
				else if (upMoved) {
					arcBall.rotateCameraAroundZ(1);
				}
			}
			else if (mouseRotating)
				if (mouseMoved) {
					arcBall.rotateCameraAroundHorizontal(xOffset);
					arcBall.rotateCameraAroundVertical(yOffset);
					mouseMoved = false;
				}
		}

		else {
			//std::cout << "QUATERNION ROTATION \n";
			if (keyRotationX) {
				if (downMoved) {
					arcBall.rotateCameraAroundQuaternionVertical(-1);
				}
				else if (upMoved) {
					arcBall.rotateCameraAroundQuaternionVertical(1);
				}
			}
			else if (keyRotationY) {
				if (downMoved) {
					arcBall.rotateCameraAroundQuaternionHorizontal(-1);
				}
				else if (upMoved) {
					arcBall.rotateCameraAroundQuaternionHorizontal(1);
				}
			}
			else if (keyRotationZ) {
				if (downMoved) {
					arcBall.rotateCameraAroundQuaternionZ(-1);
				}
				else if (upMoved) {
					arcBall.rotateCameraAroundQuaternionZ(1);
				}
			}
			else if (mouseRotating)
				if (mouseMoved) {
					arcBall.rotateCameraAroundQuaternionHorizontal(xOffset);
					arcBall.rotateCameraAroundQuaternionVertical(yOffset);
					mouseMoved = false;
				}
		}
	}

	///////////////////////////////////////////////////////////////////////
	// Get the updated view matrix
	Matrix4 viewM = arcBall.getViewMatrix();
	viewM.getRowMajor(view);
	cameraReset = false;
}

void set_view_proj() {
	Matrix4 viewM = arcBall.getViewMatrix();
	viewM.getRowMajor(view);

	Matrix4 projM;
	if (ortho) {
		projM = arcBall.getOrthProj();
	}
	else {
		projM = arcBall.getPerspProj();
	}
	projM.getRowMajor(proj);
}

void setupCamera() {
	// CAMERA SETUP //
	arcBall.setOrthoProjectionMatrix(-2.0f, 2.0f, -2.0f, 2.0f, 1.0f, 10.0f);
	arcBall.setPrespProjectionMatrix(30, ((GLfloat)window_width / (GLfloat)window_height), 1.0f, 10.0f);

	//Set initial cursor position to be the middle of the screen
	cursorX = (float)window_width / 2;
	cursorY = (float)window_height / 2;
}

void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
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
			break;
		case GLFW_KEY_W:
			forwardKeyPressed = true;
			break;
		case GLFW_KEY_S:
			backwardKeyPressed = true;
			break;
		case GLFW_KEY_R:
			//camera.resetCamera();
			arcBall.resetCamera();
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
	/*
		1. Calculate the mouse's offset since the last frame.
		2. Add the offset values to the camera's yaw and pitch values.
		3. Add some constraints to the minimum/maximum pitch values.
		4. Calculate the direction vector.
	*/

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
}

void drawScene()
{
	glBindVertexArray(VaoId);
	glUseProgram(ProgramId);

	Matrix4 view_M = arcBall.getViewMatrix();
	view_M.getColMajor(view);
	Matrix4 proj_M = arcBall.getPerspProj();
	proj_M.getColMajor(proj);

	Vector4 color (1.0f, 0.0f, 0.0f, 0.0f);

	GLfloat model[16];
	Matrix4::identity().getColMajor(model);
	glUniformMatrix4fv(ModelMatrix_UId, 1, GL_FALSE, model);
	glUniformMatrix4fv(ViewMatrix_UId, 1, GL_FALSE, view);
	glUniformMatrix4fv(ProjectionMatrix_UId, 1, GL_FALSE, proj);

	glUniform4f(Color_UId, color.getX(), color.getY(), color.getZ(), color.getW());
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)Vertices.size());

	glUseProgram(0);
	glBindVertexArray(0);
}

///////////////////////////////////////////////////////////////////// CALLBACKS

void window_close_callback(GLFWwindow* win)
{
	destroyShaderProgram();
	destroyBufferObjects();
}

void window_size_callback(GLFWwindow* win, int winx, int winy)
{
	window_width = winx;
	window_height = winy;
	glViewport(0, 0, winx, winy);
	// Change projection matrices to maintain aspect ratio
}

///////////////////////////////////////////////////////////////////////// SETUP

void glfw_error_callback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

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

	setupCallbacks(win);
	setupCamera();

	std::string mesh_dir = "resources/models/";
	std::string mesh_file = "cube.obj";
	std::string mesh_fullname = mesh_dir + mesh_file;
	createMesh(mesh_fullname);
	createBufferObjects();

	std::string vs = "resources/shaders/cube_vs.glsl";
	std::string fs = "resources/shaders/cube_fs.glsl";
	createShaderProgram(vs, fs);
	return win;
}

////////////////////////////////////////////////////////////////////////// RUN

void display(GLFWwindow* win, double elapsed_sec)
{
	drawScene();
}

void run(GLFWwindow* win)
{
	double last_time = glfwGetTime();
	while (!glfwWindowShouldClose(win))
	{
		double time = glfwGetTime();
		double elapsed_time = time - last_time;
		last_time = time;

		move_camera();

		set_view_proj();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		display(win, elapsed_time);
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
		640, 480, "Loading World", is_fullscreen, is_vsync);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	if (lockMouse) {
		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //Tell GLFW that it should hide the cursorand capture it.Capturing a cursor means that, once the application has focus, the mouse cursor stays within the center of the window(unless the application loses focus or quits)
	}
	else {
		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	run(win);
	exit(EXIT_SUCCESS);

}

///////////////////////////////////////////////////////////////////////////////
