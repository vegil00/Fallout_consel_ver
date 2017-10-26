#include"stdafx.h"
#include "SenceManager.h"


CSenceManager* CSenceManager::m_Instance = nullptr;
CSenceManager::CSenceManager()
{
	m_status = MENU;
	m_pPlayer = new CPlayer;
	m_pMap = new Cmap;
	m_monsterB = new Cmonster;
	m_Mapinfo = "../bin/map/";
	m_Mappath = "../bin/map/";
	m_viewMenu = 0;
}


CSenceManager::~CSenceManager()
{
}

CSenceManager * CSenceManager::GetInstance()
{
	if (m_Instance == NULL)
		m_Instance = new CSenceManager;
	return m_Instance;
}

void CSenceManager::Controller()
{
	
	int key;
	bool pass;
	position pos=m_pPlayer->Getpos();
	if (m_status == SENCE)
	{
		if (GetAsyncKeyState('W') & 0x8000)
			//player.y--;
		{
			//system("cls");
			m_pPlayer->SetDir(UP);
			 pos = { m_pPlayer->Getpos().x, (m_pPlayer->Getpos().y) - 1 };
			 key = m_pMap->m_map[pos.y][pos.x];
			 pass = m_pMap->m_nodes[key]->pass();
			 if (pass)
			 {
				 m_pPlayer->SetPrePos(m_pPlayer->Getpos());
				 m_pPlayer->Setpos(pos.x, pos.y);
			 }
			 update();
			 Rend();
			
		}
		if (GetAsyncKeyState('S') & 0x8000)
			//player.y++;
		{
			//system("cls");
			m_pPlayer->SetDir(DOWN);
			 pos = { m_pPlayer->Getpos().x, (m_pPlayer->Getpos().y) + 1 };
			 key = m_pMap->m_map[pos.y][pos.x];
			 pass = m_pMap->m_nodes[key]->pass();
			 if (pass)
			 {
				 m_pPlayer->SetPrePos(m_pPlayer->Getpos());
				 m_pPlayer->Setpos(pos.x, pos.y);
			 }
			 update();
			 Rend();
		}
		if (GetAsyncKeyState('A') & 0x8000)
			//player.x -= 1;
		{
			//system("cls");
			m_pPlayer->SetDir(LEFT);
			 pos = { m_pPlayer->Getpos().x-1, (m_pPlayer->Getpos().y)  };
			 key = m_pMap->m_map[pos.y][pos.x];
			 pass = m_pMap->m_nodes[key]->pass();
			 if (pass)
			 {
				 m_pPlayer->SetPrePos(m_pPlayer->Getpos());
				 m_pPlayer->Setpos(pos.x, pos.y);
			 }
			 update();
			 Rend();

		}
		if (GetAsyncKeyState('D') & 0x8000)
			//player.x += 1;
		{
			//system("cls");
			m_pPlayer->SetDir(RIGHT);
			 pos = { m_pPlayer->Getpos().x+1, (m_pPlayer->Getpos().y) };
			 key = m_pMap->m_map[pos.y][pos.x];
			 pass = m_pMap->m_nodes[key]->pass();
			 if (pass)
			 {
				 m_pPlayer->SetPrePos(m_pPlayer->Getpos());
				 m_pPlayer->Setpos(pos.x, pos.y);
			 }
			 update();
			 Rend();
		}
		if (GetAsyncKeyState('J') & 0x8000)
		{
			//system("cls");
			position act = m_pPlayer->getActPos();
			int actKey = m_pMap->m_map[act.y][act.x];
			switch (actKey)
			{
			case 4:
				if (m_pMap->m_NPClist[act] == 0)
				{
					if (m_pPlayer->getbag()->find(93) != m_pPlayer->getbag()->end())
					{
						Goto(20, 20);
					
							int id = m_pMap->m_NPClist[act];
							m_out= CNPCManager::getInstance()->getNPC(0)->getname() +":" + CNPCManager::getInstance()->getNPC(0)->talk(1);
							
							
					}
					else
					{
						Goto(20, 20);
							int id = m_pMap->m_NPClist[act];
							m_out = CNPCManager::getInstance()->getNPC(0)->getname()+":" + CNPCManager::getInstance()->getNPC(0)->talk(0);
							
						
					}
					cout << m_out;
					//Sleep(500);
				}
				break;
			
			case 5:
				Sleep(100);
				m_status = SHOP;
				system("cls");
				break;
			case 6:
				Sleep(100);
				if (m_pMap->m_chests[act]->empty())
				{

					Goto(15, 20);
					cout << "箱子为空" ;
					//Sleep(500);
				}
				if (m_pPlayer->getbag()->size() < 16&&!m_pMap->m_chests[act]->empty())
				{
					for (list<boxitem>::iterator it = m_pMap->m_chests[act]->getbox()->begin(); it != m_pMap->m_chests[act]->getbox()->end();)
					{
						m_pPlayer->getItem((*it).id, (*it).num);
						
						Goto(15, 20);
						cout << "获得" << CItemManager::getInstance()->getItem((*it).id)->getName();
						Sleep(1000);
						it = m_pMap->m_chests[act]->getbox()->erase(it);
						if (m_pPlayer->getbag()->size() >= 16)
							break;
					}
				}
				break;
			default: break;
			}
		
		}
		if (GetAsyncKeyState('M') & 0x8000)
		{
			m_viewMenu = true;
			Rend();
		}
		
			
		//if (m_pPlayer->Getpos().x <= 1)
		//	m_pPlayer->Setpos(1, m_pPlayer->Getpos().y);
		//if (m_pPlayer->Getpos().x >= m_pMap->m_icol - 1)
		//	m_pPlayer->Setpos(m_pMap->m_icol - 1, m_pPlayer->Getpos().y);
		////player.x = 10;
		//if (m_pPlayer->Getpos().y <= 1)
		//	m_pPlayer->Setpos(m_pPlayer->Getpos().x, 1);
		////player.y = 1;
		//if (m_pPlayer->Getpos().y >= m_pMap->m_irow - 1)
		//	m_pPlayer->Setpos(m_pPlayer->Getpos().x, m_pMap->m_irow - 1);
		////player.y = 10;
	}
	
}

