#include "../../headers/scene/SceneNode.h"


SceneNode::SceneNode(Mesh* m, Shader* s, float* c, Vector3 sc) {
	mesh = m;
	if (c == NULL) {
		float r = (float)(rand() % 256) / 255;
		float g = (float)(rand() % 256) / 255;
		float b = (float)(rand() % 256) / 255;

		colour[0] = r;
		colour[1] = g;
		colour[2] = b;
		colour[3] = 1.0f;
	}
	else {
		colour[0] = c[0];
		colour[1] = c[1];
		colour[2] = c[2];
		colour[3] = c[3];
	}

	parent = NULL;
	shader = s;
	scale = sc;

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
	colours[0] = colour[0];
	colours[1] = colour[1];
	colours[2] = colour[2];
	colours[3] = colour[3];
}

void SceneNode::SetColour(float* colours)
{
	colour[0] = colours[0];
	colour[1] = colours[1];
	colour[2] = colours[2];
	colour[3] = colours[3];
}

Mesh* SceneNode::GetMesh()
{
	return mesh;
}

void SceneNode::SetMesh(Mesh* m)
{
	mesh = m;
}

Vector3 SceneNode::GetScale()
{
	return scale;
}

void SceneNode::SetScale(Vector3 sc)
{
	scale = sc;
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
	Update();
}

void SceneNode::Update()
{
	if (parent != NULL) { // If we have a parent
		worldTransform = parent->worldTransform*localTransform;

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
	shader->Bind();

	shader->SetUniform4fvec("uniformColour", colour);
	shader->UnBind();


	Matrix4 scaleM = Matrix4::scaling(scale.getX(), scale.getY(), scale.getZ());

	float model[16];
	Matrix4 modelM = worldTransform * scaleM;
	modelM.getRowMajor(model);
	Renderer::DrawObject((GLsizei)mesh->getVertices().size(), (*shader), model);


	// Cascade Draw children
	for (SceneNode* child : children) {
		child->Draw();
	}
}
