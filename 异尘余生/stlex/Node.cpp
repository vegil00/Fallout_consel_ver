#include"stdafx.h"
#include "Node.h"



CNode::CNode()
{
}

void CNode::init(bool pass, string out, int kind)
{
	m_passable = pass;
	m_Output = out;
	m_type = kind;
}


CNode::~CNode()
{
}
