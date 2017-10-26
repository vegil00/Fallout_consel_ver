#pragma once
#include"Cobject.h"
#include"Player.h"
#include"Cmonster.h"
#include"Cmap.h"
#include"MapManager.h"
#include"Cmonster_manager.h"
#include"NPCManager.h"
enum status{SENCE,BATTLE,MENU,SHOP,BAG};
class CSenceManager
{private:
	list<Cmonster*> m_cMonsters;
	CPlayer* m_pPlayer;
	Cmap* m_pMap;
	status m_status;
	static CSenceManager* m_Instance;
	string m_Mapinfo;
	string m_Mappath;
	Cmonster* m_monsterB;
	bool m_viewMenu;
	string m_out;
	//+list<Cmonster*> m_InBattle;
public:
	CSenceManager();
	~CSenceManager();
	static CSenceManager* GetInstance();
	void Controller();
	void update();
	void battle(int monsterId);
	void Generate_Monster();
	void init(Cmap* map);
	void LoadMap(string name);
	void save();
	void load();
	void go();
	void initLevel();
	void main_menu();
	void setStatus(status s) { m_status = s; }
	CPlayer* getPlayer() { return m_pPlayer; }
	void Rend();
	void teleport(CTeleportNode* tel);
	void viewMenu();
};

