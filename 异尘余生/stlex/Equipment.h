#pragma once
#include"Item.h"
class CEquipment:public CItem
{
	
private:
	int m_atk;
	int m_def;
	int m_hp;
	int m_mp;
public:
	CEquipment();
	void init(int id, string name, type Type, int atk, int def,int hp,int mp,int price,string discription);
	int getAtk() { return m_atk; }
	int getDef() { return m_def; }
	int getHp() { return m_hp; }
	int getMp() { return m_mp; }
	
	~CEquipment();
};

