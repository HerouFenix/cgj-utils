#include "../../headers/scene/SceneNode.h"


SceneNode::SceneNode(Mesh* m, Shader* s, Tetromino t) {
	mesh = m;
	tetromino = t;
	parent = NULL;
	shader = s;

	localTransform = Matrix4::identity();

	if (parent != NULL) { // If we have a parent
		worldTransform = parent->worldTransform;

	}
	else { // If we are the root node
		worldTransform = localTransform;

	}
}

SceneNode::~SceneNode()
{
	for (unsigned int i = 0; i < children.size(); ++i) {
		delete  children[i];
	}
}

void SceneNode::ApplyLocalTransform(Matrix4 transform)
{

	localTransform = transform * localTransform;
	Update();
}

const Matrix4 SceneNode::GetLocalTransform()
{
	return localTransform;
}

Matrix4 SceneNode::GetWorldTransform()
{
	return worldTransform;
}

void SceneNode::GetColour(float* colours)
{
	return tetromino.getColours(colours);
}

Mesh* SceneNode::GetMesh()
{
	return mesh;
}

void SceneNode::SetMesh(Mesh* m)
{
	mesh = m;
}

Shader* SceneNode::GetShader()
{
	return shader;
}

void SceneNode::SetShader(Shader* s)
{
	shader = s;
}

void SceneNode::AddChildNode(SceneNode* s)
{
	children.push_back(s);
	s->parent = this;
}

void SceneNode::Update()
{
	if (parent != NULL) { // If we have a parent
		worldTransform = localTransform * parent->worldTransform;

	}
	else { // If we are the root node
		worldTransform = localTransform;
	}

	// Cascade Update children
	for (SceneNode* child : children) {
		child->Update();
	}
}

void SceneNode::Draw()
{
	float colours[4];

	shader->Bind();
	tetromino.getColours(colours);

	shader->SetUniform4fvec("uniformColour", colours);
	shader->UnBind();

	//Draw each square that makes up the piece using the transform matrices
	for (int j = 0; j < 4; j++) {
		float model[16];
		Matrix4 modelM = worldTransform * tetromino.getTransforms()[j];
		modelM.getRowMajor(model);
		Renderer::DrawObject((GLsizei)mesh->getVertices().size(), (*shader), model);
	}

	// Cascade Draw children
	for (SceneNode* child : children) {
		child->Draw();
	}
}
