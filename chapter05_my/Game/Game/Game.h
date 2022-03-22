#pragma once
#include<SDL.h>
#include<unordered_map>
#include<string>
#include<vector>
#include"Math.h"

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

	class Texture* GetTexture(const string& filename);

	void AddAsteroid(class Asteroid* ast);
	void RemoveAsteroid(class Asteroid* ast);
	vector<class Asteroid*>& GetAsteroid() { return mAsteroid; }

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	bool LoadShaders();
	void CreateSpriteVerts();
	void LoadData();
	void UnloadData();

	unordered_map<string, class Texture*> mTexture;
	vector<class Actor*> mActor;
	vector<class Actor*> mPandingActor;
	vector<class SpriteComponent*> mSprite;
	class Shader* mSpriteShader;
	class VertexArray* mSpriteVerts;

	SDL_Window* mWindow;
	SDL_GLContext mContext;
	Uint32 mTickCount;
	bool mIsRunning;
	bool mUpdatingActors;
	class Ship* mShip;
	vector<class Asteroid*> mAsteroid;



};

