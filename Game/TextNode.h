#pragma once

#include "PrimitiveNode.h"
#include "Font.h"
#include "Color.h"
#include "Align.h"

class TextNode : public PrimitiveNode
{
private:
	typedef PrimitiveNode	super;
	std::string				m_Text;
	Font*					m_Font;
	Color*					m_TextColor;
	Align					m_Align;
	//bool					m_IsWrapped;
public:
	//Constructors, destructor
	TextNode();
	~TextNode();

	//Accessor methods
	std::string GetText();
	void SetText(std::string value);

	Font* GetFont();
	void SetFont(Font* value);

	Align GetAlign();
	void SetAlign(Align value);

	Color* GetTextColor();
	void SetTextColor(Color* value);

	//Overidable methods
	void Draw() override;
};