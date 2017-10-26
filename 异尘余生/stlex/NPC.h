#pragma once
#include"Player.h"
class CNPC
{private:
	string m_name;
	int m_id;
	string m_dialog[10];
	int m_index;
public:
	CNPC();
	void init(int id, string name);
	void setIndex(int index);
	void updateIndex() { m_index++; }
	void addDialog(string str, int index) { m_dialog[index] = str; }
	string talk() { return m_dialog[m_index]; }
	string talk(int index) { return m_dialog[index]; }
	string getname() { return m_name; }
	~CNPC();
};

