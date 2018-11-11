#pragma once
#ifndef game_h
#define game_h

#include <iostream>

#include "player.h"
#include "stuff.h"

class Game
{
	private:
		const int dd[4] = { 1,1,0,1 }, cc[4] = { 0,1,1,-1 }, ddd[8] = { 1,1,0,-1,-1,-1,0,1 }, ccc[8] = { 0,-1,-1,-1,0,1,1,1 };
		Player player;
		vector<vector<char> > chosen; vector<pair<int, int> > moveList, threat; vector<vector<bool>> canBeThreat;
		int curX, curY, pos1, pos2, m, n, turn, moveLeft;
		bool End, WIN;
		void init();
		void gameStart(int gameMode);
		void load(std::string s, int &gameMode);
		void refresh();
		void winAnimation(int x = 80);
		void loseAnimation(int x = 80);
		bool check();
		void Move(char move, int com);
		void savegame(int com);
		void pvp();
		void pvc(int gameMode);
		void Easy();
		void Medium();
		void Hard();
		int isnear(int x, int y);
		void human(int x);
		long long evaluation(int nextMove);
		long long minimax(int depth, bool maxNode, long long alpha, long long beta, int x, int y,int nextMove);
	public:
		void run();
};

#endif