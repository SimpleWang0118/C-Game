#pragma once
#include"Component.h"
#include"AIState.h"
#include<unordered_map>
#include<string>
#include<SDL.h>
using namespace std;

class AIComponent :public Component
{
public:
	AIComponent(class Actor* owner);
	
	void Update(float deltaTime) override;
	void ChangeState(const string& name);

	void RigisterState(class AIState* state);
private:
	unordered_map<string, class AIState*> mStateMap;
	class AIState* mCurrentState;
};