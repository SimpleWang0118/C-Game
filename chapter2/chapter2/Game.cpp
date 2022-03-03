#include"Game.h"
#include"Actor.h"
#include"SpriteComponent.h"
#include<SDL_image.h>
Game::Game()
{
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO))
	{
		SDL_Log("ÊÓÆµ»òÒôÀÖ³õÊ¼»¯Ê§°Ü£º%s", SDL_GetError());
		return false;
	}
	mWindow = SDL_CreateWindow("SHIP", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("´°¿Ú³õÊ¼»¯Ê§°Ü£º%s", SDL_GetError());
		return false;
	}
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("äÖÈ¾Æ÷³õÊ¼»¯Ê§°Ü£º%s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG)==0)
	{
		SDL_Log("³õÊ¼»¯Í¼Æ¬Ê§°Ü£º%s", SDL_GetError());
		return false; 
	}
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
	while (!mActors.empty())
	{
		delete mActors.back();
	}
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
}

void Game::AddAsteroid(Asteroid* ast)
{
}

void Game::RemoveAsteroid(Asteroid* ast)
{
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
	float deltaTime;
	
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
}

void Game::LoadData()
{
}

void Game::UnloadData()
{
}
