#pragma once

#include "Texture.h"

class TextureAtlas : public Texture
{
public:
	TextureAtlas();
	~TextureAtlas();

	//int		m_ColumnCount;
	//int		m_RowCount;
	int			m_TextureWidth;
	int			m_TextureHeight;

	void GetTextureRectangle(int textureIndex, SDL_Rect* targetRect);

};