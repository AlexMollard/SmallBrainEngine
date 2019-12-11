#pragma once
#include "GameObject.h"
#include "GraphicsManager.h"
class GameObjectManager
{
public:
	GameObjectManager(GraphicsManager& newGraphicManager);
	~GameObjectManager();

	GraphicsManager* graphicManager;
	std::vector<GameObject*> gameObjects;
	void Draw(glm::mat4& projection, glm::mat4& view);
	void Update(float deltaTime);
	void AddObject(GameObject& NewGameObject);
};

