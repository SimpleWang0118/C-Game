#include "Game.h"
#include<glew.h>
#include"Texture.h"
#include"VertexArray.h"
#include"Shader.h"
#include"Actor.h"
#include"SpriteComponent.h"
#include"Ship.h"
#include"Asteroid.h"
#include"Random.h"

Game::Game()
	:mWindow(nullptr)
	,mIsRunning(true)
	,mSpriteShader(nullptr)
	,mUpdatingActors(nullptr)
{
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("初始化SDL失败，%s", SDL_GetError());
		return false;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow("game used opengl", 100, 100, 1024, 768, SDL_WINDOW_OPENGL);
	if (!mWindow)
	{
		SDL_Log("Initialize windows failed,%s", SDL_GetError());
		return false;
	}

	mContext = SDL_GL_CreateContext(mWindow);

	//初始化glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("failed to initialize glew.%s",SDL_GetError());
		return false;
	}

	glGetError();
	if (!LoadShaders())
	{
		SDL_Log("failed to load shaders.%s",SDL_GetError());
		return false;
	}

	CreateSpriteVerts();
	LoadData();
	mTickCount = SDL_GetTicks();

	return false;
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
	delete mSpriteVerts;
	mSpriteShader->Unload();
	delete mSpriteShader;
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();

}

void Game::AddActor(Actor* actor)
{
	if (mUpdatingActors)
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
	if (iter != mActor.end())
	{
		iter_swap(iter, mActor.end() - 1);
		mActor.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprite.begin();
	for (; iter != mSprite.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	mSprite.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = find(mSprite.begin(), mSprite.end(), sprite);
	if (iter != mSprite.end())
	{
		mSprite.erase(iter);
	}
}

Texture* Game::GetTexture(const string& filename)
{
	Texture* tex = nullptr;
	auto iter = mTexture.find(filename);
	if (iter != mTexture.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Texture();
		if (tex->Load(filename))
		{
			mTexture.emplace(filename, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}

void Game::AddAsteroid(Asteroid* ast)
{
	mAsteroid.emplace_back(ast);
}

void Game::RemoveAsteroid(Asteroid* ast)
{
	auto iter = find(mAsteroid.begin(), mAsteroid.end(), ast);
	if (iter != mAsteroid.end())
	{
		mAsteroid.erase(iter);
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

	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActor)
	{
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
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

	mUpdatingActors = true;
	for (auto actor : mActor)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	for (auto panding : mPandingActor)
	{
		panding->ComputeWorldTransform();
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
	glClearColor(0.88f, 0.88f, 0.88f, 1.0f);//设置颜色为灰色
	glClear(GL_COLOR_BUFFER_BIT);//清除颜色缓存

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//设置着色器
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();

	for (auto sprite : mSprite)
	{
		sprite->Draw(mSpriteShader);
	}

	SDL_GL_SwapWindow(mWindow);
}

bool Game::LoadShaders()
{
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();

	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1024.f, 768.f);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	return true;
}

void Game::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f,0.5f,0.f,0.f,0.f,
		0.5f,0.5f,0.f,1.f,0.f,
		0.5f,-0.5f,0.f,1.f,1.f,
		-0.5f,-0.5f,0.f,0.f,1.f
	};
	unsigned int indices[] = {
		0,1,2,
		2,3,0
	};
	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

void Game::LoadData()
{
	mShip = new Ship(this);
	mShip->SetRotation(Math::PiOver2);

	const int numAsteroids = 20;
	for (int i = 0; i < numAsteroids; i++)
	{
		new Asteroid(this);
	}
}

void Game::UnloadData()
{
	while (!mActor.empty())
	{
		delete mActor.back();
	}
	for (auto i : mTexture)
	{
		i.second->Unload();
		delete i.second;
	}
	mTexture.clear();
}
