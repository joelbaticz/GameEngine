#pragma once

#include <string>
#include "SDL.h"
#include <SDL_image.h>

class Texture
{
private:
	std::string		m_ResourceName;
	std::string		m_ResourceFileName;
	int				m_Width;  //Set when the resource is loaded -> needed to calculate how many textures in one row
	int				m_Height; //Set when the resource is loaded -> needed to calculate how many textures in one column
	int				m_HorizontalCount;
	int				m_VerticalCount;
	SDL_Texture*	m_SDL_Texture;
public:
	Texture();
	~Texture();

	std::string GetResourceName();
	void SetResourceName(std::string resourceName);

	std::string GetResourceFileName();
	//Purpusefully not exposed, since if we change the ResourceFileName we need to reload the texture
	//Why not drop it and recreate it then?
	//AssetManager needs to set the resource name (if we don't set everything in the Texture constructor
	void SetResourceFileName(std::string resourceFileName);

	SDL_Texture* GetTexture();
	void SetTexture(SDL_Texture* texture);

	int GetWidth();
	void SetWidth(int width);

	int GetHeight();
	void SetHeight(int height);

	int GetHorizontalCount();
	void SetHorizontalCount(int horizontalCount);

	int GetVerticalCount();
	void SetVerticalCount(int verticalCount);

	void GetTextureRectangle(int textureIndex, SDL_Rect* targetRect);
};