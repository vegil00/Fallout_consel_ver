#include"stdafx.h"
#include "Quest.h"




CQuest::CQuest()
{
}

void CQuest::init(int id, string name, string discription, QuestStatus status, list<quest>questList)
{
	m_id = id;
	m_name = name;
	m_discription = discription;
	m_status = status;
	m_questList = questList;
	

}


void CQuest::update()
{
	bool complete = 1;
	list<quest>::iterator it = m_questList.begin();
	for (it; it != m_questList.end(); it++)
	{
		if (!(*it).complete)
			complete = false;
	}
	if (complete)
	{
		m_status = COMPLETE;
	}
}

CQuest::~CQuest()
{
}
