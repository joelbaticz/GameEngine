#pragma once

#include <string>
#include "SDL.h"
#include "LogEngine.h"
#include "RenderingEngine.h"
#include "Node.h"
#include "Color.h"
#include "Font.h"
#include "Texture.h"


class RenderingEngine
{
private:
	static std::string		m_SystemName;
	static SDL_Window*		m_Window;
	static SDL_Renderer*    m_Renderer;
	static Color*			m_CurrentPenColor;
	static Color*			m_CurrentFillColor;

	RenderingEngine();
	~RenderingEngine();

public:
	static int Init(std::string windowTitle, int windowX, int windowY, int windowWidth, int windowHeigh);
	static void UnInit();
	static void BeginFrame();
	static void PresentFrame();
	static SDL_Renderer* GetRenderer();
	static void SetPenColor(Color* color);
	static void SetFillColor(Color* color);
	static SDL_Color* ColorToSDLColor(Color* color);
	static void DrawRectangle(Node* node, int x, int y, int w, int h);
	static void DrawText(Node* node, std::string text, Font* font, int x, int y);
	static void DrawTexture(Node* node, Texture* texture, int x, int y);
	static void DrawTexture(Node* node, Texture* texture, SDL_Rect* rectSource, SDL_Rect* rectTarget);

	static SDL_Rect* ClientRectToScreenRect(Node* node, SDL_Rect* rect);
};