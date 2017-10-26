#include"stdafx.h"
#include "Chest.h"



CChest::CChest()
{
}

void CChest::additem(int id,int num)
{
	boxitem temp = { id,num };
	m_items.push_back(temp);
}

void CChest::viewitem()
{
}

bool CChest::empty()
{
	if (m_items.size() <= 0)
		return true;
	else
		return false;
}


CChest::~CChest()
{
}
