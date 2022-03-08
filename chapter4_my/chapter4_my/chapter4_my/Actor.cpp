#include"Actor.h"
#include"Game.h"
#include"Component.h"
#include<algorithm>
Actor::Actor(Game* game)
	:mScale(1.0f),
	mState(EActive),
	mPosition(Vector2::Zero),
	mRotation(0.0f),
	mGame(nullptr)

{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);
	while (!mComponent.empty())
	{
		delete mComponent.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == EActive)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponent)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ProcessInput(const uint8_t& keystate)
{
	if (mState == EActive)
	{
		for (auto comp : mComponent)
		{
			comp->ProcessInput(keystate);
		}
		ActorInput(keystate);
	}
}

void Actor::ActorInput(const uint8_t keystate)
{

}

void Actor::AddComponent(Component* component)
{
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponent.begin();
	for (; iter != mComponent.end(); iter++)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	mComponent.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = find(mComponent.begin(), mComponent.end(), component);
	if (iter != mComponent.end())
	{
		mComponent.erase(iter);
	}
}
