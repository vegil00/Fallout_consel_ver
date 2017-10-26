#include "stdafx.h"
#include "ItemManager.h"


CItemManager* CItemManager::m_pInstance = nullptr;
CItemManager * CItemManager::getInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new CItemManager;
	return m_pInstance;
}
void CItemManager::init(char * path)
{
	TiXmlDocument*doc = new TiXmlDocument(path);
	doc->LoadFile();
	TiXmlElement* root = doc->FirstChildElement("Items");
	TiXmlElement* ele = root->FirstChildElement();
	for (ele; ele != nullptr; ele = ele->NextSiblingElement())
	{
		type etype = (type)atoi(ele->Attribute("type"));
		int id = atoi(ele->Attribute("id"));
		string name = ele->Attribute("name");
		string discription = ele->Attribute("discription");
		int price = atoi(ele->Attribute("price"));
		if (etype == MISC)
		{
			CMisc* tempM = new CMisc;
			tempM->init(id, name, etype, discription,price);
			m_Itemlist.insert(make_pair(id, tempM));
			continue;
		}
		int atk = atoi(ele->Attribute("atk"));
		int def = atoi(ele->Attribute("def"));
		int hp = atoi(ele->Attribute("hp"));
		int mp = atoi(ele->Attribute("mp"));
		
		
		if (etype == POSION)
		{
			int time = atoi(ele->Attribute("time"));
			CPosion* temp = new CPosion;
			temp->init(id, name, hp, mp, atk, def, time, price,discription);
			m_Itemlist.insert(make_pair(id, temp));
		}
		else if (etype == WEAPON || etype == BODY || etype == NECK)
		{
			CEquipment* tempE = new CEquipment;
			tempE->init(id, name, etype, atk, def, hp, mp, price,discription);
			m_Itemlist.insert(make_pair(id, tempE));
		}
		
		
	}
}
CItemManager::CItemManager()
{
}


CItemManager::~CItemManager()
{
}
