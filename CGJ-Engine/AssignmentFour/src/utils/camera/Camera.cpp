#include "../../../headers/camera/Camera.h"
# define PI atan(1)*4

Camera::Camera(Vector3 eye, Vector3 center, Vector3 up)
{
	cameraDirection = (center - eye);

	// Set initial pitch and yaw
	pitch = asin(center.getY() - eye.getY());
	yaw = (center.getX() - eye.getX()) / cos(pitch);

	yaw = yaw / (PI / 180.0);
	pitch = pitch / (PI / 180.0);

	setDirectionVector(0, 0);
	std::cout << cameraDirection << "\n";
	std::cout << (center - eye).normalize() << "\n";

	setViewMatrix(eye, eye + cameraDirection, up);
}

Camera::~Camera()
{
}

void Camera::setViewMatrix(Vector3 eye, Vector3 center, Vector3 up)
{
	cameraEye = eye;
	cameraCenter = center;
	cameraUp = up;

	Vector3 v = (center-eye).normalize(); // CameraDirection

	Vector3 s = v.crossProd(up).normalize(); // CameraRight

	Vector3 u = s.crossProd(v); // CameraUp

	Matrix4 axis(new float[4][4]{
			{  s.getX(),  s.getY(),	 s.getZ(), 0},
			{  u.getX(),  u.getY(),	 u.getZ(), 0},
			{ -v.getX(), -v.getY(), -v.getZ(), 0},
			{ 0,         0,		    0,        1}
		});

	Matrix4 trans(new float[4][4]{
			{ 1, 0, 0, -eye.getX()},
			{ 0, 1, 0, -eye.getY()},
			{ 0, 0, 1, -eye.getZ()},
			{ 0, 0, 0,	1		  }
		});

	view = axis * trans;
}

void Camera::setOrthoProjectionMatrix(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far)
{
	orthoProj = Matrix4(new float[4][4]{
		{2 / (right - left), 0                 , 0               , (left + right) / (left - right)},
		{0                 , 2 / (top - bottom), 0               , (bottom + top) / (bottom - top)},
		{0                 , 0                 , 2 / (near - far), (near + far) / (near - far)},
		{0                 , 0                 , 0               , 1},
		}
	);
}

void Camera::setPrespProjectionMatrix(GLfloat fovy, GLfloat aspect, GLfloat nearZ, GLfloat farZ)
{
	GLfloat ang_rad = (fovy / 2) * PI / 180.0f;
	GLfloat d = 1 / tan(ang_rad);

	perspProj = Matrix4(new float[4][4]{
			{(d / aspect), 0,  0                                , 0                                  },
			{0           , d,  0                                , 0                                  },
			{0           , 0,  ((nearZ + farZ) / (nearZ - farZ)), 2 * (nearZ * farZ) / (nearZ - farZ)},
			{0           , 0, -1                                , 0                                  }
		}
	);
}

void Camera::setDirectionVector(float xoffset, float yoffset)
{
	yaw += xoffset;
	pitch += yoffset;
	std::cout << "yaw: " << yaw << "\n";
	std::cout << "pitch: " << pitch << "\n";

	// Convert degrees to radians
	float yawR = yaw; float pitchR = pitch;
	yawR = yaw * PI / 180.0;
	pitchR = pitch * PI / 180.0;
	
	// Round - Useful for angles like PI/2 
	float cosYaw = cos(yawR);
	float cosPitch = cos(pitchR);
	float sinPitch = sin(pitchR);
	float sinYaw = sin(yawR);

	cosYaw = roundf(cosYaw * 10000000) / 10000000;
	cosPitch = roundf(cosPitch * 10000000) / 10000000;
	sinPitch = roundf(sinPitch * 10000000) / 10000000;
	sinYaw = roundf(sinYaw * 10000000) / 10000000;


	cameraDirection.setX(cosYaw * cosPitch);
	cameraDirection.setY(sinPitch);
	cameraDirection.setZ(sinYaw * cosPitch);

	cameraDirection.normalize();
}

const Matrix4 Camera::getViewMatrix() {
	return view;
}

const Matrix4 Camera::getOrthProj() {
	return orthoProj;
}

const Matrix4 Camera::getPerspProj() {
	return perspProj;
}

const Matrix4 Camera::getOrthVP()
{
	return orthoProj * view;
}

const Matrix4 Camera::getPerspVP()
{
	return perspProj * view;
}


void Camera::moveCamera(int move, float speed)
{
	
	switch (move) {
		case 0:
			cameraEye += speed * cameraDirection;
			break;
		case 1:
			cameraEye -= speed * cameraDirection;
			break;
		case 2:
			cameraEye -= cameraUp.crossProd(cameraDirection).normalize() * speed;
			break;
		case 3:
			cameraEye += cameraUp.crossProd(cameraDirection).normalize() * speed;
			break;
	}

	setViewMatrix(cameraEye, cameraEye + cameraDirection, cameraUp);

	
}