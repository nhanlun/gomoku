#include "stuff.h"
#include "background.h"
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
vector<vector<char> > hihi; vector<pair<int, int> > moveList;
int curX, curY, pos1, pos2, m, n, turn, dd[] = { 1,1,0,1 }, cc[] = { 0,1,1,-1 }, moveLeft;
bool End;

bool check()
{
	for (int i = 0; i < hihi.size(); ++i)
	{
		for (int j = 0; j < hihi[i].size(); ++j) if (hihi[i][j]!='.')
		{
			for (int k = 0; k < 4; ++k)
			{
				bool res = true;
				for (int l = 1; l < 5; ++l)
				{
					int u = i + dd[k] * l, v = j + cc[k] * l;
					if (u >= hihi.size() || v >= hihi[i].size() || hihi[u][v] != hihi[i][j])
					{
						res = false; break;
					}
				}
				if (res) return true;
			}
		}
	}
	return false;
}

void Move(char move)
{
	switch (move)
	{
		case ' ':
		{
			int tmp1 = curX - pos1 - 1, tmp2 = curY - pos2 - 1;
			tmp1 /= 2; tmp2 /= 2;
			if (hihi[tmp1][tmp2]!='.')
			{
				setcolor(14); 
				gotoXY(43, 62); cout << "Invalid move"; Sleep(1000); 
				gotoXY(43, 62); cout << "            "; gotoXY(curX, curY);
			}
			else
			{
				moveList.push_back(make_pair(tmp1, tmp2));
				if (!turn)
				{
					setcolor(12); cout << 'X'; hihi[tmp1][tmp2] = 'X';
				}
				else
				{
					setcolor(9); cout << 'O'; hihi[tmp1][tmp2] = 'O';
				}
				--moveLeft;
				if (check())
				{
					setcolor(14);
					gotoXY(43, 1);
					for (int i = 1; i <= 122; ++i)
					{
						//gotoXY(43, i);
						cout << "WOOOOOOOOOOW";
						Sleep(60);
						gotoXY(43, i);
						cout << " ";
					}
					gotoXY(43, 122); cout << "            ";
					for (int i = 10; i <= 15; ++i)
					{
						drawBorder(42, 63, 44, 72, i, 0);
						gotoXY(43, 65);
						if (turn) cout << "O wins";
						else cout << "X wins";
						Sleep(800);
					}
					End = true;
				}
				else if (moveLeft == 0)
				{
					int tmp = Centerh(20, 10);
					gotoXY(43, tmp);
					setcolor(14);
					cout << "It's a tie";
					Sleep(3000);
				}
				gotoXY(curX, curY);
				turn ^= 1;
			}
			break;
		}
		case 'D':
		{
			curY += 2;
			if (curY >= pos2 + n - 1) curY = pos2 + 1;
			gotoXY(curX, curY);
			break;
		}
		case 'A':
		{
			curY -= 2;
			if (curY <= pos2) curY = pos2 + n - 2;
			gotoXY(curX, curY);
			break;
		}
		case 'S':
		{
			curX += 2;
			if (curX >= pos1 + m - 1) curX = pos1 + 1;
			gotoXY(curX, curY);
			break;
		}
		case 'W':
		{
			curX -= 2;
			if (curX <= pos1) curX = pos1 + m - 2;
			gotoXY(curX, curY);
			break;
		}
		case 'U':
		{
			if (!moveList.empty())
			{
				int u = moveList.back().first, v = moveList.back().second;
				hihi[u][v] = '.'; ++moveLeft;
				gotoXY(u * 2 + pos1 + 1, v * 2 + pos2 + 1); cout << ' '; gotoXY(curX, curY);
				moveList.pop_back();
			}
			break;
		}
		case 'H':
		{
			End = true;
			break;
		}
	}
}

void savegame(bool com)
{
	int tmp = Centerh(1, 47);
	drawBorder(17, tmp, 23, tmp+46, 14, 0);
	char s[1005];
	gotoXY(19, tmp + 2); cout << "Enter a name: ";
	cin >> s;
	gotoXY(21, tmp + 2); cout << "Press space to confirm or any key to return";
	char tmpp = _getch();
	_getch();
	string ss = s;
	ss += ".txt";
	if (tmpp == ' ')
	{
		ofstream ou(ss.c_str());
		ou << com << ' ' << (m - 1) / 2 << ' ' << (n - 1) / 2 << ' ' << turn << '\n';
		for (int i = 0; i < hihi.size(); ++i)
		{
			for (int j = 0; j < hihi[i].size(); ++j) ou << hihi[i][j];
				ou << '\n';
		}
		ou.close();
		fstream tmp("save.inp", fstream::app);
		tmp << ss.c_str() << '\n';
		tmp.close();
	}
}

void refresh(bool bg)
{
	system("cls");
	drawboard(m, n);
	if (bg) background(1, 45, 135, pos1, pos2, pos1 + m - 1, pos2 + n - 1);
	instruction();
	for (int i = 0; i < hihi.size(); ++i)
	{
		for (int j = 0; j < hihi[i].size(); ++j)
		{
			if (hihi[i][j] != '.')
			{
				gotoXY(i * 2 + pos1 + 1, j * 2 + pos2 + 1);
				if (hihi[i][j] == 'X') setcolor(12); else setcolor(9);
				cout << hihi[i][j];
			}
		}
	}
	gotoXY(curX, curY);
}

void init()
{
	vector<char> axax;
	axax.resize(n, '.');
	for (int i = 1; i <= m; i++)
	{
		hihi.push_back(axax);
	}
}

void load(string Filename)
{
}

void pvp(Data &player,string Filename)
{
	if (Filename != "") load(Filename);
	while (!hihi.empty()) hihi.pop_back();

	m = player.m * 2 + 1, n = player.n * 2 + 1;
	pos1 = Centerv(m, n), pos2 = Centerh(m, n);

	End = false;
	moveLeft = player.m*player.n;
	curX = pos1 + 1, curY = pos2 + 1, turn = 0;
	init();
	refresh(player.bg);

	while (!End)
	{
		char move = _getch();
		_getch();
		if (move >= 'a' && move <= 'z') move = toupper(move);
		if (move == 'V')
		{
			savegame(0);
			refresh(player.bg);
		}
		else Move(move);
	}
}