#pragma once

class CTeleportNode
{
private:
	position m_newPos;
	char* m_newMap;
	position m_nodePos;
	bool m_trans;
public:
	CTeleportNode();
	void init(position nodepos, position newpos, char* mapname);
	position getpos(){ return m_nodePos; }
	string getnewMap() { return m_newMap; }
	position getTelPos() { return m_newPos; }
	bool iftel() { return m_trans; }
	~CTeleportNode();
};

