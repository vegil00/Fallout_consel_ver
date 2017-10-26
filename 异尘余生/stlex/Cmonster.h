#pragma once
#include"Cobject.h"
struct fallitem {
	int id;
	int possbility;
};
class Cmonster:public Cobject
{
	friend class CsenseManager;
private:
	list<fallitem> m_fallList;
	int m_id;
	string m_name;
public:
	Cmonster();
	void init(int id, string name, int hp, int mp, int atk, int def,list<fallitem> fall);
	string getname() { return m_name;}
	int getAtk() { return m_iatk; }
	int getDef() { return m_idef; }
	int getHpM() { return m_imhp; }
	int getHpC() { return m_ichp; }
	int getMp() { return m_immp; }
	list<fallitem>* getFallList() { return &m_fallList; }
	~Cmonster();
};

