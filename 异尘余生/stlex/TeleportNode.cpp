#include "stdafx.h"
#include "TeleportNode.h"



CTeleportNode::CTeleportNode()
{
	m_trans = 0;
	m_newMap = new char[10];
}

void CTeleportNode::init(position nodepos, position newpos, char * mapname)
{
	m_nodePos = nodepos;
	m_newPos = newpos;
	strcpy(m_newMap, mapname);
	m_trans = 1;
}




CTeleportNode::~CTeleportNode()
{
}
