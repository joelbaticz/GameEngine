#pragma once

#include "GameEngine.h"
#include "Color.h"
#include "Font.h"
#include "Texture.h"
//#include "TextureImage.h"
//#include "TextureAtlas.h"



class AssetManager
{
private:
	static std::string			m_SystemName;
	static std::string			m_ImageResourcePath;
	static std::string			m_FontResourcePath;
	static std::string			m_SoundResourcePath;

	//Default values
	static Font*				m_DefaultFont;
	static Color*				m_DefaultPenColor;
	static Color*				m_DefaultFillColor;
	static Texture*				m_DefaultTexture;
	
	static Color*				m_ColorAssets;
	static int					m_ColorAssetsCount;
	static int					m_ColorAssetsLastId;
	static Font*				m_FontAssets;
	static int					m_FontAssetCount;
	static Texture*				m_TextureAssets;
	static int					m_TextureAssetCount;
	
	AssetManager();
	~AssetManager();
	static int SetUpResourcePaths();

public:
	static int Init(std::string resourcePath);
	static void UnInit();

	static Color* CreateColor(int a, int r, int g, int b);
	static Color* GetDefaultPenColor();
	static Color* GetDefaultFillColor();

	static Font* CreateFont(std::string fontFileName, int size);
	static Font* GetDefaultFont();

	static Texture* CreateTexture(std::string imageFileName);
	//static TextureImage* CreateTextureImageEmpty //Not from file. Like just a render target for the TileMap for example
	static Texture* GetDefaultTexture();


	//static TextureAtlas* CreateTextureAtlas(std::string imageFileName, int textureWidth, int textureHeight);
	//static TextureAtlas* GetDefaultTextureAtlas();
	

};