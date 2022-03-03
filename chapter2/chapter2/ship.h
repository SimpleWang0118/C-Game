#pragma once
#include"Actor.h"
#include"SDL.h"
class Ship :public Actor {
public:
	Ship(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyBoard(const uint8_t* state);
	float GetRightSpeed()const { return mRightSpeed; }
	float GetDownSpeed()const { return mDownSpeed; }
	void ActorInput(const uint8_t* keyState) override;
private:
	float mRightSpeed;
	float mDownSpeed;
	float mLaserCooldown;
};
