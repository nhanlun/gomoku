#include <fstream>
#include <time.h>

#include "game.h"
#include "welcome.h"

//#define DEBUG

void Game::run()
{
	player.backGround.initbackground(45, 135, 55);
	player.loadData();
	player.backGround.background(1, 45, 135, 11, 32, 33, 101);

#ifndef DEBUG
	welcome(); //splash screen + about screen
#endif // !DEBUG

	int action = 0;
	HANDLE inp = GetStdHandle(STD_INPUT_HANDLE);

	while (action != 6)
	{
		FlushConsoleInputBuffer(inp);
		action = player.getAction();
		switch (action)
		{
			case 1: // pvp
			{
				player.nameOfGame = "";
				gameStart(0);
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
				if (tmpp != 4) gameStart(tmpp);
				break;
			}
			case 3: // load
			{
				player.loadGame();
				if (player.nameOfGame != "")
				{
					gameStart(0);
					player.nameOfGame = "";
				}
				break;
			}
			case 4: // stats
			{
				player.stats();
				break;
			}
			case 5: // options
			{
				player.options();
				break;
			}
			case 6: // quit
			{
				player.saveData();
				break;
			}
		}
	}
}

bool Game::check()
{
	for (int i = 0; i < chosen.size(); ++i)
	{
		for (int j = 0; j < chosen[i].size(); ++j) if (chosen[i][j] != '.')
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

void Game::Move(char move, int com)
{
	switch (move)
	{
		case ' ':
		{
			int tmp1 = curX - pos1 - 1, tmp2 = curY - pos2 - 2;
			tmp1 /= 2; tmp2 /= 4;
			if (chosen[tmp1][tmp2] != '.')
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
					setcolor(12); cout << player.playerSymbol; chosen[tmp1][tmp2] = 'X';
					gotoXY(43, 64); setcolor(9); cout << player.computerSymbol << "'s turn";
				}
				else
				{
					setcolor(9); cout << player.computerSymbol; chosen[tmp1][tmp2] = 'O';
					gotoXY(43, 64); setcolor(12); cout << player.playerSymbol << "'s turn";
				}
				for (int i = 0; i < 8; ++i)
				{
					int u = tmp1 + ddd[i], v = tmp2 + ccc[i];
					if (u >= 0 && u < player.m && v >= 0 && v < player.n)
					{
						if (chosen[u][v] == '.' && !canBeThreat[u][v])
						{
							canBeThreat[u][v] = true;
							threat.push_back(make_pair(u, v));
						}
					}
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
							if (turn) cout << player.computerSymbol << " wins";
							else cout << player.playerSymbol << " wins";
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

void Game::init()
{
	chosen.clear();
	threat.clear();
	canBeThreat.clear();

	End = WIN = false;
	m = player.m * 2 + 1, n = player.n * 4 + 1;
	pos1 = Centerv(m, n), pos2 = Centerh(m, n);
	curX = pos1 + 1, curY = pos2 + 2, turn = 0;

	vector<char> axax;
	axax.resize(player.n, '.');
	vector<bool> ax;
	ax.resize(player.n, 0);
	for (int i = 1; i <= player.m; i++)
	{
		chosen.push_back(axax);
		canBeThreat.push_back(ax);
	}
	moveLeft = player.m*player.n;
}

void Game::refresh()
{
	system("cls");
	drawboard(m, n);
	player.backGround.background(1, 45, 135, pos1, pos2, pos1 + m - 1, pos2 + n - 1);
	instruction();
	for (int i = 0; i < chosen.size(); ++i)
	{
		for (int j = 0; j < chosen[i].size(); ++j)
		{
			if (chosen[i][j] != '.')
			{
				gotoXY(i * 2 + pos1 + 1, j * 4 + pos2 + 2);
				if (chosen[i][j] == 'X') setcolor(12); else setcolor(9);
				if (chosen[i][j] == 'X') cout << player.playerSymbol; else cout << player.computerSymbol;
			}
		}
	}
	gotoXY(curX, curY);
}

void Game::savegame(int com)
{
	int tmp = Centerh(1, 47);
	drawBorder(17, tmp, 23, tmp + 46, 14, 0);
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

void Game::load(std::string s, int &gameMode)
{
	ifstream fi(s);
	fi >> gameMode >> player.m >> player.n;
	fi >> turn;
	for (int i = 0; i < player.m; ++i) for (int j = 0; j < player.n; ++j)
	{
		fi >> chosen[i][j];
		if (chosen[i][j] != '.') moveLeft--;
	}
	fi.close();
}

void Game::pvp()
{
	while (!End)
	{
		char move = _getch();
		_getch();
		if (move >= 'a' && move <= 'z') move = toupper(move);
		if (move == 'V')
		{
			savegame(0);
			refresh();
		}
		else Move(move, 0);
	}
}

void Game::human(int x)
{
	char move = _getch();
	_getch();
	if (move >= 'a' && move <= 'z') move = toupper(move);
	if (move == 'V')
	{
		savegame(x);
		refresh();
	}
	else Move(move, x);
}

int Game::isnear(int x, int y)
{
	int cnt = 0;
	for (int i = x - 1; i <= x + 1; ++i)
	{
		if (i < 0 || i >= player.m) continue;
		for (int j = y - 1; j <= y + 1; ++j)
		{
			if (j < 0 || j >= player.n) continue;
			if (chosen[i][j] == 'X') cnt++;
		}
	}
	return cnt;
}

long long Game::evaluation()
{
	int patern[2][7];
	//computerPatern = 1, playerPatern = 0   
	//6: 4 chosen 2 open, 5: 5 chosen in a row, 4: 4 chosen in a row, 3: 3 chosen 2 open, 2: 3 chosen 1 open, 1: 2 chosen 2 open
	long long score = 0;
	for (int i = 0; i < 7; ++i) patern[0][i] = patern[1][i] = 0;

	for (int i = 0; i < player.m; ++i) for (int j = 0; j < player.n; ++j)
	{
		if (chosen[i][j] != '.')
		{
			bool cur = chosen[i][j] == 'O';

			//count horizontal
			int l = 1;
			while (j - l > -1 && chosen[i][j - l] == chosen[i][j]) l++;
			int r = 1;
			while (j + r < player.n && chosen[i][j + r] == chosen[i][j]) r++;

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
					if ((j - l >= 0 && chosen[i][j - l] == '.') || (j + r < player.n && chosen[i][j + r] == '.')) patern[cur][4] += 3; //if open on any side
					if ((j - l >= 0 && chosen[i][j - l] == '.') && (j + r < player.n && chosen[i][j + r] == '.')) patern[cur][6]++;
					break;
				}
				case 3:
				{
					if ((j - l >= 0 && chosen[i][j - l] == '.') && (j + r < player.n && chosen[i][j + r] == '.'))
					{
						patern[cur][3]++; //if open on both sides
						if (!cur) patern[cur][3] += 10;
					}
					if ((j - l >= 0 && chosen[i][j - l] == '.') || (j + r < player.n && chosen[i][j + r] == '.')) patern[cur][2]++; //if open on any side
					if ((j - l >= 0 && chosen[i][j - l] == '.' && j - l - 1 >= 0 && chosen[i][j - l - 1] == chosen[i][j]) || (j + r < player.n && chosen[i][j + r] == '.' && j + r + 1 < player.n && chosen[i][j + r + 1] == chosen[i][j])) patern[cur][4] += 5;
					break;
				}
				case 2:
				{
					if ((j - l >= 0 && chosen[i][j - l] == '.') && (j + r < player.n && chosen[i][j + r] == '.')) patern[cur][1]++; //if open on both sides
					if ((j - l >= 0 && chosen[i][j - l] == '.' && j - l - 1 >= 0 && chosen[i][j - l - 1] == chosen[i][j]) || (j + r < player.n && chosen[i][j + r] == '.' && j + r + 1 < player.n && chosen[i][j + r + 1] == chosen[i][j])) patern[cur][4] += 10;
					break;
				}
			}

			//count vertical
			l = 1, r = 1;
			l = 1;
			while (i - l > -1 && chosen[i - l][j] == chosen[i][j]) l++;
			r = 1;
			while (i + r < player.m && chosen[i + r][j] == chosen[i][j]) r++;

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
					if ((i - l >= 0 && chosen[i - l][j] == '.') || (i + r < player.m && chosen[i + r][j] == '.')) patern[cur][4] += 3; //if open on any side
					if ((i - l >= 0 && chosen[i - l][j] == '.') && (i + r < player.m && chosen[i + r][j] == '.')) patern[cur][6]++;
					break;
				}
				case 3:
				{
					if ((i - l >= 0 && chosen[i - l][j] == '.') && (i + r < player.m && chosen[i + r][j] == '.')) 
					{
						patern[cur][3]++; //if open on both sides
						if (!cur) patern[cur][3] += 10;
					}
					if ((i - l >= 0 && chosen[i - l][j] == '.') || (i + r < player.m && chosen[i + r][j] == '.')) patern[cur][2]++; //if open on any side
					if ((i - l >= 0 && chosen[i - l][j] == '.' && i - l - 1 >= 0 && chosen[i - l - 1][j] == chosen[i][j]) || (i + r < player.m && chosen[i + r][j] == '.' && i + r + 1 < player.m && chosen[i + r + 1][j] == chosen[i][j])) patern[cur][4] += 5;
					break;
				}
				case 2:
				{
					if ((i - l >= 0 && chosen[i - l][j] == '.') && (i + r < player.m && chosen[i + r][j] == '.')) patern[cur][1]++; //if open on both sides
					if ((i - l >= 0 && chosen[i - l][j] == '.' && i - l - 1 >= 0 && chosen[i - l - 1][j] == chosen[i][j]) || (i + r < player.m && chosen[i + r][j] == '.' && i + r + 1 < player.m && chosen[i + r + 1][j] == chosen[i][j])) patern[cur][4] += 10;
					break;
				}
			}

			//count main diagonal
			l = 1, r = 1;
			l = 1;
			while (i - l > -1 && j - l > -1 && chosen[i - l][j - l] == chosen[i][j]) l++;
			r = 1;
			while (i + r < player.m && j + r < player.n && chosen[i + r][j + r] == chosen[i][j]) r++;

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
					if ((i - l >= 0 && j - l >= 0 && chosen[i - l][j - l] == '.') || (i + r < player.m && j + r < player.n && chosen[i + r][j + r] == '.')) patern[cur][4] += 3; //if open on any side
					if ((i - l >= 0 && j - l >= 0 && chosen[i - l][j - l] == '.') && (i + r < player.m && j + r < player.n && chosen[i + r][j + r] == '.')) patern[cur][6]++;
					break;
				}
				case 3:
				{
					if ((i - l >= 0 && j - l >= 0 && chosen[i - l][j - l] == '.') && (i + r < player.m && j + r < player.n && chosen[i + r][j + r] == '.')) 
					{
						patern[cur][3]++; //if open on both sides
						if (!cur) patern[cur][3] += 10;
					}
					if ((i - l >= 0 && j - l >= 0 && chosen[i - l][j - l] == '.') || (i + r < player.m && j + r < player.n && chosen[i + r][j + r] == '.')) patern[cur][2]++; //if open on any side
					if ((i - l >= 0 && j - l >= 0 && chosen[i - l][j - l] == '.' && i - l - 1 >= 0 && j - l - 1 >= 0 && chosen[i - l - 1][j - l - 1] == chosen[i][j]) || (i + r < player.m && j + r < player.n && chosen[i + r][j + r] == '.' && i + r + 1 < player.m && j + r + 1 < player.n && chosen[i + r + 1][j + r + 1] == chosen[i][j])) patern[cur][4] += 5;
					break;
				}
				case 2:
				{
					if ((i - l >= 0 && j - l >= 0 && chosen[i - l][j - l] == '.') && (i + r < player.m && j + r < player.n && chosen[i + r][j + r] == '.')) patern[cur][1]++; //if open on both sides
					if ((i - l >= 0 && j - l >= 0 && chosen[i - l][j - l] == '.' && i - l - 1 >= 0 && j - l - 1 >= 0 && chosen[i - l - 1][j - l - 1] == chosen[i][j]) || (i + r < player.m && j + r < player.n && chosen[i + r][j + r] == '.' && i + r + 1 < player.m && j + r + 1 < player.n && chosen[i + r + 1][j + r + 1] == chosen[i][j])) patern[cur][4] += 10;
					break;
				}
			}

			//count second diagonal
			l = 1, r = 1;
			l = 1;
			while (i - l > -1 && j + l < player.n && chosen[i - l][j + l] == chosen[i][j]) l++;
			r = 1;
			while (i + r < player.m && j - r > -1 && chosen[i + r][j - r] == chosen[i][j]) r++;

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
					if ((i - l >= 0 && j + l < player.n && chosen[i - l][j + l] == '.') || (i + r < player.m && j - r > -1 && chosen[i + r][j - r] == '.')) patern[cur][4] += 3; //if open on any side
					if ((i - l >= 0 && j + l < player.n && chosen[i - l][j + l] == '.') && (i + r < player.m && j - r > -1 && chosen[i + r][j - r] == '.')) patern[cur][6]++;
					break;
				}
				case 3:
				{
					if ((i - l >= 0 && j + l < player.n && chosen[i - l][j + l] == '.') && (i + r < player.m && j - r > -1 && chosen[i + r][j - r] == '.')) 
					{
						patern[cur][3]++; //if open on both sides
						if (!cur) patern[cur][3] += 10;
					}
					if ((i - l >= 0 && j + l < player.n && chosen[i - l][j + l] == '.') || (i + r < player.m && j - r > -1 && chosen[i + r][j - r] == '.')) patern[cur][2]++; //if open on any side
					if ((i - l >= 0 && j + l < player.n && chosen[i - l][j + l] == '.' && i - l - 1 >= 0 && j + l + 1 < player.n && chosen[i - l - 1][j + l + 1] == chosen[i][j]) || (i + r < player.m && j - r > -1 && chosen[i + r][j - r] == '.' && i + r + 1 < player.m && j - r - 1 >= 0 && chosen[i + r + 1][j - r - 1] == chosen[i][j])) patern[cur][4] += 5;
					break;
				}
				case 2:
				{
					if ((i - l >= 0 && j + l < player.n && chosen[i - l][j + l] == '.') && (i + r < player.m && j - r > -1 && chosen[i + r][j - r] == '.')) patern[cur][1]++; //if open on both sides
					if ((i - l >= 0 && j + l < player.n && chosen[i - l][j + l] == '.' && i - l - 1 >= 0 && j + l + 1 < player.n && chosen[i - l - 1][j + l + 1] == chosen[i][j]) || (i + r < player.m && j - r > -1 && chosen[i + r][j - r] == '.' && i + r + 1 < player.m && j - r - 1 >= 0 && chosen[i + r + 1][j - r - 1] == chosen[i][j])) patern[cur][4] += 10;
					break;
				}
			}

		}
	}
	//evaluate the state
	if (patern[0][5] > 0 || patern[0][6] > 0) return -1000000000000000000LL;
	if (patern[1][5] > 0) return 1000000000000000000LL;
	score += 1LL * patern[1][1] - 1LL * patern[0][1] * 5;
	score += 1LL * patern[1][2] * 100 - 1LL * patern[0][2] * 1000;
	score += 1LL * patern[1][3] * 5000 - 1LL * patern[0][3] * 500000;
	score += 1LL * patern[1][4] * 40000 - 1LL * patern[0][4] * 500000;
	score += 1LL * patern[1][6] * 5000000000;
	return score;
}

