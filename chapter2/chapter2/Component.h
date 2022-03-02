#pragma once
#include<cstdint>

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }
	virtual void ProcessInput(const uint8_t* keyState){}
protected:
	class Actor* mOwner;
	int mUpdateOrder;
};
