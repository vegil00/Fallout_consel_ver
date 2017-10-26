#include"stdafx.h"
#include "Cmonster_manager.h"


Cmonster_manager* Cmonster_manager::m_Instance = nullptr;
Cmonster_manager * Cmonster_manager::getInstance()
{
	if (m_Instance == nullptr)
		m_Instance = new Cmonster_manager;
	return m_Instance;
}

void Cmonster_manager::init(char * filename)
{
	TiXmlDocument* doc = new TiXmlDocument(filename);
	doc->LoadFile();
	TiXmlElement* root = doc->FirstChildElement();
	for (TiXmlElement* ele = root->FirstChildElement(); ele != nullptr; ele = ele->NextSiblingElement())
	{
		int id = atoi(ele->Attribute("id"));
		string name = ele->Attribute("name");
		int hp = atoi(ele->Attribute("hp"));
		int mp= atoi(ele->Attribute("mp"));
		int atk = atoi(ele->Attribute("atk"));
		int def = atoi(ele->Attribute("def"));
		list<fallitem> fall;
		TiXmlElement* fallList = ele->FirstChildElement("FallList");
		for (TiXmlElement* fallit = fallList->FirstChildElement(); fallit != nullptr; fallit = fallit->NextSiblingElement())
		{
			int id = atoi(fallit->Attribute("id"));
			int possibility = atoi(fallit->Attribute("possibility"));
			fallitem temp = { id,possibility };
			fall.push_back(temp);
		}
		Cmonster* monster = new Cmonster;
		monster->init(id, name, hp, mp, atk, def, fall);
		m_monsters.insert(make_pair(id, monster));
	}
}

Cmonster_manager::Cmonster_manager()
{
}


Cmonster_manager::~Cmonster_manager()
{
}
