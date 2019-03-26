#pragma once

#define DEFAULT_X		10
#define DEFAULT_Y		10

class Location
{
private:
	int	m_X;
	int	m_Y;
public:
	Location();
	Location(int x, int y);
	~Location();

	int GetX();
	void SetX(int value);
	int GetY();
	void SetY(int value);
};