#include <iostream>

#include "stuff.h"
#include "game.h"

using namespace std;

int main()
{
	changesize(100, 50, 980, 680);
	Game game;
	game.run();
	return 0;
}