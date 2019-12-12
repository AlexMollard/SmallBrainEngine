#pragma once
#include "Texture.h"
#include "Shader.h"

struct PointLight {
	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class Material
{
public:
	Material(Shader* matShader, Texture* matDiffuse = nullptr, Texture* matSpecular = nullptr, float matShine = 0.3f);
	~Material();

	Shader* shader = nullptr;
	Texture* diffuse = nullptr;
	Texture* specular = nullptr;
	float shininess = 0.3f;
	bool hasPointLights = false;
};

