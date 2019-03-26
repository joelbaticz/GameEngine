#include "AssetManager.h"

//Specify path seperator based on which platform we are using
#ifdef _WIN32
std::string PATH_SEPARATOR = "\\";
#else
std::string PATH_SEPARATOR = "/";
#endif

std::string		AssetManager::m_SystemName;
std::string		AssetManager::m_ImageResourcePath;
std::string		AssetManager::m_FontResourcePath;
std::string		AssetManager::m_SoundResourcePath;
Font*			AssetManager::m_DefaultFont;
Color*			AssetManager::m_DefaultPenColor;
Color*			AssetManager::m_DefaultFillColor;
Texture*		AssetManager::m_DefaultTexture;
//TextureAtlas*	AssetManager::m_DefaultTextureAtlas;

Font*			AssetManager::m_FontAssets;
int				AssetManager::m_FontAssetCount;
Texture*		AssetManager::m_TextureAssets;
int				AssetManager::m_TextureAssetCount;

Color*			AssetManager::m_ColorAssets;
int				AssetManager::m_ColorAssetsCount;
int				AssetManager::m_ColorAssetsLastId;

//Hidden Constructor - won't be called - since it's static (no instantiation)
AssetManager::AssetManager()
{
	LogEngine::Log(LOG_TRACE, m_SystemName, "Constructor called.");
}

//Hidden Desctructor - won't be called - since it's static (no instantiation)
AssetManager::~AssetManager()
{
	LogEngine::Log(LOG_TRACE, m_SystemName, "Destructor called.");
}

int AssetManager::SetUpResourcePaths()
{
	//Gather the BasePath from SDL (we use static, so it will be global --> we need to querry only once)
	static std::string basePath;

	if (basePath.empty())
	{
		basePath = SDL_GetBasePath();

		if (basePath.empty())
		{
			//Error("getResourcePath", SDL_GetError());
			return 1;
		}
		else
		{
			int pos = basePath.rfind("bin");
			basePath = basePath.substr(0, pos);
		}
	}

	m_ImageResourcePath = basePath + "res" + PATH_SEPARATOR + "images" + PATH_SEPARATOR;
	m_FontResourcePath = basePath + "res" + PATH_SEPARATOR + "fonts" + PATH_SEPARATOR;
	m_SoundResourcePath = basePath + "res" + PATH_SEPARATOR + "sounds" + PATH_SEPARATOR;

	LogEngine::Log(LOG_TRACE, m_SystemName, "ImageResourcePath: " + m_ImageResourcePath);
	LogEngine::Log(LOG_TRACE, m_SystemName, "FontResourcePath: " + m_FontResourcePath);
	LogEngine::Log(LOG_TRACE, m_SystemName, "SoundResourcePath: " + m_SoundResourcePath);

	return 0;
}

int AssetManager::Init(std::string resourcePath)
{
	m_SystemName = "AssetManager";
	m_ImageResourcePath = "";
	m_FontResourcePath = "";
	m_SoundResourcePath = "";
	m_FontAssets = nullptr;
	m_FontAssetCount = 0;
	m_TextureAssets = nullptr;
	m_FontAssetCount = 0;

	LogEngine::Log(LOG_TRACE, m_SystemName, "Init() called.");

	//Set up Paths
	if (AssetManager::SetUpResourcePaths() != 0)
	{
		LogEngine::Log(LOG_ERROR, m_SystemName, "Init...ERROR.");
		return 1;
	};

	//Create Default Font
	m_DefaultFont = CreateFont("segoeui.ttf", 12);
	if (m_DefaultFont == nullptr)
	{
		LogEngine::Log(LOG_ERROR, m_SystemName, "CreateFont()...ERROR.");
		return 1;
	}

	//Create Default Colors
	m_DefaultPenColor = CreateColor(255, 192, 192, 192);
	m_DefaultFillColor = CreateColor(255, 128, 128, 128);
	if (m_DefaultPenColor == nullptr || m_DefaultFillColor == nullptr)
	{
		LogEngine::Log(LOG_ERROR, m_SystemName, "CreateColor()...ERROR.");
		return 1;
	}

	//Create Default Texture Image
	m_DefaultTexture = CreateTexture("Button.png");
	if (m_DefaultTexture == nullptr)
	{
		LogEngine::Log(LOG_ERROR, m_SystemName, "CreateTextureImage()...ERROR.");
		return 1;
	}
	m_DefaultTexture->SetHorizontalCount(8);
	m_DefaultTexture->SetVerticalCount(7);


	LogEngine::Log(LOG_TRACE, m_SystemName, "Init()...OK.");

	return 0;
}

Color* AssetManager::CreateColor(int a, int r, int g, int b)
{
	Color* newColor = new Color();
	newColor->m_ResourceName = "Color" + m_ColorAssetsLastId;

	//Put it in ColorAssetList

	newColor->m_SDL_Color = new SDL_Color();
	newColor->m_SDL_Color->a = a;
	newColor->m_SDL_Color->r = r;
	newColor->m_SDL_Color->g = g;
	newColor->m_SDL_Color->b = b;



	return newColor;
}

Color* AssetManager::GetDefaultPenColor()
{
	return m_DefaultPenColor;
}

Color* AssetManager::GetDefaultFillColor()
{
	return m_DefaultFillColor;
}

Font* AssetManager::CreateFont(std::string fontFileName, int size)
{
	std::string path = m_FontResourcePath + fontFileName;

	Font* newFont = new Font();
	newFont->SetFontName("Font" + m_FontAssetCount);
	newFont->SetFontName(fontFileName);
	newFont->SetSize(size);
	newFont->SetTTFFont(TTF_OpenFont(path.c_str(), size));

	if (newFont->GetTTFFont() == nullptr)
	{
		delete newFont;
		return nullptr;
	}

	//Add to FontAssetList

	return newFont;
}

Font* AssetManager::GetDefaultFont()
{
	return m_DefaultFont;
}

Texture* AssetManager::CreateTexture(std::string imageFileName)
{
	Texture* newTexture = nullptr; //Return null if texture could not be created
	
	SDL_Texture* newSDLTexture = nullptr;
	newSDLTexture = IMG_LoadTexture(RenderingEngine::GetRenderer(), (m_ImageResourcePath + imageFileName).c_str());

	if (newSDLTexture == nullptr)
	{
		LogEngine::Log(LOG_TRACE, m_SystemName, "CreateTexture() failed on " + imageFileName);
		return nullptr;
	}

	int textureWidth = 0;
	int textureHeight = 0;
	SDL_QueryTexture(newSDLTexture, NULL, NULL, &textureWidth, &textureHeight);

	newTexture =new Texture();
	newTexture->SetResourceName("TextureImage");
	newTexture->SetResourceFileName(imageFileName);
	newTexture->SetTexture(newSDLTexture);
	newTexture->SetWidth(textureWidth);
	newTexture->SetHeight(textureHeight);

	return newTexture;
}

Texture* AssetManager::GetDefaultTexture()
{
	return m_DefaultTexture;
}

//TextureAtlas* AssetManager::CreateTextureAtlas(std::string imageFileName, int textureWidth, int textureHeight)
//{
//	TextureAtlas* newAtlas = new TextureAtlas();
//	return newAtlas;
//}