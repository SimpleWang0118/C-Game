#include "Component.h"
#include "Actor.h"
Component::Component(Actor* owner, int UpdateOrder)
	:mOwner(owner)
	,mUpdateOrder(UpdateOrder)
{
	mOwner->AddComponent(this);
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

void Component::Update(float DeltaTime)
{

}
