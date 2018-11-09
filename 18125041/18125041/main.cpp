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
fstream File;
Data player;

void saveData() //save profile
{
	ofstream ou("player.inp");
	ou << player.bg << ' ' << player.m << ' ' << player.n << ' ' << player.playerSymbol << ' ' << player.computerSymbol << ' ' << player.totalGame1 << ' ' << player.totalWin1 << ' ' << player.totalGame2 << ' ' << player.totalWin2 << ' ' << player.totalGame3 << ' ' << player.totalWin3;
	ou.close();
}

void loadData() //load profile 
{
	File.open("player.inp");
	File >> player.bg >> player.m >> player.n >> player.playerSymbol >> player.computerSymbol >> player.totalGame1 >> player.totalWin1 >> player.totalGame2 >> player.totalWin2 >> player.totalGame3 >> player.totalWin3;
	File.close();
	if (player.m == 0 || player.n == 0)
	{
		player.bg = 1;
		player.m = player.n = 16;
		player.playerSymbol = 'X';
		player.computerSymbol = 'O';
		saveData();
	}
}

void loadGame() //load game
{
	File.open("save.inp");
	char x[1005];
	vector<string> gameList;
	while (File >> x) gameList.push_back(x);
	drawBorder(14, 42, 30, 91, 14, 0);
	for (int i = 0; i < gameList.size(); ++i)
	{
		gotoXY(16 + i, 44); cout << i << ": " << gameList[i].c_str(); //print out list of file save
	}
	gotoXY(29, 44); cout << "Enter a number to chose or any key to return";
	char tmp = _getch();
	_getch();
	File.close();

	if (tmp<'0' || tmp>'9') return;
	int tmpp = tmp - '0';
	if (tmpp + 1 > gameList.size()) return;

	drawBorder(19, 49, 25, 84, 12, 0);
	gotoXY(21, 51); cout << "press 1 to load";
	gotoXY(22, 51); cout << "press 2 to erase";
	gotoXY(23, 51); cout << "press 3 to return";
	while (1)
	{
		tmp = _getch();
		_getch();
		if (tmp == '3') return;
		if (tmp == '2') //delete file save
		{
			DeleteFile(gameList[tmpp].c_str());
			gameList.erase(gameList.begin() + tmpp); 
			ofstream ou("save.inp");
			for (int i = 0; i < gameList.size(); ++i) ou << gameList[i].c_str() << '\n';
			ou.close();
			return;
		}
		if (tmp == '1') //load file
		{
			int gameMode = 0;
			File.open(gameList[tmpp]);
			File >> gameMode >> player.m >> player.n;
			File.close();
			game(player, gameList[tmpp].c_str(), gameMode);
			return;
		}
	}
}

void stats()
{
	drawBorder(16, 44, 28, 89, 14, 0);
	gotoXY(18, 47); cout << "Total easy game played: " << player.totalGame1;
	gotoXY(19, 47); cout << "Total easy game winned: " << player.totalWin1;
	gotoXY(20, 47); cout << "Total medium game played: " << player.totalGame2;
	gotoXY(21, 47); cout << "Total medium game winned: " << player.totalWin2;
	gotoXY(22, 47); cout << "Total hard game played: " << player.totalGame3;
	gotoXY(23, 47); cout << "Total hard game winned: " << player.totalWin3;
	gotoXY(25, 58); cout << "Press R to reset";
	gotoXY(26, 58); cout << "Press B to back";
	while (1)
	{
		char tmp = _getch();
		_getch();
		if (tmp == 'b') break;
		if (tmp == 'r')
		{
			player.totalGame1 = player.totalGame2 = player.totalGame3 = 0;
			player.totalWin1 = player.totalWin2 = player.totalWin3 = 0;
			break;
		}
	}
}

void options()
{
	while (1)
	{
		drawBorder(19, 52, 26, 81, 14, 0);
		gotoXY(21, 54); cout << "1: background";
		gotoXY(22, 54); cout << "2: size of the board";
		gotoXY(23, 54); cout << "3: symbol";
		gotoXY(24, 54); cout << "4: back";
		char k = _getch();
		_getch();
		if (k >= '1' && k <= '4')
		{
			int tmp = k - '0';
			switch (tmp)
			{
				case 1:
				{
					drawBorder(21, 58, 24, 75, 14, 0);
					gotoXY(22, 60); cout << "1: Turn on";
					gotoXY(23, 60); cout << "2: Turn off";
					while (1)
					{
						char boom = _getch();
						_getch();
						if (boom >= '1' && boom <= '2')
						{
							int tmpp = boom - '0';
							if (tmpp == 1) player.bg = true;
							else player.bg = false;
							break;
						}
					}
					return;
				}
				case 2:
				{
					while (1)
					{
						drawBorder(21, 48, 24, 85, 14, 0);
						gotoXY(22, 50); cout << "Enter height (max 16, min 1): "; 
						int m;
						cin >> m;
						if (m < 1 || m > 16)
						{
							gotoXY(23, 59); cout << "Invalid number"; Sleep(800);
							gotoXY(23, 55); cout << "              ";
							gotoXY(22, 52); cout << "                             ";
						}
						else
						{
							player.m = m;
							break;
						}
					}
					while (1)
					{
						drawBorder(21, 48, 24, 85, 14, 0);
						gotoXY(22, 50); cout << "Enter width (max 16, min 1): ";
						int n;
						cin >> n;
						if (n < 1 || n > 16)
						{
							gotoXY(23, 59); cout << "Invalid number"; Sleep(800);
							gotoXY(23, 55); cout << "              ";
							gotoXY(22, 52); cout << "                             ";
						}
						else
						{
							player.n = n;
							break;
						}
					}
					//gotoXY(23, 60); cout << "Enter n: ";
					return;
				}
				case 3:
				{
					drawBorder(21, 50, 24, 83, 14, 0);
					gotoXY(22, 52); cout << "Enter player's symbol: ";
					char tmp = _getch();
					_getch();
					player.playerSymbol = tmp;
					gotoXY(22, 52); cout << "Enter computer's symbol: ";
					tmp = _getch();
					_getch();
					player.computerSymbol = tmp;
					return;
				}
				case 4:
				{
					return;
				}
			}
		}
	}
}

int main()
{
	loadData();
	changesize(100, 50, 980, 680);
	initbackground(45, 135, 55);
	welcome(player); //splash screen + about screen
	int action = 0;
	HANDLE inp = GetStdHandle(STD_INPUT_HANDLE);

	while (action != 6)
	{
		FlushConsoleInputBuffer(inp);
		action = menu(player);
		switch (action)
		{
			case 1: // pvp
			{
				game(player, "", 0);
				break;
			}
			case 2: // pvc
			{
				drawBorder(22, 58, 29, 75, 14, 0);
				gotoXY(24, 60); cout << "1: easy";
				gotoXY(25, 60); cout << "2: medium";
				gotoXY(26, 60); cout << "3: hard";
				gotoXY(27, 60); cout << "4: back\n";
				char tmp = ' ';
				while (tmp<'1' || tmp>'4')
				{
					tmp = _getch();
					_getch();
				}
				int tmpp = tmp - '0';
				if (tmpp != 4) game(player, "", tmpp);
				break;
			}
			case 3: // load
			{
				loadGame();
				break;
			}
			case 4: // stats
			{
				stats();
				break;
			}
			case 5: // options
			{
				options();
				break;
			}
			case 6: // quit
			{
				saveData();
				break;
			}
		}
	}
	return 0;
}