void CSenceManager::update()
{
	
	//Controller();
	position playerPos=m_pPlayer->Getpos();//获取玩家当前位置
	position prePlayerPos = m_pPlayer->getPrePos();//获取玩家上一位置
	if (m_pMap->m_telList.size() > 0)
	{
		for (map<position, CTeleportNode*>::iterator it = m_pMap->m_telList.begin(); it != m_pMap->m_telList.end(); )
		{
			if ((*it).second->getpos() == m_pPlayer->Getpos())
			{
				teleport((*it).second);
				return;
			}
			else
				it++;
		}
	}
	if (m_pMap->m_map[playerPos.y][playerPos.x] == 3)
	{
		m_status = BATTLE;
	}
	m_pMap->m_map[prePlayerPos.y][prePlayerPos.x] = 0;
	m_pMap->m_map[playerPos.y][playerPos.x] = 2;
	
	//设置键值
	list<Cmonster*>::iterator it = m_cMonsters.begin();
	for (; it != m_cMonsters.end(); it++)
	{
		m_pMap->m_map[(*it)->Getpos().y][(*it)->Getpos().x] = 2;
		if (m_pPlayer->Getpos() == (*it)->Getpos())
		{
			//m_status = BATTLE;
			//battle(*it);
			//it = m_cMonsters.erase(it);
			////m_InBattle.push_back(*it);
			//return;
		}
		else it++;
	}
	
		

}

