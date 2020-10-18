#ifndef TETROMINO
#define TETROMINO

// Tetromino I CLASS HEADER
/// Class used to create, manipulate and draw a Tetromino I shape
#include<iostream>

#include <cstdlib>  
#include <ctime> 

#include "../vertex/Vertex.h"

#include "../vectors/Vector4.h"
#include "../matrices/Matrix4.h"

class Tetromino {
protected:
	Vertex vertices[4];	// Vertices of the base square
	Matrix4 transforms[4];	// Transform matrices used to draw entire shape
	unsigned char indices[4] = { 0,1,2,3 };
public: 
	// FUNCTION DECLARATIONS
	/********************************************/ /**
	* Creates a new Tetromino
	* @param colour - An int array containing information on R,G,B,A. Values should range from 0 to 255.
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	***********************************************/
	Tetromino(float colour[4], Vector4 center = Vector4());

	/********************************************/ /**
	* Creates a new Tetromino with a random colour
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	***********************************************/
	Tetromino(Vector4 center = Vector4());

	/********************************************/ /**
	* Returns this shape's vertices information
	* @return vertices - An array of Vertex structs. Each vertex contains a position (Vector4) and colour array (int array)
	***********************************************/
	Vertex* getVertices();

	/********************************************/ /**
	* Copies this shape's vertices information into the passed array
	***********************************************/
	void getVertices(Vertex arr[4]);

	/********************************************/ /**
	* Returns this shape's index buffer
	* @return indices - An array of unsigned ints containing the base shape's indices
	***********************************************/
	unsigned char* getIndices();

	/********************************************/ /**
	* Copies this shape's index buffer into given array
	* @return indices - An array of unsigned ints containing the base shape's indices
	***********************************************/
	void getIndices(unsigned char arr[4]);

	/********************************************/ /**
	* Returns this shape's transform matrices needed to draw the shape from it's primary square
	* @return transforms - An array of Matrix 4 for each square of the shape
	***********************************************/
	Matrix4* getTransforms();

	/********************************************/ /**
	* Applies a transformation to the shape as specified by the given matrix 4
	* @param transformMatrix - The matrix 4 that specifies the transformation to be applied
	***********************************************/
	void transform(Matrix4 transformMatrix);

	/********************************************/ /**
	* Resets all transformations made
	***********************************************/
	void reset();
};

class Tetromino_I: public Tetromino {
public:
	// FUNCTION DECLARATIONS
	/********************************************/ /**
	* Creates a new Tetromino I
	* @param colour - An int array containing information on R,G,B,A. Values should range from 0 to 255.
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	***********************************************/
	Tetromino_I(float colour[4], Vector4 center = Vector4());

	/********************************************/ /**
	* Creates a new Tetromino I with a random colour
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	***********************************************/
	Tetromino_I(Vector4 center = Vector4());

	/********************************************/ /**
	* Resets all transformations made
	***********************************************/
	void reset();

};

class Tetromino_L : public Tetromino {
public:
	// FUNCTION DECLARATIONS
	/********************************************/ /**
	* Creates a new Tetromino L
	* @param colour - An int array containing information on R,G,B,A. Values should range from 0 to 255.
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	***********************************************/
	Tetromino_L(float colour[4], Vector4 center = Vector4());

	/********************************************/ /**
	* Creates a new Tetromino L with a random colour
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	***********************************************/
	Tetromino_L(Vector4 center = Vector4());

	/********************************************/ /**
	* Resets all transformations made
	***********************************************/
	void reset();

};

class Tetromino_RL : public Tetromino {
public:
	// FUNCTION DECLARATIONS
	/********************************************/ /**
	* Creates a new Tetromino Reverse L
	* @param colour - An int array containing information on R,G,B,A. Values should range from 0 to 255.
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	***********************************************/
	Tetromino_RL(float colour[4], Vector4 center = Vector4());

	/********************************************/ /**
	* Creates a new Tetromino Reverse L with a random colour
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	***********************************************/
	Tetromino_RL(Vector4 center = Vector4());

	/********************************************/ /**
	* Resets all transformations made
	***********************************************/
	void reset();

};

class Tetromino_SQ : public Tetromino {
public:
	// FUNCTION DECLARATIONS
	/********************************************/ /**
	* Creates a new Tetromino Square
	* @param colour - An int array containing information on R,G,B,A. Values should range from 0 to 255.
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	***********************************************/
	Tetromino_SQ(float colour[4], Vector4 center = Vector4());

	/********************************************/ /**
	* Creates a new Tetromino Square with a random colour
	* @param center - A Vector4 specifying the center position of the shape. (0,0,0,0) by default
	***********************************************/
	Tetromino_SQ(Vector4 center = Vector4());

	/********************************************/ /**
	* Resets all transformations made
	***********************************************/
	void reset();

};

#endif