#include "../../../headers/camera/Camera.h"

Camera::Camera()
{
	
}

Camera::~Camera()
{
}

void Camera::createViewMatrix(Vector3 eye, Vector3 center, Vector3 up)
{
	Vector3 v = ((center - eye) / (center-eye).magnitude());
	Vector3 s = ((v.crossProd(up)) / v.crossProd(up).magnitude());
	Vector3 u = s.crossProd(v);
	Matrix4 rot(new float[4][4]{
			{s.getX(), s.getY(), s.getZ(), 0},
			{u.getX(), u.getY(), u.getZ(), 0},
			{-v.getX(), -v.getY(), -v.getZ(), 0},
			{0,0,0,1} }
	);
	Matrix4 trans(new float[4][4]{
			{1, 0, 0, -eye.getX()},
			{0, 1, 0, -eye.getY() },
			{0, 0, 1, -eye.getZ() },
			{0,0,0,1} }
	);
	ViewMatrix = rot * trans;
}

void Camera::createOrthoProjectionMatrix(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far)
{
	Matrix4 proj_orth(new float[4][4]{
			{2 / (top - left), 0, 0, -((top + left) / (top - left))},
			{0, 2 / (right - bottom), 0, -((right + bottom) / (right - bottom))},
			{0, 0, (-2) / (far - near), -((far + near) / (far - near))},
			{0,0,0,1} }
	);
	OrthProjMatrix = proj_orth;
}

void Camera::createPrespProjectionMatrix(GLfloat fovy, GLfloat aspect, GLfloat nearZ, GLfloat farZ)
{
	GLfloat ang_rad = (fovy/2) * glm::pi<float>() / 180.0f;
	GLfloat d = 1 / tan(ang_rad);
	std::cout << aspect;

	Matrix4 proj_presp(new float[4][4]{

			{(d/aspect), 0, 0, 0},
			{0, d, 0, 0},
			{0, 0, ((nearZ+farZ)/(nearZ - farZ)), 2*(nearZ * farZ) / (nearZ - farZ)},
			{0,0,-1, 0} }
	);
	PrespProjMatrix = proj_presp;
}

const Matrix4 Camera::getMVP_orth()
{
	return OrthProjMatrix * ViewMatrix;
}

const Matrix4 Camera::getMVP_presp()
{
	return PrespProjMatrix * ViewMatrix;
}
