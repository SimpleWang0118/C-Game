#include "Laser.h"
#include"SpriteComponent.h"
#include"Game.h"
#include"MoveComponent.h"
#include"CircleComponent.h"
#include"Asteroid.h"
Laser::Laser(Game* game)
	:Actor(game)
	,mDeathTimer(1.0f)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.0f);

}

void Laser::UpdateActor(float DeltaTime)
{
	mDeathTimer -= DeltaTime;
	if (mDeathTimer <= 0.0f)
	{
		SetState(EDead);
	}
	else
	{
		for (auto ast : GetGame()->GetAsteroid())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				SetState(EDead);
				ast->SetState(EDead);
				break;
			}
		}
	}
}
