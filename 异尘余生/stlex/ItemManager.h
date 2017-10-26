#pragma once
#include "Item.h"
#include"Posion.h"
#include"Equipment.h"
#include"Misc.h"
class CItemManager
{
private:
	static CItemManager* m_pInstance;
	map<int, CItem*> m_Itemlist;
public:
	static CItemManager* getInstance();
	void init(char* path);
	CItem* getItem(int id) { return m_Itemlist[id]; }
	CItemManager();
	~CItemManager();
};

