#include "../../../headers/matrices/Matrix4.h"

#include "../../../headers/vectors/Vector4.h"

#include <cassert>

// Matrix 4 Constructors
Matrix4::Matrix4() {
}

Matrix4::Matrix4(float val) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = val;
		}
	}
}

Matrix4::Matrix4(float mat[4][4]) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = mat[row][col];
		}
	}
}

//Matrix4 Print
std::ostream& operator<<(std::ostream& os, const Matrix4& matrix)
{
	os << "\n";
	for (int row = 0; row < 4; row++) {
		os << "[";

		for (int col = 0; col < 4; col++) {
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
Matrix4 Matrix4::clone() {
	return Matrix4(matrix);
}

//Matrix4 Getters
float Matrix4::get(int row, int col) {
	assert(row > 0 && row < 4 && col > 0 && col < 4);
	return matrix[row][col];
}

//Matrix4 Setters
void Matrix4::set(int row, int col, float val) {
	assert(row >= 0 && row < 4 && col >= 0 && col < 4);
	matrix[row][col] = val;
}


//Matrix4 Operations
Matrix4 Matrix4::operator+(const Matrix4& mat)
{
	/* NEEDLESS ASSERTION
	int noRows = sizeof(mat.matrix) / sizeof(mat.matrix[0]);
	int noCols = sizeof(mat.matrix[0]) / sizeof(float);
	std::cout << noRows << "\n";
	assert(noRows == 4 && noCols == 4);
	*/

	Matrix4 matSum;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matSum.matrix[row][col] = matrix[row][col] + mat.matrix[row][col];
		}
	}

	return matSum;
}

Matrix4 Matrix4::operator-(const Matrix4& mat)
{
	Matrix4 matSub;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matSub.matrix[row][col] = matrix[row][col] - mat.matrix[row][col];
		}
	}

	return matSub;
}

Matrix4 Matrix4::operator*(const Matrix4& mat) {
	Matrix4 matMul;

	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			for (int i = 0; i < 4; ++i)
			{
				matMul.matrix[row][col] += matrix[row][i] * mat.matrix[i][col];
			}
		}
	}

	return matMul;
}

Matrix4 Matrix4::operator*(float val)
{
	Matrix4 matMul;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matMul.matrix[row][col] = matrix[row][col] * val;
		}
	}

	return matMul;
}

Matrix4 operator*(float val, Matrix4& mat)
{
	Matrix4 matMul;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matMul.matrix[row][col] = mat.matrix[row][col] * val;
		}
	}

	return matMul;
}

Vector4 Matrix4::operator*(Vector4& vec) {
	float x = matrix[0][0] * vec.getX() + matrix[0][1] * vec.getY() + matrix[0][2] * vec.getZ() + matrix[0][3] * vec.getW();

	float y = matrix[1][0] * vec.getX() + matrix[1][1] * vec.getY() + matrix[1][2] * vec.getZ() + matrix[1][3] * vec.getW();

	float z = matrix[2][0] * vec.getX() + matrix[2][1] * vec.getY() + matrix[2][2] * vec.getZ() + matrix[2][3] * vec.getW();

	float w = matrix[3][0] * vec.getX() + matrix[3][1] * vec.getY() + matrix[3][2] * vec.getZ() + matrix[3][3] * vec.getW();

	return Vector4(x, y, z, w);
}

Vector4 operator*(Vector4& vec, Matrix4& mat) {
	float x = vec.getX() * mat.matrix[0][0] + vec.getY() * mat.matrix[1][0] + vec.getZ() * mat.matrix[2][0] + vec.getZ() * mat.matrix[3][0];

	float y = vec.getX() * mat.matrix[0][1] + vec.getY() * mat.matrix[1][1] + vec.getZ() * mat.matrix[2][1] + vec.getZ() * mat.matrix[3][1];

	float z = vec.getX() * mat.matrix[0][2] + vec.getY() * mat.matrix[1][2] + vec.getZ() * mat.matrix[2][2] + vec.getZ() * mat.matrix[3][2];

	float w = vec.getX() * mat.matrix[0][3] + vec.getY() * mat.matrix[1][3] + vec.getZ() * mat.matrix[2][3] + vec.getZ() * mat.matrix[3][3];

	return Vector4(x, y, z, w);
}

Matrix4 Matrix4::operator/(float val)
{
	Matrix4 matMul;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matMul.matrix[row][col] = matrix[row][col] / val;
		}
	}

	return matMul;
}

