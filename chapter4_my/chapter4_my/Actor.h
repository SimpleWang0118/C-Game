#pragma once
#include<SDL.h>
#include"Math.h"
#include<cstdint>
#include<vector>

using namespace std;

class Actor
{
public:
	enum State
	{
		EActive,
		EPause,
		EDead
	};
	Actor(class Game* game);
	virtual ~Actor();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	void ProcessInput(const uint8_t* keystate);
	virtual void ActorInput(const uint8_t* keystate);

	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rot) { mRotation = rot; }

	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }
	
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	Vector2 mPosition;
	float mScale;
	float mRotation;
	State mState;
	class Game* mGame;
	vector<class Component*> mComponent;


};