#include "stuff.h"
#include "background.h"
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map> 
#include <time.h>

//#define DEBUG

using namespace std;
vector<vector<char> > chosen; vector<pair<int, int> > moveList; //vector<vector<bool> > threat;
int curX, curY, pos1, pos2, m, n, turn, dd[] = { 1,1,0,1 }, cc[] = { 0,1,1,-1 }, moveLeft;
char playerSymbol, computerSymbol;
bool End,WIN;
Data PLAYER;

void winAnimation(int x)
{
	setcolor(14);
	int pos1 = Centerv(9, 106);
	int pos2 = Centerh(9, 106);
	gotoXY(pos1, pos2); cout << "YY      YY        OOOO        UU        UU       WW                          WW    IIIIIIII    NNNN        NN"; pos1++; Sleep(x);
	gotoXY(pos1, pos2); cout << " YY    YY       OO    OO      UU        UU        WW                        WW        II       NN NN       NN"; pos1++; Sleep(x);
	gotoXY(pos1, pos2); cout << "  YY  YY      OO        OO    UU        UU         WW                      WW         II       NN  NN      NN"; pos1++; Sleep(x);
	gotoXY(pos1, pos2); cout << "   YYYY       OO        OO    UU        UU          WW                    WW          II       NN   NN     NN"; pos1++; Sleep(x);
	gotoXY(pos1, pos2); cout << "    YY        OO        OO    UU        UU           WW       WWWW       WW           II       NN    NN    NN"; pos1++; Sleep(x);
	gotoXY(pos1, pos2); cout << "    YY        OO        OO    UU        UU            WW     WW  WW     WW            II       NN     NN   NN"; pos1++; Sleep(x);
	gotoXY(pos1, pos2); cout << "    YY        OO        OO    UU        UU             WW   WW    WW   WW             II       NN      NN  NN"; pos1++; Sleep(x);
	gotoXY(pos1, pos2); cout << "    YY          OO    OO        UU    UU                WWWW        WWWW              II       NN       NN NN"; pos1++; Sleep(x);
	gotoXY(pos1, pos2); cout << "    YY            OOOO            UUUU                   WW          WW            IIIIIIII    NN        NNNN"; pos1++; Sleep(x);
	Sleep(3000);
}

void loseAnimation(int x)
{
	setcolor(14);
	int pos1 = Centerv(9, 103);
	int pos2 = Centerh(9, 103);
	gotoXY(pos1, pos2); cout << "YY      YY        OOOO        UU        UU       LL                OOOO          SSSSSSSS      EEEEEEEE"; pos1++; Sleep(x);
	gotoXY(pos1, pos2); cout << " YY    YY       OO    OO      UU        UU       LL              OO    OO      SS            EE        "; pos1++; Sleep(x);
	gotoXY(pos1, pos2); cout << "  YY  YY      OO        OO    UU        UU       LL            OO        OO    SS            EE        "; pos1++; Sleep(x);
	gotoXY(pos1, pos2); cout << "   YYYY       OO        OO    UU        UU       LL            OO        OO    SS            EE        "; pos1++; Sleep(x);
	gotoXY(pos1, pos2); cout << "    YY        OO        OO    UU        UU       LL            OO        OO      SSSSSS        EEEEEEEE"; pos1++; Sleep(x);
	gotoXY(pos1, pos2); cout << "    YY        OO        OO    UU        UU       LL            OO        OO            SS    EE        "; pos1++; Sleep(x);
	gotoXY(pos1, pos2); cout << "    YY        OO        OO    UU        UU       LL            OO        OO            SS    EE        "; pos1++; Sleep(x);
	gotoXY(pos1, pos2); cout << "    YY          OO    OO        UU    UU         LL              OO    OO              SS    EE        "; pos1++; Sleep(x);
	gotoXY(pos1, pos2); cout << "    YY            OOOO            UUUU           LLLLLLLLLL        OOOO        SSSSSSSS        EEEEEEEE"; pos1++; Sleep(x);
	Sleep(3000);
}

