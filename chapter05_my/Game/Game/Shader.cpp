#include "Shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{
}

bool Shader::Load(const string& vertName, const string fragName)
{
	return false;
}

void Shader::Unload()
{
	glDeleteProgram(mShaderProgram);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragShader);
}

void Shader::SetActive()
{
	glUseProgram(mShaderProgram);
}

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr());
}

bool Shader::CompileShader(const string& filename, GLenum shaderType, GLuint outShader)
{
	return false;
}

bool Shader::IsCompiled(GLuint shader)
{
	return false;
}

bool Shader::IsValidProgram()
{
	return false;
}
