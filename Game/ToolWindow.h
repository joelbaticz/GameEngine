#pragma once

#include "ControlNode.h"
#include "ShapeNode.h"
#include "SpriteNode.h"
#include "TextNode.h"
#include "Button.h"

class ToolWindow : public ControlNode
{
private:
	typedef	ControlNode	super;
	
	SpriteNode*		m_WindowFrame;
	SpriteNode*		m_WindowTitleBar;
	TextNode*		m_TitleTextNode;
	SpriteNode*		m_WindowBackground;

	Button*			m_CloseButton;

	void SetSubComponentSizes();
	void Init(Node* parent, std::string name, std::string title, int x, int y, int width, int height);
	void ProcessState();
public:
	//Constructors, destructor
	ToolWindow();
	ToolWindow(Node* parent, std::string name, std::string title, int x, int y, int width, int height);
	~ToolWindow();

	//Accessor methods
	std::string GetTitle();
	void SetTitle(std::string value);
	void SetSize(Size* value);

	//Overridable methods
	void ProcessMessage(Message* msg);
	void Update();
	void Draw() override;
	/*
	void OnMouseEnter(Message* msg) override;
	void OnMouseLeave(Message* msg) override;
	void OnMouseDown(Message* msg) override;
	void OnMouseUp(Message* msg) override;
	*/
	void OnMouseClick(Message* msg) override;
};