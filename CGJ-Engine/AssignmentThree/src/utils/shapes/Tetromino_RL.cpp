#include "../../../headers/shapes/Tetromino.h"

#include "../../../headers/vectors/Vector3.h"
#include "../../../headers/vectors/Vector4.h"
#include "../../../headers/matrices/Matrix4.h"


// Tetromino RL Constructors
Tetromino_RL::Tetromino_RL(float colour[4], Vector4 center) : Tetromino(colour, center) {


	// Define base transformations to create the figure from the base square
	Matrix4 identity = Matrix4::identity();
	identity[0][3] = 0.055f;
	transforms[0] = identity;

	identity[1][3] = -0.110f;
	transforms[1] = identity;

	identity[1][3] = 0.110f;
	transforms[2] = identity;

	identity[0][3] = -0.055f;
	identity[1][3] = -0.110f;
	transforms[3] = identity;
}

Tetromino_RL::Tetromino_RL(Vector4 center) :Tetromino(center)
{

	// Define base transformations to create the figure from the base square
	Matrix4 identity = Matrix4::identity();
	identity[0][3] = 0.055f;
	transforms[0] = identity;

	identity[1][3] = -0.110f;
	transforms[1] = identity;

	identity[1][3] = 0.110f;
	transforms[2] = identity;

	identity[0][3] = -0.055f;
	identity[1][3] = -0.110f;
	transforms[3] = identity;
}

void Tetromino_RL::reset()
{
	Matrix4 identity = Matrix4::identity();
	identity[0][3] = 0.055f;
	transforms[0] = identity;

	identity[1][3] = -0.110f;
	transforms[1] = identity;

	identity[1][3] = 0.110f;
	transforms[2] = identity;

	identity[0][3] = -0.055f;
	identity[1][3] = -0.110f;
	transforms[3] = identity;
}
