#include "GameObject.h"

GameObject::GameObject(Model& newModel, Material& newMaterial)
{
	model = &newModel;
	material = &newMaterial;
}

GameObject::~GameObject()
{
}

void GameObject::SetPostition(glm::vec3 newPostition)
{
	postition = newPostition;
	UpdateModel();
}

glm::vec3 GameObject::GetPostition()
{
	return postition;
}

void GameObject::SetScale(glm::vec3 newScale)
{
	scale = newScale;
	UpdateModel();
}

glm::vec3 GameObject::GetScale()
{
	return scale;
}

void GameObject::UpdateModel()
{
	transform = glm::mat4(1);
	transform = glm::translate(transform, postition);
	transform = glm::scale(transform, scale);
}

void GameObject::SetModel(glm::mat4 newModel)
{
	transform = newModel;
}

glm::mat4 GameObject::GetModel()
{
	return transform;
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw(glm::mat4& projection, glm::mat4& view)
{
	material->shader->setVec2("UvPos", UvPos);
	material->shader->setMat4("model", transform);
	model->Draw();
}
