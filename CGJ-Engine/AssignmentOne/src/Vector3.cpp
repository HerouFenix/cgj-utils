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

std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
    os << '(' << vec.x << ',' << vec.y << ',' << vec.z << ')';
    return os;
}
