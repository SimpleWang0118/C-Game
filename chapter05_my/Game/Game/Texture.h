#pragma once
#include<string>
using namespace std;
class Texture
{
public:
	Texture();
	~Texture();

	bool Load(const string& filename);
	void Unload();
	void SetActive();

	int GetWidth()const { return mWidth; }
	int GetHeight()const { return mHeight; }
private:
	unsigned int mTextureID;
	int mWidth;
	int mHeight;

};