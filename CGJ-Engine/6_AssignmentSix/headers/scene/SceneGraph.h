#pragma once
#include "../camera/ArcBallCamera.h"
#include "SceneNode.h"

class SceneGraph {
private:
	SceneNode* root;
public:
	ArcBallCamera camera;

	SceneGraph(ArcBallCamera c = NULL);
	~SceneGraph();

	void SetCamera(ArcBallCamera c);

	SceneNode* GetRoot();

	SceneNode* AddNode(Mesh* m, Shader* s, Tetromino t);

	void DrawSceneGraph(bool ortho = false);
};