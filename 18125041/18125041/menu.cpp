#include <iostream>
#include <conio.h>
#include "stuff.h"
#include "background.h"

using namespace std;
int a[] = { 0,1,2,3,4,5,6 };

int menu(Data &player)
{
	system("cls");

	if (player.bg) background(1, 45, 135, 11, 32, 33, 101);
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
	
	char tmp=' ';
	while (!_kbhit())
	{
		tmp = _getch();
		_getch();
		if (tmp >= '1' && tmp <= '6') break;
	}
	return(a[tmp - '0']);
}