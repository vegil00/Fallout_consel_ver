#pragma once
#include"Item.h"
class CMisc:public CItem
{
public:
	CMisc();
	void init(int id, string name, type Type, string discription,int price);
	~CMisc();
};

