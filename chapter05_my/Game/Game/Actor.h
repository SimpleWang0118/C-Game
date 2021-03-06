#pragma once
#include<vector>
#include"Math.h"
#include<cstdint>

using namespace std;
class Actor
{
public:
	enum State
	{
		EActive,
		EDead,
		EPaused
	};
	Actor(class Game* game);
	virtual ~Actor();

	void Update(float DeltaTime);
	virtual void UpdateActor(float DeltaTime);
	 void UpdateComponent(float DeltaTime);

	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState);

	const Vector2& GetPosition()const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos;mRecomputeWorldTransform = true;}
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; mRecomputeWorldTransform = true; }
	float GetRotation()const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation;mRecomputeWorldTransform = true; }

	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform()const { return mWorldTransform; }
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), Math::Sin(mRotation)); }

	State GetState()const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	State mState;
	Matrix4 mWorldTransform;

	Vector2 mPosition;
	float mScale;
	float mRotation;
	bool mRecomputeWorldTransform;

	vector<class Component*>mComponent;
	class Game* mGame;





};