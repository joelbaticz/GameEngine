#include "TextureAtlas.h"

TextureAtlas::TextureAtlas()
{

}

TextureAtlas::~TextureAtlas()
{

}

void TextureAtlas::GetTextureRectangle(int textureIndex, SDL_Rect* targetRect)
{


	targetRect->x = 0;
	targetRect->y = 0;
	targetRect->w = 0;
	targetRect->h = 0;
	SDL_QueryTexture(this->GetTexture(), NULL, NULL, &targetRect->w, &targetRect->h);


	double columnCount = (double)targetRect->w / (double)m_TextureWidth;
	double rowCount = (double)targetRect->w / (double)m_TextureHeight;

}