long long Game::minimax(int depth, bool maxNode, long long alpha, long long beta, int x, int y) //alpha beta pruning
{
	if (maxNode) chosen[x][y] = 'X';
	else chosen[x][y] = 'O';

	if (depth==1 && check()) //if someone wins
	{
		chosen[x][y] = '.';
		if (maxNode) return -1000000000000000000LL;
		else return 1000000000000000000LL;
	}
	if (moveLeft == 0) //if draw
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
		for (int i = 0; i < threat.size(); ++i)
		{
			int u = threat[i].first, v = threat[i].second;
			vector<pair<int, int>> thisTerm;
			if (chosen[u][v] != '.') continue;

			long long tmp = minimax(depth - 1, 0, alpha, beta, u, v);
			val = max(val, tmp);
			alpha = max(alpha, val);

			if (alpha >= beta) break;
		}
	}
	else
	{
		val = 1000000000000000000LL;
		for (int i = 0; i < threat.size(); ++i)
		{
			int u = threat[i].first, v = threat[i].second;
			vector<pair<int, int>> thisTerm;
			if (chosen[u][v] != '.') continue;

			for (int k = 0; k < 8; ++k)
			{
				int u1 = u + ddd[k], v1 = v + ccc[k];
				if (u1<0 || u1>player.m || v1<0 || v1>player.n) continue;
				if (!canBeThreat[u1][v1])
				{
					thisTerm.push_back(make_pair(u1, v1));
					canBeThreat[u1][v1] = true;
					threat.push_back(make_pair(u1, v1));
				}
			}

			long long tmp = minimax(depth - 1, 1, alpha, beta, u, v);
			val = min(val, tmp);
			beta = min(beta, val);

			for (int k = (int)thisTerm.size()-1; k >= 0; --k)
			{
				int u1 = thisTerm[k].first, v1 = thisTerm[k].second;
				canBeThreat[u1][v1] = false;
				threat.pop_back();
			}
			thisTerm.clear();

			if (alpha >= beta) break;
		}
	}
	chosen[x][y] = '.';
	return val;
}

