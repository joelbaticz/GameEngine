#include "RenderingEngine.h"
#include "GameEngine.h"

std::string			RenderingEngine::m_SystemName;
SDL_Window*			RenderingEngine::m_Window;
SDL_Renderer*		RenderingEngine::m_Renderer;
Color*				RenderingEngine::m_CurrentPenColor;
Color*				RenderingEngine::m_CurrentFillColor;

//Hidden Constructor - won't be called - since it's static (no instantiation)
RenderingEngine::RenderingEngine()
{
	LogEngine::Log(LOG_TRACE, m_SystemName, "Constructor called.");
}

//Hidden Desctructor
RenderingEngine::~RenderingEngine()
{
	LogEngine::Log(LOG_TRACE, m_SystemName, "Destructor called.");
}

int RenderingEngine::Init(std::string windowTitle, int windowX, int windowY, int windowWidth, int windowHeight)
{
	m_SystemName = "RenderingEngine";
	m_Window = nullptr;
	m_Renderer = nullptr;
	m_CurrentFillColor = nullptr;
	m_CurrentPenColor = nullptr;

	LogEngine::Log(LOG_TRACE, m_SystemName, "Init() called.");

	//Set up SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		LogEngine::Log(LOG_ERROR, m_SystemName, SDL_GetError());
		return 1;
	}
	LogEngine::Log(LOG_TRACE, m_SystemName, "SDL_Init...OK");

	//Init img subsystem
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		LogEngine::Log(LOG_ERROR, m_SystemName, SDL_GetError());
		return 1;
	}
	LogEngine::Log(LOG_TRACE, m_SystemName, "SDL_Image...OK");

	//Init ttf subsystem
	if (TTF_Init() != 0)
	{
		LogEngine::Log(LOG_ERROR, m_SystemName, SDL_GetError());
		return 1;
	}
	LogEngine::Log(LOG_TRACE, m_SystemName, "SDL_Ttf...OK");

	//Create primary window
	m_Window = SDL_CreateWindow("Hello World!", windowX, windowY, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (m_Window == nullptr)
	{
		LogEngine::Log(LOG_ERROR, m_SystemName, SDL_GetError());
		return 1;
	}
	LogEngine::Log(LOG_TRACE, m_SystemName, "Creating window...OK");

	//Create window renderer
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_TARGETTEXTURE);// | SDL_RENDERER_ACCELERATED);// | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr)
	{
		LogEngine::Log(LOG_ERROR, m_SystemName, SDL_GetError());
		return 1;
	}
	LogEngine::Log(LOG_TRACE, m_SystemName, "Creating renderer...OK");

	//Set Clearing Color
	SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);

	LogEngine::Log(LOG_TRACE, m_SystemName, "Setting background color...OK");
	
	//Setup Colors
	m_CurrentPenColor = AssetManager::CreateColor(255, 192, 192, 192);
	m_CurrentFillColor = AssetManager::CreateColor(255, 128, 128, 128);
	
	LogEngine::Log(LOG_TRACE, m_SystemName, "Init()...OK.");
	return 0;
}

void RenderingEngine::SetPenColor(Color* color)
{
	m_CurrentPenColor = color;
}

void RenderingEngine::SetFillColor(Color* color)
{
	m_CurrentFillColor = color;
}



void RenderingEngine::BeginFrame()
{
	//Set DrawColor before???
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);

	SDL_RenderClear(m_Renderer);
}

void RenderingEngine::PresentFrame()
{
	SDL_RenderPresent(m_Renderer);
}

SDL_Renderer* RenderingEngine::GetRenderer()
{
	return m_Renderer;
}

void RenderingEngine::UnInit()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
	}

	if (m_Window != nullptr)
	{
		SDL_DestroyWindow(m_Window);
	}

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Color* RenderingEngine::ColorToSDLColor(Color* color)
{
	//THIS REALLY SHOULD BE A FUNCTION IN COLOR.CPP

	SDL_Color* sdlColor = new SDL_Color();
	//sdlColor->a = color->a;
	//sdlColor->r = color->r;
	//sdlColor->g = color->g;
	//sdlColor->b = color->b;

	return sdlColor;
}

