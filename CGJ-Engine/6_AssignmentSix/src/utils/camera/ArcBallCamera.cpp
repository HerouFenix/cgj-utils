#include "../../../headers/camera/ArcBallCamera.h"
# define PI (float)atan(1)*4
#include <GLFW/glfw3.h>

ArcBallCamera::ArcBallCamera(float sRadius)
{
	Vector3 vec(0, 0, -sRadius);
	translation = Matrix4::translation(vec);

	rotation = Matrix4::identity();

	radius = sRadius;
	initialRadius = sRadius;
}

ArcBallCamera::~ArcBallCamera()
{
}

void ArcBallCamera::setOrthoProjectionMatrix(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far)
{
	orthoProj = Matrix4(new float[4][4]{
		{2 / (right - left), 0                 , 0               , (left + right) / (left - right)},
		{0                 , 2 / (top - bottom), 0               , (bottom + top) / (bottom - top)},
		{0                 , 0                 , 2 / (near - far), (near + far) / (near - far)},
		{0                 , 0                 , 0               , 1},
		}
	);
}

void ArcBallCamera::setPrespProjectionMatrix(GLfloat fovy, GLfloat aspect, GLfloat nearZ, GLfloat farZ)
{
	GLfloat ang_rad = (fovy / 2.0f) * PI / 180.0f;
	GLfloat d = 1 / tan(ang_rad);

	perspProj = Matrix4(new float[4][4]{
			{(d / aspect), 0,  0                                , 0                                  },
			{0           , d,  0                                , 0                                  },
			{0           , 0,  ((nearZ + farZ) / (nearZ - farZ)), 2 * (nearZ * farZ) / (nearZ - farZ)},
			{0           , 0, -1                                , 0                                  }
		}
	);
}

const Matrix4 ArcBallCamera::getViewMatrix() {
	return translation * rotation;
}

void ArcBallCamera::incrementRadius(float inc)
{
	radius += inc;

	Vector3 vec(0, 0, -inc);
	translation = Matrix4::translation(vec) * translation;
}

const Matrix4 ArcBallCamera::getOrthProj() {
	return orthoProj;
}

const Matrix4 ArcBallCamera::getPerspProj() {
	return perspProj;
}

void ArcBallCamera::rotateCameraAroundHorizontal(float rotationDegree)
{
	float rotationRads = rotationDegree * PI / 180.0f;

	rotation = Matrix4::rotationY(rotationRads) * rotation;
}

void ArcBallCamera::rotateCameraAroundQuaternionHorizontal(float rotationDegree)
{
	Vector4 axis_i = { 0.0f, 1.0f, 0.0f, 1.0f };
	Quaternion qtr(rotationDegree, axis_i);

	rotation = qtr.GLRotationMatrix() * rotation;

}

void ArcBallCamera::rotateCameraAroundVertical(float rotationDegree)
{
	float rotationRads = rotationDegree * PI / 180.0f;

	rotation = Matrix4::rotationX(rotationRads) * rotation;
}

void ArcBallCamera::rotateCameraAroundQuaternionVertical(float rotationDegree)
{
	Vector4 axis_i = { 1.0f, 0.0f, 0.0f, 1.0f };
	Quaternion qtr(rotationDegree, axis_i);

	rotation = qtr.GLRotationMatrix() * rotation;

}

void ArcBallCamera::rotateCameraAroundZ(float rotationDegree)
{
	float rotationRads = rotationDegree * PI / 180.0f;

	rotation = Matrix4::rotationZ(rotationRads) * rotation;
}

void ArcBallCamera::rotateCameraAroundQuaternionZ(float rotationDegree)
{
	Vector4 axis_i = { 0.0f, 0.0f, 1.0f, 1.0f };
	Quaternion qtr(rotationDegree, axis_i);

	rotation = qtr.GLRotationMatrix() * rotation;

}

void ArcBallCamera::resetCamera()
{
	Vector3 vec(0, 0, -initialRadius);
	translation = Matrix4::translation(vec);

	rotation = Matrix4::identity();

	radius = initialRadius;
}
