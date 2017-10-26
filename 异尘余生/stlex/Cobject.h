#pragma once

class Cobject
{protected:
	int m_oatk;
	int m_odef;
	int m_iatk;
	int m_idef;
	int m_imhp;
	int m_iohp;
	int m_ichp;
	int m_immp;
	int m_iomp;
	int m_icmp;
	position m_Position;

public:
	Cobject();
	void Atk(Cobject* target);
	void Atked(int atk);
	position Getpos() { return m_Position; }
	void Setpos(int x, int y) { m_Position.x = x; m_Position.y = y; }
	int getAtk() { return m_iatk; }
	int getDef() { return m_idef; }
	virtual ~Cobject();
};

