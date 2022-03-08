#pragma once
#include<cstdint>

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void Update(float deltaTime);
	virtual void ProcessInput(const uint8_t& keystate){}
	int GetUpdateOrder()const { return mUpdateOrder; }
private:
	class Actor* mOwner;
	int mUpdateOrder;
};