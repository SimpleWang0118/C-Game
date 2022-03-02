#include"AnimSpriteComponent.h"

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	if (mAnimTextures.size() > 0)
	{
		mCurrentFrame += mAnimFPS * deltaTime;

		while (mCurrentFrame >= mAnimTextures.size())
		{
			mCurrentFrame -= mAnimTextures.size();
		}
		SetTexture(mAnimTextures[static_cast<int>(mCurrentFrame)]);
	}
}
