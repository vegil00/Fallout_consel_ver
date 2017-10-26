#include"stdafx.h"
#include "Player.h"



CPlayer::CPlayer()
{
	m_dir = UP;
	m_money = 200;
	m_HaveWeapon = 0;
	m_HaveArmor = 0;
	m_HaveJewlly = 0;
	m_Weapon = new CEquipment;
	m_Weapon->init(-1, "未装备", WEAPON, 0, 0, 0, 0, 0, "未装备");
	m_Armor = new CEquipment;
	m_Armor->init(-1, "未装备", BODY, 0, 0, 0, 0, 0, "未装备");
	m_Jewlly = new CEquipment;
	m_Jewlly->init(-1, "未装备", NECK, 0, 0, 0, 0, 0, "未装备");
}

void CPlayer::SetPrePos(position pre)
{
	m_PrePos.x = pre.x;
	m_PrePos.y = pre.y;
}

void CPlayer::SetDir(direction dir)
{
	m_dir = dir;
	SetActPos();
}

void CPlayer::SetActPos()
{
	switch (m_dir)
	{
	case UP:
		m_ActPos = { m_Position.x,m_Position.y - 1 };
		break;
	case DOWN:
		m_ActPos = { m_Position.x,m_Position.y + 1 };
		break;
	case LEFT:
		m_ActPos = { m_Position.x-1,m_Position.y  };
		break;
	case RIGHT:
		m_ActPos = { m_Position.x + 1,m_Position.y };
		break;
	default:
		break;
	}
}

void CPlayer::UseItem(map<int, bagItem>::iterator it)
{
	type itemtype = CItemManager::getInstance()->getItem((*it).second.id)->getType();
	if (itemtype == POSION)
	{
		UsePosion((*it).second.id);
		
	}
		
	if (itemtype == WEAPON || itemtype == BODY || itemtype == NECK)
		equipment((CEquipment*)CItemManager::getInstance()->getItem((*it).second.id));
	(*it).second.num--;
	if ((*it).second.num <= 0)
		m_bag.erase(it);
}

void CPlayer::UsePosion(int id)
{
	CPosion* temp = (CPosion*)CItemManager::getInstance()->getItem(id);
	m_ichp += temp->hpRec();
	m_icmp += temp->mpRec();
	if (m_ichp > m_imhp)
		m_ichp = m_imhp;
	if (m_icmp > m_immp)
		m_icmp = m_immp;
	
}


void CPlayer::equipment(CEquipment * equ)
{
	string name = equ->getName();
	int id = equ->getId();
	type etype = equ->getType();
	int atk = equ->getAtk();
	int def = equ->getDef();
	int hp = equ->getHp();
	int mp = equ->getMp();
	int price = equ->getPrice();
	string discription = equ->getScrip();
	switch (etype)
	{
	case WEAPON:
		if (m_HaveWeapon==0)
		{
			
			m_Weapon->init(id, name, etype, atk, def, hp, mp, price, discription);
			m_HaveWeapon =1;
		}
			
		else
		{
			getItem(m_Weapon->getId(), 1);
			m_Weapon->init(id, name, etype, atk, def, hp, mp, price, discription);
		}
			
		break;
	case BODY:
		if (m_HaveArmor==0)
		{
			m_HaveArmor = 1;
			m_Armor->init(id, name, etype, atk, def, hp, mp, price, discription);
		}
		else
		{
			getItem(m_Armor->getId(), 1);
			m_Armor->init(id, name, etype, atk, def, hp, mp, price, discription);
		}
	
		break;
	case NECK:
		if (m_HaveJewlly==0)
		{
			m_HaveJewlly = 1;
			m_Jewlly->init(id, name, etype, atk, def, hp, mp, price, discription);
		}
		else
		{
			getItem(m_Jewlly->getId(), 1);
			m_Jewlly->init(id, name, etype, atk, def, hp, mp, price, discription);
		}
		break;
	default: break;
	}
	updateEqu();
}

void CPlayer::updateEqu()
{
	m_iatk = m_oatk + m_Weapon->getAtk() + m_Armor->getAtk() + m_Jewlly->getAtk();
	m_idef = m_odef + m_Weapon->getDef() + m_Armor->getDef() + m_Jewlly->getDef();
	m_imhp = m_iohp + m_Weapon->getHp() + m_Armor->getHp() + m_Jewlly->getHp();
	m_immp = m_iohp + m_Weapon->getMp() + m_Armor->getMp() + m_Jewlly->getMp();
}



void CPlayer::getItem(int id, int num)
{
	if (m_bag.find(id)==m_bag.end())
	{
		bagItem temp;
		temp.id = id;
		temp.num = num;
		m_bag.insert(make_pair(id, temp));
	}
	else
	{
		m_bag[id].num += num;
	}
	//for (list<CQuest>::iterator it1 = m_Quests.begin(); it1 != m_Quests.end(); it1++)
	//{
	//	for (list<quest>::iterator it2 = (*it1).m_questList.begin(); it2 != (*it1).m_questList.end(); it2++)
	//	{
	//		if ((*it2).item&&(*it2).id==id)
	//		{
	//			(*it2).doneNum+=num;
	//			if ((*it2).doneNum == (*it2).num)
	//				(*it2).complete = true;
	//			(*it1).update();

	//		}
	//	}
	//}
}

void CPlayer::init(int hp, int mp, int atk, int def)
{
	m_iohp = m_ichp = m_imhp = hp;
	m_immp = m_iomp = m_icmp = mp;
	m_iatk = m_oatk = atk;
	m_idef = m_odef = def;
}

void CPlayer::init(int hpo, int hpc, int mp, int atk, int def)
{
	m_imhp=m_iohp = hpo;
	m_ichp = hpc;
	m_immp = m_iomp = m_icmp = mp;
	m_iatk = m_oatk = atk;
	m_idef = m_odef = def;
}

void CPlayer::sell(CShop* shop)
{
	system("cls");
	Goto(5, 0);
	cout << "name";
	Goto(15, 0);
	cout << "num";
	Goto(25, 0);
	cout << "price";
	if (!m_bag.empty())
	{
		int i = 0;
		for (map<int, bagItem>::iterator it=m_bag.begin(); it != m_bag.end(); it++)
		{
			Goto(5, i + 1);
			cout << CItemManager::getInstance()->getItem((*it).second.id)->getName();
			Goto(15, i + 1);
			cout << (*it).second.num;
			Goto(25, i+1);
			cout << CItemManager::getInstance()->getItem((*it).second.id)->getPrice();
			i++;
		}
		i = 0;
	}
	else {
		Goto(15, 15);
		cout << "背包为空;";
		Sleep(500);
		shop->setStatus(MAIN);
		system("cls");
		return;
	}
	static int line = 0;
	if (GetAsyncKeyState('W') & 0x8000)
	{
		Sleep(50);
		line--;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		Sleep(50);
		line++;
	}
	if (line < 0)
		line = 0;
	if (line > m_bag.size())
		line = m_bag.size();
	Goto(2, line + 1);
	cout << "-->";
	if (GetAsyncKeyState('J') & 0x8000)
	{
		map<int, bagItem>::iterator it=m_bag.begin();
		for (int i = 0; i < line; i++)
		{
			it++;
		}
		(*it).second.num--;
		m_money += CItemManager::getInstance()->getItem((*it).second.id)->getPrice();
		if ((*it).second.num == 0)
			m_bag.erase(it);
	}
	if (GetAsyncKeyState('K') & 0x8000)
	{
		system("cls");
		shop->setStatus(MAIN);
	}
	
}

CPlayer::~CPlayer()
{
}