void Game::Easy()
{
	int Max = 0, x = 0, y = 0; bool found = false;
	for (int i = 0; i < player.m; ++i) for (int j = 0; j < player.n; ++j)
	{
		if (chosen[i][j] == '.')
		{
			int tmp = isnear(i, j);
			if (tmp > Max)
			{
				Max = tmp;
				x = i; y = j;
				found = true;
			}
		}
	}
	if (!found) for (int i = 0; i < player.m; ++i) for (int j = 0; j < player.n; ++j) if (chosen[i][j] == '.')
	{
		x = i; y = j;
		i = j = 1e8;
	}
	curX = x * 2 + pos1 + 1, curY = y * 4 + pos2 + 2;
	gotoXY(curX, curY);
	Move(' ', 1);
}

void Game::Medium()
{
	long long tmp = -1000000000000000000LL - 5LL;
	int x = 0, y = 0;
	for (int i = 0; i < threat.size(); ++i)
	{
		if (i >= threat.size()) break;
		int u = threat[i].first, v = threat[i].second;

		if (chosen[u][v] != '.')
		{
			swap(threat[i], threat.back());
			threat.pop_back();
			--i;
			continue;
		}
		vector<pair<int, int>> thisTerm;
		for (int k = 0; k < 8; ++k)
		{
			int u1 = u + ddd[k], v1 = v + ccc[k];
			if (u1<0 || u1>player.m || v1<0 || v1>player.n) continue;
			if (!canBeThreat[u1][v1])
			{
				thisTerm.push_back(make_pair(u1, v1));
				canBeThreat[u1][v1] = true;
				threat.push_back(make_pair(u1, v1));
			}
		}

		long long tmpVal = minimax(0, 0, -1000000000000000000LL, 1000000000000000000LL, u, v);
		if (tmpVal > tmp)
		{
			tmp = tmpVal;
			x = u; y = v;
		}

		for (int k = (int)thisTerm.size()-1; k >= 0; --k)
		{
			int u1 = thisTerm[k].first, v1 = thisTerm[k].second;
			canBeThreat[u1][v1] = false;
			threat.pop_back();
		}
		thisTerm.clear();
	}
	curX = x * 2 + pos1 + 1; curY = y * 4 + pos2 + 2;
	gotoXY(curX, curY);
	Move(' ', 2);
}