bool check()
{
	for (int i = 0; i < chosen.size(); ++i)
	{
		for (int j = 0; j < chosen[i].size(); ++j) if (chosen[i][j]!='.')
		{
			for (int k = 0; k < 4; ++k)
			{
				bool res = true;
				for (int l = 1; l < 5; ++l)
				{
					int u = i + dd[k] * l, v = j + cc[k] * l;
					if (u >= chosen.size() || v >= chosen[i].size() || chosen[u][v] != chosen[i][j])
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

void Move(char move,int com)
{
	switch (move)
	{
		case ' ':
		{
			int tmp1 = curX - pos1 - 1, tmp2 = curY - pos2 - 2;
			tmp1 /= 2; tmp2 /= 4;
			if (chosen[tmp1][tmp2]!='.')
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
					setcolor(12); cout << playerSymbol; chosen[tmp1][tmp2] = 'X'; 
					gotoXY(43, 64); setcolor(9); cout << computerSymbol << "'s turn";
				}
				else
				{
					setcolor(9); cout << computerSymbol; chosen[tmp1][tmp2] = 'O';
					gotoXY(43, 64); setcolor(12); cout << playerSymbol <<"'s turn";
				}
				--moveLeft;
				if (check())
				{
					if (!com)
					{
						setcolor(14);
						gotoXY(43, 1);
						for (int i = 1; i <= 122; ++i)
						{
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
							if (turn) cout << computerSymbol << " wins";
							else cout << playerSymbol << " wins";
							Sleep(800);
						}
					}
					else /// boommmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
					{
						WIN = true;
						if (!turn) winAnimation(100);
						else loseAnimation(100);
					}
					End = true;
				}
				else if (moveLeft == 0)
				{
					int tmp = Centerh(20, 10);
					gotoXY(43, tmp);
					setcolor(14);
					cout << "It's a tie";
					End = true;
					Sleep(3000);
				}
				gotoXY(curX, curY);
				turn ^= 1;
			}
			break;
		}
		case 'D':
		{
			curY += 4;
			if (curY >= pos2 + n - 1) curY = pos2 + 2;
			gotoXY(curX, curY);
			break;
		}
		case 'A':
		{
			curY -= 4;
			if (curY <= pos2) curY = pos2 + n - 3;
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
				chosen[u][v] = '.'; ++moveLeft;
				gotoXY(u * 2 + pos1 + 1, v * 4 + pos2 + 2); cout << ' '; gotoXY(curX, curY);
				moveList.pop_back();
				turn ^= 1;
			}
			if (com)
			{
				if (!moveList.empty())
				{
					int u = moveList.back().first, v = moveList.back().second;
					chosen[u][v] = '.'; ++moveLeft;
					gotoXY(u * 2 + pos1 + 1, v * 4 + pos2 + 2); cout << ' '; gotoXY(curX, curY);
					moveList.pop_back();
					turn ^= 1;
				}
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

void savegame(int com)
{
	int tmp = Centerh(1, 47);
	drawBorder(17, tmp, 23, tmp+46, 14, 0);
	char s[1005];
	gotoXY(19, tmp + 2); cout << "Enter a name: ";
	cin >> s;
	gotoXY(21, tmp + 2); cout << "Press space to confirm or any key to return";

	char tmpp = _getch();
	_getch();
	if (tmpp == ' ')
	{
		string ss = s;
		ss += ".txt";

		fstream File;
		vector<string> gameList;
		char x[1005];
		File.open("save.inp");
		while (File >> x) gameList.push_back(x);
		File.close(); 

		bool found = false;
		for (int i = 0; i < gameList.size(); ++i)
		{
			if (gameList[i] == ss)
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			gameList.push_back(ss);
			if (gameList.size() > 10)
			{
				DeleteFile(gameList[0].c_str());
				gameList.erase(gameList.begin());
			}
		}

		ofstream ou("save.inp");
		for (int i = 0; i < gameList.size(); ++i) ou << gameList[i].c_str() << '\n';
		ou.close();

		ou.open(ss.c_str());
		ou << com << ' ' << chosen.size() << ' ' << chosen[0].size() << ' ' << turn << '\n';
		for (int i = 0; i < chosen.size(); ++i)
		{
			for (int j = 0; j < chosen[i].size(); ++j) ou << chosen[i][j];
			ou << '\n';
		}
		ou.close();
	}
}

void refresh(bool bg)
{
	system("cls");
	drawboard(m, n);
	if (bg) background(1, 45, 135, pos1, pos2, pos1 + m - 1, pos2 + n - 1);
	instruction();
	for (int i = 0; i < chosen.size(); ++i)
	{
		for (int j = 0; j < chosen[i].size(); ++j)
		{
			if (chosen[i][j] != '.')
			{
				gotoXY(i * 2 + pos1 + 1, j * 4 + pos2 + 2);
				if (chosen[i][j] == 'X') setcolor(12); else setcolor(9);
				if (chosen[i][j] == 'X') cout << playerSymbol; else cout << computerSymbol;
			}
		}
	}
	gotoXY(curX, curY);
}

void init()
{
	while (!chosen.empty()) chosen.pop_back();
	playerSymbol = PLAYER.playerSymbol;
	computerSymbol = PLAYER.computerSymbol;

	End = WIN = false;
	m = PLAYER.m * 2 + 1, n = PLAYER.n * 4 + 1;
	pos1 = Centerv(m, n), pos2 = Centerh(m, n);
	curX = pos1 + 1, curY = pos2 + 2, turn = 0;

	vector<char> axax;
	axax.resize(PLAYER.n, '.');
	for (int i = 1; i <= PLAYER.m; i++)	chosen.push_back(axax);
	moveLeft = PLAYER.m*PLAYER.n;
}

void load(const char s[])
{
	ifstream fi(s);
	int gameMode;
	fi >> gameMode >> PLAYER.m >> PLAYER.n;
	fi >> turn;
	for (int i = 0; i < PLAYER.m; ++i) for (int j = 0; j < PLAYER.n; ++j)
	{
		fi >> chosen[i][j];
		if (chosen[i][j] != '.') moveLeft--;
	}
	fi.close();
}

void pvp()
{
	while (!End)
	{
		char move = _getch();
		_getch();
		if (move >= 'a' && move <= 'z') move = toupper(move);
		if (move == 'V')
		{
			savegame(0);
			refresh(PLAYER.bg);
		}
		else Move(move, 0);
	}
}

bool isnear(int x, int y)
{
	for (int i = x - 1; i <= x + 1; ++i)
	{
		if (i < 0 || i >= PLAYER.m) continue;
		for (int j = y - 1; j <= y + 1; ++j)
		{
			if (j < 0 || j >= PLAYER.n) continue;
			if (chosen[i][j] != '.') return true;
		}
	}
	return false;
}

long long evaluation()
{
	int patern[2][6];
	//computerPatern = 1, playerPatern = 0   
	//5: 5 chosen in a row, 4: 4 chosen in a row, 3: 3 chosen 2 open, 2: 3 chosen 1 open, 1: 2 chosen 2 open
	long long score = 0;
	for (int i = 0; i < 6; ++i) patern[0][i] = patern[1][i] = 0;

	for (int i = 0; i < PLAYER.m; ++i) for (int j = 0; j < PLAYER.n; ++j)
	{
		if (chosen[i][j] != '.')
		{
			bool cur = chosen[i][j] == 'O';

			//count horizontal
			int l = 1; 
			while (j - l > -1 && chosen[i][j - l] == chosen[i][j]) l++;
			int r = 1;
			while (j + r < PLAYER.n && chosen[i][j + r] == chosen[i][j]) r++;

			int total = r + l - 1;
			if (total > 5) total = 5;
			switch (total)
			{
				case 5: //if consecutive=5
				{
					patern[cur][5]++;
					break;
				}
				case 4: 
				{
					if ((j - l >= 0 && chosen[i][j - l] == '.') || (j + r < PLAYER.n && chosen[i][j + r] == '.')) patern[cur][4]++; //if open on any side
					if ((j - l >= 0 && chosen[i][j - l] == '.') && (j + r < PLAYER.n && chosen[i][j + r] == '.')) patern[cur][5]++;
					break;
				}
				case 3: 
				{
					if ((j - l >= 0 && chosen[i][j - l] == '.') && (j + r < PLAYER.n && chosen[i][j + r] == '.'))
					{
						patern[cur][3]++; //if open on both sides
						if (!cur) patern[cur][3] += 10;
					}
					if ((j - l >= 0 && chosen[i][j - l] == '.') || (j + r < PLAYER.n && chosen[i][j + r] == '.')) patern[cur][2]++; //if open on any side
					if ((j - l >= 0 && chosen[i][j - l] == '.' && j - l - 1 >= 0 && chosen[i][j - l - 1] == chosen[i][j]) || (j + r < PLAYER.n && chosen[i][j + r] == '.' && j + r + 1 < PLAYER.n && chosen[i][j + r + 1] == chosen[i][j])) patern[cur][4] += 5;
					break;
				}
				case 2:
				{
					if ((j - l >= 0 && chosen[i][j - l] == '.') && (j + r < PLAYER.n && chosen[i][j + r] == '.')) patern[cur][1]++; //if open on both sides
					if ((j - l >= 0 && chosen[i][j - l] == '.' && j - l - 1 >= 0 && chosen[i][j - l - 1] == chosen[i][j]) || (j + r < PLAYER.n && chosen[i][j + r] == '.' && j + r + 1 < PLAYER.n && chosen[i][j + r + 1] == chosen[i][j])) patern[cur][4] += 10;
					break;
				}
			}

			//count vertical
			l = 1, r = 1;
			l = 1;
			while (i - l > -1 && chosen[i - l][j] == chosen[i][j]) l++;
			r = 1;
			while (i + r < PLAYER.m && chosen[i + r][j] == chosen[i][j]) r++;

			total = r + l - 1;
			if (total > 5) total = 5;
			switch (total)
			{
				case 5: //if consecutive=5
				{
					patern[cur][5]++;
					break;
				}
				case 4:
				{
					if ((i - l >= 0 && chosen[i - l][j] == '.') || (i + r < PLAYER.m && chosen[i + r][j] == '.')) patern[cur][4]++; //if open on any side
					if ((i - l >= 0 && chosen[i - l][j] == '.') && (i + r < PLAYER.m && chosen[i + r][j] == '.')) patern[cur][5]++;
					break;
				}
				case 3:
				{
					if ((i - l >= 0 && chosen[i - l][j] == '.') && (i + r < PLAYER.m && chosen[i + r][j] == '.')) {
						patern[cur][3]++; //if open on both sides
						if (!cur) patern[cur][3] += 10;
					}
					if ((i - l >= 0 && chosen[i - l][j] == '.') || (i + r < PLAYER.m && chosen[i + r][j] == '.')) patern[cur][2]++; //if open on any side
					if ((i - l >= 0 && chosen[i - l][j] == '.' && i - l - 1 >= 0 && chosen[i - l - 1][j] == chosen[i][j]) || (i + r < PLAYER.m && chosen[i + r][j] == '.' && i + r + 1 < PLAYER.m && chosen[i + r + 1][j] == chosen[i][j])) patern[cur][4] += 5;
					break;
				}
				case 2:
				{
					if ((i - l >= 0 && chosen[i - l][j] == '.') && (i + r < PLAYER.m && chosen[i + r][j] == '.')) patern[cur][1]++; //if open on both sides
					if ((i - l >= 0 && chosen[i - l][j] == '.' && i - l - 1 >= 0 && chosen[i - l - 1][j] == chosen[i][j]) || (i + r < PLAYER.m && chosen[i + r][j] == '.' && i + r + 1 < PLAYER.m && chosen[i + r + 1][j] == chosen[i][j])) patern[cur][4] += 10;
					break;
				}
			}

			//count main diagonal
			l = 1, r = 1;
			l = 1;
			while (i - l > -1 && j - l > -1 && chosen[i - l][j - l] == chosen[i][j]) l++;
			r = 1;
			while (i + r < PLAYER.m && j + r < PLAYER.n && chosen[i + r][j + r] == chosen[i][j]) r++;

			total = r + l - 1;
			if (total > 5) total = 5;
			switch (total)
			{
				case 5: //if consecutive=5
				{
					patern[cur][5]++;
					break;
				}
				case 4:
				{
					if ((i - l >= 0 && j - l >= 0 && chosen[i - l][j - l] == '.') || (i + r < PLAYER.m && j + r < PLAYER.n && chosen[i + r][j + r] == '.')) patern[cur][4]++; //if open on any side
					if ((i - l >= 0 && j - l >= 0 && chosen[i - l][j - l] == '.') && (i + r < PLAYER.m && j + r < PLAYER.n && chosen[i + r][j + r] == '.')) patern[cur][5]++;
					break;
				}
				case 3:
				{
					if ((i - l >= 0 && j - l >= 0 && chosen[i - l][j - l] == '.') && (i + r < PLAYER.m && j + r < PLAYER.n && chosen[i + r][j + r] == '.')) {
						patern[cur][3]++; //if open on both sides
						if (!cur) patern[cur][3] += 10;
					}
					if ((i - l >= 0 && j - l >= 0 && chosen[i - l][j - l] == '.') || (i + r < PLAYER.m && j + r < PLAYER.n && chosen[i + r][j + r] == '.')) patern[cur][2]++; //if open on any side
					if ((i - l >= 0 && j - l >= 0 && chosen[i - l][j - l] == '.' && i - l - 1 >= 0 && j - l - 1 >= 0 && chosen[i - l - 1][j - l - 1] == chosen[i][j]) || (i + r < PLAYER.m && j + r < PLAYER.n && chosen[i + r][j + r] == '.' && i + r + 1 < PLAYER.m && j + r + 1 < PLAYER.n && chosen[i + r + 1][j + r + 1] == chosen[i][j])) patern[cur][4] += 5;
					break;
				}
				case 2:
				{
					if ((i - l >= 0 && j - l >= 0 && chosen[i - l][j - l] == '.') && (i + r < PLAYER.m && j + r < PLAYER.n && chosen[i + r][j + r] == '.')) patern[cur][1]++; //if open on both sides
					if ((i - l >= 0 && j - l >= 0 && chosen[i - l][j - l] == '.' && i - l - 1 >= 0 && j - l - 1 >= 0 && chosen[i - l - 1][j - l - 1] == chosen[i][j]) || (i + r < PLAYER.m && j + r < PLAYER.n && chosen[i + r][j + r] == '.' && i + r + 1 < PLAYER.m && j + r + 1 < PLAYER.n && chosen[i + r + 1][j + r + 1] == chosen[i][j])) patern[cur][4] += 10;
					break;
				}
			}

			//count second diagonal
			l = 1, r = 1;
			l = 1;
			while (i - l > -1 && j + l < PLAYER.n && chosen[i - l][j + l] == chosen[i][j]) l++;
			r = 1;
			while (i + r < PLAYER.m && j - r > -1 && chosen[i + r][j - r] == chosen[i][j]) r++;

			total = r + l - 1;
			if (total > 5) total = 5;
			switch (total)
			{
				case 5: //if consecutive=5
				{
					patern[cur][5]++;
					break;
				}
				case 4:
				{
					if ((i - l >= 0 && j + l < PLAYER.n && chosen[i - l][j + l] == '.') || (i + r < PLAYER.m && j - r > -1 && chosen[i + r][j - r] == '.')) patern[cur][4]++; //if open on any side
					if ((i - l >= 0 && j + l < PLAYER.n && chosen[i - l][j + l] == '.') && (i + r < PLAYER.m && j - r > -1 && chosen[i + r][j - r] == '.')) patern[cur][5]++;
					break;
				}
				case 3:
				{
					if ((i - l >= 0 && j + l < PLAYER.n && chosen[i - l][j + l] == '.') && (i + r < PLAYER.m && j - r > -1 && chosen[i + r][j - r] == '.')) {
						patern[cur][3]++; //if open on both sides
						if (!cur) patern[cur][3] += 10;
					}
					if ((i - l >= 0 && j + l < PLAYER.n && chosen[i - l][j + l] == '.') || (i + r < PLAYER.m && j - r > -1 && chosen[i + r][j - r] == '.')) patern[cur][2]++; //if open on any side
					if ((i - l >= 0 && j + l < PLAYER.n && chosen[i - l][j + l] == '.' && i - l - 1 >= 0 && j + l + 1 < PLAYER.n && chosen[i - l - 1][j + l + 1] == chosen[i][j]) || (i + r < PLAYER.m && j - r > -1 && chosen[i + r][j - r] == '.' && i + r + 1 < PLAYER.m && j - r - 1 >= 0 && chosen[i + r + 1][j - r - 1] == chosen[i][j])) patern[cur][4] += 5;  
					break;
				}
				case 2:
				{
					if ((i - l >= 0 && j + l < PLAYER.n && chosen[i - l][j + l] == '.') && (i + r < PLAYER.m && j - r > -1 && chosen[i + r][j - r] == '.')) patern[cur][1]++; //if open on both sides
					if ((i - l >= 0 && j + l < PLAYER.n && chosen[i - l][j + l] == '.' && i - l - 1 >= 0 && j + l + 1 < PLAYER.n && chosen[i - l - 1][j + l + 1] == chosen[i][j]) || (i + r < PLAYER.m && j - r > -1 && chosen[i + r][j - r] == '.' && i + r + 1 < PLAYER.m && j - r - 1 >= 0 && chosen[i + r + 1][j - r - 1] == chosen[i][j])) patern[cur][4] += 10;
					break;
				}
			}

		}
	}
	//evaluate the state
	if (patern[1][5] > 0) return 1000000000000000000LL;
	if (patern[0][5] > 0) return -1000000000000000000LL;
	score += 1LL * patern[1][1] - 1LL * patern[0][1] * 5;
	score += 1LL * patern[1][2] * 100 - 1LL * patern[0][2] * 1000;
	score += 1LL * patern[1][3] * 5000 - 1LL * patern[0][3] * 500000;
	score += 1LL * patern[1][4] * 40000 - 1LL * patern[0][4] * 500000;
	return score;
}

long long minimax(int depth, bool maxNode, long long alpha, long long beta, int x, int y) //alpha beta pruning
{
	if (maxNode) chosen[x][y] = 'X';
	else chosen[x][y] = 'O';

	if (check()) //if someone wins
	{
		chosen[x][y] = '.';
		if (maxNode) return -1000000000000000000LL;
		else return 1000000000000000000LL;
	}
	else if (moveLeft == 0) //if draw
	{
		chosen[x][y] = '.';
		return 0;
	}

	if (depth == 0) //evaluate 
	{
		long long eval = 0;
		eval = evaluation();
		chosen[x][y] = '.';
		return eval;
	}
	long long val;

	if (maxNode)
	{
		val = -1000000000000000000LL;
		for (int i = 0; i < chosen.size(); ++i)
		{
			for (int j = 0; j < chosen[i].size(); ++j)
			{
				if (chosen[i][j] == '.' && isnear(i, j))
				{
					long long tmp = minimax(depth - 1, 0, alpha, beta, i, j);
					val = max(val, tmp);
					alpha = max(alpha, val);
					if (alpha >= beta)
					{
						i = chosen.size() - 1;
						j = chosen[i].size() - 1;
					}
				}
			}
		}
	}
	else
	{
		val = 1000000000000000000LL;
		for (int i = 0; i < chosen.size(); ++i)
		{
			for (int j = 0; j < chosen[i].size(); ++j)
			{
				if (chosen[i][j] == '.' && isnear(i, j))
				{
					long long tmp = minimax(depth - 1, 1, alpha, beta, i, j);
					val = min(val, tmp);
					beta = min(beta, val);
					if (alpha >= beta)
					{
						i = chosen.size() - 1;
						j = chosen[i].size() - 1;
					}
				}
			}
		}
	}
	chosen[x][y] = '.';
	return val;
}

void Easy()
{
	while (!End)
	{
		char move = _getch();
		_getch();
		if (move >= 'a' && move <= 'z') move = toupper(move);
		if (move == 'V')
		{
			savegame(1);
			refresh(PLAYER.bg);
		}
		else Move(move, 1);
		if (End) break;
		if (turn)
		{
			for (int i = 0; i < PLAYER.m; ++i) for (int j = 0; j < PLAYER.n; ++j)
			{
				if (chosen[i][j] == '.')
				{
					curX = i * 2 + pos1 + 1, curY = j * 4 + pos2 + 2;
					gotoXY(curX, curY);
					Move(' ', 1);
					i = 1e8; j = 1e8;
				}
			}
		}
	}
	if (WIN)
	{
		++PLAYER.totalGame1;
		if (turn) ++PLAYER.totalWin1;
	}
}

void Medium()
{
	while (!End)
	{
		if (!turn)
		{
			char move = _getch();
			_getch();
			if (move >= 'a' && move <= 'z') move = toupper(move);
			if (move == 'V')
			{
				savegame(2);
				refresh(PLAYER.bg);
			}
			else Move(move, 2);
		}
		else
		{
			long long tmp = -1000000000000000000LL - 5;
			int x = 0, y = 0;
			for (int i = 0; i < PLAYER.m; ++i) for (int j = 0; j < PLAYER.n; ++j) if (chosen[i][j] == '.' && isnear(i, j)) //chose a cell to make a move
			{
				long long tmpVal = minimax(0, 0, -1000000000000000000LL, 1000000000000000000LL, i, j);
				if (tmpVal > tmp)
				{
					tmp = tmpVal;
					x = i; y = j;
				}
			}
			curX = x * 2 + pos1 + 1; curY = y * 4 + pos2 + 2;
			gotoXY(curX, curY);
			Move(' ', 2);
		}
	}
	if (WIN)
	{
		++PLAYER.totalGame2;
		if (turn) ++PLAYER.totalWin2;
	}
}

void Hard()
{
	while (!End)
	{
		if (!turn)
		{
			char move = _getch();
			_getch();
			if (move >= 'a' && move <= 'z') move = toupper(move);
			if (move == 'V')
			{
				savegame(3);
				refresh(PLAYER.bg);
			}
			else Move(move, 3);
		}
		else
		{
#ifdef DEBUG
	double startTime = clock();
#endif // DEBUG

			long long tmp = -1000000000000000000LL - 5;
			int x = 0, y = 0;
			for (int i = 0; i < PLAYER.m; ++i) for (int j = 0; j < PLAYER.n; ++j) if (chosen[i][j]=='.' && isnear(i,j)) //chose a cell to make a move
			{
				long long tmpVal = minimax(1, 0, -1000000000000000000LL, 1000000000000000000LL, i, j);
				if (tmpVal > tmp)
				{
					tmp = tmpVal;
					x = i; y = j;
				}
			}
			curX = x * 2 + pos1 + 1; curY = y * 4 + pos2 + 2;
			gotoXY(curX, curY);
			Move(' ', 3);
#ifdef DEBUG
	double endTime = clock();
	gotoXY(0, 0);
	cerr << "Execution time: " << (endTime - startTime) / CLOCKS_PER_SEC * 1000 << ".ms\n";
	gotoXY(curX, curY);
#endif // DEBUG
		}
	}
	if (WIN)
	{
		++PLAYER.totalGame3;
		if (turn) ++PLAYER.totalWin3;
	}
}

void game(Data &player, const char s[], int gamemode)
{
	PLAYER = player;
	init();
	if (s != "") load(s);
	refresh(player.bg);

	gotoXY(43, 64);
	if (!turn)
	{
		setcolor(12); cout << playerSymbol << "'s turn";
	}
	else
	{
		setcolor(9); cout << computerSymbol << "'s turn";
	}
	gotoXY(curX, curY);

	switch (gamemode)
	{
		case 0:
		{
			pvp();
			break;
		}
		case 1:
		{
			Easy();
			break;
		}
		case 2:
		{
			Medium();
			break;
		}
		case 3:
		{
			Hard();
			break;
		}
	}
	//loseAnimation(100);
	//winAnimation(100);
	player = PLAYER;
}