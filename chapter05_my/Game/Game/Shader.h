#pragma once

#include<glew.h>
#include<string>
#include"Math.h"

using namespace std;
class Shader
{
public:
	Shader();
	~Shader();

	bool Load(const string& vertName, const string fragName);
	void Unload();
	void SetActive();
	void SetMatrixUniform(const char* name, const Matrix4& matrix);
private:
	bool CompileShader(const string& filename, GLenum shaderType, GLuint outShader);
	bool IsCompiled(GLuint shader);
	bool IsValidProgram();
private:
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};
