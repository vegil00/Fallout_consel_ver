#include"stdafx.h"
int Goto(int X,int Y)
{
	COORD cd;
	cd.X = 2 * X;
	cd.Y =  Y;
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}