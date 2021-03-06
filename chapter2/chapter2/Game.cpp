#include"Game.h"
#include"Actor.h"
#include"SpriteComponent.h"
#include"SDL_image.h"
#include<algorithm>
#include"SpriteComponent.h"
#include"ship.h"
#include"Random.h"
#include"Asteroid.h"

Game::Game()
	:mWindow(nullptr)
	,mRenderer(nullptr)
	,mIsRunning(true)
	,mUpdatingActors(false)
{

}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO))
	{
		SDL_Log("fail to initialize the video or aduio:%s", SDL_GetError());
		return false;
	}
	mWindow = SDL_CreateWindow("SHIP", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("fail to initialize the window:%s", SDL_GetError());
		return false;
	}
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("fail to initialize the renderer:%s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG)==0)
	{
		SDL_Log("fail to initialize the png:%s", SDL_GetError());
		return false; 
	}

	Random::Init();
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
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}


}

void Game::AddSprite(SpriteComponent* sprite)
{
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
	auto iter = find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;

	auto iter = mTexture.find(fileName);
	if (iter != mTexture.end())
	{
		tex = iter->second;
	}
	else
	{
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("fail to load Texture:%d", fileName.c_str());
			return nullptr;
		}

		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for:% s", fileName.c_str());
			return nullptr;
		}

		mTexture.emplace(fileName.c_str(), tex);
	}

	return tex;
}

void Game::AddAsteroid(Asteroid* ast)
{
	mAsteroids.emplace_back(ast);
}

void Game::RemoveAsteroid(Asteroid* ast)
{
	auto iter = find(mAsteroids.begin(),mAsteroids.end(),ast);
	if (iter!=mAsteroids.end())
	{
		mAsteroids.erase(iter);
	}
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
	const uint8_t* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
}

void Game::UpdateGame()
{
	while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));
	float deltaTime=(SDL_GetTicks()-mTickCount)/1000.0f;
	
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTickCount = SDL_GetTicks();


	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}

	mUpdatingActors = false;
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	vector<class Actor*> deadActors;
	for (auto actor : mActors)
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
	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mRenderer);

	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}
	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	mShip = new Ship(this);
	mShip->SetPosition(Vector2(512.0f, 383.0f));
	mShip->SetRotation(Math::PiOver2);

	const int numAsteroid = 20;
	for (int i = 0; i < numAsteroid; i++)
	{
		new Asteroid(this);
	}
}

void Game::UnloadData()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	for (auto i : mTexture)
	{
		SDL_DestroyTexture(i.second);
	}

	mTexture.clear();
}