void CSenceManager::battle(int monsterId)
{
	string name = Cmonster_manager::getInstance()->findMonster(monsterId)->getname();
	int atk = Cmonster_manager::getInstance()->findMonster(monsterId)->getAtk();
	int hp = Cmonster_manager::getInstance()->findMonster(monsterId)->getHpM();
	int mp = Cmonster_manager::getInstance()->findMonster(monsterId)->getMp();
	int def = Cmonster_manager::getInstance()->findMonster(monsterId)->getDef();
	list<fallitem> fall =*( Cmonster_manager::getInstance()->findMonster(monsterId)->getFallList());
	m_monsterB->init(monsterId, name, hp, mp, atk, def, fall);
	bool playerturn = 1;
	bool viewbag = 0;
	bool victory=0;
	int damge;
	int line = 0;
	while (m_pPlayer->getHpC() > 0 && m_monsterB->getHpC() > 0)
	{
		system("cls");
		int itshowline = 0;
		Goto(0, 0);
		cout << m_monsterB->getname();
		Goto(0, 1);
		cout<<"HP:" << m_monsterB->getHpC();
		Goto(15, 14);
		cout << "YOU";
		Goto(15, 15);
		cout << "HP:" << m_pPlayer->getHpC();
		
		
		Goto(20, 0);
		cout << "攻击";
		Goto(20, 2);
		cout << "道具";
		Goto(20, 4);
		cout << "逃跑";
		
		if (viewbag)
		{
			
			map<int, bagItem>::iterator it = m_pPlayer->getbag()->begin();
			for (it; it != m_pPlayer->getbag()->end(); it++)
			{
				Goto(30, itshowline);
				cout << CItemManager::getInstance()->getItem((*it).second.id)->getName() << "  " << (*it).second.num<<endl;
				itshowline++;
			}
			itshowline = 0;
			Goto(28, line);
			cout << "-->";
		}
		if (playerturn)
		{
			if (!viewbag)
			{
				Goto(17, line * 2);
				cout << "-->";
				if (GetAsyncKeyState('W') & 0x8000)
					
				{
					
					line--;
					if (line < 0)
						line = 0;
					Sleep(100);
				}
				if (GetAsyncKeyState('S') & 0x8000)
				
				{
					
					line++;
					if (line > 2)
						line = 2;
					Sleep(100);
				}
				if (GetAsyncKeyState('J') & 0x8000)
				{
					Sleep(100);
					switch (line)
					{
					case 0:
						playerturn = 0;
						m_pPlayer->Atk(m_monsterB);
						damge = m_pPlayer->getAtk() - m_monsterB->getDef();
						if (damge <= 0)
							damge = 1;
						Goto(15, 20);
						cout << m_monsterB->getname() << "受到" << damge << "点伤害";
						Sleep(1000);
						break;
					case 1:
						if (m_pPlayer->getbag()->size() > 0)
						{
							viewbag = true;
							line = 0;
							
						}
						else
						{
							Goto(15, 20);
							cout << "背包为空";
						}
						break;
					case 2:
						playerturn = 0;
						srand(time(NULL));
						if (rand() % 100 > 30)
						{
							Goto(0, 20);
							cout << "逃跑成功";
							Sleep(200);
							m_status = SENCE;
							return;
						}
						else {
							Goto(0, 20);
							cout << "逃跑失败";
							Sleep(200);

						}
							
						
					default:
						break;
					}
				}
			}
			else 
			{
				
				if (GetAsyncKeyState('W') & 0x8000)
				
				{
					line--;
					if (line < 0)
					{
						line = 0;
					}
					Sleep(100);
					
				}
					
				if (GetAsyncKeyState('S') & 0x8000)
				{
					
					line++;
					if (line > m_pPlayer->getbag()->size() - 1)
						line = m_pPlayer->getbag()->size() - 1;
					Sleep(100);
				}
					
				if (GetAsyncKeyState('J') & 0x8000)
				{
					
					map<int, bagItem>::iterator it = m_pPlayer->getbag()->begin();
					for (int i = 0; i <line; i++)
					{
						it++;
					}
					int id = (*it).first;
					type itemtype = CItemManager::getInstance()->getItem(id)->getType();
					if (itemtype == POSION)
					{
						playerturn = 0;
						m_pPlayer->UseItem(it);
						line = 0;
						viewbag = false;
					}
					else {
						Goto(15, 30);
						cout << "不可使用";
					}
					
				}
				if (GetAsyncKeyState('K'))
				{
					Sleep(100);
					system("cls");
					viewbag = false;
				}
			}
			
		}
		else
		{
			m_monsterB->Atk(m_pPlayer);
			damge = m_monsterB->getAtk() - m_pPlayer->getDef();
			if (damge <= 0)
				damge = 1;
			playerturn = 1;
			Goto(15, 20);
			cout << "你受到" << damge << "点伤害";
			Sleep(2000);
			
		}
		if (m_pPlayer->getHpC() <= 0)
		{
			Goto(15, 20);
			cout << "YOU DIE";
			Sleep(1000);
			victory = false;
			break;
		}
		if ((m_monsterB->getHpC() <= 0))
		{
			
			Sleep(2000);
			victory = 1;
			break;
		}
	}
	if (victory)
	{
		string get;
		srand(time(NULL));
		list<fallitem>::iterator it = (m_monsterB->getFallList())->begin();
		Goto(15, 21);
		cout << "YOU WIN";
		for (; it != (m_monsterB->getFallList()->end());)
		{
			if (it == m_monsterB->getFallList()->end())
				break;
			if (rand() % 100 > (*it).possbility)
			{
				m_pPlayer->getItem((*it).id, 1);
				get +=("\t获得" + CItemManager::getInstance()->getItem((*it).id)->getName() + "\n");
			}
			it++;
				
		}
		Goto(15, 22);
		cout << get;
		Sleep(1500);
		system("cls");
		m_status = SENCE;
		Rend();
	}
	else {
		main_menu();
	}
}


