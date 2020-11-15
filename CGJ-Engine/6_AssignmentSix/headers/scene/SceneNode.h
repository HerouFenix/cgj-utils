#pragma once
#include  <vector>
#include "../vectors/Vector4.h"
#include "../vectors/Vector3.h"
#include "../matrices/Matrix4.h"
#include "../drawing/Mesh.h"
#include "../drawing/Shader.h"
#include "../shapes/Tetromino.h"
#include "../drawing/Renderer.h"

// SCENE NODE CLASS
/// Class used to represent a Node on our Scene Graph
/// 
/// Each SceneNode has a Tetromino (holds local transform and colour) a world transform, a colour, and a pointer to a Mesh.

// Based on https://research.ncl.ac.uk/game/mastersdegree/graphicsforgames/scenegraphs/Tutorial%206%20-%20Scene%20Graphs.pdf

class SceneNode {
public:
	SceneNode(Mesh* m = NULL, Shader* s = NULL, Tetromino t = NULL);
	~SceneNode();

	void ApplyLocalTransform(Matrix4 transform);

	const Matrix4 GetLocalTransform();

	Matrix4 GetWorldTransform();

	void GetColour(float* colours);

	Mesh* GetMesh();
	void SetMesh(Mesh* m);

	Shader* GetShader();
	void SetShader(Shader* s);

	void AddChildNode(SceneNode* s);

	void Update();

	void Draw();

protected:
	SceneNode* parent;
	Mesh* mesh;
	Matrix4 worldTransform;
	Matrix4 localTransform;
	Tetromino tetromino;
	std::vector<SceneNode*> children;
	Shader* shader;
};