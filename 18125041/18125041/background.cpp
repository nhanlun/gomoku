#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "stuff.h"
#include "background.h"

#define pb push_back

using namespace std;

void bg::initbackground(int m, int n, int num)
{
	srand(time(NULL)); 
	on = true;
	for (int i = 1; i <= num; ++i) List1.pb(make_pair(rand() % m, rand() % n));
	for (int i = 1; i <= num; ++i) List2.pb(make_pair(rand() % m, rand() % n));
}

void bg::background(int status, int m, int n, int x1, int y1, int x2, int y2)
{
	if (!on) return;
	setcolor(3);
	for (int i = 0; i < List1.size(); ++i)
	{
		if (List1[i].first >= x1 && List1[i].first <= x2 && List1[i].second >= y1 && List1[i].second <= y2) continue;
		gotoXY(List1[i].first, List1[i].second);
		cout << 'X';
	}
	setcolor(5);
	for (int i = 0; i < List2.size(); ++i)
	{
		if (List2[i].first >= x1 && List2[i].first <= x2 && List2[i].second >= y1 && List2[i].second <= y2) continue;
		gotoXY(List2[i].first, List2[i].second);
		cout << 'O';
	}
}