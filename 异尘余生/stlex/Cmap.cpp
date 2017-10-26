#include"stdafx.h"
#include "Cmap.h"



Cmap::Cmap()
{
	m_name = new char[20];
}

void Cmap::init(char* mappath, char* mapinfo)
{
	
	FILE*f = fopen(mappath, "r");
	char temp[255];
	fscanf(f, "rows:%d,cols:%d\n", &m_irow, &m_icol);
		
			m_map = new int*[m_irow];
			for (int i = 0; i < m_irow; i++)
			{
				m_map[i] = new int[m_icol];
				for (int j = 0; j < m_icol; j++)
				{
					fscanf(f, "%d,", &m_map[i][j]);
				}
			}
			

				

				
			
	
	
	fclose(f);


	//////////////load info
	TiXmlDocument* doc = new TiXmlDocument(mapinfo);
	if (doc->LoadFile())
	{
		TiXmlElement* root = doc->FirstChildElement("level");
		TiXmlElement* ele = root->FirstChildElement();
		for (ele; ele != nullptr; ele = ele->NextSiblingElement())
		{
			string name;
			name = ele->Attribute("name");
			if (name == "地图名")
			{
				strcpy(m_name, ele->Attribute("mapname"));
			}
			if (name == "刷新区")
			{
				for (TiXmlElement* spawn = ele->FirstChildElement("Rect"); spawn != nullptr; spawn = spawn->NextSiblingElement())
				{
					Rect temp;
					temp.left = atoi(spawn->Attribute("left"));
					temp.top = atoi(spawn->Attribute("top"));
					temp.right = atoi(spawn->Attribute("right"));
					temp.buttom = atoi(spawn->Attribute("buttom"));
					temp.num = atoi(spawn->Attribute("num"));
					temp.generate = 1;
					m_SpwanArea.push_back(temp);
				}
			}
			if (name == "刷新数量")
			{
				m_respawnNumMin = atoi(ele->Attribute("min"));
				m_respawnNumMax = atoi(ele->Attribute("max"));
			}
			if (name == "节点")
			{
				for (TiXmlElement* node = ele->FirstChildElement("Node"); node != nullptr; node = node->NextSiblingElement())
				{
					int key;
					string out;
					bool pass;
					int kind;
					CNode* tempNode = new CNode;

					kind = key = atoi(node->Attribute("key"));
					out = node->Attribute("Output");
					pass = atoi(node->Attribute("passable"));
					tempNode->init(pass, out, kind);
					m_nodes.insert(make_pair(key, tempNode));
				}
			}
			if (name == "传送点")
			{
				for (TiXmlElement* tele = ele->FirstChildElement(); tele != nullptr; tele = tele->NextSiblingElement())
				{
					position nodepos;
					position newpos;
					char* newmap = new char[10];
					nodepos.x = atoi(tele->Attribute("posX"));
					nodepos.y = atoi(tele->Attribute("posY"));
					newpos.x= atoi(tele->Attribute("newposX"));
					newpos.y = atoi(tele->Attribute("newposY"));
					strcpy(newmap, tele->Attribute("newmap"));
					CTeleportNode* telenode = new CTeleportNode;
					telenode->init(nodepos, newpos, newmap);
					m_telList.insert(make_pair(nodepos, telenode));
				}
			}
			if (name == "玩家")
			{
				for (TiXmlElement* info = ele->FirstChildElement(); info != nullptr; info = info->NextSiblingElement())
				{
					int x = atoi(info->Attribute("x"));
					int y = atoi(info->Attribute("y"));
					m_PlayerOriPos = { x,y };
				}
			}
			if (name == "商店")
			{
				for (TiXmlElement* shop = ele->FirstChildElement(); shop != nullptr; shop = shop->NextSiblingElement())
				{
					position pos;
					pos.x = atoi(shop->Attribute("x"));
					pos.y= atoi(shop->Attribute("y"));
					CShop* Nshop = new CShop;
					Nshop->setPos(pos.x, pos.y);
					for (TiXmlElement* good = shop->FirstChildElement(); good != nullptr; good = good->NextSiblingElement())
					{
						int num = atoi(good->Attribute("num"));
						int id = atoi(good->Attribute("id"));
						CItem* temp = new CItem;
						temp = CItemManager::getInstance()->getItem(id);
						Nshop->addItem(temp, num);
					}
					m_shops.insert(make_pair(pos, Nshop));
					int s;
				}
			}
			if (name == "箱子")
			{
				for (TiXmlElement* chest = ele->FirstChildElement(); chest != nullptr; chest = chest->NextSiblingElement())
				{
					CChest* box = new CChest;
					position pos;
					pos.x = atoi(chest->Attribute("posX"));
					pos.y = atoi(chest->Attribute("posY"));
					box->setpos(pos.x, pos.y);
					for (TiXmlElement* item = chest->FirstChildElement(); item != nullptr; item = item->NextSiblingElement())
					{
						
						int id = atoi(item->Attribute("id"));
						int num = atoi(item->Attribute("num"));
						box->additem(id, num);
						
					}
					m_chests.insert(make_pair(pos, box));
				}
			}
			if (name == "敌人")
			{
				srand(time(NULL));
				for (TiXmlElement* monster = ele->FirstChildElement(); monster != nullptr; monster = monster->NextSiblingElement())
				{
					position pos;
					pos.x = atoi(monster->Attribute("posX"));
					pos.y = atoi(monster->Attribute("posY"));
					int idmin = atoi(monster->Attribute("idmin"));
					int idmax = atoi(monster->Attribute("idmax"));
					int id;
					if (idmax == idmin)
						id = idmin;
					else 
						id= idmin + rand() % (idmax - idmin+1);
					m_monsterList[pos] = id;
					m_map[pos.y][pos.x] = 3;
					
					
				}
			}
			if (name == "NPC")
			{
				for (TiXmlElement* NPC = ele->FirstChildElement(); NPC != nullptr; NPC = NPC->NextSiblingElement())
				{
					position npcpos;
					npcpos.x = atoi(NPC->Attribute("posX"));
					npcpos.y = atoi(NPC->Attribute("posY"));
					int id= atoi(NPC->Attribute("id"));
					m_NPClist.insert(make_pair(npcpos, id));
					m_map[npcpos.y][npcpos.x] = 4;
				}
			}
		}
			
			
			
			
			
		
	}

}

void Cmap::Rend()
{
	//system("cls");
	for (int i = 0; i < m_irow; i++)
	{
		for (int j = 0; j < m_icol; j++)
		{
			int key = m_map[i][j];
			Goto(j, i);
			cout << m_nodes[key]->out();
		}
		cout << endl;
	}
	
	
}

void Cmap::setvalue(int x, int y, int value)
{
	m_map[y][x] = value;
}

CNode* Cmap::getNode(int x, int y)
{
	int temp = m_map[y][x];
	return m_nodes[temp];

}


Cmap::~Cmap()
{
}
