#include"Actor.h"
#include"Game.h"
#include"Component.h"
#include<algorithm>

Actor::Actor(Game* game)
{
}

Actor::~Actor()
{
}

void Actor::Update(float DeltaTime)
{
}

void Actor::UpdateActor(float DeltaTime)
{
}

void Actor::UpdateComponent(float DeltaTime)
{
}

void Actor::ProcessInput(const uint8_t* keyState)
{
}

void Actor::ActorInput(const uint8_t* keyState)
{
}

void Actor::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;
		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateRotationZ(mRotation);
		mWorldTransform *= Matrix4::CreateTranslation(Vector3(mPosition.x, mPosition.y, 0.0f));

		for (auto comp : mComponent)
		{
			comp->OnUpdateWorldTransform();
		}
	}
}
