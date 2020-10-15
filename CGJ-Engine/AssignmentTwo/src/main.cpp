#include <iostream>
#include "../headers/vectors/Vector3.h"
#include "../headers/vectors/Vector2.h"
#include "../headers/vectors/Vector4.h"

#include "../headers/matrices/Matrix3.h"
#include "../headers/matrices/Matrix2.h"
#include "../headers/matrices/Matrix4.h"


int main() {
	std::cout << "=====================MATRIX 3x3=====================\n";

	std::cout << "=======CONSTRUCTORS, SETTERS & GETTERS=======\n";

	Matrix3 mat1;
	std::cout << "Matrix 1: " << mat1 << "\n";

	Matrix3 mat2(new float[3][3]{ {1,2,3},{4,5,6},{7,8,9} });
	std::cout << "Matrix 2: " << mat2 << "\n";

	std::cout << "Matrix 2 [2][2]: " << mat2.get(2,2) << "\n";

	std::cout << "Matrix 2 [1]: " << mat2[1] << "\n";
	std::cout << "Matrix 2 [1][1]: " << mat2[1][1] << "\n";

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

	std::cout << "Matrix3 + 2 = " << mat3 + 2 << "\n";
	std::cout << "Matrix3 - 2 = " << mat3 - 2 << "\n";
	std::cout << "2 + Matrix3 = " << 2 + mat3 << "\n";
	std::cout << "2 - Matrix3 = " << 2 - mat3 << "\n";

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
	Matrix4 matC(1);
	Matrix3 matA(matC);
	std::cout << "Matrix3 from Matrix4: " << matA;

	Matrix2 matB(1);
	matA = matB;
	std::cout << "Matrix3 from Matrix2: " << matA;

	std::cout << "=====================MATRIX 3x3=====================\n\n\n";

	std::cout << "=====================MATRIX 2x2=====================\n";

	std::cout << "=======CONSTRUCTORS, SETTERS & GETTERS=======\n";

	Matrix2 mat5;
	std::cout << "Matrix 5: " << mat5 << "\n";

	Matrix2 mat6(new float[2][2]{ {1,2},{3,4}});
	std::cout << "Matrix 6: " << mat6 << "\n";

	std::cout << "Matrix 6 [1][1]: " << mat6.get(1, 1) << "\n";

	std::cout << "Matrix 6 [1]: " << mat6[1] << "\n";
	std::cout << "Matrix 6 [1][1]: " << mat6[1][1] << "\n";

	mat6.set(1, 1, 10);
	std::cout << "Matrix 6 [1][1] after Set: " << mat6.get(1, 1) << "\n\n";

	Matrix2 mat7(1);
	std::cout << "Matrix 7: " << mat7 << "\n";

	std::cout << "\n=======MATRIX-MATRIX OPERATORS=======\n";
	std::cout << "Matrix 5: " << mat5 << "\n";
	std::cout << "Matrix 6: " << mat6 << "\n";
	std::cout << "Matrix 7: " << mat7 << "\n";

	std::cout << "Matrix 5 + Matrix 6 = " << mat5 + mat6 << "\n";
	std::cout << "Matrix 6 - Matrix 5 = " << mat6 - mat5 << "\n";

	std::cout << "Matrix 7 * Matrix 6 = " << mat7 * mat6 << "\n";
	std::cout << "Matrix 6 * Matrix 7 = " << mat6 * mat7 << "\n";


	std::cout << "\n=======MATRIX-SCALAR OPERATORS=======\n";
	std::cout << "Matrix 7: " << mat7 << "\n";

	std::cout << "Matrix7 + 2 = " << mat7 + 2 << "\n";
	std::cout << "Matrix7 - 2 = " << mat7 - 2 << "\n";
	std::cout << "2 + Matrix7 = " << 2 + mat7 << "\n";
	std::cout << "2 - Matrix7 = " << 2 - mat7 << "\n";

	std::cout << "Matrix 7 * 2 = " << mat7 * 2 << "\n";
	std::cout << "1/2.0f * Matrix 7 = " << 1 / 2.0f * mat7 << "\n";

	std::cout << "Matrix 7 / 4 = " << mat7 / 4 << "\n";
	std::cout << "4.0f / Matrix 7 = " << 4.0f / mat7 << "\n";

	std::cout << "\n=======MATRIX-VECTOR OPERATORS=======\n";
	std::cout << "Matrix 7: " << mat7;

	Vector2 vec2(1, 2);
	std::cout << "Vector2: " << vec2 << "\n";

	std::cout << "Matrix 7 * Vector 2 = " << mat7 * vec2 << "\n";
	std::cout << "Vector 2 * Matrix 7 = " << vec2 * mat7 << "\n\n";

	std::cout << "Matrix 6: " << mat6;
	std::cout << "Vector 2: " << vec2 << "\n";

	std::cout << "Matrix 6 * Vector 2 = " << mat6 * vec2 << "\n";
	std::cout << "Vector 2 * Matrix 6 = " << vec2 * mat6 << "\n";

	std::cout << "\n=======ASSIGNMENTS=======\n";
	std::cout << "Matrix 7: " << mat7;

	vec2.set(1, 2);
	std::cout << "Vector 2: " << vec2 << "\n";

	Matrix2 mat8;
	std::cout << "Matrix 8: " << mat7;

	mat8 = mat7;
	std::cout << "Matrix 8 = Matrix 7: " << mat7;

	mat8 += mat7;
	std::cout << "Matrix 8 += Matrix 7: " << mat7;

	mat8 -= mat7;
	std::cout << "Matrix 8 -= Matrix 7: " << mat7;

	mat8 += 1;
	std::cout << "Matrix 8 += 1: " << mat8;

	mat8 -= 1;
	std::cout << "Matrix 8 -= 1: " << mat8;

	mat8 = 1;
	std::cout << "Matrix 8 = 1: " << mat8;

	mat8 *= mat7;
	std::cout << "Matrix 8 *= Matrix 7: " << mat8;

	mat8 *= 2;
	std::cout << "Matrix 8 *= 2: " << mat8;

	mat8 /= 2;
	std::cout << "Matrix 8 /= 2: " << mat8;

	vec2 *= mat8;
	std::cout << "Vector 2 /= Matrix 8: " << vec2;

	std::cout << "\n=======COMPARISSONS=======\n";
	std::cout << "Matrix 5: " << mat5;
	std::cout << "Matrix 6: " << mat6;
	std::cout << "Matrix 7: " << mat7;

	mat7 = mat6;
	std::cout << "Matrix 7 = Matrix 6: " << mat7;

	std::cout << "Matrix 5 == Matrix 6 : " << (mat5 == mat6) << "\n";
	std::cout << "Matrix 5 != Matrix 6 : " << (mat5 != mat6) << "\n";

	std::cout << "Matrix 7 == Matrix 6 : " << (mat7 == mat6) << "\n";
	std::cout << "Matrix 6 != Matrix 7 : " << (mat6 != mat7) << "\n";

	std::cout << "\n=======MATRIX METHODS=======\n";
	std::cout << "Matrix 5: " << mat5;
	mat6 = Matrix2(new float[2][2]{ {1,2},{0,1} });
	std::cout << "Matrix 6: " << mat6 << "\n";

	std::cout << "Transposed Matrix 5: " << mat5.transposed();
	std::cout << "Transposed Matrix 6: " << mat6.transposed();

	std::cout << "Col Major Matrix 6: " << mat6.convertMajorOrder();
	std::cout << "Row Major Matrix 6: " << mat6.convertMajorOrder();

	std::cout << "Determinant Matrix 5: " << mat5.determinant() << "\n";
	std::cout << "Determinant Matrix 6: " << mat6.determinant() << "\n";

	std::cout << "Adjoint Matrix 5: " << mat5.adjoint() << "\n";
	std::cout << "Adjoint Matrix 6: " << mat6.adjoint() << "\n";

	std::cout << "Inverse Matrix 6: " << mat6.inverse() << "\n";

	std::cout << "Identity Matrix: " << Matrix2::identity();

	std::cout << "\n=======CONVERSIONS=======\n";
	matA = Matrix3(1);
	matB = matA;
	std::cout << "Matrix2 from Matrix3: " << matB;

	matC = Matrix4(1);
	matB = matC;
	std::cout << "Matrix2 from Matrix4: " << matB;

	std::cout << "=====================MATRIX 2x2=====================\n\n\n";


	std::cout << "=====================MATRIX 4x4=====================\n";

	std::cout << "=======CONSTRUCTORS, SETTERS & GETTERS=======\n";

	Matrix4 mat9;
	std::cout << "Matrix 9: " << mat9 << "\n";

	Matrix4 mat10(new float[4][4]{ {1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16} });
	std::cout << "Matrix 10: " << mat10 << "\n";

	std::cout << "Matrix 10 [2][2]: " << mat10.get(2, 2) << "\n";

	std::cout << "Matrix 10 [1]: " << mat10[1] << "\n";
	std::cout << "Matrix 10 [1][1]: " << mat10[1][1] << "\n";

	mat10.set(2, 2, 10);
	std::cout << "Matrix 10 [2][2] after Set: " << mat10.get(2, 2) << "\n\n";

	Matrix4 mat11(1);
	std::cout << "Matrix 11: " << mat11 << "\n";

	std::cout << "\n=======MATRIX-MATRIX OPERATORS=======\n";
	std::cout << "Matrix 9: " << mat9 << "\n";
	std::cout << "Matrix 10: " << mat10 << "\n";
	std::cout << "Matrix 11: " << mat11 << "\n";

	std::cout << "Matrix9 + Matrix10 = " << mat9 + mat10 << "\n";
	std::cout << "Matrix9 - Matrix10 = " << mat9 - mat10 << "\n";

	std::cout << "Matrix11 * Matrix10 = " << mat11 * mat10 << "\n";
	std::cout << "Matrix10 * Matrix11 = " << mat10 * mat11 << "\n";


	std::cout << "\n=======MATRIX-SCALAR OPERATORS=======\n";
	std::cout << "Matrix11: " << mat11 << "\n";

	std::cout << "Matrix11 * 2 = " << mat11 * 2 << "\n";
	std::cout << "1/2.0f * Matrix11 = " << 1 / 2.0f * mat11 << "\n";

	std::cout << "Matrix11 + 2 = " << mat11 + 2 << "\n";
	std::cout << "Matrix11 - 2 = " << mat11 - 2 << "\n";
	std::cout << "2 + Matrix11 = " << 2 + mat11 << "\n";
	std::cout << "2 - Matrix11 = " << 2 - mat11 << "\n";

	std::cout << "Matrix11 / 4 = " << mat11 / 4 << "\n";
	std::cout << "4.0f / Matrix11 = " << 4.0f / mat11 << "\n";

	std::cout << "\n=======MATRIX-VECTOR OPERATORS=======\n";
	std::cout << "Matrix11: " << mat11;

	Vector4 vec3(1, 2, 3,4);
	std::cout << "Vector3: " << vec3 << "\n";

	std::cout << "Matrix11 * Vector3 = " << mat11 * vec3 << "\n";
	std::cout << "Vector3 * Matrix11 = " << vec3 * mat11 << "\n\n";

	std::cout << "Matrix10: " << mat10;
	std::cout << "Vector3: " << vec3 << "\n";

	std::cout << "Matrix10 * Vector3 = " << mat10 * vec3 << "\n";
	std::cout << "Vector3 * Matrix10 = " << vec3 * mat10 << "\n";

	std::cout << "\n=======ASSIGNMENTS=======\n";
	std::cout << "Matrix11: " << mat11;

	vec3.set(1, 2, 3,4);
	std::cout << "Vector3: " << vec3 << "\n";

	Matrix4 mat12;
	std::cout << "Matrix12: " << mat12;

	mat12 = mat11;
	std::cout << "Matrix12 = Matrix11: " << mat12;

	mat12 += mat11;
	std::cout << "Matrix12 += Matrix11: " << mat12;

	mat12 -= mat11;
	std::cout << "Matrix12 -= Matrix11: " << mat12;

	mat12 += 1;
	std::cout << "Matrix12 += 1: " << mat12;

	mat12 -= 1;
	std::cout << "Matrix12 -= 1: " << mat12;

	mat12 = 1;
	std::cout << "Matrix12 = 1: " << mat12;

	mat12 *= mat11;
	std::cout << "Matrix12 *= Matrix11: " << mat12;

	mat12 *= 2;
	std::cout << "Matrix12 *= 2: " << mat12;

	mat12 /= 2;
	std::cout << "Matrix12 /= 2: " << mat12;

	vec3 *= mat12;
	std::cout << "Vector3 /= Matrix12: " << vec3;

	std::cout << "\n=======COMPARISSONS=======\n";
	std::cout << "Matrix9: " << mat9;
	std::cout << "Matrix10: " << mat10;

	mat11 = mat10;
	std::cout << "Matrix11 = Matrix 10: " << mat11;

	std::cout << "Matrix9 == Matrix10 : " << (mat9 == mat10) << "\n";
	std::cout << "Matrix9 != Matrix10 : " << (mat9 != mat10) << "\n";

	std::cout << "Matrix11 == Matrix10 : " << (mat11 == mat10) << "\n";
	std::cout << "Matrix10 != Matrix11 : " << (mat10 != mat11) << "\n";

	std::cout << "\n=======MATRIX METHODS=======\n";
	std::cout << "Matrix9: " << mat9;
	mat10 = Matrix4(new float[4][4]{ {1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16} });
	std::cout << "Matrix10: " << mat10 << "\n";

	std::cout << "Transposed Matrix9: " << mat9.transposed();
	std::cout << "Transposed Matrix10: " << mat10.transposed();

	std::cout << "Col Major Matrix10: " << mat10.convertMajorOrder();
	std::cout << "Row Major Matrix10: " << mat10.convertMajorOrder();

	std::cout << "Identity Matrix: " << Matrix3::identity();

	vec1.set(1, 2, 3);
	std::cout << "Scaling Matrix (Vector (1,2,3)): " << Matrix4::scaling(vec1) << "\n";
	std::cout << "Scaling Matrix values (1,2,3)): " << Matrix4::scaling(1,2,3) << "\n\n";

	std::cout << "Transition Matrix (Vector (1,2,3)): " << Matrix4::translation(vec1) << "\n";
	std::cout << "Transition Matrix values (1,2,3)): " << Matrix4::translation(1, 2, 3) << "\n\n";

	std::cout << "Rotation Matrix (Vector (1,2,3)): " << Matrix4::rotation(vec1) << "\n";
	std::cout << "Rotation Matrix radians (1,2,3)): " << Matrix4::rotation(1, 2, 3) << "\n";
	std::cout << "Rotation Matrix degrees (90,0,0)): " << Matrix4::rotation(90, 0,0, false) << "\n\n";

	std::cout << "\n=======CONVERSIONS=======\n";
	matA = Matrix3(1);
	matC = matA;
	std::cout << "Matrix4 from Matrix3: " << matC;

	matB = Matrix2(1);
	matC = matB;
	std::cout << "Matrix4 from Matrix2: " << matC;

	std::cout << "=====================MATRIX 4x4=====================\n\n\n";

	return 0;
}