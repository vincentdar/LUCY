#include "Game.h"
#include <time.h>


int main()
{
	srand(time(NULL));

	LUCY::Game game(SCREEN_WIDTH, SCREEN_HEIGHT, "Engine LUCY");
	return EXIT_SUCCESS;
}
