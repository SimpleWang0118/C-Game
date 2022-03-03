#include"Actor.h"
#include"Component.h"
#include"Game.h"
Actor::Actor(Game* game)
	:mState(EActive)
	, mPosition(Vector2::Zero)
	, mScale(1.0f)
	, mRotation(0.0f)
	, mGame(game)
{
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

void Actor::AddComponent(Component* component)
{
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponent.begin();
	for (; iter != mComponent.begin(); ++iter)
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
	auto iter = find(mComponent.begin(), mComponent.end(),component);
	if (iter != mComponent.end())
	{
		mComponent.erase(iter);
	}
}

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == EActive)
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