void CSenceManager::Generate_Monster()
{
	
	srand(time(NULL));
	
		Cmonster* temp = new Cmonster;
		temp->Setpos(1 + rand() % 10, 1 + rand() % 10);
		bool generate = 0;
		while (!generate)
		{
			if (m_pMap->m_map[temp->Getpos().y][temp->Getpos().x] == 0)
			{

				m_cMonsters.push_back(temp);
				generate = 1;

			}
			else
			{
				temp->Setpos(1 + rand() % 10, 1 + rand() % 10);
			}
		}
		
		
		
}

void CSenceManager::init(Cmap * map)
{
	m_pMap = map;
}

void CSenceManager::LoadMap(string name)
{
	m_status = SENCE;
	m_Mapinfo = m_Mapinfo+name+".xml";
	m_Mappath = m_Mappath + name + ".txt";
	m_pMap = CMapManager::GetInstance()->GetMap(name);
	m_Mapinfo = "../bin/map/";
	m_Mappath = "../bin/map/";
}

void CSenceManager::save()
{
	TiXmlDocument*doc = new TiXmlDocument();
	doc->LoadFile("../bin/save/save.xml");
	TiXmlElement* root = doc->FirstChildElement();//TiXmlElement("Save");
	TiXmlElement* ele = root->FirstChildElement();//new TiXmlElement("Player");
	for (ele; ele != nullptr; ele = ele->NextSiblingElement())
	{
		string elename = ele->Attribute("name");
		if (elename == "玩家")
		{
			for (TiXmlElement* player = ele->FirstChildElement(); player != nullptr; player = player->NextSiblingElement())
			{
				string temp = player->Attribute("name");
				if (temp == "位置")
				{
					int mhp = m_pPlayer->getHpM();
					char* posX; char* posY;
					posX = new char[10];
					posY = new char[10];
					itoa(m_pPlayer->Getpos().x, posX, 10);
					itoa(m_pPlayer->Getpos().y, posY, 10);
					player->SetAttribute("posX", posX);
					player->SetAttribute("posY", posY);

				}
				if (temp == "HP")
				{
					char* mhp = new char[10];
					char* ohp = new char[10];
					char* chp = new char[10];

					int hpm = m_pPlayer->getHpM();
					int hpo = m_pPlayer->getHPO();
					int hpc = m_pPlayer->getHpC();
					itoa(hpm, mhp, 10);
					itoa(hpo, ohp, 10);
					itoa(hpc, chp, 10);

					player->SetAttribute("mhp", mhp);
					player->SetAttribute("ohp", ohp);
					player->SetAttribute("chp", chp);
				}
				if (temp == "ATK")
				{
					char* iatk = new char[10];
					char* oatk = new char[10];
					int atki = m_pPlayer->getAtk();
					int atko = m_pPlayer->getATKO();
					itoa(atki, iatk, 10);
					itoa(atko, oatk, 10);
					player->SetAttribute("iatk", iatk);
					player->SetAttribute("oatk", oatk);
				}
				if (temp == "DEF")
				{
					char* idef = new char[10];
					char* odef = new char[10];
					int defi = m_pPlayer->getDef();
					int defo = m_pPlayer->getDEFO();
					itoa(defi, idef, 10);
					itoa(defo, odef, 10);
					player->SetAttribute("idef", idef);
					player->SetAttribute("odef", odef);
				}
				if (temp == "WEAPON")
				{
					if (m_pPlayer->haveWeapon())
					{
						char* weapon = new char[10];
						int id = m_pPlayer->getWeapon()->getId();
						itoa(id, weapon, 10);
						player->SetAttribute("id", weapon);
						player->SetAttribute("equ", "1");
					}
					else
					{
						player->SetAttribute("id", "-1");
						player->SetAttribute("equ", "0");
					}

				}
				if (temp == "ARMOR")
				{
					if (m_pPlayer->haveArmor())
					{
						char* armor = new char[10];
						int id = m_pPlayer->getArmor()->getId();
						itoa(id, armor, 10);
						player->SetAttribute("id", armor);
						player->SetAttribute("equ", "1");
					}
					else
					{
						player->SetAttribute("id", "-1");
						player->SetAttribute("equ", "0");
					}

				}
				if (temp == "JEWLLY")
				{
					if (m_pPlayer->haveJewlly())
					{
						char* jewlly = new char[10];
						int id = m_pPlayer->getWeapon()->getId();
						itoa(id, jewlly, 10);
						player->SetAttribute("id", jewlly);
						player->SetAttribute("equ", "1");
					}
					else
					{
						player->SetAttribute("id", "-1");
						player->SetAttribute("equ", "0");
					}

				}
				if (temp == "Money")
				{
					int money = m_pPlayer->getMoney();
					char* cap = new char[10];
					itoa(money, cap, 10);
					player->SetAttribute("money", cap);
				}
				if (temp == "bag")
				{
					int itemnum = m_pPlayer->getbag()->size();
					for (TiXmlElement* item = player->FirstChildElement(); item != nullptr;)
					{
						if (item->NextSiblingElement() != nullptr)
							item = item->NextSiblingElement();
						else
						{
							player->RemoveChild(item);
							item = player->FirstChildElement();
						}
					}
					if (itemnum> 0)
					{

						for (map<int, bagItem>::iterator it = m_pPlayer->getbag()->begin(); it != m_pPlayer->getbag()->end(); it++)
						{
							TiXmlElement* item = new TiXmlElement("item");
							int id = (*it).first;
							int num = (*it).second.num;
							char* Id = new char[10];
							char* Num = new char[10];
							itoa(id, Id, 10);
							itoa(num, Num, 10);
							item->SetAttribute("id", Id);
							item->SetAttribute("num", Num);
							player->LinkEndChild(item);
						}


					}
				}
		}
	}
	if (elename == "地图")
	{
		char* mapname = new char[10];
		strcpy(mapname, m_pMap->getName());
		ele->SetAttribute("mapname", mapname);
	}
	


	}
	doc->SaveFile("../bin/save/save.xml");
}

