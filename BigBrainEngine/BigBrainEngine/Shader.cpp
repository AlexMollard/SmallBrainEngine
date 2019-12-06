#include "Shader.h"

Shader::Shader(std::string shaderDIR)
{
	ShaderPROSource source = ParseShader(shaderDIR);
	shaderProgram = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(shaderProgram);
}

ShaderPROSource Shader::ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::stringstream ss[2];
	std::string line;
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const GLchar* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* errorMessage = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, errorMessage);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "fragment") << "Shader" << std::endl;
		std::cout << errorMessage << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	int Success;
	glGetProgramiv(program, GL_LINK_STATUS, &Success);
	if (Success == GL_FALSE)
	{
		char errorMessage[128];
		int errorSize;
		glGetProgramInfoLog(program, 128, &errorSize, errorMessage);
		std::cout << "Error linking shader program:" << std::endl;
		std::cout << errorMessage << std::endl;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setMat4(const std::string & name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string & name, glm::vec3 value) const
{
	glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::use()
{
	glUseProgram(shaderProgram);
}