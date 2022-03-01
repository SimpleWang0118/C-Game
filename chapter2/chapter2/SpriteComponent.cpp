#include"SpriteComponent.h"



SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
{
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect r;
		r.w = static_cast<int> (mTexWidth * mOwner->GetScale());
		r.h = static_cast<int> (mTexHeight*mOwner->GetState());
		r.x = static_cast<int> (mOwner->GetPosition().x-r.w/2);
		r.y = static_cast<int> (mOwner->GetPosition().y-r.h/2);

		SDL_RenderCopyEx(
			renderer,
			mTexture,
			nullptr,
			&r,
			-Math::ToDegrees(mOwner->GetRotation()),
			nullptr,
			SDL_FLIP_NONE
		)


	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
