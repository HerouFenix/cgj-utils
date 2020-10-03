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

    std::cout << "Vector1 + Vector2 = " << vec1+vec2 << "\n";

    Vector3 test = vec1 += vec2;
    std::cout << "Vector1 += Vector2 = " << test << "\n";

    std::cout << "Vector1 - Vector2 = " << vec1 - vec2 << "\n";

    test = vec1 -= vec2;
    std::cout << "Vector1 -= Vector2 = " << test << "\n";

    std::cout << "Vector1 * 2.0f = " << vec1 * 2.0f << "\n";

    test = vec1 *= 2.0f;
    std::cout << "Vector1 *= 2.0f = " << test << "\n";

    std::cout << "Vector1 / 2.0f = " << vec1 / 2.0f << "\n";

    test = vec1 /= 2.0f;
    std::cout << "Vector1 /= 2.0f = " << test << "\n";

    test = vec1 = vec2;
    std::cout << "Vector1 = Vector2 = " << test << "\n";

    std::cout << "Vector1 dot product with Vector2 = " << vec1.dotProd(vec2) << "\n";

    std::cout << "Vector1 cross product with Vector2 = " << vec1.crossProd(vec2) << "\n";

    std::cout << "Vector1  Normalized" << vec1.normalized() << "\n";

    return 0;
}