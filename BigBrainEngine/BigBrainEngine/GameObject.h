#pragma once
#include "BigBrainMath.h"
#include "Model.h"
class GameObject
{
public:
	GameObject(Model* newModel, Texture* newTexture, Shader* newShader);
	~GameObject();
	
	Model* model;
	Shader* shader;
	Texture* texture;

	glm::vec3 postition = glm::vec3(0);
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
	void Draw(glm::mat4* projection, glm::mat4* view);
};

