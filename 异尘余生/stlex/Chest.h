#pragma once
struct boxitem { int id; int num; };
class CChest
{private:
	list<boxitem> m_items;
	position m_pos;
public:
	CChest();
	void additem(int id,int num);
	list<boxitem>* getbox() { return &m_items; }
	position getpos() { return m_pos; }
	void setpos(int x, int y) { m_pos.x = x; m_pos.y = y; }
	void viewitem();
	bool empty();
	~CChest();
};