void CSenceManager::load()
{
	TiXmlDocument* doc = new TiXmlDocument("../bin/save/save.xml");
	doc->LoadFile();
	int chp;
	int ohp;
	int oatk;
	int odef;
	TiXmlElement* root = doc->FirstChildElement();
	for (TiXmlElement* ele = root->FirstChildElement(); ele != nullptr; ele = ele->NextSiblingElement())
	{
		string elename=ele->Attribute("name");
		if (elename == "玩家")
		{
			for (TiXmlElement* player = ele->FirstChildElement(); player != nullptr; player = player->NextSiblingElement())
			{
				string temp = player->Attribute("name");
				if (temp == "位置")
				{
					position pos;
					pos.x = atoi(player->Attribute("posX"));
					pos.y = atoi(player->Attribute("posY"));
					m_pPlayer->Setpos(pos.x, pos.y);
				}
				if (temp == "HP")
				{
					ohp = atoi(player->Attribute("ohp"));
					chp = atoi(player->Attribute("chp"));

				}
				if (temp == "ATK")
				{
					oatk = atoi(player->Attribute("oatk"));

				}
				if (temp == "DEF")
				{
					odef = atoi(player->Attribute("odef"));
					m_pPlayer->init(ohp, chp, 0, oatk, odef);
				}
				if (temp == "WEAPON" || temp == "ARMOR"||temp=="JEWLLY")
				{
					int id = atoi(player->Attribute("id"));
					bool equ = (bool)atoi(player->Attribute("equ"));
					if(equ)
					m_pPlayer->equipment((CEquipment*)CItemManager::getInstance()->getItem(id));
				}
				if (temp == "Money")
				{
					int money = atoi(player->Attribute("money"));
					m_pPlayer->setMoney(money);
				}
				if (temp == "bag"&&player->FirstChildElement()!=nullptr)
				{
					m_pPlayer->getbag()->clear();
					for (TiXmlElement* item = player->FirstChildElement(); item != nullptr; item = item->NextSiblingElement())
					{
						
						int id = atoi(item->Attribute("id"));
						int num = atoi(item->Attribute("num"));
						m_pPlayer->getItem(id, num);
					}
				}
			}
		}
		if (elename == "地图")
		{
			string mapname = ele->Attribute("mapname");
			LoadMap(mapname);
		}
			
	}
}

