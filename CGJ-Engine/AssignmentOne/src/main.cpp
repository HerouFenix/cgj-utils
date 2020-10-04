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
	std::cout << "Vector1  = " << vec1 << " ; Vector2 = " << vec2 << "\n";
	std::cout << "Vector1 * 2.0f = " << vec1 * 2.0f << "\n";

	std::cout << "Vector1 / 2.0f = " << vec1 / 2.0f << "\n";

	std::cout << "-1.0f * Vector2 = " << -1.0f * vec2 << "\n";

	std::cout << "Vector2 / -2 = " << vec2 / -2 << "\n";

	std::cout << "-Vector2 = " << -vec2 << "\n";


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


	std::cout << "\n=======COMPARISSONS=======\n";
	std::cout << "Vector1 == Vector2: " << (vec1 == vec2) << "\n";
	std::cout << "Vector1 != Vector2: " << (vec1 != vec2) << "\n";

	vec3 = vec1.clone();
	std::cout << "Vector1 == Vector3: " << (vec1 == vec3) << "\n";
	std::cout << "Vector1 != Vector3: " << (vec1 != vec3) << "\n";

	std::cout << "Vector1 magnitude compared to Vector2: " << vec1.compareMag(vec2) << "\n";
	std::cout << "Vector2 magnitude compared to Vector1: " << vec2.compareMag(vec1) << "\n";
	std::cout << "Vector1 magnitude compared to Vector3: " << vec1.compareMag(vec3) << "\n";

	std::cout << "Vector1 magnitude compared to 0: " << vec1.compareMag(0.0f) << "\n";
	std::cout << "Vector1 magnitude compared to 100: " << vec1.compareMag(100) << "\n";
	std::cout << "Vector1 magnitude compared to Vector1's magnitude: " << vec1.compareMag(vec1.magnitude()) << "\n";

	std::cout << "\n=======VECTOR METHODS=======\n";
	std::cout << "Vector1 Dot product with Vector2 = " << vec1.dotProd(vec2) << "\n";

	std::cout << "Vector1 Cross product with Vector2 = " << vec1.crossProd(vec2) << "\n";

	std::cout << "Vector1 Normalized: " << vec1.normalized() << "\n";

	std::cout << "Vector1 Inverted: " << vec1.invert() << "\n";

	std::cout << "Vector2 Quadrance: " << vec2.quadrance() << "\n";

	std::cout << "Vector2 Magnitude: " << vec2.magnitude() << "\n";

	std::cout << "Vector2 Normalize: " << vec2.normalize() << "\n";

	std::cout << "Vector2 Magnitude after Normalized: " << vec2.magnitude() << "\n";

	return 0;
}