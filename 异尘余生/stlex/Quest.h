#pragma once
#include"Cmonster_manager.h"
#include"ItemManager.h"
#include"Player.h"
enum QuestStatus{DIACTIVATE,ACTIVATE,COMPLETE};
struct quest { int id; int num; bool complete; bool kill; bool item; int doneNum; };
class CQuest
{
	friend class CPlayer;
private:
	int m_id;
	string m_name;
	string m_discription;
	QuestStatus m_status;

	list<quest> m_questList;
public:
	CQuest();
	void init(int id,string name,string discription,QuestStatus status,list<quest>questList);
	string getname() { return m_name; }
	string getDiscribe(){ return m_discription; }
	QuestStatus getStatus() { return m_status; }
	void update();

	~CQuest();
};

