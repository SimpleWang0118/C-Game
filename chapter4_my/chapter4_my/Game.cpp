#include"Game.h"
#include"SDL_image.h"
#include"Actor.h"
#include<algorithm>
#include"SpriteComponent.h"
#include"Enemy.h"
#include"Grid.h"
#include"AIComponent.h"
#include"AIState.h"
using namespace std;
Game::Game()
	:mWindow(nullptr),
	mRenderer(nullptr),
	upDatingActors(false),
	mIsRunning(true)
{
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Game failed to Initialize:%s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Tower Defend", 100, 100, 1024, 768, 0);
	if(!mWindow)
	{
		SDL_Log("Window is failed to creat:%s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Renderer is failed to creat:%s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Failed to initialize the png:%s", SDL_GetError());
		return false;
	}

	LoadData();
	mTickCount = SDL_GetTicks();
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ShutDown()
{
	UnloadData();
	IMG_Quit();

	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	if (upDatingActors)
	{
		mPandingActor.emplace_back(actor);
	}
	else
	{
		mActor.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = find(mPandingActor.begin(), mPandingActor.end(), actor);
	if (iter != mPandingActor.end())
	{
		iter_swap(iter, mPandingActor.end() - 1);
		mPandingActor.pop_back();
	}

	iter = find(mActor.begin(), mActor.end(), actor);
	if(iter!=mActor.end())
	{
		iter_swap(iter, mActor.end() - 1);
		mActor.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	//TODO
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	//TODO
	auto iter = find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

SDL_Texture* Game::GetTexture(const string& filename)
{
	SDL_Texture* tex = nullptr;
	auto iter = mTexture.find(filename);
	if (iter != mTexture.end())
	{
		tex = iter->second;
	}
	else
	{
		SDL_Surface* surf = IMG_Load(filename.c_str());
		if (!surf)
		{
			SDL_Log("failed to load texture file %s", filename.c_str());
			return nullptr;
		}

		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", filename.c_str());
			return nullptr;
		}
		mTexture.emplace(filename.c_str(), tex);
	}
	return tex;
}

Enemy* Game::GetNearestEnemy(const Vector2& pos)
{
	//TODO
	Enemy* best = nullptr;
	if (mEnemies.size() > 0)
	{
		best = mEnemies[0];

		float bestDistSq = (pos - mEnemies[0]->GetPosition()).LengthSq();
		for (size_t i = 1; i < mEnemies.size(); i++)
		{
			float newDistSq = (pos - mEnemies[i]->GetPosition()).LengthSq();
			if (newDistSq < bestDistSq)
			{
				bestDistSq = newDistSq;
				best = mEnemies[i];
			}
		}
	}
	return best;
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}

	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	//TODO:
	if (keystate[SDL_SCANCODE_B])
	{
		mGrid->BuildTower();
	}

	int x, y;
	Uint32 buttons = SDL_GetMouseState(&x, &y);
	if (SDL_BUTTON(buttons) & SDL_BUTTON_LEFT)
	{
		mGrid->ProcessClick(x, y);
	}
	upDatingActors = true;
	for (auto actor : mActor)
	{
		actor->ProcessInput(keystate);
	}
	upDatingActors = false;
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));

	float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTickCount = SDL_GetTicks();


	upDatingActors = true;
	for (auto actor : mActor)
	{
		actor->Update(deltaTime);
	}
	upDatingActors = false;

	for (auto panding : mPandingActor)
	{
		mActor.emplace_back(panding);
	}
	mPandingActor.clear();

	vector<Actor*> deadActors;
	for (auto actor : mActor)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	for (auto actor : deadActors)
	{
		delete actor;
	}

}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 32, 233, 233, 255);
	SDL_RenderClear(mRenderer);

	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);

}

void Game::LoadData()
{
	//TODO:
}

void Game::UnloadData()
{
	while (!mActor.empty())
	{
		mActor.pop_back();//wlh
	}

	for (auto i : mTexture)
	{
		SDL_DestroyTexture(i.second);
	}
	mTexture.clear();
}
