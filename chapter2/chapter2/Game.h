#pragma once
#include<SDL.h>
#include<unordered_map>
#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void ShutDown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	SDL_Texture* GetTexture(const std::string& fileName);

	vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }
	
	void AddAsteroid(class Asteroid* ast);
	void RemoveAsteroid(class Asteroid* ast);


private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	unordered_map<string, SDL_Texture*> mTexture;

	vector<class Actor*> mActors;
	vector<class Actor*> mPendingActors;
	vector<class SpriteComponent*> mSprites;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTickCount;
	bool mIsRunning;
	bool mUpdatingActors;
	class Ship* mShip;
	vector<class Asteroid*> mAsteroids;





};
