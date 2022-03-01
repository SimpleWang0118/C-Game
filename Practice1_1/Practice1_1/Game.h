#pragma once
#include<iostream>
#include<SDL.h>


using namespace std;
struct Vector2
{
	float x;
	float y;
};
class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void ShutDown();
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTickCount;
	bool mIsRunning;

	int mPaddledir1;
	int mPaddledir2;
	Vector2 mBallpos;
	Vector2 mPaddlepos1;
	Vector2 mPaddlepos2;
	Vector2 mBallVel;

};