#include"Actor.h"
#include"Component.h"
Actor::Actor(Game* game)
{
}

Actor::~Actor()
{
}

void Actor::Update(float deltaTime)
{
}

void Actor::UpdateComponents(float deltaTime)
{
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(Component* component)
{
}

void Actor::RemoveComponent(Component* component)
{
}

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == Eactive)
	{
		for (auto comp : mComponent)
		{
			comp->ProcessInput(keyState);
		}
		ActorInput(keyState);
	}
}
void Actor::ActorInput(const uint8_t* keyState)
{
}
