#include"AIComponent.h"

AIComponent::AIComponent(Actor* owner)
	:Component(owner)
	,mCurrentState(nullptr)
{
}

void AIComponent::Update(float deltaTime)
{
	if (mCurrentState)
	{
		mCurrentState->Update(deltaTime);
	}
}

void AIComponent::ChangeState(const string& name)
{
	if (mCurrentState)
	{
		mCurrentState->OnExit();
	}

	auto iter = mStateMap.find(name);
	if (iter != mStateMap.end())
	{
		mCurrentState = iter->second;
		mCurrentState->OnEnter();
	}
	else
	{
		SDL_Log("could't find AIState %s in state map", name.c_str());
		mCurrentState = nullptr;
	}
}

void AIComponent::RigisterState(AIState* state)
{
	mStateMap.emplace(state->GetName(), state);
}
