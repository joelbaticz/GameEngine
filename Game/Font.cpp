#include "Font.h"

Font::Font()
{
	m_FontName = "Font";
	m_FileName = "FileName";
	m_Size = 10;
	m_TTF_Font = nullptr;
	//m_FontStyle = nullptr;
	//m_IsInitialized = false;
}

Font::~Font()
{}

std::string Font::GetFontName()
{
	return m_FontName;
}

void Font::SetFontName(std::string value)
{
	m_FontName = value;
}

std::string Font::GetFileName()
{
	return m_FileName;
}

void Font::SetFileName(std::string value)
{
	m_FileName = value;
}

int Font::GetSize()
{
	return m_Size;
}

void Font::SetSize(int value)
{
	m_Size = value;
}

TTF_Font* Font::GetTTFFont()
{
	return m_TTF_Font;
}

void Font::SetTTFFont(TTF_Font* value)
{
	m_TTF_Font = value;
}
