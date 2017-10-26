#pragma once
#include"Node.h"
#include"Shop.h"
#include"ItemManager.h"
#include"TeleportNode.h"
#include"Chest.h"
struct Rect { int left; int top; int right; int buttom; int num; bool generate; };
class Cmap
{
	friend class CSenceManager;
	int** m_map;
	int m_irow;
	int m_icol;
	char* m_name;
	vector<Rect> m_SpwanArea;
	int m_respawnNumMin,m_respawnNumMax;
	map<int, CNode*> m_nodes;
	map<position, CShop*> m_shops;
	position m_PlayerOriPos;
	map<position, int> m_monsterList;
	map<position, CTeleportNode*> m_telList;
	map<position, CChest*> m_chests;
	map<position, int> m_NPClist;
public:
	Cmap();
	void init(char* mappath, char* mapinfo);
	void Rend();
	void setvalue(int x, int y, int value);
	CNode* getNode(int x, int y);
	char* getName() { return m_name; }
	~Cmap();
};

