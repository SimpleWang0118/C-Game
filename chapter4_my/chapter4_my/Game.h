#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

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

	SDL_Texture* GetTexture(const string& filename);

	class Grid* GetGrid() { return mGrid; }
	vector<class Enemy*>& GetEnemies() { return mEnemies; }
	class Enemy* GetNearestEnemy(const Vector2& pos);

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	unordered_map <string, SDL_Texture*> mTexture;

	vector<class Actor*> mActor;
	vector<class Actor*> mPandingActor;
	vector<class SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTickCount;
	bool mIsRunning;
	bool upDatingActors;

	vector<class Enemy*> mEnemies;
	class Grid* mGrid;
	float mNextEnemy;

};