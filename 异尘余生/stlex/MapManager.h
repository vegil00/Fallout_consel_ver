#pragma once
#include"Cmap.h"
class CMapManager
{private:
	static CMapManager* m_Mapmanager;
	map<string, Cmap*>m_Maplist;
	CMapManager();
public:
	static CMapManager *GetInstance();
	Cmap* GetMap(string name);
	void init(char* filename);
	~CMapManager();
};

