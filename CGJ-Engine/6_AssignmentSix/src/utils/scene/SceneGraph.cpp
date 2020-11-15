#include "../../headers/scene/SceneGraph.h"

SceneGraph::SceneGraph(ArcBallCamera c)
{
	camera = c;
}

SceneGraph::~SceneGraph()
{
}

void SceneGraph::SetCamera(ArcBallCamera c)
{
	camera = c;
}

SceneNode* SceneGraph::GetRoot()
{
	return root;
}

SceneNode* SceneGraph::AddNode(Mesh* m, Shader* s, Tetromino t)
{
	SceneNode* newNode = new SceneNode(m, s, t);
	if (root == NULL) {
		root = newNode;
	}
	else {
		root->AddChildNode(newNode);
	}
	std::cout << root->GetShader() << "\n";

	return newNode;
}

void SceneGraph::DrawSceneGraph(bool ortho)
{
	camera.RenderCamera(ortho);
	if (root != NULL) {
		root->Draw();
	}
}
