#include"stdafx.h"
#include "Misc.h"



CMisc::CMisc()
{
}

void CMisc::init(int id, string name, type Type, string discription,int price)
{
	m_id = id;
	m_name = name;
	m_type = Type;
	m_discription = discription;
	m_price = price;

}


CMisc::~CMisc()
{
}
