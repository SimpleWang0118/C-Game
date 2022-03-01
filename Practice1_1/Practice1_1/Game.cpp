#include"Game.h"

const float thickness = 15;
const float paddleH = 100.0f;
Game::Game():mWindow(nullptr),mRenderer(nullptr),mTickCount(0),mIsRunning(true),mPaddledir1(0),mPaddledir2(0)
{
}
bool Game::Initialize()
{
	int initresult = SDL_Init(SDL_INIT_VIDEO);
	if (initresult != 0)
	{
		SDL_Log("³õÊ¼»¯Ê§°Ü£º%s", SDL_GetError());
		return false;
	}
	mWindow = SDL_CreateWindow(
		"My First Game PING-PONG",
		100,
		100,
		1024,
		768,
		0
	);
	if (!mWindow)
	{
		SDL_Log("´°¿Ú³õÊ¼»¯Ê§°Ü£º%s",SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (!mRenderer)
	{
		SDL_Log("äÖÈ¾Æ÷³õÊ¼»¯Ê§°Ü£º%s", SDL_GetError);
		return false;
	}

	mPaddlepos1.x = 10.0f;
	mPaddlepos1.y = 768.0f / 2 ;
	mPaddlepos2.x = 1024.0f-mPaddledir1;
	mPaddlepos2.y = 768.0f / 2;
	mBallpos.x = 1024.0f / 2 + thickness;
	mBallpos.y = 768.0f / 2;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;
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
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::ProcessInput()
{
	SDL_Event Event;
	while (SDL_PollEvent(&Event))
	{
		switch (Event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	mPaddledir1 = 0;
	mPaddledir2 = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddledir1 -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddledir1 += 1;
	}
	if (state[SDL_SCANCODE_I])
	{
		mPaddledir2 -= 1;
	}
	if (state[SDL_SCANCODE_K])
	{
		mPaddledir2 += 1;
	}
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));//²»¶®£¿£¿£¿

	float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;

	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	mTickCount = SDL_GetTicks();

	if (mPaddledir1 != 0)
	{
		mPaddlepos1.y += mPaddledir1 * 300.0f * deltaTime;
		if (mPaddlepos1.y < (paddleH / 2.0f + thickness))
		{
			mPaddlepos1.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlepos1.y > (768.0f - paddleH / 2.0f - thickness))
		{
			mPaddlepos1.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}

	if (mPaddledir2 != 0)
	{
		mPaddlepos2.y += mPaddledir2 * 300.0f * deltaTime;
		if (mPaddlepos2.y < (paddleH / 2.0f + thickness))
		{
			mPaddlepos2.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlepos2.y > (768.0f - paddleH / 2.0f - thickness))
		{
			mPaddlepos2.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}
	mBallpos.x += mBallVel.x * deltaTime;
	mBallpos.y += mBallVel.y * deltaTime;

	float diff1 = mPaddlepos1.y - mBallpos.y;
	diff1 = (diff1 > 0.0f) ? diff1 : -diff1;
	if (diff1 <= paddleH / 2.0f && mBallpos.x <= 25.0f && mBallpos.x >= 20.0f && mBallVel.x < 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	else if (mBallpos.x <= 0.0f)
	{
		mIsRunning = false;
	}

	float diff2 = mPaddlepos2.y - mBallpos.y;
	diff2 = (diff2 > 0.0f) ? diff2 : -diff2;
	if (diff2 <= paddleH / 2.0f && mBallpos.x<= (1024.0f - 20)&&mBallpos.x>= (1024.0f - 25)&&mBallVel.x>0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	else if (mBallpos.x >= 1024.0f)
	{
		mIsRunning = false;
	}

	if (mBallpos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}
	else if (mBallpos.y >= (768 - thickness) && mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}

}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer,0, 0, 255, 255);

	SDL_RenderClear(mRenderer);

	SDL_SetRenderDrawColor(mRenderer, 255, 0, 255, 255);

	SDL_Rect topwall{
		0,0,1024,thickness
	};
	SDL_RenderFillRect(mRenderer, &topwall);

	SDL_Rect bottomwall{
		0,768.0f - thickness,1024,thickness
	};
	SDL_RenderFillRect(mRenderer, &bottomwall);

	SDL_Rect paddle1{
		static_cast<int> (mPaddlepos1.x),
		static_cast<int> (mPaddlepos1.y-paddleH/2),
		thickness,
		static_cast<int> (paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle1);

	SDL_Rect paddle2{
		static_cast<int> (mPaddlepos2.x-thickness-mPaddlepos1.x),
		static_cast<int> (mPaddlepos2.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle2);

	SDL_Rect ball{
		static_cast<int>(mBallpos.x - thickness / 2),
		static_cast<int>(mBallpos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	SDL_RenderPresent(mRenderer);
}
