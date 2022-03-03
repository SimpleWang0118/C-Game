#include"InputComponent.h"
#include"Actor.h"
InputComponent::InputComponent(class Actor* owner) :
MoveComponent(owner)
,mForwardKey(0)
,mBackKey(0)
,mClockwiseKey(0)
,mCounterClockwiseKey(0)
{

}
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
	if (keyState[mCounterClockwiseKey])
	{
		angularspeed -= mMaxAngularSpeed;
	}
}
