#include "../../headers/camera/Quaternion.h"
#include "../../headers/vectors/Vector3.h"
#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913
const float qThreshold = (float)1.0e-5;

Quaternion::Quaternion()
{
}

Quaternion::Quaternion(float angle, float xx, float yy, float zz)
{
	a = angle;
	x = xx;
	y = yy;
	z = zz;
}

Quaternion::Quaternion(float theta, Vector4 axis)
{
}

float Quaternion::getA()
{
	return a;
}

float Quaternion::getX()
{
	return x;
}

float Quaternion::getY()
{
	return y;
}

float Quaternion::getZ()
{
	return z;
}

void Quaternion::setA(const float aa)
{
	a = aa;
}

void Quaternion::setX(const float xx)
{
	x = xx;
}

void Quaternion::setY(const float yy)
{
	y = yy;
}

void Quaternion::setZ(const float zz)
{
	z = zz;
}

Vector4 Quaternion::normalizeVec4(Vector4& v)
{
	Vector4 vn;
	float s = 1 / (v.getW() * sqrt(v.getX() * v.getX() + v.getY() * v.getY() + v.getZ() * v.getZ()));
	vn.setX(v.getX() * s);
	vn.setY(v.getY() * s);
	vn.setZ(v.getZ() * s);
	vn.setW(1.0f);
	return vn;
}

Quaternion Quaternion::fromAngleAxis(float theta, Vector4& axis)
{
	Vector4 axisn = axis.Normalize_Quaternions();
	Quaternion q;
	float a = theta * (float)DEGREES_TO_RADIANS;
	q.setA(cos(a / 2.0f));
	float s = sin(a / 2.0f);
	q.setX(axisn.getX() * s);
	q.setY(axisn.getY() * s);
	q.setZ(axisn.getZ() * s);
	q.clean();
	return q.Normalize();
}

void Quaternion::toAngleAxis(float& angle, Vector4& axis)
{
	Quaternion q = this->Normalize();
	angle = 2.0f * acos(q.a) * (float)RADIANS_TO_DEGREES;
	float s = sqrt(1.0f - q.a * q.a);
	if (s < qThreshold) {
		axis.setX(1.0f);
		axis.setY(0.0f);
		axis.setZ(0.0f);
		axis.setW(1.0f);
	}
	else {
		float sinv = 1 / s;
		axis.setX(q.x * sinv);
		axis.setY(q.y * sinv);
		axis.setZ(q.z * sinv);
		axis.setW(1.0f);
	}
}

void Quaternion::clean()
{
	if (fabs(a) < qThreshold) a = 0.0f;
	if (fabs(x) < qThreshold) x = 0.0f;
	if (fabs(y) < qThreshold) y = 0.0f;
	if (fabs(z) < qThreshold) z = 0.0f;
}

float Quaternion::Quadrance()
{
	return a * a + x * x + y * y + z * z;
}

float Quaternion::Norm()
{
	return sqrt(this->Quadrance());
}

Quaternion Quaternion::Normalize()
{
	float s = 1 / this->Norm();
	return *this * s;
}

Quaternion Quaternion::Conjugate()
{
	return Quaternion(a, -x, -y, -z);
}

Quaternion Quaternion::Inverse()
{
	return this->Conjugate() * (1.0f / this->Quadrance());
}

Quaternion& Quaternion::operator=(const Quaternion& quat)
{
	a = quat.a;
	x = quat.x;
	y = quat.y;
	z = quat.z;
	return *this;
}

bool Quaternion::operator==(const Quaternion& quat)
{
	return (fabs(a - quat.a) < qThreshold && fabs(x - quat.x) < qThreshold &&
		fabs(y - quat.y) < qThreshold && fabs(z - quat.z) < qThreshold);
}

Quaternion Quaternion::operator+(const Quaternion& q1)
{
	return Quaternion(a + q1.a, q1.x, y + q1.y, z + q1.z);
}

Quaternion Quaternion::operator*(float s)
{
	return Quaternion(a * s, s * x, s * y, s * z);
}

Quaternion Quaternion::operator*(const Quaternion& q1)
{
	return Quaternion(a * q1.a - x * q1.x - y * q1.y - z * q1.z, 
		a * q1.x + x * q1.a + y * q1.z - z * q1.y,
		a * q1.y + y * q1.a + z * q1.x - x * q1.z,
		a * q1.z + z * q1.a + x * q1.y - y * q1.x);
}


Matrix4 Quaternion::GLRotationMatrix()
{
	Quaternion qn = this->Normalize();
	float xx = qn.x * qn.x;
	float xy = qn.x * qn.y;
	float xz = qn.x * qn.z;
	float xt = qn.x * qn.a;
	float yy = qn.y * qn.y;
	float yz = qn.y * qn.z;
	float yt = qn.y * qn.a;
	float zz = qn.z * qn.z;
	float zt = qn.z * qn.a;

	return Matrix4(new float[4][4]{
		{1.0f - 2.0f * (yy + zz),2.0f * (xy - zt), 2.0f * (xz + yt), 0.0f},
		{2.0f * (xy + zt), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - xt), 0.0f},
		{2.0f * (xz - yt), 2.0f * (yz + xt), 1.0f - 2.0f * (xx + yy), 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}
		});

}

Quaternion Quaternion::Lerp(Quaternion& q1, float k)
{
	float cos_angle = x * q1.x + y * q1.y + z * q1.z + a * q1.a;
	float k0 = 1.0f - k;
	float k1 = (cos_angle > 0) ? k : -k;
	return ((*this * k0) + (q1 * k1));
}

Quaternion Quaternion::Slerp(Quaternion& q1, float k)
{
	float angle = acos(x * q1.x + y * q1.y + z * q1.z + a * q1.a);
	float k0 = sin((1 - k) * angle) / sin(angle);
	float k1 = sin(k * angle) / sin(angle);
	return Quaternion((*this * k0) + (q1 * k1)).Normalize();
}

std::ostream& operator<<(std::ostream& output, Quaternion& q)
{
	output << "(" << q.getA() << ", " << q.getX() << ", " << q.getY() << ", " << q.getZ() << ")" << std::endl;
	return output;
}
