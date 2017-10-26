#include"stdafx.h"
#include "Shop.h"
#include"SenceManager.h"



CShop::CShop()
{
	m_curPage = 0;
	m_line = 0;
	m_status = MAIN;
}

void CShop::setPos(int x, int y)
{
	m_pos.x = x;
	m_pos.y = y;
}


void CShop::addItem(CItem * item, int num)
{
	good temp;
	temp.item = item;
	temp.num = num;
	m_items.push_back(temp);
}

void CShop::buyItem(CItem * item, int num)
{
	list<good>::iterator it;
	for (it = m_items.begin(); it != m_items.end();)
	{
		if ((*it).item->getId() == item->getId())
		{
			if (num > (*it).num)
				num = (*it).num;
			(*it).num -= num;
			if ((*it).num == 0)
			{
				it = m_items.erase(it);
				system("cls");
				break;
			}
			break;
		}
		else
			it++;
	}
}

void CShop::trade()
{
	Sleep(100);
	if (m_status == MAIN)
	{
		
		Goto(15, 10);
		cout << "BUY";
		Goto(15, 13);
		cout << "SELL";
		for (int i = 0; i < 2; i++)
		{
			Goto(12, 10 + i * 3);
			if (i == m_line)
				cout << "-->";
			else
				cout << "   ";

		}
		if (GetAsyncKeyState('W') & 0x8000)
			m_line--;
		if (GetAsyncKeyState('S') & 0x8000)
			m_line++;
		if (GetAsyncKeyState('J') & 0x8000)
		{
			Sleep(100);
			switch (m_line)
			{
			case 0:
				m_status = BUY;
				break;
			case 1:
				m_status = SELL;
				break;
			default:
				break;
			}
		}
		if (GetAsyncKeyState('K') & 0x8000)
		{
			Sleep(100);
			reset();
			//m_status = MAIN;
			system("cls");
			CSenceManager::GetInstance()->setStatus(SENCE);
			CSenceManager::GetInstance()->Rend();
			return;
		}
		if (m_line < 0)
			m_line = 0;
		if (m_line > 1)
			m_line = 1;
		
	}
	if(m_status==BUY)
	{
		system("cls");
		list<good>::iterator it = m_items.begin();
		m_inScreen = new good*[5];
		bool over = 0;
		int goodNum;
		for (int i = 0; i < 5; i++)
		{
			if (over)
			{
				m_pageNum = i - 1;
				break;
			}
			m_inScreen[i] = new good[5];
			for (int j = 0; j < 5; j++)
			{
				if (it == m_items.end())
				{
					m_lastnum = j - 1;
					over = 1;
					break;
				}
				m_inScreen[i][j] = (*it);
				it++;
			}
		}
		Goto(5, 0);
		cout << "name";
		Goto(15, 0);
		cout << "num";
		Goto(25, 0);
		cout << "price";
		for (int i = 0; i < 5; i++)
		{
			Goto(5, i + 1);
			cout << m_inScreen[m_curPage][i].item->getName();
			Goto(15, i + 1);
			cout << m_inScreen[m_curPage][i].num;
			Goto(25, i + 1);
			cout << m_inScreen[m_curPage][i].item->getPrice() * 2;
			if (m_curPage == m_pageNum&&i == m_lastnum)
				break;
		}
		for (int i = 0; i <= m_lastnum; i++)
		{
			Goto(3, i + 1);
			if (i == m_line)
				cout << "-->";
			else
				cout << "   ";

		}




		if (GetAsyncKeyState('W') & 0x8000)
		{
			Sleep(50);
			m_line--;
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			Sleep(50);
			m_line++;
		}

		if (GetAsyncKeyState('J') & 0x8000)
		{
			Sleep(100);
			int itemnum = CSenceManager::GetInstance()->getPlayer()->getItemNum();
			int money = CSenceManager::GetInstance()->getPlayer()->getMoney();
			int price = m_inScreen[m_curPage][m_line].item->getPrice() * 2;
			if (itemnum < 16 && money >= price)
			{
				buyItem(m_inScreen[m_curPage][m_line].item, 1);
				int id = m_inScreen[m_curPage][m_line].item->getId();
				CSenceManager::GetInstance()->getPlayer()->getItem(id, 1);
				CSenceManager::GetInstance()->getPlayer()->buy(price);
			}
			if (money < price)
			{
				Goto(10, 11);
				cout << "Ç®²»¹»";
			}
			if (itemnum == 16)
			{
				Goto(10, 11);
				cout << "±³°üÒÑÂú";
			}


		}
		if (GetAsyncKeyState('K') & 0x8000)
		{
			Sleep(100);
			reset();
			m_status = MAIN;
			system("cls");
			//CSenceManager::GetInstance()->setStatus(SENCE);
			//CSenceManager::GetInstance()->Rend();
			return;
		}

		if (m_line < 0 && m_curPage>0)
		{
			m_line = 0;
			m_curPage--;
		}
		if (m_line > 5 && m_curPage < m_pageNum)
		{
			m_line = 0;
			m_curPage++;

		}
		if (m_line > m_lastnum && m_curPage == m_pageNum)
		{
			m_line = m_lastnum;
		}
		if (m_line < 0 && m_curPage == 0)
		{
			m_line = 0;
		}
		Goto(30, 0);
		cout << "money:" << CSenceManager::GetInstance()->getPlayer()->getMoney();
		Goto(15, 10);
		cout << m_inScreen[m_curPage][m_line].item->getScrip();
	}
	if (m_status == SELL)
	{
		CSenceManager::GetInstance()->getPlayer()->sell(this);
	}
	
}

void CShop::reset()
{
	m_line = 0;
	m_curPage = 0;
}

CShop::~CShop()
{
}
