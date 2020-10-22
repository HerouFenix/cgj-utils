#pragma once
#include "../../../AssignmentOne/headers/Vector3.h"
#include "../../../AssignmentTwo/headers/matrices/Matrix4.h"
#include "../../../CGJ-Engine/dependencies/glew/include/GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
private:
	Matrix4 ViewMatrix;
	Matrix4 OrthProjMatrix;
	Matrix4 PrespProjMatrix;

public:
	Camera();
	~Camera();

	void createViewMatrix(Vector3 eye, Vector3 center, Vector3 up);
	void createOrthoProjectionMatrix(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);
	void createPrespProjectionMatrix(GLfloat fovy, GLfloat aspect, GLfloat nearZ, GLfloat farZ);

	const Matrix4 getVP_orth();
	const Matrix4 getVP_presp();

	const Matrix4 getOrthProj();
	const Matrix4 getView();
	const Matrix4 getPerspProj();
};

