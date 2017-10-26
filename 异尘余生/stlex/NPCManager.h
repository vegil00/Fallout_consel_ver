#pragma once
#include"NPC.h"
class CNPCManager
{private:
	static CNPCManager* m_Instance;
	map<int, CNPC*> m_NPClist;
public:
	static CNPCManager* getInstance();
	void init(char* path);
	CNPC* getNPC(int id) { return m_NPClist[id]; }
	CNPCManager();
	~CNPCManager();
};

