#include "GraphicsManager.h"



GraphicsManager::GraphicsManager()
{

}


GraphicsManager::~GraphicsManager()
{
}

Shader GraphicsManager::GetShader(int shaderIndex)
{
	return *shaders[shaderIndex];
}

void GraphicsManager::AddShader(Shader *newShader)
{
	shaders.push_back(newShader);
}

bool GraphicsManager::SetShader(Shader * newShader)
{
	if (LastShader == newShader)
	{
		return false;
	}

	newShader->use();
	LastShader = newShader;
	return true;
}

Material GraphicsManager::GetMaterial(int materialIndex)
{
	return *materials[materialIndex];
}

void GraphicsManager::AddMaterial(Material *newMaterial)
{
	materials.push_back(newMaterial);
}

bool GraphicsManager::SetMaterial(Material * newMaterial)
{
	// Broken because text renderer isnt a object
	if (LastMaterial == newMaterial)
	{
		return false;
	}

	if (newMaterial->diffuse == nullptr)
	{
		LastMaterial = newMaterial;
		return false;
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, newMaterial->diffuse->imageID);

	LastMaterial = newMaterial;
	return true;
}

Model GraphicsManager::GetModel(int modelIndex)
{
	return *models[modelIndex];
}

void GraphicsManager::AddModel(Model * newModel)
{
	if (std::find(models.begin(), models.end(), newModel) != models.end())
	{
		return;
	}

	models.push_back(newModel);
}

bool GraphicsManager::SetModel(Model * newModel)
{
	if (LastModel == newModel)
	{
		return false;
	}

}
