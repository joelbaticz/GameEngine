#pragma once

#include "ControlNode.h"
#include "ShapeNode.h"
#include "SpriteNode.h"
#include "TextNode.h"

class Button : public ControlNode
{
private:
	typedef ControlNode	super;
	SpriteNode*			m_ButtonSprite;
	TextNode*			m_CaptionTextNode;

	void SetSubComponentSizes();
	void Init(Node* parent, std::string name, std::string caption, int x, int y, int width, int height);
	void ProcessState();
public:
	//Constructors, destructor
	Button();
	Button(Node* parent, std::string name, std::string caption, int x, int y, int width, int height);
	~Button();

	//Accessor methods
	std::string GetCaption();
	void SetCaption(std::string value);
	void SetSize(Size* value);

	//Overridable methods
	void Update();
	void Draw() override;
};