#include"NavComponent.h"
#include"Component.h"


NavComponent::NavComponent(Actor* owner, int updateOrder)
	:mNextNode(nullptr)
{
}

void NavComponent::Update(float deltaTime)
{
	Vector2 diff = mOwner->GetPosition() - mNextNode->GetPosition();
	if (diff.Length() <= 2.0f)
	{
		mNextNode = mNextNode->GetParent();
		TurnTo(mNextNode->GetPosition());
	}
	MoveComponent::Update(deltaTime);
}

void NavComponent::StartPath(const Tile* start)
{
}

void NavComponent::TurnTo(const Vector2& pos)
{
	Vector2 dir = pos - mOwner->GetPosition();
	float angle = Math::Atan2(-dir.y, dir.x);
	mOwner->SetRotation(angle);
}
