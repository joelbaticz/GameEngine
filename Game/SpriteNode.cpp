#include "SpriteNode.h"
#include "RenderingEngine.h"


SpriteNode::SpriteNode()
{
	SetName("SpriteNode");
	m_Texture = nullptr;
	m_CornerSize = 0;
	m_TextureIndex = 0;
	//m_Layout = LayoutTile;
	//m_Align = AlignLeft

	//m_Texture = AssetManager::CreateTexture("Button.png");
	//m_Texture->SetHorizontalCount(1);
	//m_Texture->SetVerticalCount(5);
}

SpriteNode::~SpriteNode()
{

}

Texture* SpriteNode::GetTexture()
{
	return m_Texture;
}

void SpriteNode::SetTexture(Texture* value)
{
	m_Texture = value;
}

int SpriteNode::GetCornerSize()
{
	return m_CornerSize;
}

void SpriteNode::SetCornerSize(int value)
{
	m_CornerSize = value;
}

int SpriteNode::GetTextureIndex()
{
	return m_TextureIndex;
}

void SpriteNode::SetTextureIndex(int value)
{
	m_TextureIndex = value;
}

void SpriteNode::Draw()
{
	//No call to parent is needed

	LogEngine::Log(LOG_DEBUG, "SpriteNode", "Draw() called on " + this->GetName());

	if (GetIsVisible())
	{

		//We don't have to know anything about the TextureImage or the TextureAtlas
		//We just try to grab whatever our TextureIndex says

		SDL_Rect* rectTexture = new SDL_Rect();
		m_Texture->GetTextureRectangle(m_TextureIndex, rectTexture);

		SDL_Rect* rectSprite = new SDL_Rect();
		rectSprite->x = this->GetLocation()->GetX();
		rectSprite->y = this->GetLocation()->GetY();
		rectSprite->w = this->GetSize()->GetWidth();
		rectSprite->h = this->GetSize()->GetHeight();

		//RenderingEngine::DrawTexture(this, m_Texture, 0, 0);
		//RenderingEngine::DrawTexture(this, m_Texture, rectTexture, this->GetRect());

		//Do 9TilePath thingy with using TextureIndex

		SDL_Rect* rectSource = new SDL_Rect();
		SDL_Rect* rectTarget = new SDL_Rect();
		int cs = m_CornerSize;

		//Top Left
		rectSource->x = rectTexture->x;
		rectSource->y = rectTexture->y;
		rectSource->w = cs;
		rectSource->h = cs;
		rectTarget->x = rectSprite->x;
		rectTarget->y = rectSprite->y;
		rectTarget->w = cs;
		rectTarget->h = cs;
		RenderingEngine::DrawTexture(this, m_Texture, rectSource, rectTarget);



		//Top Middle
		rectSource->x = rectTexture->x + cs;
		rectSource->y = rectTexture->y;
		rectSource->w = rectTexture->w - cs * 2;
		rectSource->h = cs;
		rectTarget->x = rectSprite->x + cs;
		rectTarget->y = rectSprite->y;
		rectTarget->w = rectSprite->w - cs * 2;
		rectTarget->h = cs;
		RenderingEngine::DrawTexture(this, m_Texture, rectSource, rectTarget);

		//Top Right
		rectSource->x = rectTexture->x + rectTexture->w - cs;
		rectSource->y = rectTexture->y;
		rectSource->w = cs;
		rectSource->h = cs;
		rectTarget->x = rectSprite->x + rectSprite->w - cs;
		rectTarget->y = rectSprite->y;
		rectTarget->w = cs;
		rectTarget->h = cs;
		RenderingEngine::DrawTexture(this, m_Texture, rectSource, rectTarget);



		//Middle Left
		rectSource->x = rectTexture->x;
		rectSource->y = rectTexture->y + cs;
		rectSource->w = cs;
		rectSource->h = rectTexture->h - cs * 2;
		rectTarget->x = rectSprite->x;
		rectTarget->y = rectSprite->y + cs;
		rectTarget->w = cs;
		rectTarget->h = rectSprite->h - cs * 2;
		RenderingEngine::DrawTexture(this, m_Texture, rectSource, rectTarget);


		//Middle Middle
		rectSource->x = rectTexture->x + cs;
		rectSource->y = rectTexture->y + cs;
		rectSource->w = rectTexture->w - cs * 2;
		rectSource->h = rectTexture->h - cs * 2;
		rectTarget->x = rectSprite->x + cs;
		rectTarget->y = rectSprite->y + cs;
		rectTarget->w = rectSprite->w - cs * 2;
		rectTarget->h = rectSprite->h - cs * 2;
		RenderingEngine::DrawTexture(this, m_Texture, rectSource, rectTarget);


		//Middle Right
		rectSource->x = rectTexture->x + rectTexture->w - cs;
		rectSource->y = rectTexture->y + cs;
		rectSource->w = cs;
		rectSource->h = rectTexture->h - cs * 2;
		rectTarget->x = rectSprite->x + rectSprite->w - cs;
		rectTarget->y = rectSprite->y + cs;
		rectTarget->w = cs;
		rectTarget->h = rectSprite->h - cs * 2;
		RenderingEngine::DrawTexture(this, m_Texture, rectSource, rectTarget);


		//Bottom Left
		rectSource->x = rectTexture->x;
		rectSource->y = rectTexture->y + rectTexture->h - cs;
		rectSource->w = cs;
		rectSource->h = cs;
		rectTarget->x = rectSprite->x;
		rectTarget->y = rectSprite->y + rectSprite->h - cs;
		rectTarget->w = cs;
		rectTarget->h = cs;
		RenderingEngine::DrawTexture(this, m_Texture, rectSource, rectTarget);


		//Bottom Middle
		rectSource->x = rectTexture->x + cs;
		rectSource->y = rectTexture->y + rectTexture->h - cs;
		rectSource->w = rectTexture->w - cs * 2;
		rectSource->h = cs;
		rectTarget->x = rectSprite->x + cs;
		rectTarget->y = rectSprite->y + rectSprite->h - cs;
		rectTarget->w = rectSprite->w - cs * 2;
		rectTarget->h = cs;
		RenderingEngine::DrawTexture(this, m_Texture, rectSource, rectTarget);


		//Bottom Right
		rectSource->x = rectTexture->x + rectTexture->w - cs;
		rectSource->y = rectTexture->y + rectTexture->h - cs;
		rectSource->w = cs;
		rectSource->h = cs;
		rectTarget->x = rectSprite->x + rectSprite->w - cs;
		rectTarget->y = rectSprite->y + rectSprite->h - cs;
		rectTarget->w = cs;
		rectTarget->h = cs;
		RenderingEngine::DrawTexture(this, m_Texture, rectSource, rectTarget);



	}

	//Don't bubble upwards
	//super::Draw();
}

