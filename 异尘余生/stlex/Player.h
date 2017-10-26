#pragma once
#include"Cobject.h"
#include"Equipment.h"
#include"Posion.h"
#include"ItemManager.h"
#include"Quest.h"
#include"Shop.h"

enum direction {UP,DOWN,LEFT,RIGHT};
struct bagItem
{
	int id;
	int num;
};
class CPlayer:public Cobject

{
	friend class CsenceManager;

private:
	position m_PrePos;
	position m_ActPos;
	direction m_dir;
	CEquipment* m_Weapon;
	CEquipment* m_Armor;
	CEquipment* m_Jewlly;
	map<int, bagItem> m_bag;
	bool m_HaveWeapon;
	bool m_HaveArmor;
	bool m_HaveJewlly;
	int m_money;
	//list<CQuest> m_Quests;
public:
	CPlayer();
	void SetPrePos(position pre);
	void SetDir(direction dir);
	void SetActPos();
	void UseItem(map<int, bagItem>::iterator it);
	void UsePosion(int id);
	position getActPos() { return m_ActPos; }
	position getPrePos() { return m_PrePos; }
	void equipment(CEquipment* equ);
	void updateEqu();
	int getItemNum() { return m_bag.size(); }
	void getItem(int id, int num);
	int getMoney() { return m_money; }
	void earnMoney(int money) { m_money += money; }
	void setMoney(int money) {	m_money = money;}
	void buy(int price) { m_money -= price; }
	int getHpC() { return m_ichp; }
	int getHpM() { return m_imhp; }
	int getHPO() { return m_iohp; }
	int getATKO() { return m_oatk; }
	int getDEFO() { return m_odef; }
	map<int, bagItem>* getbag() { return &m_bag; }
	void init(int hp, int mp, int atk, int def);
	void init(int hpo,int hpc, int mp, int atk, int def);
	bool haveWeapon() { return m_HaveWeapon; }
	bool haveArmor() { return m_HaveArmor; }
	bool haveJewlly() { return m_HaveJewlly; }
	CEquipment* getWeapon() { return m_Weapon; }
	CEquipment* getArmor() { return m_Armor; }
	CEquipment* getJewlly() { return m_Jewlly; }
	void sell(CShop* shop);
	//list<CQuest>* getQuests(){ return &m_Quests; }
	~CPlayer();
};