void Game::Hard()
{
#ifdef DEBUG
	double startTime = clock();
#endif // DEBUG
	long long tmp = -1000000000000000000LL - 5LL;
	int x = 0, y = 0;
	for (int i = 0; i < threat.size(); ++i)
	{
		if (i >= threat.size()) break;
		int u = threat[i].first, v = threat[i].second;
		vector<pair<int, int>> thisTerm;

		if (chosen[u][v] != '.')
		{
			swap(threat[i], threat.back());
			threat.pop_back();
			--i;
			continue;
		}
		for (int k = 0; k < 8; ++k)
		{
			int u1 = u + ddd[k], v1 = v + ccc[k];
			if (u1<0 || u1>player.m || v1<0 || v1>player.n) continue;
			if (!canBeThreat[u1][v1])
			{
				thisTerm.push_back(make_pair(u1, v1));
				canBeThreat[u1][v1] = true;
				threat.push_back(make_pair(u1, v1));
			}
		}

		long long tmpVal = minimax(1, 0, -1000000000000000000LL, 1000000000000000000LL, u, v);
		if (tmpVal > tmp)
		{
			tmp = tmpVal;
			x = u; y = v;
		}

		for (int k = (int)thisTerm.size() - 1; k >= 0; --k)
		{
			int u1 = thisTerm[k].first, v1 = thisTerm[k].second;
			canBeThreat[u1][v1] = false;
			threat.pop_back();
		}
		thisTerm.clear();
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

void Game::pvc(int gameMode)
{
	while (!End)
	{
		if (!turn) human(gameMode);
		else
		{
			switch (gameMode)
			{
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
		}
	}
	if (WIN)
	{
		++player.totalGame[gameMode];
		if (turn) ++player.totalWin[gameMode];
	}
}

void Game::gameStart(int gameMode)
{
	init();
	if (player.nameOfGame != "") load(player.nameOfGame, gameMode);
	refresh();

	gotoXY(43, 64);
	if (!turn)
	{
		setcolor(12); cout << player.playerSymbol << "'s turn";
	}
	else
	{
		setcolor(9); cout << player.computerSymbol << "'s turn";
	}
	gotoXY(curX, curY);
	if (gameMode==0) pvp();
	else pvc(gameMode);
}

void Game::winAnimation(int x)
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

void Game::loseAnimation(int x)
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



