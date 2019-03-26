#pragma once

#include <string>
#include <SDL_ttf.h>

class Font
{
private:
	std::string		m_FontName;
	std::string		m_FileName;
	int				m_Size;
	TTF_Font*		m_TTF_Font;
	//FontStyle*	m_FontStyle;
	//bool			m_IsInitialized; //??? Means = it is already loaded
public:
	//Constructors, destructor
	Font();
	~Font();

	//Accessor methods
	std::string GetFontName();
	void SetFontName(std::string value);
	std::string GetFileName();
	void SetFileName(std::string value);
	int GetSize();
	void SetSize(int value);
	TTF_Font* GetTTFFont();
	void SetTTFFont(TTF_Font* value);
};