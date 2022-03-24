#pragma once
#include<cstdint>

class Component
{
public:
	Component(class Actor* owner, int UpdateOrder = 100);

	virtual ~Component();
	virtual void Update(float DeltaTime);
	virtual void ProcessInput(const uint8_t* keyState){}
	virtual void OnUpdateWorldTransform(){}
	int GetUpdateOrder()const { return mUpdateOrder; }
protected:
	class Actor* mOwner;
	int mUpdateOrder;

}