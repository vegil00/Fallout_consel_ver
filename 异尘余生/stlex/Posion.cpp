#include "stdafx.h"
#include "Posion.h"



CPosion::CPosion()
{
	m_type = POSION;
	m_used = false;
}



void CPosion::init(int id, string name, int hp, int mp, int atk, int def, int time,int price,string discription)
{
	m_id = id;
	m_name = name;
	m_hpRec = hp;
	m_mpRec = mp;
	m_atkAdd = atk;
	m_defAdd = def;
	m_effRound = time;
	m_price = price;
	m_used = false;
	m_discription = discription;
}

CPosion::~CPosion()
{
}
