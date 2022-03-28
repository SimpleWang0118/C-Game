#include "Shader.h"
#include<SDL.h>
#include"Texture.h"
#include<fstream>
#include<sstream>
#include<iostream>
Shader::Shader()
	:mShaderProgram(0)
	,mVertexShader(0)
	,mFragShader(0)
{
}

Shader::~Shader()
{
}

bool Shader::Load(const string& vertName, const string& fragName)
{

	if (!CompileShader(vertName, GL_VERTEX_SHADER, mVertexShader) || !CompileShader(fragName,
		GL_FRAGMENT_SHADER,
		mFragShader))
	{
		return false;
	}

	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragShader);
	glLinkProgram(mShaderProgram);

	if (!IsValidProgram())
	{
		return false;
	}
	return true;
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

bool Shader::CompileShader(const string& filename, GLenum shaderType, GLuint& outShader)
{
	cout << "4444" << endl;
	ifstream shaderFile(filename);
	if (shaderFile.is_open())
	{
		stringstream sstream;
		sstream << shaderFile.rdbuf();
		string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		outShader = glCreateShader(shaderType);
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);

		if (!IsCompiled(outShader))
		{

			SDL_Log("Failed to compile shader %s", filename.c_str());
			return false;
		}
	}
	else
	{

		SDL_Log("shader file not found:%s", filename.c_str());
		return false;
	}
	return true;
}

bool Shader::IsCompiled(GLuint shader)
{
	cout << "7777" << endl;
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		cout << "8888" << endl;
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("GLSL Compile failed:%s", buffer);
		return false;
	}
	cout << "9999" << endl;
	return true;
}

bool Shader::IsValidProgram()
{
	GLint status;
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
		SDL_Log("GLSL LINK STATUS:%s", buffer);
		return false;
	}
	return true;
}




