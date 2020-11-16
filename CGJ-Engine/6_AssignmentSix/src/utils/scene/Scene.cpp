#include "../../headers/scene/Scene.h"

Scene::Scene()
{
	srand((unsigned int)time(0));
}

SceneGraph* Scene::CreateSceneGraph()
{
	SceneGraph* newSceneGraph = new SceneGraph();
	sceneGraphs.push_back(newSceneGraph);

	return newSceneGraph;
}

SceneGraph* Scene::CreateSceneGraph(ArcBallCamera c)
{
	SceneGraph* newSceneGraph = new SceneGraph(c);
	sceneGraphs.push_back(newSceneGraph);

	return newSceneGraph;
}

std::vector<SceneGraph*> Scene::GetSceneGraphs()
{
	return sceneGraphs;
}

SceneGraph* Scene::SetupTetrominoSceneGraph(SceneGraph* sceneGraph,Mesh* m, Shader* s)
{
	//SceneNode* root = sceneGraph->AddNode(m, s, NULL, Vector3(1, 1, 1));
	return sceneGraph;
}

void Scene::ClearScene()
{
	sceneGraphs.clear();
}

void Scene::DrawSceneGraphs(bool ortho)
{
	for (SceneGraph* sceneGraph : sceneGraphs) {
		sceneGraph->DrawSceneGraph(ortho);
	}
}
