#include "../../../headers/matrices/Matrix3.h"

#include "../../../headers/vectors/Vector3.h"

#include <cassert>

// Matrix 3 Constructors
Matrix3::Matrix3() {
}

Matrix3::Matrix3(float val) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			matrix[row][col] = val;
		}
	}
}

Matrix3::Matrix3(float mat[3][3]) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			matrix[row][col] = mat[row][col];
		}
	}
}

//Matrix3 Print
std::ostream& operator<<(std::ostream& os, const Matrix3& matrix)
{
	os << "\n";
	for (int row = 0; row < 3; row++) {
		os << "[";

		for (int col = 0; col < 3; col++) {
			os << matrix.matrix[row][col];
			if (col != 2) {
				os << ", ";
			}
		}
		os << "]\n";
	}
	return os;
}


//Clone
Matrix3 Matrix3::clone() {
	return Matrix3(matrix);
}

//Matrix3 Getters
float Matrix3::get(int row, int col) {
	assert(row > 0 && row < 3 && col > 0 && col < 3);
	return matrix[row][col];
}

//Matrix3 Setters
void Matrix3::set(int row, int col, float val) {
	assert(row >= 0 && row < 3 && col >= 0 && col < 3);
	matrix[row][col] = val;
}


//Matrix3 Operations
Matrix3 Matrix3::operator+(const Matrix3& mat)
{
	/* NEEDLESS ASSERTION
	int noRows = sizeof(mat.matrix) / sizeof(mat.matrix[0]);
	int noCols = sizeof(mat.matrix[0]) / sizeof(float);
	std::cout << noRows << "\n";
	assert(noRows == 3 && noCols == 3);
	*/

	Matrix3 matSum;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			matSum.matrix[row][col] = matrix[row][col] + mat.matrix[row][col];
		}
	}

	return matSum;
}

Matrix3 Matrix3::operator-(const Matrix3& mat)
{
	Matrix3 matSub;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			matSub.matrix[row][col] = matrix[row][col] - mat.matrix[row][col];
		}
	}

	return matSub;
}

Matrix3 Matrix3::operator*(const Matrix3& mat) {
	Matrix3 matMul;

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			for (int i = 0; i < 3; ++i)
			{
				matMul.matrix[row][col] += matrix[row][i] * mat.matrix[i][col];
			}
		}
	}

	return matMul;
}

Matrix3 Matrix3::operator*(float val)
{
	Matrix3 matMul;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			matMul.matrix[row][col] = matrix[row][col] * val;
		}
	}

	return matMul;
}

Matrix3 operator*(float val, Matrix3& mat)
{
	Matrix3 matMul;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			matMul.matrix[row][col] = mat.matrix[row][col] * val;
		}
	}

	return matMul;
}

Vector3 Matrix3::operator*(Vector3& vec) {
	float x = matrix[0][0] * vec.getX() + matrix[0][1] * vec.getY() + matrix[0][2] * vec.getZ();

	float y = matrix[1][0] * vec.getX() + matrix[1][1] * vec.getY() + matrix[1][2] * vec.getZ();

	float z = matrix[2][0] * vec.getX() + matrix[2][1] * vec.getY() + matrix[2][2] * vec.getZ();

	return Vector3(x, y, z);
}

Vector3 operator*(Vector3& vec, Matrix3& mat) {
	float x = vec.getX() * mat.matrix[0][0] + vec.getY() * mat.matrix[1][0] + vec.getZ() * mat.matrix[2][0];

	float y = vec.getX() * mat.matrix[0][1] + vec.getY() * mat.matrix[1][1] + vec.getZ() * mat.matrix[2][1];

	float z = vec.getX() * mat.matrix[0][2] + vec.getY() * mat.matrix[1][2] + vec.getZ() * mat.matrix[2][2];

	return Vector3(x, y, z);
}

Matrix3 Matrix3::operator/(float val)
{
	Matrix3 matMul;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			matMul.matrix[row][col] = matrix[row][col] / val;
		}
	}

	return matMul;
}

Matrix3 operator/(float val, Matrix3& mat)
{
	Matrix3 matMul;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			matMul.matrix[row][col] = mat.matrix[row][col] / val;
		}
	}

	return matMul;
}

//Matrix3 Assignments
Matrix3& Matrix3::operator+=(const Matrix3& mat) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			matrix[row][col] = matrix[row][col] + mat.matrix[row][col];
		}
	}

	return *this;
}

Matrix3& Matrix3::operator-=(const Matrix3& mat) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			matrix[row][col] = matrix[row][col] - mat.matrix[row][col];
		}
	}

	return *this;
}

Matrix3& Matrix3::operator*=(const Matrix3& mat) {
	/*TODO : THIS FUNCTION CAN PROBABLY BE OPTIMIZED. MB JUST CHANGE THE OBJECT *this = *this * mat??*/
	float tempMatrix[3][3] = { {0,0,0}, {0,0,0}, {0,0,0} };

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			for (int i = 0; i < 3; ++i)
			{
				tempMatrix[row][col] += matrix[row][i] * mat.matrix[i][col];
			}
		}
	}

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			matrix[row][col] = tempMatrix[row][col];
		}
	}

	return *this;
}

Matrix3& Matrix3::operator*=(float val) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			matrix[row][col] = matrix[row][col] * val;
		}
	}

	return *this;
}

Vector3 operator*=(Vector3& vec, Matrix3& mat) {
	vec.setX(vec.getX() * mat.matrix[0][0] + vec.getY() * mat.matrix[1][0] + vec.getZ() * mat.matrix[2][0]);

	vec.setY(vec.getX() * mat.matrix[0][1] + vec.getY() * mat.matrix[1][1] + vec.getZ() * mat.matrix[2][1]);

	vec.setZ(vec.getX() * mat.matrix[0][2] + vec.getY() * mat.matrix[1][2] + vec.getZ() * mat.matrix[2][2]);

	return vec;
}

Matrix3& Matrix3::operator/=(float val) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			matrix[row][col] = matrix[row][col] / val;
		}
	}

	return *this;
}

Matrix3& Matrix3::operator=(const Matrix3& mat) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			matrix[row][col] = mat.matrix[row][col];
		}
	}

	return *this;
}

Matrix3& Matrix3::operator=(float val) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			matrix[row][col] = val;
		}
	}

	return *this;
}

//Matrix3 Comparators

//Matrix3 Methods