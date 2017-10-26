#pragma once
#include"stdafx.h"
#include "MapManager.h"

 CMapManager* CMapManager::m_Mapmanager = nullptr;

CMapManager::CMapManager()
{
}

CMapManager * CMapManager::GetInstance()
{
	if (m_Mapmanager == nullptr)
		m_Mapmanager = new CMapManager;
	 return m_Mapmanager;
}

Cmap* CMapManager::GetMap(string name)
{
	return m_Maplist.find(name)->second;
}

void CMapManager::init(char* filename)
{
	string Mapinfo = "../bin/map/";
	string Mappath = "../bin/map/";
	TiXmlDocument* doc = new TiXmlDocument(filename);
	doc->LoadFile();
	TiXmlElement* root = doc->FirstChildElement();
	for (TiXmlElement* ele = root->FirstChildElement(); ele != nullptr; ele = ele->NextSiblingElement())
	{
		Cmap* map = new Cmap;
		Mapinfo += ele->Attribute("name");
		Mappath += ele->Attribute("name");
		Mapinfo += ".xml";
		Mappath += ".txt";
		map->init((char*)Mappath.c_str(), (char*)Mapinfo.c_str());
		m_Maplist.insert(make_pair(map->getName(), map));
		 Mapinfo = "../bin/map/";
		Mappath = "../bin/map/";
	}

}


CMapManager::~CMapManager()
{
}
