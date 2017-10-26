#pragma once
#include"Item.h"
#include"Cobject.h"
class CPosion:public CItem

{
private:
	int m_hpRec;
	int m_mpRec;
	int m_atkAdd;
	int m_defAdd;
	int m_effRound;
	bool m_used;
public:
	CPosion();
	int hpRec() { return m_hpRec; }
	int mpRec() { return m_mpRec;}
	void beUsed() { m_used = true; }
	void init(int id, string name, int hp, int mp, int atk, int def, int time,int price,string discription);
	~CPosion();
};

