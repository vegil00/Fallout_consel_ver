#pragma once
#include"ItemManager.h"
struct good {
	CItem* item;
	int num;
};
enum shopStatus{MAIN,BUY,SELL};

class CShop
{private:
	list<good> m_items;
	position m_pos;
	good** m_inScreen;
	int m_line;
	int m_pageNum;
	int m_curPage;
	int m_lastnum;
	shopStatus m_status;
public:
	CShop();
	void setPos(int x,int y);
	position getPos() { return m_pos; }
	void addItem(CItem* item,int num);
	void buyItem(CItem* item, int num);
	void trade();
	void reset();
	void setStatus(shopStatus s) { m_status = s; }
	~CShop();
};

