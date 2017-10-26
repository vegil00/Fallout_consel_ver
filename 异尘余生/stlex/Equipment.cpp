#include"stdafx.h"
#include "Equipment.h"



CEquipment::CEquipment()
{
}

void CEquipment::init(int id, string name, type Type, int atk, int def, int hp, int mp, int price,string discription)
{
	m_id = id;
	m_name = name;
	m_type = Type;
	m_atk = atk;
	m_def = def;
	m_price = price;
	m_hp = hp;
	m_mp = mp;
	m_discription = discription;
}


CEquipment::~CEquipment()
{
}


