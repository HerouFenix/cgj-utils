#include <iostream>
#include "../headers/Vector3.h"

int main() {
	std::cout << "=======CONSTRUCTORS, SETTERS & GETTERS=======\n";

	Vector3 vec1(1, 2, 3);
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

	std::cout << "\n=======MAGNITUDE=======\n";


	std::cout << "Vector1's Magnitude: " << vec1.magnitude() << "\n";
	std::cout << "Vector2's Magnitude: " << vec2.magnitude() << "\n";

	std::cout << "\n=======VECTOR-VECTOR OPERATORS=======\n";
	std::cout << "Vector1 + Vector2 = " << vec1 + vec2 << "\n";

	std::cout << "Vector1 - Vector2 = " << vec1 - vec2 << "\n";

	std::cout << "\n=======VECTOR-SCALAR OPERATORS=======\n";
	std::cout << "Vector1 * 2.0f = " << vec1 * 2.0f << "\n";

	std::cout << "Vector1 / 2.0f = " << vec1 / 2.0f << "\n";

	std::cout << "\n=======ASSIGNMENTS=======\n";
	Vector3 vec3(1, 1, 1);
	std::cout << "Vector 3: " << vec3 << "\n";
	vec3 += vec1;
	std::cout << "Vector3 += Vector1 = " << vec3 << "\n";

	std::cout << "Vector 3: " << vec3 << "\n";

	vec3 -= vec1;
	std::cout << "Vector3 -= Vector1 = " << vec3 << "\n";

	std::cout << "Vector 3: " << vec3 << "\n";

	vec3 *= 2.0f;
	std::cout << "Vector3 *= 2.0f = " << vec3 << "\n";

	std::cout << "Vector 3: " << vec3 << "\n";

	vec3 /= 2.0f;
	std::cout << "Vector3 /= 2.0f = " << vec3 << "\n";

	vec3 = vec1;
	std::cout << "Vector3 = Vector1 = " << vec3 << "\n";

	std::cout << "\n=======VECTOR METHODS=======\n";

	std::cout << "Vector1 dot product with Vector2 = " << vec1.dotProd(vec2) << "\n";

	std::cout << "Vector1 cross product with Vector2 = " << vec1.crossProd(vec2) << "\n";

	std::cout << "Vector1  Normalized" << vec1.normalized() << "\n";

	return 0;
}