#include"Game.h"
 
int main(int argc,char** argv)
{
	Game game;
	bool init = game.Initialize();
	if (init)
	{
		game.RunLoop();
	}
	game.ShutDown();
	return 0;
}