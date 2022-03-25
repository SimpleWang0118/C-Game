#include "MoveComponent.h"
#include"Actor.h"
MoveComponent::MoveComponent(Actor* owner, int updateOrder)
	:mAngularSpeed(0.0f)
	,mForwardSpeed(0.0f)
	,Component(owner,updateOrder)
{

}

void MoveComponent::Update(float DeltaTime)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		float rot = mOwner->GetRotation();
		rot += mAngularSpeed * DeltaTime;
		mOwner->SetRotation(rot);
	}
	if (Math::NearZero(mForwardSpeed))
	{
		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * DeltaTime;

		if (pos.x < -512.0f) {
			pos.x = 510.0f;
		}
		else if (pos.x > 521.0f) {
			pos.x = -510.0f;
		}

		if (pos.y < -384.0f) {
			pos.y = 382.0f;
		}
		else if (pos.y > 384.0f) {
			pos.y = -382.0f;
		}
		mOwner->SetPosition(pos);
	}
}
