#include "Texture.h"

Texture::Texture()
{
	m_ResourceName = "Texture";
	m_ResourceFileName = "\\";
	m_Width = 0;
	m_Height = 0;
	m_HorizontalCount = 1;
	m_VerticalCount = 1;
	m_SDL_Texture = nullptr;
}

Texture::~Texture()
{

}

std::string Texture::GetResourceName()
{
	return m_ResourceName;
}

void Texture::SetResourceName(std::string resourceName)
{
	m_ResourceName = resourceName;
}

std::string Texture::GetResourceFileName()
{
	return m_ResourceFileName;
}

void Texture::SetResourceFileName(std::string resourceFileName)
{
	m_ResourceFileName = resourceFileName;
}

SDL_Texture* Texture::GetTexture()
{
	return m_SDL_Texture;
}

void Texture::SetTexture(SDL_Texture* texture)
{
	m_SDL_Texture = texture;
}

int Texture::GetWidth()
{
	return m_Width;
}

void Texture::SetWidth(int width)
{
	m_Width = width;
}

int Texture::GetHeight()
{
	return m_Height;
}

void Texture::SetHeight(int height)
{
	m_Height = height;
}

int Texture::GetHorizontalCount()
{
	return m_HorizontalCount;
}

void Texture::SetHorizontalCount(int horizontalCount)
{
	m_HorizontalCount = horizontalCount;
}

int Texture::GetVerticalCount()
{
	return m_VerticalCount;
}

void Texture::SetVerticalCount(int verticalCount)
{
	m_VerticalCount = verticalCount;
}

void Texture::GetTextureRectangle(int textureIndex, SDL_Rect* targetRect)
{
	//targetRect->x = 0;
	//targetRect->y = 0;
	//targetRect->w = 0;
	//targetRect->h = 0;
	//SDL_QueryTexture(this->GetTexture(), NULL, NULL, &targetRect->w, &targetRect->h);
	
	int textureWidth = this->m_Width / m_HorizontalCount;
	int textureHeight = this->m_Height / m_VerticalCount;

	int column = textureIndex % m_HorizontalCount;
	int row = textureIndex / m_HorizontalCount;

	targetRect->x = column * textureWidth;
	targetRect->y = row * textureHeight;
	targetRect->w = textureWidth;
	targetRect->h = textureHeight;
	


}