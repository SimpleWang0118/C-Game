#pragma once
#include<vector>
#include<cstdint>
#include"Math.h"
using namespace std;
class Actor
{
public:
	enum State
	{
		Eactive,
		EPaused,
		EDead
	};
	Actor(class Game* game);
	virtual ~Actor();
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
	State GetState() const { return mState; }
	float GetScale() const { return mScale; }
	const Vector2& GetPosition() const { return mPosition; }
	float GetRotation() const { return mRotation; }
	void SetPosition(const Vector2& pos) { mPosition = pos; };
private:
	State mState;
	Vector2 mPosition;
	float mScale;
	float mRotation;
	vector<class Component* > mComponent;
	class Game* game;
};