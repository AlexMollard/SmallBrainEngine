#include "Material.h"



Material::Material(Shader* matShader, Texture* matDiffuse, Texture* matSpecular, float matShine)
{
	shader = matShader;
	diffuse = matDiffuse;
	specular = matSpecular;
	shininess = matShine;
}


Material::~Material()
{
}
