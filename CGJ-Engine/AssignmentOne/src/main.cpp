#include <iostream>
#include "../headers/Vector3.h"
#include "../headers/Vector2.h"
#include "../headers/Vector4.h"

int main() {
	std::cout << "=====================VECTOR 3=====================\n";

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

	std::cout << "Vector1 + 2.0f = " << vec1 + 2.0f << "\n";

	std::cout << "2 + Vector1 = " << 2 + vec1 << "\n";

	std::cout << "Vector1 - 2.0f = " << vec1 - 2.0f << "\n";

	std::cout << "2 - Vector1 = " << 2 - vec1 << "\n";

	std::cout << "Vector1 / 2.0f = " << vec1 / 2.0f << "\n";

	std::cout << "-2.0f * Vector2 = " << -2.0f * vec2 << "\n";

	std::cout << "Vector2 / -2 = " << vec2 / -2 << "\n";

	std::cout << "-Vector2 = " << -vec2 << "\n";


	std::cout << "\n=======ASSIGNMENTS=======\n";
	Vector3 vec3(1, 1, 1);
	std::cout << "Vector 3: " << vec3 << "\n";
	vec3 += vec1;
	std::cout << "Vector3 += Vector1 = " << vec3 << "\n";

	std::cout << "Vector 3: " << vec3 << "\n";

	vec3 += 1;
	std::cout << "Vector3 += 1 = " << vec3 << "\n";

	std::cout << "Vector 3: " << vec3 << "\n";

	vec3 -= vec1;
	std::cout << "Vector3 -= Vector1 = " << vec3 << "\n";

	std::cout << "Vector 3: " << vec3 << "\n";

	vec3 -= 1;
	std::cout << "Vector3 -= 1 = " << vec3 << "\n";

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

	std::cout << "Vector1 angle with Vector2: " << vec1.angle(vec2) << "\n";

	std::cout << "Vector1 distance to Vector2: " << vec1.dist(vec2) << "\n";

	std::cout << "Vector1 Inverted: " << vec1.invert() << "\n";

	std::cout << "Vector2 Quadrance: " << vec2.quadrance() << "\n";

	std::cout << "Vector2 Magnitude: " << vec2.magnitude() << "\n";

	std::cout << "Vector2 Normalize: " << vec2.normalize() << "\n";

	std::cout << "Vector2 Magnitude after Normalized: " << vec2.magnitude() << "\n";

	std::cout << "\n=======CONVERSIONS=======\n";
	//3D to 2D
	Vector2 vec2D_A(5, 6);
	Vector3 vec3D_A = vec2D_A;

	std::cout << "Vector2D_A  = " << vec2D_A << " ; Vector3D_A = " << vec3D_A << "\n";

	vec2D_A.setX(10);
	vec2D_A.setY(10);

	vec3D_A = vec2D_A;
	std::cout << "Vector2D_A  = " << vec2D_A << " ; Vector3D_A = " << vec3D_A << "\n";

	std::cout << "Vector3D_A  + Vector2D_A = " << vec3D_A + vec2D_A << "\n";

	//3D to 4D
	Vector4 vec4D_A(5, 6,7,8);
	Vector3 vec3D_A2 = vec4D_A;

	std::cout << "Vector4D_A  = " << vec4D_A << " ; Vector3D_A2 = " << vec3D_A2 << "\n";

	vec4D_A.setX(10);
	vec4D_A.setY(10);
	vec4D_A.setZ(11);
	vec4D_A.setW(12);

	vec3D_A2 = vec4D_A;
	std::cout << "Vector4D_A  = " << vec4D_A << " ; Vector3D_A2 = " << vec3D_A2 << "\n";

	std::cout << "Vector3D_A2  + Vector4D_A = " << vec3D_A2 + vec4D_A << "\n";

	std::cout << "=====================VECTOR 3=====================\n\n\n";



	std::cout << "=====================VECTOR 4=====================\n";

	std::cout << "=======CONSTRUCTORS, SETTERS & GETTERS=======\n";

	Vector4 vec7(1, 2, 3, 4);
	std::cout << "Vector 7: " << vec7 << "\n";
	std::cout << "  x: " << vec7.getX() << "\n";
	std::cout << "  y: " << vec7.getY() << "\n";
	std::cout << "  z: " << vec7.getZ() << "\n";
	std::cout << "  w: " << vec7.getW() << "\n";

	Vector4 vec8;
	std::cout << "Vector 8: " << vec8 << "\n";
	vec8.setX(-3);
	vec8.setY(2);
	vec8.setZ(5);
	vec8.setW(8);

	std::cout << "Vector 8 after set:\n";
	std::cout << "  x: " << vec8.getX() << "\n";
	std::cout << "  y: " << vec8.getY() << "\n";
	std::cout << "  z: " << vec8.getZ() << "\n";
	std::cout << "  w: " << vec8.getW() << "\n";

	std::cout << "\n=======MAGNITUDE=======\n";
	std::cout << "Vector7's Magnitude: " << vec7.magnitude() << "\n";
	std::cout << "Vector8's Magnitude: " << vec8.magnitude() << "\n";


	std::cout << "\n=======VECTOR-VECTOR OPERATORS=======\n";
	std::cout << "Vector7 + Vector8 = " << vec7 + vec8 << "\n";

	std::cout << "Vector7 - Vector8 = " << vec7 - vec8 << "\n";


	std::cout << "\n=======VECTOR-SCALAR OPERATORS=======\n";
	std::cout << "Vector7  = " << vec7 << " ; Vector8 = " << vec8 << "\n";
	std::cout << "Vector7 * 2.0f = " << vec7 * 2.0f << "\n";

	std::cout << "Vector7 + 2.0f = " << vec7 + 2.0f << "\n";

	std::cout << "2 + Vector7 = " << 2 + vec7 << "\n";

	std::cout << "Vector7 - 2.0f = " << vec7 - 2.0f << "\n";

	std::cout << "2 - Vector7 = " << 2 - vec7 << "\n";

	std::cout << "Vector7 / 2.0f = " << vec7 / 2.0f << "\n";

	std::cout << "-2.0f * Vector8 = " << -2.0f * vec8 << "\n";

	std::cout << "Vector8 / -2 = " << vec8 / -2 << "\n";

	std::cout << "-Vector8 = " << -vec8 << "\n";


	std::cout << "\n=======ASSIGNMENTS=======\n";
	Vector4 vec9(1, 1, 1, 1);
	std::cout << "Vector 9: " << vec9 << "\n";
	vec9 += vec7;
	std::cout << "Vector9 += Vector7 = " << vec9 << "\n";

	std::cout << "Vector 9: " << vec9 << "\n";

	vec9 += 1;
	std::cout << "Vector9 += 1 = " << vec9 << "\n";

	std::cout << "Vector 9: " << vec9 << "\n";

	vec9 -= vec7;
	std::cout << "Vector9 -= Vector7 = " << vec9 << "\n";

	std::cout << "Vector 9: " << vec9 << "\n";

	vec9 -= 1;
	std::cout << "Vector9 -= 1 = " << vec9 << "\n";

	std::cout << "Vector 9: " << vec9 << "\n";

	vec9 *= 2.0f;
	std::cout << "Vector9 *= 2.0f = " << vec9 << "\n";

	std::cout << "Vector 93: " << vec9 << "\n";

	vec9 /= 2.0f;
	std::cout << "Vector9 /= 2.0f = " << vec9 << "\n";

	vec9 = vec7;
	std::cout << "Vector9 = Vector7 = " << vec9 << "\n";


	std::cout << "\n=======COMPARISSONS=======\n";
	std::cout << "Vector7 == Vector8: " << (vec7 == vec8) << "\n";
	std::cout << "Vector7 != Vector8: " << (vec7 != vec8) << "\n";

	vec9 = vec7.clone();
	std::cout << "Vector7 == Vector9: " << (vec7 == vec9) << "\n";
	std::cout << "Vector7 != Vector9: " << (vec7 != vec9) << "\n";

	std::cout << "Vector7 magnitude compared to Vector8: " << vec7.compareMag(vec8) << "\n";
	std::cout << "Vector8 magnitude compared to Vector7: " << vec8.compareMag(vec7) << "\n";
	std::cout << "Vector7 magnitude compared to Vector9: " << vec7.compareMag(vec9) << "\n";

	std::cout << "Vector7 magnitude compared to 0: " << vec7.compareMag(0.0f) << "\n";
	std::cout << "Vector7 magnitude compared to 100: " << vec7.compareMag(100) << "\n";
	std::cout << "Vector7 magnitude compared to Vector7's magnitude: " << vec7.compareMag(vec7.magnitude()) << "\n";

	std::cout << "\n=======VECTOR METHODS=======\n";
	std::cout << "Vector7 Dot product with Vector8 = " << vec7.dotProd(vec8) << "\n";

	std::cout << "Vector7 Normalized: " << vec7.normalized() << "\n";

	std::cout << "Vector7 angle with Vector8: " << vec7.angle(vec8) << "\n";

	std::cout << "Vector7 distance to Vector8: " << vec7.dist(vec8) << "\n";

	std::cout << "Vector7 Inverted: " << vec7.invert() << "\n";

	std::cout << "Vector8 Quadrance: " << vec8.quadrance() << "\n";

	std::cout << "Vector8 Magnitude: " << vec8.magnitude() << "\n";

	std::cout << "Vector8 Normalize: " << vec8.normalize() << "\n";

	std::cout << "Vector8 Magnitude after Normalized: " << vec8.magnitude() << "\n";

	std::cout << "\n=======CONVERSIONS=======\n";
	//4D to 2D
	Vector2 vec2D_B(5, 6);
	Vector4 vec4D_B = vec2D_B;

	std::cout << "Vector2D_B  = " << vec2D_B << " ; Vector4D_B = " << vec4D_B << "\n";

	vec2D_A.setX(10);
	vec2D_A.setY(10);

	vec4D_B = vec2D_B;
	std::cout << "Vector2D_B  = " << vec2D_B << " ; Vector4D_B = " << vec4D_B << "\n";

	std::cout << "Vector4D_B  + Vector2D_B = " << vec4D_B + vec2D_B << "\n";

	//4D to 3D
	Vector3 vec3D_B(5, 6, 7);
	Vector4 vec4D_B2 = vec3D_B;

	std::cout << "Vector3D_B  = " << vec3D_B << " ; Vector4D_B2 = " << vec4D_B2 << "\n";

	vec3D_B.setX(10);
	vec3D_B.setY(10);
	vec3D_B.setZ(11);

	vec4D_B2 = vec3D_B;
	std::cout << "Vector3D_B  = " << vec3D_B << " ; Vector4D_B2 = " << vec4D_B2 << "\n";

	std::cout << "Vector4D_B2  + Vector3D_B = " << vec4D_B2 + vec3D_B << "\n";

	std::cout << "=====================VECTOR 4=====================\n\n\n";



	std::cout << "=====================VECTOR 2=====================\n";
	std::cout << "=======CONSTRUCTORS, SETTERS & GETTERS=======\n";

	Vector2 vec4(1, 2);
	std::cout << "Vector 4: " << vec4 << "\n";
	std::cout << "  x: " << vec4.getX() << "\n";
	std::cout << "  y: " << vec4.getY() << "\n";

	Vector2 vec5;
	std::cout << "Vector 5: " << vec5 << "\n";
	vec5.setX(-3);
	vec5.setY(2);

	std::cout << "Vector 5 after set:\n";
	std::cout << "  x: " << vec5.getX() << "\n";
	std::cout << "  y: " << vec5.getY() << "\n";


	std::cout << "\n=======MAGNITUDE=======\n";
	std::cout << "Vector4's Magnitude: " << vec4.magnitude() << "\n";
	std::cout << "Vector5's Magnitude: " << vec5.magnitude() << "\n";


	std::cout << "\n=======VECTOR-VECTOR OPERATORS=======\n";
	std::cout << "Vector4 + Vector5 = " << vec4 + vec5 << "\n";
	std::cout << "Vector4 + Vector1 = " << vec4 + vec1 << "\n";
	std::cout << "Vector1 + Vector4 = " << vec1 + vec4 << "\n";

	std::cout << "Vector4 - Vector5 = " << vec4 - vec5 << "\n";


	std::cout << "\n=======VECTOR-SCALAR OPERATORS=======\n";
	std::cout << "Vector4  = " << vec4 << " ; Vector5 = " << vec5 << "\n";
	std::cout << "Vector4 * 2.0f = " << vec4 * 2.0f << "\n";

	std::cout << "Vector4 + 2.0f = " << vec4 + 2.0f << "\n";

	std::cout << "2 + Vector4 = " << 2 + vec4 << "\n";

	std::cout << "Vector4 - 2.0f = " << vec4 - 2.0f << "\n";

	std::cout << "2 - Vector4 = " << 2 - vec4 << "\n";

	std::cout << "Vector4 / 2.0f = " << vec4 / 2.0f << "\n";

	std::cout << "-2.0f * Vector5 = " << -2.0f * vec5 << "\n";

	std::cout << "Vector2 / -5 = " << vec5 / -2 << "\n";

	std::cout << "-Vector5 = " << -vec5 << "\n";


	std::cout << "\n=======ASSIGNMENTS=======\n";
	Vector2 vec6(1, 1);
	std::cout << "Vector 6: " << vec6 << "\n";
	vec6 += vec4;
	std::cout << "Vector6 += Vector4 = " << vec6 << "\n";

	std::cout << "Vector 6: " << vec6 << "\n";

	vec6 += 1;
	std::cout << "Vector6 += 1 = " << vec6 << "\n";

	std::cout << "Vector 6: " << vec6 << "\n";

	vec6 -= vec4;
	std::cout << "Vector6 -= Vector4 = " << vec6 << "\n";

	std::cout << "Vector 6: " << vec6 << "\n";

	vec6 -= 1;
	std::cout << "Vector6 -= 1 = " << vec6 << "\n";

	std::cout << "Vector 6: " << vec6 << "\n";

	vec6 *= 2.0f;
	std::cout << "Vector6 *= 2.0f = " << vec6 << "\n";

	std::cout << "Vector 6: " << vec6 << "\n";

	vec6 /= 2.0f;
	std::cout << "Vector6 /= 2.0f = " << vec6 << "\n";

	vec6 = vec4;
	std::cout << "Vector6 = Vector4 = " << vec6 << "\n";


	std::cout << "\n=======COMPARISSONS=======\n";
	std::cout << "Vector4 == Vector5: " << (vec4 == vec5) << "\n";
	std::cout << "Vector4 != Vector5: " << (vec4 != vec5) << "\n";

	vec6 = vec4.clone();
	std::cout << "Vector4  = " << vec4 << " ; Vector6 = " << vec6 << "\n";
	std::cout << "Vector4 == Vector6: " << (vec4 == vec6) << "\n";
	std::cout << "Vector4 != Vector6: " << (vec4 != vec6) << "\n";

	std::cout << "Vector4 magnitude compared to Vector5: " << vec4.compareMag(vec5) << "\n";
	std::cout << "Vector5 magnitude compared to Vector4: " << vec5.compareMag(vec4) << "\n";
	std::cout << "Vector4 magnitude compared to Vector6: " << vec4.compareMag(vec6) << "\n";

	std::cout << "Vector4 magnitude compared to 0: " << vec4.compareMag(0.0f) << "\n";
	std::cout << "Vector4 magnitude compared to 100: " << vec4.compareMag(100) << "\n";
	std::cout << "Vector4 magnitude compared to Vector4's magnitude: " << vec4.compareMag(vec4.magnitude()) << "\n";

	std::cout << "\n=======VECTOR METHODS=======\n";
	std::cout << "Vector4 Dot product with Vector5 = " << vec4.dotProd(vec5) << "\n";

	vec6 = vec4.perpendicular();
	std::cout << "Vector perpendicular to Vector4 = " << vec6 << "\n";

	std::cout << "Vector4 Normalized: " << vec4.normalized() << "\n";

	std::cout << "Vector4 angle with perpendicular vector: " << vec4.angle(vec6) << "\n";

	std::cout << "Vector4 distance to Vector5: " << vec4.dist(vec5) << "\n";

	std::cout << "Vector4 distance to perpendicular vector: " << vec4.dist(vec6) << "\n";

	std::cout << "Vector4 Inverted: " << vec4.invert() << "\n";

	std::cout << "Vector5 Quadrance: " << vec5.quadrance() << "\n";

	std::cout << "Vector5 Magnitude: " << vec5.magnitude() << "\n";

	std::cout << "Vector5 Normalize: " << vec5.normalize() << "\n";

	std::cout << "Vector5 Magnitude after Normalized: " << vec5.magnitude() << "\n";

	std::cout << "\n=======CONVERSIONS=======\n";
	//2D to 3D
	Vector3 vec3D_C(7,8,9);
	Vector2 vec2D_C = vec3D_C;

	std::cout << "Vector3D_C  = " << vec3D_C << " ; Vector2D_C = " << vec2D_C << "\n";

	vec3D_C.setX(10);
	vec3D_C.setY(10);
	vec3D_C.setZ(10);

	vec2D_C = vec3D_C;
	std::cout << "Vector3D_C  = " << vec3D_C << " ; Vector2D_C = " << vec2D_C << "\n";

	std::cout << "Vector2D_C  + Vector3D_C = " << vec2D_C + vec3D_C << "\n";

	//2D to 4D
	Vector4 vec4D_C(4,3,2,1);
	Vector2 vec2D_C2 = vec3D_C;

	std::cout << "Vector4D_C  = " << vec3D_C << " ; Vector2D_C2 = " << vec2D_C << "\n";

	vec4D_C.setX(10);
	vec4D_C.setY(9);
	vec4D_C.setZ(8);
	vec4D_C.setW(7);

	vec2D_C2 = vec4D_C;
	std::cout << "Vector4D_C  = " << vec4D_C << " ; Vector2D_C2 = " << vec2D_C2 << "\n";

	std::cout << "Vector2D_C2  + Vector4D_C = " << vec2D_C2 + vec4D_C << "\n";



	std::cout << "=====================VECTOR 2=====================\n\n\n";

	return 0;
}