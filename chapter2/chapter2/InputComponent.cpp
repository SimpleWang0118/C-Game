#include"InputComponent.h"

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	float forwardspeed = 0.0f;
	if (keyState[mForwardKey])
	{
		forwardspeed += mMaxForwardSpeed;
	}
	if (keyState[mBackKey])
	{
		forwardspeed -= mMaxForwardSpeed;
	}
	float angularspeed = 0.0f;
	if (keyState[mClockwiseKey])
	{
		angularspeed += mMaxAngularSpeed;
	}
	if (keyState[mCounterClockKey])
	{
		angularspeed -= mMaxAngularSpeed;
	}
}
