#include "TextNode.h"
#include "AssetManager.h"

TextNode::TextNode()
{
	SetName("TextNode");
	m_Text = "Text";
	m_Font = AssetManager::GetDefaultFont();
	m_TextColor = AssetManager::GetDefaultPenColor();
	m_Align = AlignLeftTop;
	//m_IsWrapped = false;
}

TextNode::~TextNode()
{}

std::string TextNode::GetText()
{
	return m_Text;
}

void TextNode::SetText(std::string value)
{
	m_Text = value;
}

Font* TextNode::GetFont()
{
	return m_Font;
}

void TextNode::SetFont(Font* value)
{
	m_Font = value;
}

Align TextNode::GetAlign()
{
	return m_Align;
}

void TextNode::SetAlign(Align value)
{
	m_Align = value;
}

Color* TextNode::GetTextColor()
{
	return m_TextColor;
}

void TextNode::SetTextColor(Color* value)
{
	m_TextColor = value;
}

void TextNode::Draw()
{
	LogEngine::Log(LOG_DEBUG, "TextNode", "Draw() called on " + this->GetName());

	if (GetIsVisible())
	{
		RenderingEngine::SetPenColor(m_TextColor);
		//RenderingEngine::DrawText(this, m_Text, m_Font, 0, 0);
	}

	//Don't bubble upwards
	//super::Draw();
}
