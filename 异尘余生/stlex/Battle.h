#pragma once
#include"SenceManager.h"
#include"Cmonster.h"
#include"Player.h"
class CBattle
{
	friend class CSenceManager;
private:
	list<Cmonster> m_Monsters;
	CPlayer* m_pPlayer;

public:
	CBattle();
	void init(CPlayer* p);
	~CBattle();
};