Matrix4 operator/(float val, Matrix4& mat)
{
	Matrix4 matMul;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matMul.matrix[row][col] = mat.matrix[row][col] / val;
		}
	}

	return matMul;
}

//Matrix4 Assignments
Matrix4& Matrix4::operator+=(const Matrix4& mat) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = matrix[row][col] + mat.matrix[row][col];
		}
	}

	return *this;
}

Matrix4& Matrix4::operator-=(const Matrix4& mat) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = matrix[row][col] - mat.matrix[row][col];
		}
	}

	return *this;
}

Matrix4& Matrix4::operator*=(const Matrix4& mat) {
	return *this = *this *mat;
}

Matrix4& Matrix4::operator*=(float val) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = matrix[row][col] * val;
		}
	}

	return *this;
}

Vector4 operator*=(Vector4& vec, Matrix4& mat) {
	vec.setX(vec.getX() * mat.matrix[0][0] + vec.getY() * mat.matrix[1][0] + vec.getZ() * mat.matrix[2][0] + vec.getW() * mat.matrix[3][0]);

	vec.setY(vec.getX() * mat.matrix[0][1] + vec.getY() * mat.matrix[1][1] + vec.getZ() * mat.matrix[2][1] + vec.getW() * mat.matrix[3][1]);

	vec.setZ(vec.getX() * mat.matrix[0][2] + vec.getY() * mat.matrix[1][2] + vec.getZ() * mat.matrix[2][2] + vec.getW() * mat.matrix[3][2]);

	vec.setW(vec.getW() * mat.matrix[0][3] + vec.getY() * mat.matrix[1][3] + vec.getZ() * mat.matrix[2][3] + vec.getW() * mat.matrix[3][2]);

	return vec;
}

Matrix4& Matrix4::operator/=(float val) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = matrix[row][col] / val;
		}
	}

	return *this;
}

Matrix4& Matrix4::operator=(const Matrix4& mat) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = mat.matrix[row][col];
		}
	}

	return *this;
}

Matrix4& Matrix4::operator=(float val) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = val;
		}
	}

	return *this;
}

//Matrix4 Comparators
bool Matrix4::operator==(const Matrix4& mat) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			if (matrix[row][col] != mat.matrix[row][col]) {
				return false;
			}
		}
	}

	return true;
}


bool Matrix4::operator!=(const Matrix4& mat) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			if (matrix[row][col] == mat.matrix[row][col]) { 
				return false;
			}
		}
	}

	return true;
}

//Matrix4 Methods
Matrix4 Matrix4::transposed() {
	Matrix4 trans;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			trans.matrix[col][row] = matrix[row][col];
		}
	}

	return trans;
}

/*TODO : VERIFICAR QUE ISTO ESTA BEM*/
Matrix4 Matrix4::convertMajorOrder() {  
	Matrix4 trans = this->transposed();

	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = trans.matrix[row][col];
		}
	}

	return *this;
}

/*AQUI FICAVA MELHOR COM MATRIX2 / Theres probably a way to make this not O(n^4)*/
Matrix4 Matrix4::adjoint() {  // NÃO MEXI PORQUE NÃO CONHEÇO ESTA TUA SOLUÇÃO, mas suponho que a dos coeficientes funcione
	Matrix4 trans = transposed();
	Matrix4 adj;

	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			float temp[4] = { 0,0,0,0 };
			int index = 0;

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (i == row || j == col) continue;
					temp[index++] = trans.matrix[i][j];
				}
			}

			adj.matrix[row][col] = temp[0] * temp[4] - temp[1] * temp[2];

			if ((row + col) % 2 != 0) adj.matrix[row][col] = -adj.matrix[row][col];
		}
	}

	return adj;
	}

	Matrix4 Matrix4::identity() {
		return Matrix4(new float[4][4]{ {1,0,0},{0,1,0},{0,0,1} });
	}

	Matrix4 Matrix4::scaling(float sx, float sy, float sz, float sw) {
		return Matrix4(new float[4][4]{ {sx,0,0,0}, {0,sy,0,0}, {0,0,sz,0}, {0,0,0,sw} });
	}

	/* Não implementei poruqe não consigo arranjar uma forma de o fazer
	Matrix4 Matrix4::translation(Vector4& vec) {   

	}

	Matrix4 Matrix4::rotation(Vector4& vec) {

	}
	*/