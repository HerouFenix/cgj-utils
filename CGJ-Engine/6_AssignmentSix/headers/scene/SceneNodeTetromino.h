#pragma once
#include  <vector>
#include "../vectors/Vector4.h"
#include "../vectors/Vector3.h"
#include "../matrices/Matrix4.h"
#include "../drawing/Mesh.h"
#include "../drawing/Shader.h"
#include "../shapes/Tetromino.h"
#include "../drawing/Renderer.h"
#include "SceneNode.h"

// SCENE NODE CLASS
/// Class used to represent a Node on our Scene Graph
/// 
/// Each SceneNode has a Tetromino (holds local transform and colour) a world transform, a colour, and a pointer to a Mesh.

// Based on https://research.ncl.ac.uk/game/mastersdegree/graphicsforgames/scenegraphs/Tutorial%206%20-%20Scene%20Graphs.pdf

class SceneNodeTetromino : public SceneNode {
public:
	SceneNodeTetromino(Mesh* m = NULL, Shader* s = NULL, Tetromino t = NULL, Vector3 sc = Vector3(1,1,1));
	~SceneNodeTetromino();

	void Draw() override;

protected:
	Tetromino tetromino;
};