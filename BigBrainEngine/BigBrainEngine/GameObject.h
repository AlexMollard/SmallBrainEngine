#pragma once
#include "BigBrainMath.h"
#include "Model.h"
#include "Material.h"
class GameObject
{
public:
	GameObject(Model* newModel, Material* newMaterial);
	~GameObject();
	
	Model* model = nullptr;
	Material* material = nullptr;

	glm::vec3 postition = glm::vec3(0);
	glm::vec2 UvPos = glm::vec2(0.0f,0.0f);
	glm::vec3 scale = glm::vec3(1);;
	glm::mat4 transform = glm::mat4(1);;

	void SetPostition(glm::vec3 newPostition);
	glm::vec3 GetPostition();

	void SetScale(glm::vec3 newScale);
	glm::vec3 GetScale();

	void UpdateModel();

	void SetModel(glm::mat4 newModel);
	glm::mat4 GetModel();

	void Update(float deltaTime);
	void Draw();
};

