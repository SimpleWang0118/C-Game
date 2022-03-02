#include"Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include"Random.h"
Asteroid::Asteroid(Game* game):Actor(game)
{
	Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("asset/Asteroid.png"));
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);
}

Asteroid::~Asteroid()
{
}
