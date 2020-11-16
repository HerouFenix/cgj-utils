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

void Scene::SetupTetrominoSceneGraph(SceneGraph* sceneGraph,Mesh* m, Shader* s)
{
	//Floor
	//SceneNode* root = sceneGraph.AddNode(&mesh, &shader, NULL, Vector3(1, 0.01, 1));
	//root->ApplyLocalTransform(Matrix4::translation(0, -0.44, 0));
	//
	//Tetromino_SQ sq;
	//SceneNode* square = sceneGraph.AddNode(&mesh, &shader, sq, Vector3(0.1, 0.1, 0.1));
	//square->ApplyLocalTransform(Matrix4::translation(-0.11, 0.33, 0));
	//
	//Tetromino_L l;
	//SceneNode* letterL = sceneGraph.AddNode(&mesh, &shader, l, Vector3(0.1, 0.1, 0.1));
	//letterL->ApplyLocalTransform(Matrix4::translation(-0.33, 0.11, 0));
	//
	//Tetromino_RL rl;
	//SceneNode* letterRL = sceneGraph.AddNode(&mesh, &shader, rl, Vector3(0.1, 0.1, 0.1));
	//letterRL->ApplyLocalTransform(Matrix4::translation(0.33, 0.11, 0));
	//
	//Tetromino_I i;
	//SceneNode* letterI = sceneGraph.AddNode(&mesh, &shader, i, Vector3(0.1, 0.1, 0.1));
	//letterI->ApplyLocalTransform(Matrix4::rotationZ(90, false, true));
	//letterI->ApplyLocalTransform(Matrix4::translation(0.33, 0.77, 0));

	//Floor
	SceneNode* root = sceneGraph->AddNode(m, s, NULL, Vector3(1, 0.01, 1));
	root->ApplyLocalTransform(Matrix4::translation(0, -0.44, 0));

	float colour[4];

	//Square
	SceneNode* squareBase = sceneGraph->AddNode(m, s, NULL, Vector3(0.1, 0.1, 0.1));
	squareBase->GetColour(colour);
	squareBase->ApplyLocalTransform(Matrix4::translation(-0.11, 0.44, 0));
	SceneNode* squareTwo = sceneGraph->AddNode(m, s, squareBase, colour, Vector3(0.1, 0.1, 0.1));
	squareTwo->ApplyLocalTransform(Matrix4::translation(0, 0.22, 0));
	SceneNode* squareThree = sceneGraph->AddNode(m,s, squareBase, colour, Vector3(0.1, 0.1, 0.1));
	squareThree->ApplyLocalTransform(Matrix4::translation(0.22, 0.22, 0));
	SceneNode* squareFour = sceneGraph->AddNode(m,s, squareBase, colour, Vector3(0.1, 0.1, 0.1));
	squareFour->ApplyLocalTransform(Matrix4::translation(0.22, 0, 0));

	// L
	SceneNode* lBase = sceneGraph->AddNode(m, s, NULL, Vector3(0.1, 0.1, 0.1));
	lBase->GetColour(colour);
	lBase->ApplyLocalTransform(Matrix4::translation(-0.33, 0.22, 0));
	SceneNode* lTwo = sceneGraph->AddNode(m, s, lBase, colour, Vector3(0.1, 0.1, 0.1));
	lTwo->ApplyLocalTransform(Matrix4::translation(0, 0.22, 0));
	SceneNode* lThree = sceneGraph->AddNode(m, s, lBase, colour, Vector3(0.1, 0.1, 0.1));
	lThree->ApplyLocalTransform(Matrix4::translation(0, 0.44, 0));
	SceneNode* lFour = sceneGraph->AddNode(m, s, lBase, colour, Vector3(0.1, 0.1, 0.1));
	lFour->ApplyLocalTransform(Matrix4::translation(0.22, 0, 0));

	// Reverse L
	SceneNode* rlBase = sceneGraph->AddNode(m, s, NULL, Vector3(0.1, 0.1, 0.1));
	rlBase->GetColour(colour);
	rlBase->ApplyLocalTransform(Matrix4::translation(0.33, 0.22, 0));
	SceneNode* rlTwo = sceneGraph->AddNode(m, s, rlBase, colour, Vector3(0.1, 0.1, 0.1));
	rlTwo->ApplyLocalTransform(Matrix4::translation(0, 0.22, 0));
	SceneNode* rlThree = sceneGraph->AddNode(m, s, rlBase, colour, Vector3(0.1, 0.1, 0.1));
	rlThree->ApplyLocalTransform(Matrix4::translation(0, 0.44, 0));
	SceneNode* rlFour = sceneGraph->AddNode(m, s, rlBase, colour, Vector3(0.1, 0.1, 0.1));
	rlFour->ApplyLocalTransform(Matrix4::translation(-0.22, 0, 0));

	// I
	SceneNode* iBase = sceneGraph->AddNode(m, s, NULL, Vector3(0.1, 0.1, 0.1));
	iBase->GetColour(colour);
	iBase->ApplyLocalTransform(Matrix4::rotationZ(90, false, true));
	iBase->ApplyLocalTransform(Matrix4::translation(0.33, 0.88, 0));

	SceneNode* iTwo = sceneGraph->AddNode(m, s, iBase, colour, Vector3(0.1, 0.1, 0.1));
	iTwo->ApplyLocalTransform(Matrix4::translation(0, 0.22, 0));
	SceneNode* iThree = sceneGraph->AddNode(m, s, iBase, colour, Vector3(0.1, 0.1, 0.1));
	iThree->ApplyLocalTransform(Matrix4::translation(0, 0.44, 0));
	SceneNode* iFour = sceneGraph->AddNode(m, s, iBase, colour, Vector3(0.1, 0.1, 0.1));
	iFour->ApplyLocalTransform(Matrix4::translation(0, 0.66, 0));
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
