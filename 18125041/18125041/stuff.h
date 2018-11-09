#pragma once
#ifndef stuff_h
#define stuff_h
#include <Windows.h>
#include <conio.h>

void gotoXY(int x, int y);

void setcolor(int x);

void changesize(int x, int y, int w, int h);

int Centerh(int m, int n);

int Centerv(int m, int n);

void drawboard(int m, int n);

void drawBorder(int x1, int y1, int x2, int y2, int color, int delay);

void instruction();

#endif