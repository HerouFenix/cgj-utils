#include "../../headers/scene/SceneNode.h"


SceneNode::SceneNode(Mesh* m, Shader* s, Tetromino t) {
	mesh = m;
	tetromino = t;
	parent = NULL;
	shader = s;

	worldTransforms[0] = Matrix4::identity();
	worldTransforms[1] = Matrix4::identity();
	worldTransforms[2] = Matrix4::identity();
	worldTransforms[3] = Matrix4::identity();

}

SceneNode::~SceneNode()
{
	for (unsigned int i = 0; i < children.size(); ++i) {
		delete  children[i];
	}
}

void SceneNode::ApplyLocalTransform(const Matrix4 transform)
{
	tetromino.transform(transform);
}

const Matrix4* SceneNode::GetLocalTransforms()
{
	return tetromino.getTransforms();
}

Matrix4* SceneNode::GetWorldTransforms()
{
	return worldTransforms;
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
		for (int j = 0; j < 4; j++) {
			worldTransforms[j] = parent->worldTransforms[j] * tetromino.getTransforms()[j];
		}
	}
	else { // If we are the root node
		for (int j = 0; j < 4; j++) {
			worldTransforms[j] = tetromino.getTransforms()[j];
		}
	}

	// Cascade Update children
	for (SceneNode* child : children) {
		(*child).Update();
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
		tetromino.getTransforms()[j].getRowMajor(model);
		Renderer::DrawObject((GLsizei)mesh->getVertices().size(), (*shader), model);
	}

	// Cascade Draw children
	for (SceneNode* child : children) {
		child->Draw();
	}
}
