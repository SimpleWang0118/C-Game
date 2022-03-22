#include "Texture.h"
#include<glew.h>
Texture::Texture()
{
}

Texture::~Texture()
{
}

bool Texture::Load(const string& filename)
{
	return false;
}

void Texture::Unload()
{
}

void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}
