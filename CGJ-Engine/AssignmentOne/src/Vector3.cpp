#include "../headers/Vector3.h"

// Vector 3 Constructors
Vector3::Vector3() {
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
}

//Vector3 Print

std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
    os << '(' << vec.x << ',' << vec.y << ',' << vec.z << ')';
    return os;
}

//Vector3 Getters

float Vector3::getX() {
    return x;
}

float Vector3::getY() {
    return y;
}

float Vector3::getZ() {
    return z;
}

//Vector3 Setters

void Vector3::setX(float _x) {
    x = _x;
}

void Vector3::setY(float _y) {
    y = _y;  
}

void Vector3::setZ(float _z) {
    z = _z;
}


//Vector3 Operations

//Vector3 Assignments

//Vector3 Methods