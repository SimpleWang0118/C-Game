#include"Game.h"
#include"SDL_image.h"
#include"Actor.h"
#include<algorithm>

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
	UnloadDate();
	IMG_Quit();

	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
}

void Game::RemoveActor(Actor* actor)
{
}

void Game::AddSprite(SpriteComponent* sprite)
{
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
}

Enemy* Game::GetNearestEnemy(const Vector2& pos)
{
	return nullptr;
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
