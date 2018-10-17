#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <vector>

#include "stuff.h"
#include "welcome.h"
#include "menu.h"
#include "background.h"
#include "play.h"

using namespace std;
//ifstream fi("player.inp");
//ofstream fo("data.txt");
fstream File;
Data player;

void loadData()
{
	File.open("player.inp");
	File >> player.bg >> player.m >> player.n;
	File.close();
}

void saveData()
{
	ofstream ou("player.inp");
	ou << player.bg << ' ' << player.m << ' ' << player.n;
	ou.close();
}

void loadGame()
{
	File.open("save.inp");
	char x[1005];
	vector<string> gameList;
	while (File >> x)
	{
		string ss = x;
		gameList.push_back(ss);
	}
	drawBorder(14, 41, 30, 92, 14, 0);
	for (int i = max(0, (int)gameList.size() - 10); i < gameList.size(); ++i)
	{
		gotoXY(16 + i, 43); cout << i << ": " << gameList[i].c_str();
	}
	gotoXY(29, 43); cout << "Enter a number to load game or any key to return";
	char tmp = _getch();
	_getch();
	if (tmp<'0' || tmp>'9') return;
	int tmpp = tmp - '0';
	if (tmpp + 1 > gameList.size()) return;
}

int main()
{
	loadData();
	changesize(100, 50, 980, 680);
	initbackground(45, 135, 60);
	//welcome(player);
	int action = 0;
	while (action != 6)
	{
		action = menu(player);
		switch (action)
		{
			case 1: // pvp
			{
				pvp(player,"");
				break;
			}
			case 2: // pvc
			{
				//drawBorder(24,)
			}
			case 3: // load
			{
				loadGame();
			}
			case 4: // stats
			{
			}
			case 5: // options
			{
			}
			case 6: // quit
			{
				saveData();
				break;
			}
		}
	}
	//pvp(player);
	//system("pause");
	return 0;
}