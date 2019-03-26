#pragma once

#include "Texture.h"

class TextureImage: public Texture
{
public:

	int		m_ColumnCount;
	int		m_RowCount;

	TextureImage();
	~TextureImage();

	void GetTextureRectangle(int textureIndex, SDL_Rect* targetRect);
};