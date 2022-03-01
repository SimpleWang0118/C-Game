#pragma once
#include"SpriteComponent.h"
#include<vector>
using namespace std;

class AnimSpriteComponent:public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder =100);
	void Update(float deltaTime) override;
	void setAnimTexture(const vector<SDL_Texture*>& texture);
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }
private:
	vector<SDL_Texture*> mAnimTextures;
	float mAnimFPS;
	float mCurrentFrame;
};
