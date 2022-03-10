#pragma once

#include"Component.h"

class MoveComponent :public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTime) override;

	float GetForwardSpeed() const { return mForwardSpeed; }
	void  SetForwardSpeed(float speed) { mForwardSpeed = speed; }
	float GetAngularSpeed() const { return mAngularSpeed; }
	void  SetAngularSpeed(float speed) { mAngularSpeed = speed; }
private:
	float mForwardSpeed;
	float mAngularSpeed;
};