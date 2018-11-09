#include "player.h"
#include "stuff.h"
#include <fstream>
#include <conio.h>

Player::Player()
{
	m = n = 0;
	for (int i = 1; i <= 3; ++i) totalGame[i] = totalWin[i] = 0;
}

void Player::saveData() //save profile
{
	ofstream ou("player.inp");
	ou << backGround.on << ' ' << m << ' ' << n << ' ' <<
		playerSymbol << ' ' << computerSymbol;
	for (int i = 1; i <= 3; ++i) ou << ' ' << totalGame[i] << ' ' << totalWin[i];
	ou.close();
}

void Player::loadData() //load profile 
{
	fstream File;
	File.open("player.inp");
	File >> backGround.on >> m >> n >> playerSymbol >> computerSymbol;
	for (int i = 1; i <= 3; ++i) File >> totalGame[i] >> totalWin[i];
	File.close();
	if (m == 0 || n == 0)
	{
		backGround.on = true;
		m = n = 16;
		playerSymbol = 'X';
		computerSymbol = 'O';
	}
}

void Player::loadGame() //load game
{
	nameOfGame = "";
	fstream File;
	File.open("save.inp");
	char x[1005];
	std::vector<string> gameList;
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
			nameOfGame = gameList[tmpp];
			return;
		}
	}
}

void Player::stats()
{
	drawBorder(16, 44, 28, 89, 14, 0);
	gotoXY(18, 47); cout << "Total easy game played: " << totalGame[1];
	gotoXY(19, 47); cout << "Total easy game winned: " << totalWin[1];
	gotoXY(20, 47); cout << "Total medium game played: " << totalGame[2];
	gotoXY(21, 47); cout << "Total medium game winned: " << totalWin[2];
	gotoXY(22, 47); cout << "Total hard game played: " << totalGame[3];
	gotoXY(23, 47); cout << "Total hard game winned: " << totalWin[3];
	gotoXY(25, 58); cout << "Press R to reset";
	gotoXY(26, 58); cout << "Press B to back";
	while (1)
	{
		char tmp = _getch();
		_getch();
		if (tmp == 'b') break;
		if (tmp == 'r')
		{
			totalGame[1] = totalGame[2] = totalGame[3] = 0;
			totalWin[1] = totalWin[2] = totalWin[3] = 0;
			break;
		}
	}
}

void Player::options()
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
							if (tmpp == 1) backGround.on = true;
							else backGround.on = false;
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
						cin >> m;
						if (m < 1 || m > 16)
						{
							gotoXY(23, 59); cout << "Invalid number"; Sleep(800);
							gotoXY(23, 55); cout << "              ";
							gotoXY(22, 52); cout << "                             ";
						}
						else break;
					}
					while (1)
					{
						drawBorder(21, 48, 24, 85, 14, 0);
						gotoXY(22, 50); cout << "Enter width (max 16, min 1): ";
						cin >> n;
						if (n < 1 || n > 16)
						{
							gotoXY(23, 59); cout << "Invalid number"; Sleep(800);
							gotoXY(23, 55); cout << "              ";
							gotoXY(22, 52); cout << "                             ";
						}
						else break;
					}
					return;
				}
				case 3:
				{
					drawBorder(21, 50, 24, 83, 14, 0);
					gotoXY(22, 52); cout << "Enter player's symbol: ";
					char tmp = _getch();
					_getch();
					playerSymbol = tmp;
					gotoXY(22, 52); cout << "Enter computer's symbol: ";
					tmp = _getch();
					_getch();
					computerSymbol = tmp;
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

int Player::getAction()
{
	system("cls");

	backGround.background(1, 45, 135, 11, 32, 33, 101);
	drawBorder(11, 32, 33, 101, 10, 0);

	setcolor(12);

	gotoXY(15, 52); cout << "|\\    /|  ----  |\\    |  |   |\n";
	gotoXY(16, 52); cout << "| \\  / |  |     | \\   |  |   |\n";
	gotoXY(17, 52); cout << "|  \\/  |  |--   |  \\  |  |   |\n";
	gotoXY(18, 52); cout << "|      |  |     |   \\ |  |   |\n";
	gotoXY(19, 52); cout << "|      |  ----  |    \\|   ---\n";

	gotoXY(23, 59); cout << "Select an option\n";
	gotoXY(24, 56); cout << "1: player vs player";
	gotoXY(25, 56); cout << "2: player vs computer";
	gotoXY(26, 56); cout << "3: load game";
	gotoXY(27, 56); cout << "4: stats";
	gotoXY(28, 56); cout << "5: settings";
	gotoXY(29, 56); cout << "6: quit";

	char tmp = ' ';
	while (tmp<'1' || tmp>'6')
	{
		tmp = _getch();
		_getch();
	}
	int a[] = { 0,1,2,3,4,5,6 };
	return(a[tmp - '0']);
}