SDL_Rect* RenderingEngine::ClientRectToScreenRect(Node* node, SDL_Rect* rect)
{
	//Should create new Rect for result???

	//node = node->GetParent();
	//We need to process the current node as well
	while (node != nullptr)
	{
		if (dynamic_cast<CanvasNode*>(node))
		{
			//Node is Drawable
			CanvasNode* cNode = (CanvasNode*)node;
			int cNodeX = cNode->GetLocation()->GetX();
			int cNodeY = cNode->GetLocation()->GetY();
			int cNodeW = cNode->GetSize()->GetWidth();
			int cNodeH = cNode->GetSize()->GetHeight();

			//SDL_Rect* nodeRect = cNode->GetRect();
			//rect->x += nodeRect->x;
			//rect->y += nodeRect->y;
			//if (rect->x + rect->w > nodeRect->x + nodeRect->w)
			//{
			//	rect->w = nodeRect->x + nodeRect->w - rect->x;
			//}
			//if (rect->y + rect->h > nodeRect->y + nodeRect->h)
			//{
			//	rect->h = nodeRect->y + nodeRect->h - rect->y;
			//}
			//if (rect->w < 0) rect->w = 0;
			//if (rect->h < 0) rect->h = 0;

			rect->x += cNodeX;
			rect->y += cNodeY;
			if (rect->x + rect->w > cNodeX + cNodeW)
			{
				rect->w = cNodeX + cNodeW - rect->x;
			}
			if (rect->y + rect->h > cNodeY + cNodeH)
			{
				rect->h = cNodeY + cNodeH - rect->y;
			}
			if (rect->w < 0) rect->w = 0;
			if (rect->h < 0) rect->h = 0;

		}
		node = node->GetParent();
	}
	return rect;
}

void RenderingEngine::DrawRectangle(Node* node, int x, int y, int w, int h)
{
	SDL_Rect* rect = new SDL_Rect();
	rect->x = x; //The rectangles containing rect will be added at ClientRectToScreen calculation
	rect->y = y;
	rect->w = w;
	rect->h = h;
	rect = ClientRectToScreenRect(node->GetParent(), rect);
	if (rect->w != 0 && rect->h != 0)
	{
		SDL_SetRenderDrawColor(m_Renderer, m_CurrentFillColor->m_SDL_Color->r, m_CurrentFillColor->m_SDL_Color->g, m_CurrentFillColor->m_SDL_Color->b, m_CurrentFillColor->m_SDL_Color->a);
		SDL_RenderFillRect(m_Renderer, rect);
		SDL_SetRenderDrawColor(m_Renderer, m_CurrentPenColor->m_SDL_Color->r, m_CurrentPenColor->m_SDL_Color->g, m_CurrentPenColor->m_SDL_Color->b, m_CurrentPenColor->m_SDL_Color->a);
		SDL_RenderDrawRect(m_Renderer, rect);
	}
}

void RenderingEngine::DrawText(Node* node, std::string text, Font* font, int x, int y)
{
	SDL_Surface* surface = nullptr;
	//surface = TTF_RenderText_Solid(font->m_TTF_Font, text.c_str(), *colorForeground);
	//surface = TTF_RenderText_Shaded(font->m_TTF_Font, text.c_str(), *colorForeground, *colorBackground);
	SDL_Color* sdlColor = m_CurrentPenColor->m_SDL_Color;
	surface = TTF_RenderText_Solid(font->GetTTFFont(), text.c_str(), *sdlColor);

	if (surface == nullptr)
	{
		LogEngine::Log(LOG_ERROR, m_SystemName, "TTF_RenderText_Solid() ERROR.");
		return;
	}

	SDL_Texture* drawableTexture = SDL_CreateTextureFromSurface(m_Renderer, surface);
	
	SDL_Rect* rectTarget = new SDL_Rect();
	rectTarget->x = x;
	rectTarget->y = y;
	rectTarget->w = surface->w;
	rectTarget->h = surface->h;
	rectTarget = ClientRectToScreenRect(node, rectTarget);

	SDL_Rect* rectSource = new SDL_Rect();
	rectSource->x = 0;
	rectSource->y = 0;
	rectSource->w = rectTarget->w;
	rectSource->h = rectTarget->h;

	//SDL_SetRenderDrawColor(m_Renderer, m_CurrentFillColor->m_SDL_Color->r, m_CurrentFillColor->m_SDL_Color->g, m_CurrentFillColor->m_SDL_Color->b, m_CurrentFillColor->m_SDL_Color->a);
	//SDL_RenderFillRect(m_Renderer, rectTarget);

	if (rectTarget->w != 0 && rectTarget->h != 0)
	{
		SDL_RenderCopy(m_Renderer, drawableTexture, rectSource, rectTarget);
	}
	
	delete rectTarget;
	delete rectSource;
//	delete texture;
	SDL_DestroyTexture(drawableTexture);
	SDL_FreeSurface(surface);
}

