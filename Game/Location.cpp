#include "Location.h"

Location::Location()
{
	m_X = DEFAULT_X;
	m_Y = DEFAULT_Y;
}

Location::Location(int x, int y)
{
	m_X = x;
	m_Y = y;
}

Location::~Location()
{}

int Location::GetX()
{
	return m_X;
}

void Location::SetX(int value)
{
	m_X = value;
}

int Location::GetY()
{
	return m_Y;
}

void Location::SetY(int value)
{
	m_Y = value;
}

