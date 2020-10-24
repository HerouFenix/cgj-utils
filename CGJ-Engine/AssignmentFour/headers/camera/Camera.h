#pragma once
#include "../../../AssignmentOne/headers/Vector3.h"
#include "../../../AssignmentTwo/headers/matrices/Matrix4.h"
#include "../../../CGJ-Engine/dependencies/glew/include/GL/glew.h"

class Camera
{
private:
	Vector3 cameraEye; // The camera position is a vector in world space that points to the camera's position.
	Vector3 cameraCenter; // The camera's target (i.e what it is looking at)
	Vector3 cameraUp; // The up vector that points upwards (in world space)

	Vector3 cameraDirection; // What constitutes as "moving forward"
	float pitch = 0;
	float yaw = 0;

	Matrix4 view;
	Matrix4 orthoProj;
	Matrix4 perspProj;

public:
	Camera(Vector3 eye, Vector3 center, Vector3 up);
	~Camera();

	void setViewMatrix(Vector3 eye, Vector3 center, Vector3 up);
	void setOrthoProjectionMatrix(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);
	void setPrespProjectionMatrix(GLfloat fovy, GLfloat aspect, GLfloat nearZ, GLfloat farZ);

	void setDirection(float xOffset, float yOffset);

	const Matrix4 getOrthVP();
	const Matrix4 getPerspVP();

	const Matrix4 getOrthProj();
	const Matrix4 getPerspProj();
	const Matrix4 getViewMatrix();

	void moveCamera(int move, float speed = 0.1f);
	void rotateCamera(float xOffset, float yOffset, float sensitivity = 0.1f);

};