#include "../headers/Vector3.h"
#include <cassert>

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
float Vector3::magnitude() {
    return sqrt((x * x) + (y * y) + (z * z));
}

//Vector3 Assignments

//Vector3 Methods

    //addition
    Vector3 Vector3::operator+(const Vector3& operand)
    {
        return Vector3(x + operand.x, y + operand.y, z + operand.z);
    }
    Vector3& Vector3::operator+=(const Vector3& operand)
    {
        x += operand.x;
        y += operand.y;
        z += operand.z;
        return *this;
    }

    //subtraction
    Vector3 Vector3::operator-(const Vector3& operand)
    {
        return Vector3(x - operand.x, y - operand.y, z - operand.z);
    }

    Vector3& Vector3::operator-=(const Vector3& operand)
    {
        x -= operand.x;
        y -= operand.y;
        z -= operand.z;
        return *this;
    }

    //multiplication by scalar
    Vector3 Vector3::operator*(float operand)
    {
        return Vector3(x * operand, y * operand, z * operand);
    }
    Vector3& Vector3::operator*=(float operand)
    {
        x *= operand;
        y *= operand;
        z *= operand;
        return *this;
    }

    //Division by scalar
    Vector3 Vector3::operator/(float operand)
    {
        assert(operand != 0);
        return Vector3(x / operand, y / operand, z / operand);
    }

    Vector3& Vector3::operator/=(float operand)
    {
        x /= operand;
        y /= operand;
        z /= operand;
        return *this;
    }

    //Vector comparison
    Vector3& Vector3::operator=(const Vector3& operand)
    {
        x = operand.x;
        y = operand.y;
        z = operand.z;
        return *this;
    }

    //Dot product
    float Vector3::dotProd(const Vector3& operand)
    {
        return x * operand.x + operand.y * y + operand.z * z;
    }

    //Cross product
    Vector3 Vector3::crossProd(const Vector3& operand)
    {
        return Vector3(y * operand.z - z * operand.y, 
            z * operand.x - x * operand.z, x * operand.y - y * operand.x);
    }

    //Normalize
    Vector3 Vector3::normalized()
    {
        assert(magnitude() != 0);
        *this /= magnitude();
        return *this;
    }

    