void RenderingEngine::DrawTexture(Node* node, Texture* texture, int x, int y)
{
	//THERE IS ANOTHER DRAWTEXTURE WHICH SPRITENODE IS USING!!!

	SDL_Texture* drawableTexture = texture->GetTexture();

	SDL_Rect* rectTarget = new SDL_Rect();
	rectTarget->x = x;
	rectTarget->y = y;
	rectTarget->w = texture->GetWidth();
	rectTarget->h = texture->GetHeight();
	rectTarget = ClientRectToScreenRect(node->GetParent(), rectTarget);

	SDL_Rect* rectSource = new SDL_Rect();
	rectSource->x = 0;
	rectSource->y = 0;
	rectSource->w = rectTarget->w;
	rectSource->h = rectTarget->h;

	//SDL_SetRenderDrawColor(m_Renderer, m_CurrentFillColor->m_SDL_Color->r, m_CurrentFillColor->m_SDL_Color->g, m_CurrentFillColor->m_SDL_Color->b, m_CurrentFillColor->m_SDL_Color->a);
	//SDL_RenderFillRect(m_Renderer, rectTarget);

	if (rectTarget->w != 0 && rectTarget->h != 0)
	{
		//SDL_SetTextureAlphaMod(drawableTexture, 128);
		SDL_SetTextureColorMod(drawableTexture, 255, 0, 0);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		SDL_RenderCopy(m_Renderer, drawableTexture, rectSource, rectTarget);
	}

	delete rectTarget;
	delete rectSource;
	//Do not delete the sdl texture - it belongs to the TextureImage
	//	delete texture;
	//SDL_DestroyTexture(texture);
}

void RenderingEngine::DrawTexture(Node* node, Texture* texture, SDL_Rect* rectSource, SDL_Rect* rectTarget)
{
	SDL_Texture* drawableTexture = texture->GetTexture();

	//SDL_Rect* rectTarget = new SDL_Rect();
	//rectTarget->x = x;
	//rectTarget->y = y;
	//rectTarget->w = texture->GetWidth();
	//rectTarget->h = texture->GetHeight();
	rectTarget = ClientRectToScreenRect(node->GetParent(), rectTarget);

	//SDL_Rect* rectSource = new SDL_Rect();
	//rectSource->x = 0;
	//rectSource->y = 0;
	//rectSource->w = rectTarget->w;
	//rectSource->h = rectTarget->h;

	//SDL_SetRenderDrawColor(m_Renderer, m_CurrentFillColor->m_SDL_Color->r, m_CurrentFillColor->m_SDL_Color->g, m_CurrentFillColor->m_SDL_Color->b, m_CurrentFillColor->m_SDL_Color->a);
	//SDL_RenderFillRect(m_Renderer, rectTarget);

	if (rectTarget->w != 0 && rectTarget->h != 0)
	{
		//SDL_SetTextureBlendMode(drawableTexture, SDL_BLENDMODE_BLEND);
		//SDL_SetTextureAlphaMod(drawableTexture, 240);
		//SDL_SetTextureColorMod(drawableTexture, 255, 0, 0);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		SDL_RenderCopy(m_Renderer, drawableTexture, rectSource, rectTarget);
	}

	//delete rectTarget;
	//delete rectSource;
	//Do not delete the sdl texture - it belongs to the TextureImage
	//	delete texture;
	//SDL_DestroyTexture(texture);
}