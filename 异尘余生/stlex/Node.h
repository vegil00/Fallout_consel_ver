#pragma once

class CNode
{private:
	bool m_passable;
	string m_Output;
	int m_type;
public:
	CNode();
	void init(bool pass, string out, int kind);
	string out() { return m_Output; }
	bool pass() { return m_passable; }
	~CNode();
};

