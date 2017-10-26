
#include"stdafx.h"
#include"MapManager.h"
#include"SenceManager.h"
#include"ItemManager.h"
int main()
{
	CItemManager::getInstance()->init("../bin/script/items.xml");
	CMapManager::GetInstance()->init("../bin/script/map_manager.xml");
	Cmonster_manager::getInstance()->init("../bin/script/monsterlist.xml");
	CNPCManager::getInstance()->init("../bin/script/npc.xml");
	CSenceManager::GetInstance()->go();
	
	system("pause");
	
	return 0;
}
