
#define _WIN32_WINNT 0x0500

//#define DEBUG

#include <Windows.h>
#include <iostream>
#include "background.h"

using namespace std;
static HANDLE cursor = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoXY(int x, int y)
{
	COORD tmp = { y,x };
	SetConsoleCursorPosition(cursor, tmp);
}

void setcolor(int x)
{
	SetConsoleTextAttribute(cursor, x);
}

void changesize(int x, int y, int w, int h)
{
	HWND console = GetConsoleWindow();
	MoveWindow(console, x, y, w, h, true);
}

int Centerh(int m, int n)
{
	return 68 - n / 2;
}

int Centerv(int m, int n)
{
	return 22 - m / 2;
}

void drawboard(int m, int n)
{
	int pos1 = Centerv(m, n), pos2 = Centerh(m, n);
#ifdef DEBUG
	int poss1 = pos1, poss2 = pos2;
	poss1--; poss2-=2;
	for (int i = 0; i < n; ++i) if (i % 4 == 2) 
	{
		gotoXY(poss1, pos2 + i); cout << i / 4;
	}
	for (int i = 0; i < m-1; ++i) if (i % 2 == 0)
	{
		gotoXY(pos1 + i + 1, poss2); cout << i / 2;
	}
	//cout << m << ' ' << n;
#endif // DEBUG
	setcolor(7);
	gotoXY(pos1, pos2); cout << (char)201; for (int i = 1; i <= n - 2; ++i) if (i % 4) cout << (char)205; else cout << (char)209; cout << (char)187;

	for (int i = 2; i < m; ++i)
	{
		gotoXY(pos1 + i - 1,pos2);
		if (i % 2 == 0)
		{
			cout << (char)186;
			for (int j = 2; j < n; ++j) if (j % 4 == 1) cout << (char)179; else cout << ' ';
			cout << (char)186;
		}
		else
		{
			cout << (char)199;
			for (int j = 1; j < n-1; ++j) if (j % 4) cout << (char)196; else cout << (char)197; 
			cout << (char)182;
		}
	}
	gotoXY(pos1 + m - 1, pos2); cout << (char)200; for (int i = 1; i <= n - 2; ++i) if (i % 4) cout << (char)205; else cout << (char)207; cout << (char)188;
}

void drawBorder(int x1, int y1, int x2, int y2,int color,int delay)
{
	setcolor(color);
	gotoXY(x1, y1); cout << (char)201; for (int i = y1 + 1; i < y2; ++i) cout << (char)205; cout << (char)187; Sleep(delay);
	for (int i = x1 + 1; i < x2; ++i) { gotoXY(i, y1);  cout << (char)186; for (int j = y1 + 1; j < y2; ++j) cout << ' '; cout << (char)186; Sleep(delay); }
	gotoXY(x2, y1); cout << (char)200; for (int i = y1 + 1; i < y2; ++i) cout << (char)205; cout << (char)188; Sleep(delay);
}

void instruction()
{
	string s = "A: left,  D: right,  S: down,  W: up,  space: choose,  U: undo,  H: Home,  V:save game";
	int tmp = Centerh(20, s.length());
	drawBorder(0, tmp - 2, 2, tmp + s.length() + 1, 10, 0);
	setcolor(15);  gotoXY(1, tmp); cout << s.c_str();
}