void CSenceManager::viewMenu()
{
	int line = 0;
	bool viewItem = 0;
	bool viewEqu = 0;
	int itemline = 0;
	while (m_viewMenu)
	{
		//system("cls");
		m_pMap->Rend();
		Goto(25, 0);
		cout << "道具";
		Goto(25, 2);
		cout << "任务";
		Goto(25, 4);
		cout << "存档";
		Goto(25, 6);
		cout << "读档";
		Goto(25, 8);
		cout << "退出";
		Goto(20, 10);
		cout << "装备：";
		if (m_pPlayer->haveWeapon())
		{
			Goto(22, 11);
			cout << m_pPlayer->getWeapon()->getName() << "  " << m_pPlayer->getWeapon()->getScrip();
		}
		else
		{
			Goto(22, 11);
			cout << "未装备  未装备";
		}
		if (m_pPlayer->haveWeapon())
		{
			Goto(22, 12);
			cout << m_pPlayer->getArmor()->getName() << "  " << m_pPlayer->getArmor()->getScrip();
		}
		else
		{
			Goto(22, 12);
			cout << "未装备  未装备";
		}
		if (m_pPlayer->haveWeapon())
		{
			Goto(22, 13);
			cout << m_pPlayer->getJewlly()->getName() << "  " << m_pPlayer->getJewlly()->getScrip();
		}
		else
		{
			Goto(22, 13);
			cout << "未装备  未装备";
		}
		Goto(20, 14);
		cout << "状态:";
		Goto(22, 15);
		cout << "HP:" << m_pPlayer->getHpC() << "/" << m_pPlayer->getHpM();
		Goto(22, 16);
		cout << "ATK:" << m_pPlayer->getAtk();
		Goto(22, 17);
		cout << "DEF:"<<m_pPlayer->getDef();

		if (viewItem)
		{

			map<int, bagItem>::iterator it = m_pPlayer->getbag()->begin();
			for (it; it != m_pPlayer->getbag()->end(); it++)
			{
				Goto(30, itemline);
				cout << CItemManager::getInstance()->getItem((*it).second.id)->getName() << "  " << (*it).second.num << endl;
				itemline++;
			}
			itemline = 0;


		}
		if (!viewItem)
		{
			for (int i = 0; i < 5; i++)
			{
				Goto(23, i * 2);
				if (i == line)
					cout << ">";
				else
					cout << " ";
			}
			
			if (GetAsyncKeyState('W') & 0x8000)

			{

				line--;
				if (line < 0)
					line = 0;
				Sleep(100);
			}
			if (GetAsyncKeyState('S') & 0x8000)

			{

				line++;
				if (line > 4)
					line = 4;
				Sleep(100);
			}
			if (GetAsyncKeyState('K') & 0x8000)
			{
				
				Sleep(100);
				system("cls");
				m_viewMenu = 0;
				Rend();
			}
			if (GetAsyncKeyState('J') & 0x8000)
			{
				Sleep(100);
				switch (line)
				{
				case 0:
					if (m_pPlayer->getbag()->size() > 0)
					{
						viewItem = true;
						line = 0;

					}
					else
					{
						Goto(15, 20);
						cout << "背包为空";
					}


					break;
				case 1:
					
					break;
				case 2:
					save();
					Goto(22, 18);
					cout << "保存成功";
					Sleep(1000);
					break;
				case 3:
					load();
					Goto(22, 18);
					cout << "载入中";
					Sleep(1000);
					m_viewMenu = 0;
				default:
					break;
				}
			}
		}
		else {
			Goto(28, line);
			cout << ">";
			if (GetAsyncKeyState('W') & 0x8000)

			{
				line--;
				if (line < 0)
				{
					line = 0;
				}
				Sleep(100);

			}
		
			if (GetAsyncKeyState('S') & 0x8000)
			{

				line++;
				if (line > m_pPlayer->getbag()->size() - 1)
					line = m_pPlayer->getbag()->size() - 1;
				Sleep(100);
			}

			map<int, bagItem>::iterator it = m_pPlayer->getbag()->begin();
			for (int i = 0; i < line; i++)
			{
				it++;
			}
			int id = (*it).first;
			string discribe = CItemManager::getInstance()->getItem(id)->getScrip();
			Goto(15, 21);
			cout << discribe;
			if (GetAsyncKeyState('K') & 0x8000)
			{
				Sleep(100);
				viewItem = 0;
			}
			if (GetAsyncKeyState('J') & 0x8000)
			{

				
				type itemtype = CItemManager::getInstance()->getItem(id)->getType();
				if (itemtype != MISC)
				{
					m_pPlayer->UseItem(it);
					if (m_pPlayer->getbag()->size() <= 0)
						viewItem = 0;
					line = 0;
					
				}
				else
				{
					Goto(15, 22);
					cout << "不可使用";
				}

			}
		}
		Sleep(200);
	}
}
void CSenceManager::go()
{
	
		main_menu();
		while (true)
		{
			if(m_status==SENCE)
			Controller();
			if (m_status == SHOP)
				Rend();
			//update();
			//Rend();
		}
	
	
	
}

