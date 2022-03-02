#include"MoveComponent.h"
#include"Actor.h"
void MoveComponent::Update(float deltaTime)
{
	if (!(Math::NearZero(mAngularSpeed)))
	{
		float rot = mOwner->GetRotation();
		rot += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rot);
	}
	if (!(Math::NearZero(mForwardSpeed)))
	{
		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
		mOwner->SetPosition(pos);
	}
}
