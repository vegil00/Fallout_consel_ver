#include"stdafx.h"
#include "NPCManager.h"


CNPCManager*  CNPCManager::m_Instance = nullptr;
CNPCManager * CNPCManager::getInstance()
{
	if (m_Instance == nullptr)
		m_Instance = new CNPCManager;
	return m_Instance;
}

void CNPCManager::init(char * path)
{
	TiXmlDocument* doc = new TiXmlDocument(path);
	doc->LoadFile();
	TiXmlElement* root = doc->FirstChildElement();
	for (TiXmlElement* ele = root->FirstChildElement(); ele != nullptr; ele = ele->NextSiblingElement())
	{
		CNPC* npc = new CNPC;
		int id = atoi(ele->Attribute("id"));
		string name = ele->Attribute("name");
		npc->init(id, name);
		int index = 0;
		for (TiXmlElement* dialog = ele->FirstChildElement(); dialog != nullptr; dialog = dialog->NextSiblingElement())
		{
			string temp = dialog->Attribute("str");
			npc->addDialog(dialog->Attribute("str"), index);
			index++;
		}
		m_NPClist.insert(make_pair(id, npc));
	}
}

CNPCManager::CNPCManager()
{
}


CNPCManager::~CNPCManager()
{
}
