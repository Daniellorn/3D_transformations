#pragma once

#include <glad/glad.h>
#include <string>
#include <cstdint>
#include <filesystem>

struct ShaderSource
{
	std::string VertextShaderSource{};
	std::string FragmentShaderSource{};

	ShaderSource(const std::string& _VertexShaderSource, const std::string& _FragmentShaderSource):
		VertextShaderSource(_VertexShaderSource), FragmentShaderSource(_FragmentShaderSource)
	{}
};


class Shader
{
public:

	Shader(const std::filesystem::path& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

private:

	ShaderSource ParseShader(const std::filesystem::path& filepath);
	GLuint CompileShader(GLuint Type, const std::string& source);
	GLuint CreateShader(const std::string& VertexShader, const std::string& FragmentShader);

private:
	GLuint m_id;
	std::filesystem::path m_FilePath;

};