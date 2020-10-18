#include "..\..\..\headers\scene\SceneManager.h"
#include <cstdlib>  
#include <ctime> 

SceneManager::SceneManager()
{
	srand(time(0));
}

std::vector<Tetromino> SceneManager::getPieces()
{
	return sceneShapes;
}

int SceneManager::getSize()
{
	return currentSize;
}

Tetromino SceneManager::getPieceAt(int index)
{
	return sceneShapes.at(index);
}

int SceneManager::createLPiece(float colour[4], Vector4 center)
{
	sceneShapes.push_back(Tetromino_L(colour, center));
	currentSize++;

	return currentSize - 1;
}

int SceneManager::createLPiece(Vector4 center)
{
	sceneShapes.push_back(Tetromino_L(center));
	currentSize++;

	return currentSize - 1;
}

int SceneManager::createRLPiece(float colour[4], Vector4 center)
{
	sceneShapes.push_back(Tetromino_RL(colour, center));
	currentSize++;

	return currentSize - 1;
}

int SceneManager::createRLPiece(Vector4 center)
{
	sceneShapes.push_back(Tetromino_RL(center));
	currentSize++;

	return currentSize - 1;
}

int SceneManager::createIPiece(float colour[4], Vector4 center)
{
	sceneShapes.push_back(Tetromino_I(colour, center));
	currentSize++;

	return currentSize - 1;
}

int SceneManager::createIPiece(Vector4 center)
{
	sceneShapes.push_back(Tetromino_I(center));
	currentSize++;

	return currentSize - 1;
}

int SceneManager::createSQPiece(float colour[4], Vector4 center)
{
	sceneShapes.push_back(Tetromino_SQ(colour, center));
	currentSize++;

	return currentSize - 1;
}

int SceneManager::createSQPiece(Vector4 center)
{
	sceneShapes.push_back(Tetromino_SQ(center));
	currentSize++;

	return currentSize - 1;
}

void SceneManager::transformPiece(int index, Matrix4 mat)
{
	sceneShapes.at(index).transform(mat);
}

void SceneManager::clearScene()
{
	sceneShapes.clear();
	currentSize = 0;
}
