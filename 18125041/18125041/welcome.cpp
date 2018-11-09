#include <iostream>
#include <conio.h>
#include <windows.h>
#include "stuff.h"
#include "background.h"

using namespace std;

void welcome()
{
	drawBorder(11, 32, 33, 101, 10, 80);

	gotoXY(14, 40); cout << " -----    -----   |        |   -----   |   /  |     |\n"; Sleep(80);
	gotoXY(15, 40); cout << "|        |     |  |\\      /|  |     |  |  /   |     |\n"; Sleep(80);
	gotoXY(16, 40); cout << "|        |     |  | \\    / |  |     |  | /    |     |\n"; Sleep(80);
	gotoXY(17, 40); cout << "|        |     |  |  \\  /  |  |     |  |/     |     |\n"; Sleep(80);
	gotoXY(18, 40); cout << "|        |     |  |   \\/   |  |     |  |\\     |     |\n"; Sleep(80);
	gotoXY(19, 40); cout << "|   --|  |     |  |        |  |     |  | \\    |     |\n"; Sleep(80);
	gotoXY(20, 40); cout << "|     |  |     |  |        |  |     |  |  \\   |     |\n"; Sleep(80);
	gotoXY(21, 40); cout << " -----    -----   |        |   -----   |   \\   ----- \n"; Sleep(80);


	setcolor(12); gotoXY(27, 57); cout << "loading"; Sleep(100); cout << '.'; Sleep(100); cout << '.'; Sleep(100); cout << '.'; Sleep(100); cout << '.'; Sleep(100); cout << '.'; Sleep(100); cout << '.'; Sleep(100); cout << '.'; Sleep(100); cout << '.'; Sleep(100); cout << '.'; Sleep(100); cout << '.'; Sleep(100); cout << '.'; Sleep(100); cout << '.'; Sleep(100); cout << '.'; 


	gotoXY(14, 40); cout << "                                                     ";
	gotoXY(15, 40); cout << "                                                     ";
	gotoXY(16, 40); cout << "                                                     ";
	gotoXY(17, 40); cout << "                                                     ";
	gotoXY(18, 40); cout << "                                                     ";
	gotoXY(19, 40); cout << "                                                     ";
	gotoXY(20, 40); cout << "                                                     ";
	gotoXY(21, 40); cout << "                                                     ";

	gotoXY(27, 57); cout << "                     ";

	setcolor(12);
	gotoXY(15, 38); cout << "    /\\      -----    ---   |   |  -----      |   |   ----\n";
	gotoXY(16, 38); cout << "   /  \\     |    |  |   |  |   |    |        |   |  |";
	gotoXY(17, 38); cout << "  /----\\    |----   |   |  |   |    |        |   |   ---";
	gotoXY(18, 38); cout << " /      \\   |    |  |   |  |   |    |        |   |      |";
	gotoXY(19, 38); cout << "/        \\  -----    ---    ---     |         ---   ----";

	gotoXY(23, 57); cout << "writen by: Nhan lun";
	gotoXY(24, 62); cout << "APCS k18";
	gotoXY(25, 63); cout << "18CTT1";
	gotoXY(26, 55); cout << "email: ntnhan18@apcs.vn";
	gotoXY(27, 59); cout << "enjoy the game";
	Sleep(2600);
}