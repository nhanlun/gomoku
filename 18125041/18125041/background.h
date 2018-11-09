#pragma once
#ifndef background_h
#define background_h

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <utility>

using namespace std;

class bg
{
	private:
		vector <pair<int, int>> List1, List2;
	public:
		bool on;
		void initbackground(int m, int n, int num);
		void background(int status, int m, int n, int x1, int y1, int x2, int y2);
};

#endif