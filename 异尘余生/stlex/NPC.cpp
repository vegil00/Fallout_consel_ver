#include"stdafx.h"
#include "NPC.h"



CNPC::CNPC()
{
	
}

void CNPC::init(int id, string name)
{
	m_id = id;
	m_name = name;
	m_index = 0;
}

void CNPC::setIndex(int index)
{
	 m_index = index; 
	 
}


CNPC::~CNPC()
{
}
