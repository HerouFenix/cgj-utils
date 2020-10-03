#include <iostream>
#include "../headers/Vector3.h"

int main() {
    Vector3 vec1(1,2,3);
    std::cout << "Vector 1: " << vec1 << "\n";
    std::cout << "  x: " << vec1.getX() << "\n";
    std::cout << "  y: " << vec1.getY() << "\n";
    std::cout << "  z: " << vec1.getZ() << "\n";

    Vector3 vec2;
    std::cout << "Vector 2: " << vec2 << "\n";
    vec2.setX(-3);
    vec2.setY(2);
    vec2.setZ(5);

    std::cout << "Vector 2 after set:\n";
    std::cout << "  x: " << vec2.getX() << "\n";
    std::cout << "  y: " << vec2.getY() << "\n";
    std::cout << "  z: " << vec2.getZ() << "\n";


    std::cout << "Vector1's Magnitude: " << vec1.magnitude() << "\n";
    std::cout << "Vector2's Magnitude: " << vec2.magnitude() << "\n";

    Vector3 vec1Norm = vec1.normalized();
    Vector3 vec2Norm = vec2.normalized();

    std::cout << "Vector1  Normalized" << vec1Norm << "\n";
    std::cout << "Vector2 Normalized: " << vec2Norm << "\n";

    return 0;
}