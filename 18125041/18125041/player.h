#pragma once
#ifndef player_h
#define player_h

#include "background.h"

class Player
{
	public:
		Player();
		int m, n, totalGame[4], totalWin[4];
		char playerSymbol, computerSymbol;
		std::string nameOfGame;
		bg backGround;
		void saveData();
		void loadData();
		void loadGame();
		void stats();
		void options();
		int	getAction();
};

#endif