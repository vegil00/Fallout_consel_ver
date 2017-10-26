#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<Windows.h>
#include<time.h>
#include<map>
#include<string>
//#include"tinystr.h"
#include"tinyxml.h"
#include"tinystr.h"
using namespace std;
struct position
{
	int x;
	int y;
	bool operator ==(position a)
	{
		if (x == a.x&&y == a.y)
			return true;
		else
			return false;
	}
	bool operator <(position a)const
	{
		if (y < a.y)
			return true;
		else if (y>a.y)
			return false;
		else if (y == a.y&&x < a.x)
			return true;
		else if (y == a.y&&x > a.x)
		{
			return false;
		}
		else if (y == a.y&&x == a.x)
		{
			return false;
		}
	}
};
int Goto(int X, int Y);

