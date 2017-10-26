#pragma once

#include"Cmonster.h"

class Cmonster_manager
{private:
	map<int,Cmonster*> m_monsters;
	static Cmonster_manager* m_Instance;
public:
	static Cmonster_manager* getInstance();
	void init(char* filename);
	Cmonster_manager();
	Cmonster* findMonster(int id) { return m_monsters[id]; }
	~Cmonster_manager();
};

