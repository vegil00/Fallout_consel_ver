#include"stdafx.h"
#include "Cmonster.h"



Cmonster::Cmonster()
{
}

void Cmonster::init(int id, string name, int hp, int mp, int atk, int def, list<fallitem> fall)
{
	m_id = id;
	m_name = name;
	m_ichp = m_iohp = m_imhp = hp;
	m_icmp = m_iomp = m_immp = mp;
	m_iatk = m_oatk = atk;
	m_idef = m_odef = def;
	
	
	m_fallList = fall;
}


Cmonster::~Cmonster()
{
}
