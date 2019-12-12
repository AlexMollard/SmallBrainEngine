#pragma once
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "GraphicsManager.h"
#include "GameObjectManager.h"
#include "TextRenderer.h"

class GameController
{
public:
	GameController(Camera* camera);
	~GameController();

	GraphicsManager* graphicManager = nullptr;
	GameObjectManager* gameObjectManager = nullptr;

	void Update(float deltaTime, glm::mat4* projection, glm::mat4* view);
	void Draw(glm::mat4* projection, glm::mat4* view);
	void GetFPS();

	Camera* camera = nullptr;
	TextRenderer* textRenderer = nullptr;
	Shader* lightingShader = nullptr;
	Shader* lightShader = nullptr;
	Shader* textShader = nullptr;
	Texture* texture = nullptr;
	Texture* texture2 = nullptr;
	Material* planeMat = nullptr;
	Material* lightMat = nullptr;
	Material* textMat = nullptr;
	Model* hexModel = nullptr;
	Model* plane = nullptr;
	std::vector<GameObject*> tempObjects;

	//FPS stuff
	double previousTime;
	int frameCount = 0;
	int FPS = 0;
};