void CSenceManager::initLevel()
{
	position OriPosP = m_pMap->m_PlayerOriPos;
	m_pPlayer->Setpos(OriPosP.x, OriPosP.y);
	m_pPlayer->SetPrePos(OriPosP);
	m_pMap->m_map[OriPosP.y][OriPosP.x]=2;
}

void CSenceManager::main_menu()
{
	int line=0;
	while (true)
	{
		system("cls");
		Goto(17, 3);
		cout << "异尘余生";
		Goto(15, 7 + line*3);
		cout << "-->";
		Goto(17, 7);
		cout << "NEW GAME" << endl;
		Goto(17, 10);
		cout << "CONTINUE" << endl;
		if (GetAsyncKeyState('W') & 0x8000)
			line--;
		if (GetAsyncKeyState('S') & 0x8000)
			line++;
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			break;
		if (line < 0)
			line = 0;
		if (line > 1)
			line = 1;
	}
	string title = "  \n世界末日的降临是有很多原因的，但那都不重要，最主要的是人类自己踏上了毁灭之路。\n就在公元2077年，几乎所有的人类都从地球的表面消失。\n地球表面受到火的洗礼，由人类所点起的小火花燃起了原子武器，很快整个情况就失去了控制。\n核子炸弹所点燃的炙热火焰如同刀刃般的从天空倾盆而下，地面被火焰吞咽，并且被滚烫的海水所包围。\n人类就这样几乎遭到灭绝的命运，死者的灵魂就如同剩下的辐射线一样，随风飘浮接着黑暗降临地球，在往后的许多年地面都是一片死寂。\n直到数百年后，少数在躲过一劫的人类开始在地表建立起零落的村庄。\n";
	string output;
	int index=0;
	output += title[0];
	switch (line)
	{case 0:
		LoadMap("level1");
		initLevel();
		m_pPlayer->init(50, 0, 10, 5);
		system("cls");
		while (index < title.size())
		{
			
			//Goto(0, 0);
			cout << output;
			index++;
			output = title[index];
			
			Sleep(10);
			if (GetAsyncKeyState('J') & 0x8000)
				break;

		}
		system("pause");
		system("cls");
		Rend();
		break;
	case 1:
		load();
		break;
	default:
		break;
	}
	
}

void CSenceManager::Rend()
{
	//Sleep(100);
	//system("cls");
	
	switch (m_status)
	{case SENCE:
		Sleep(100);
		m_pMap->Rend();
		Goto(0, 20);
		cout << "移动：W,A,S,D\n互动/确认：J\n返回上一级：K";
		if (m_viewMenu)
			viewMenu();
		break;
	case SHOP:
		
		m_pMap->m_shops[m_pPlayer->getActPos()]->trade();
		break;
	case BATTLE:
		position playerPos = m_pPlayer->Getpos();
		battle(m_pMap->m_monsterList[playerPos]);
		break;
	default:
		break;
	}
}

void CSenceManager::teleport(CTeleportNode * tel)
{
	LoadMap(tel->getnewMap());
	m_pPlayer->Setpos(tel->getTelPos().x, tel->getTelPos().y);
}
