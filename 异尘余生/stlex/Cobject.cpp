#include"stdafx.h"
#include "Cobject.h"



Cobject::Cobject()
{
}

void Cobject::Atk(Cobject * target)
{
	target->Atked(m_iatk);
}

void Cobject::Atked(int atk)
{
	if (atk - m_idef < 0)
		return;
	else
	{
		m_ichp -= (atk - m_idef);
	}
	

	if (m_ichp <= 0)
		m_ichp = 0;
}


Cobject::~Cobject()
{
}
