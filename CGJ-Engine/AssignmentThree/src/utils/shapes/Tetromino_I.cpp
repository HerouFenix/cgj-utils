#include "../../../headers/shapes/Tetromino.h"

#include "../../../headers/vectors/Vector3.h"
#include "../../../headers/vectors/Vector4.h"
#include "../../../headers/matrices/Matrix4.h"


// Tetromino I Constructors
Tetromino_I::Tetromino_I(float colour[4], Vector4 center) : Tetromino(colour, center) {
	// Define base transformations to create the figure from the base square
	Matrix4 identity = Matrix4::identity();
	transforms[0] = identity;

	identity[0][3] = 0.11f;
	transforms[1] = identity;

	identity[0][3] = 0.22f;
	transforms[2] = identity;

	identity[0][3] = -0.11f;
	transforms[3] = identity;
}

Tetromino_I::Tetromino_I(Vector4 center) : Tetromino(center) {
	// Define base transformations to create the figure from the base square
	Matrix4 identity = Matrix4::identity();
	transforms[0] = identity;

	identity[0][3] = 0.11f;
	transforms[1] = identity;

	identity[0][3] = 0.22f;
	transforms[2] = identity;

	identity[0][3] = -0.11f;
	transforms[3] = identity;
}

void Tetromino_I::reset()
{
	Matrix4 identity = Matrix4::identity();
	transforms[0] = identity;

	identity[0][3] = 0.11f;
	transforms[1] = identity;

	identity[0][3] = 0.22f;
	transforms[2] = identity;

	identity[0][3] = -0.11f;
	transforms[3] = identity;
}

