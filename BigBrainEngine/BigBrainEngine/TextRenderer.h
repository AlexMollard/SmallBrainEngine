#pragma once
#include "BigBrainMath.h"
#include <ft2build.h>
#include <map>
#include FT_FREETYPE_H
#include "GraphicsManager.h"

struct Character {
	GLuint TextureID;  
	glm::ivec2 Size;   
	glm::ivec2 Bearing;
	GLuint Advance;    
};

class TextRenderer
{
public:
	TextRenderer();
	~TextRenderer();

	GLuint VAO, VBO;
	void RenderText(Shader* shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color = glm::vec3(0, 0, 0));

	std::map<GLchar, Character> Characters;
	glm::mat4 projection;
};

