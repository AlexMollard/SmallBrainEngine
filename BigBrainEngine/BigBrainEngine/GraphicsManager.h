#pragma once
#include "Material.h"
#include "Model.h"
class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();

	std::vector<Material*> materials;
	std::vector<Shader*> shaders;
	std::vector<Model*> models;

	Shader* LastShader = nullptr;
	Material* LastMaterial = nullptr;
	Model* LastModel = nullptr;

	Shader GetShader(int shaderIndex);
	void AddShader(Shader& newShader);
	bool SetShader(Shader& newShader);

	Material GetMaterial(int materialIndex);
	void AddMaterial(Material& newMaterial);
	bool SetMaterial(Material& newMaterial);

	Model GetModel(int modelIndex);
	void AddModel(Model& newModel);
	bool SetModel(Model& newModel);

};

