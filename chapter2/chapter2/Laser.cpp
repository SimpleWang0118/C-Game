#include"Laser.h"
#include"Game.h"
#include"Actor.h"
#include"CircleComponent.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include"Asteroid.h"

Laser::Laser(Game* game) :Actor(game),mDeathTimer(1.0f)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));

	// Create a move component, and set a forward speed
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.0f);
}

void Laser::UpdateActor(float deltaTime)
{
	for (auto ast : GetGame()->GetAsteroids())
	{
		if (Intersect(*mCircle, *(ast->GetCircle())))
		{
			SetState(EDead);
			ast->SetState(EDead);
			break;
		}
	}
}
