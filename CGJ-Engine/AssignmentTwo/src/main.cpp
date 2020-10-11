#include <iostream>
#include "../headers/vectors/Vector3.h"
#include "../headers/vectors/Vector2.h"
#include "../headers/vectors/Vector4.h"

#include "../headers/matrices/Matrix3.h"
#include "../headers/matrices/Matrix2.h"


int main() {
	std::cout << "=====================MATRIX 3x3=====================\n";

	std::cout << "=======CONSTRUCTORS, SETTERS & GETTERS=======\n";

	Matrix3 mat1;
	std::cout << "Matrix 1: " << mat1 << "\n";

	Matrix3 mat2(new float[3][3]{ {1,2,3},{4,5,6},{7,8,9} });
	std::cout << "Matrix 2: " << mat2 << "\n";

	std::cout << "Matrix 2 [2][2]: " << mat2.get(2,2) << "\n";

	mat2.set(2, 2, 10);
	std::cout << "Matrix 2 [2][2] after Set: " << mat2.get(2, 2) << "\n\n";

	Matrix3 mat3(1);
	std::cout << "Matrix 3: " << mat3 << "\n";

	std::cout << "\n=======MATRIX-MATRIX OPERATORS=======\n";
	std::cout << "Matrix 1: " << mat1 << "\n";
	std::cout << "Matrix 2: " << mat2 << "\n";
	std::cout << "Matrix3: " << mat3 << "\n";

	std::cout << "Matrix1 + Matrix2 = " << mat1 + mat2 << "\n";
	std::cout << "Matrix2 - Matrix1 = " << mat1 - mat2 << "\n";

	std::cout << "Matrix3 * Matrix2 = " << mat3 * mat2 << "\n";
	std::cout << "Matrix2 * Matrix3 = " << mat2 * mat3 << "\n";


	std::cout << "\n=======MATRIX-SCALAR OPERATORS=======\n";
	std::cout << "Matrix3: " << mat3 << "\n";

	std::cout << "Matrix3 * 2 = " << mat3 * 2 << "\n";
	std::cout << "1/2.0f * Matrix3 = " << 1/2.0f * mat3 << "\n";

	std::cout << "Matrix3 / 4 = " << mat3 / 4 << "\n";
	std::cout << "4.0f / Matrix3 = " << 4.0f / mat3 << "\n";

	std::cout << "\n=======MATRIX-VECTOR OPERATORS=======\n";
	std::cout << "Matrix3: " << mat3;

	Vector3 vec1(1, 2, 3);
	std::cout << "Vector1: " << vec1 << "\n";

	std::cout << "Matrix3 * Vector1 = " << mat3*vec1 << "\n";
	std::cout << "Vector1 * Matrix3 = " << vec1*mat3 << "\n\n";

	std::cout << "Matrix2: " << mat2;
	std::cout << "Vector1: " << vec1 << "\n";

	std::cout << "Matrix2 * Vector1 = " << mat2 * vec1 << "\n";
	std::cout << "Vector1 * Matrix2 = " << vec1 * mat2 << "\n";

	std::cout << "\n=======ASSIGNMENTS=======\n";
	std::cout << "Matrix3: " << mat3;

	vec1.set(1,2,3);
	std::cout << "Vector1: " << vec1 << "\n";

	Matrix3 mat4;
	std::cout << "Matrix4: " << mat4;

	mat4 = mat3;
	std::cout << "Matrix4 = Matrix3: " << mat4;

	mat4 += mat3;
	std::cout << "Matrix4 += Matrix3: " << mat4;

	mat4 -= mat3;
	std::cout << "Matrix4 -= Matrix3: " << mat4;

	mat4 += 1;
	std::cout << "Matrix4 += 1: " << mat4;

	mat4 -= 1;
	std::cout << "Matrix4 -= 1: " << mat4;

	mat4 = 1;
	std::cout << "Matrix4 = 1: " << mat4;

	mat4 *= mat3;
	std::cout << "Matrix4 *= Matrix3: " << mat4;

	mat4 *= 2;
	std::cout << "Matrix4 *= 2: " << mat4;

	mat4 /= 2;
	std::cout << "Matrix4 /= 2: " << mat4;

	vec1 *= mat4;
	std::cout << "Vector1 /= Matrix4: " << vec1;

	std::cout << "\n=======COMPARISSONS=======\n";
	std::cout << "Matrix1: " << mat1;
	std::cout << "Matrix2: " << mat2;

	mat3 = mat2;
	std::cout << "Matrix3: " << mat3;

	std::cout << "Matrix1 == Matrix2 : " << (mat1 == mat2) << "\n";
	std::cout << "Matrix1 != Matrix2 : " << (mat1 != mat2) << "\n";

	std::cout << "Matrix3 == Matrix2 : " << (mat3 == mat2) << "\n";
	std::cout << "Matrix2 != Matrix3 : " << (mat2 != mat3) << "\n";

	std::cout << "\n=======MATRIX METHODS=======\n";
	std::cout << "Matrix1: " << mat1;
	mat2 = Matrix3(new float[3][3]{ {1,2,3},{0,1,4},{5,6,0} });
	std::cout << "Matrix2: " << mat2 << "\n";

	std::cout << "Transposed Matrix1: " << mat1.transposed();
	std::cout << "Transposed Matrix2: " << mat2.transposed();

	std::cout << "Col Major Matrix2: " << mat2.convertMajorOrder();
	std::cout << "Row Major Matrix2: " << mat2.convertMajorOrder();

	std::cout << "Determinant Matrix1: " << mat1.determinant() << "\n";
	std::cout << "Determinant Matrix2: " << mat2.determinant() << "\n";

	std::cout << "Adjoint Matrix1: " << mat1.adjoint() << "\n";
	std::cout << "Adjoint Matrix2: " << mat2.adjoint() << "\n";

	std::cout << "Inverse Matrix2: " << mat2.inverse() << "\n";

	std::cout << "Identity Matrix: " << Matrix3::identity();

	vec1.set(1, 2, 3);
	std::cout << "Dual Matrix (Vector (1,2,3)): " << Matrix3::dual(vec1);



	std::cout << "\n=======CONVERSIONS=======\n";

	std::cout << "=====================MATRIX 3x3=====================\n\n\n";

	std::cout << "=====================MATRIX 2x2=====================\n";

	std::cout << "=======CONSTRUCTORS, SETTERS & GETTERS=======\n";

	Matrix2 mat8;
	std::cout << "Matrix 8: " << mat8 << "\n";

	Matrix2 mat5(new float[2][2]{ {1,2},{3,4}});
	std::cout << "Matrix 5: " << mat5 << "\n";

	std::cout << "Matrix 5 [1][1]: " << mat5.get(1, 1) << "\n";

	mat5.set(1, 1, 10);
	std::cout << "Matrix 5 [1][1] after Set: " << mat5.get(1, 1) << "\n\n";

	Matrix2 mat6(1);
	std::cout << "Matrix 6: " << mat6 << "\n";

	std::cout << "\n=======MATRIX-MATRIX OPERATORS=======\n";
	std::cout << "Matrix 8: " << mat8 << "\n";
	std::cout << "Matrix 5: " << mat5 << "\n";
	std::cout << "Matrix 6: " << mat6 << "\n";

	std::cout << "Matrix 8 + Matrix 5 = " << mat8 + mat5 << "\n";
	std::cout << "Matrix 5 - Matrix 8 = " << mat5 - mat8 << "\n";

	std::cout << "Matrix 6 * Matrix 5 = " << mat6 * mat5 << "\n";
	std::cout << "Matrix 5 * Matrix 6 = " << mat5 * mat6 << "\n";


	std::cout << "\n=======MATRIX-SCALAR OPERATORS=======\n";
	std::cout << "Matrix 6: " << mat6 << "\n";

	std::cout << "Matrix 6 * 2 = " << mat6 * 2 << "\n";
	std::cout << "1/2.0f * Matrix 6 = " << 1 / 2.0f * mat6 << "\n";

	std::cout << "Matrix 6 / 4 = " << mat6 / 4 << "\n";
	std::cout << "4.0f / Matrix 6 = " << 4.0f / mat6 << "\n";

	std::cout << "\n=======MATRIX-VECTOR OPERATORS=======\n";
	std::cout << "Matrix 6: " << mat6;

	Vector2 vec2(1, 2);
	std::cout << "Vector1: " << vec1 << "\n";

	std::cout << "Matrix 6 * Vector 2 = " << mat6 * vec2 << "\n";
	std::cout << "Vector 2 * Matrix 6 = " << vec2 * mat6 << "\n\n";

	std::cout << "Matrix 5: " << mat5;
	std::cout << "Vector 2: " << vec2 << "\n";

	std::cout << "Matrix 5 * Vector 2 = " << mat5 * vec2 << "\n";
	std::cout << "Vector 2 * Matrix 5 = " << vec2 * mat5 << "\n";

	std::cout << "\n=======ASSIGNMENTS=======\n";
	std::cout << "Matrix 6: " << mat6;

	vec2.set(1, 2);
	std::cout << "Vector 2: " << vec2 << "\n";

	Matrix2 mat7;
	std::cout << "Matrix 7: " << mat7;

	mat7 = mat6;
	std::cout << "Matrix 7 = Matrix 6: " << mat7;

	mat7 += mat6;
	std::cout << "Matrix 7 += Matrix 6: " << mat7;

	mat7 -= mat6;
	std::cout << "Matrix 7 -= Matrix 6: " << mat7;

	mat7 += 1;
	std::cout << "Matrix 7 += 1: " << mat7;

	mat7 -= 1;
	std::cout << "Matrix 7 -= 1: " << mat7;

	mat7 = 1;
	std::cout << "Matrix 7 = 1: " << mat7;

	mat7 *= mat6;
	std::cout << "Matrix 7 *= Matrix 6: " << mat7;

	mat7 *= 2;
	std::cout << "Matrix 7 *= 2: " << mat7;

	mat7 /= 2;
	std::cout << "Matrix 7 /= 2: " << mat7;

	vec2 *= mat7;
	std::cout << "Vector 2 /= Matrix 7: " << vec2;

	std::cout << "\n=======COMPARISSONS=======\n";
	std::cout << "Matrix 8: " << mat8;
	std::cout << "Matrix 5: " << mat5;

	mat6 = mat5;
	std::cout << "Matrix 6: " << mat6;

	std::cout << "Matrix 8 == Matrix 5 : " << (mat8 == mat5) << "\n";
	std::cout << "Matrix 8 != Matrix 5 : " << (mat8 != mat5) << "\n";

	std::cout << "Matrix 6 == Matrix 5 : " << (mat6 == mat5) << "\n";
	std::cout << "Matrix 5 != Matrix 6 : " << (mat5 != mat6) << "\n";

	std::cout << "\n=======MATRIX METHODS=======\n";
	std::cout << "Matrix 8: " << mat8;
	mat5 = Matrix2(new float[2][2]{ {1,2},{0,1} });
	std::cout << "Matrix 5: " << mat5 << "\n";

	std::cout << "Transposed Matrix 8: " << mat8.transposed();
	std::cout << "Transposed Matrix 5: " << mat5.transposed();

	std::cout << "Col Major Matrix 5: " << mat5.convertMajorOrder();
	std::cout << "Row Major Matrix 5: " << mat5.convertMajorOrder();

	std::cout << "Determinant Matrix 8: " << mat8.determinant() << "\n";
	std::cout << "Determinant Matrix 5: " << mat5.determinant() << "\n";

	std::cout << "Adjoint Matrix 8: " << mat8.adjoint() << "\n";
	std::cout << "Adjoint Matrix 5: " << mat5.adjoint() << "\n";

	std::cout << "Inverse Matrix 5: " << mat5.inverse() << "\n";

	std::cout << "Identity Matrix: " << Matrix2::identity();

	std::cout << "\n=======CONVERSIONS=======\n";

	std::cout << "=====================MATRIX 3x3=====================\n\n\n";

	return 0;
}