#include "Size.h"

Size::Size()
{
	m_Width = DEFAULT_WIDTH;
	m_Height = DEFAULT_HEIGHT;
}

Size::Size(int width, int height)
{
	m_Width = width;
	m_Height = height;
}

Size::~Size()
{}

int Size::GetWidth()
{
	return m_Width;
}

void Size::SetWidth(int value)
{
	m_Width = value;
}

int Size::GetHeight()
{
	return m_Height;
}

void Size::SetHeight(int value)
{
	m_Height = value;
}

