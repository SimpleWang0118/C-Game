#pragma once
#include"SpriteComponent.h"

class BGSpriteComponent:public SpriteComponent
{
public:
	BGSpriteComponent(class Actor* owner, int drawOrder = 100);
	~BGSpriteComponent();
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	void SetBGTextures(vector<SDL_Texture*>& textures);
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeend(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const {
		return mScrollSpeed;
	}

private:
	struct BGTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;

};
