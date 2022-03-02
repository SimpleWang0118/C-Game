#pragma once
#include"MoveComponent.h"

class InputComponent :public MoveComponent
{
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;
private:
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;

	int mForwardKey;
	int mBackKey;
	int mClockwiseKey;
	int mCounterClockKey;
};