#include"Actor.h"
#include"Game.h"
#include"Component.h"
#include<algorithm>

Actor::Actor(Game* game)
	:mState(EActive)
	,mPosition(Vector2::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
	,mGame(game)
	,mRecomputeWorldTransform(true)
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

void Actor::Update(float DeltaTime)
{
	if (mState == EActive)
	{
		ComputeWorldTransform();

		UpdateComponent(DeltaTime);
		UpdateActor(DeltaTime);
		ComputeWorldTransform();
	}
}

void Actor::UpdateActor(float DeltaTime)
{
}

void Actor::UpdateComponent(float DeltaTime)
{
	for (auto comp : mComponent)
	{
		comp->Update(DeltaTime);
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
