#include "GameObjectManager.h"



GameObjectManager::GameObjectManager(GraphicsManager& newGraphicManager)
{
	graphicManager = &newGraphicManager;
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Draw(glm::mat4 &projection, glm::mat4 &view)
{
	bool firstFrame = true;
	for (int i = 0; i < gameObjects.size(); i++)
	{
		Shader* currentShader = gameObjects[i]->material->shader;
		if (graphicManager->SetShader(*currentShader) || firstFrame)
		{
			currentShader->setMat4("projection", projection);
			currentShader->setMat4("view", view);
			firstFrame = false;
		}

		graphicManager->SetMaterial(*gameObjects[i]->material);
		gameObjects[i]->Draw(projection, view);
	}
}

void GameObjectManager::Update(float deltaTime)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update(deltaTime);
	}
}

void GameObjectManager::AddObject(GameObject &NewGameObject)
{
	gameObjects.push_back(&NewGameObject);
}
