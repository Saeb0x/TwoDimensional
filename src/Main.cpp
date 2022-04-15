#include "Game.h"

int main(int argc, char* argv[])
{
	Game* pGame = new Game;

	bool Success = pGame->initialization();

	if (Success)
	{
		pGame->gameLoop();
	}
	pGame->shutDown();

	return 0;
}