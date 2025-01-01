#include "Shader.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>




Shader::Shader(const std::filesystem::path& filepath) :
	m_id(0), m_FilePath(filepath)
{
	ShaderSource source = ParseShader(m_FilePath);
	m_id = CreateShader(source.VertextShaderSource, source.FragmentShaderSource);
}

Shader::~Shader()
{
	glDeleteProgram(m_id);
}

void Shader::Bind() const
{
	glUseProgram(m_id);
}

void Shader::UnBind() const
{
	glUseProgram(0);
}

ShaderSource Shader::ParseShader(const std::filesystem::path& filepath)
{
	std::ifstream file(filepath);


	if (!file)
	{
		std::cerr << "Error: Can't open file " << filepath << std::endl; 
		std::exit(-1);
	}

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream sstr[2];
	ShaderType type = ShaderType::NONE;

	while (std::getline(file, line))
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
			sstr[(int)type] << line << "\n";
		}

	}

	return { sstr[0].str(), sstr[1].str() };
}

GLuint Shader::CompileShader(GLuint Type, const std::string& source)
{
	GLuint id = glCreateShader(Type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);


	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (Type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

GLuint Shader::CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
{
	GLuint program = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, VertexShader);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);


	return program;
}





