#include "Asteroid.h"
#include"Game.h"
#include"Random.h"
#include"SpriteComponent.h"
Asteroid::Asteroid(Game* game)
	:Actor(game)
	,mCircle(nullptr)
{
	Vector2 randPos = Random::GetVector(Vector2(-512.0f, -384.0f), Vector2(512.0f, 384.0f));

	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));
	
	
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}
