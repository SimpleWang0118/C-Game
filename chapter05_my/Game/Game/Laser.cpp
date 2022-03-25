#include "Laser.h"
#include"SpriteComponent.h"
#include"Game.h"
Laser::Laser(Game* game)
	:Actor(game)
	,mDeathTimer(1.0f)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));


}

void Laser::UpdateActor(float DeltaTime)
{
}
