#pragma once
#include "BigBrainMath.h"
struct ShaderPROSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(std::string shaderDIR);
	~Shader();

	ShaderPROSource ParseShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	// Set Uniforms
	void setBool(const std::string &name, bool value) const;

	void setInt(const std::string &name, int value) const;

	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, glm::mat4 value) const;
	

	// Use this shader
	void use();

	//Uniforms
	GLuint shaderProgram;
};


