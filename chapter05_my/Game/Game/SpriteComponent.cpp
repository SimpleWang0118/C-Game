#include "SpriteComponent.h"
#include"Math.h"
#include"Actor.h"
#include"Shader.h"
#include"Texture.h"
#include"Game.h"
SpriteComponent::SpriteComponent(Actor* owner, int updateOrder)
	:Component(owner)
	,mTexture(nullptr)
	,mDrawOrder(updateOrder)
	,mTexWidth(0)
	,mTexHeight(0)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
	if (mTexture)
	{
		Matrix4 scaleMat = Matrix4::CreateScale(
			static_cast<float>(mTexWidth),
			static_cast<float>(mTexHeight),
			1.0f);
		Matrix4 world = scaleMat * mOwner->GetWorldTransform();

		shader->SetMatrixUniform("uWorldTransform", world);
		mTexture->SetActive();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}


}

void SpriteComponent::SetTexture( Texture* texture)
{
	mTexture = texture;

	mTexWidth = texture->GetWidth();
	mTexHeight = texture->GetHeight();
}
