#include "Button.h"
#include "AssetManager.h"

void Button::SetSubComponentSizes()
{
	//Pass it on to our basic shapes
	if (m_ButtonSprite != nullptr)
	{
		m_ButtonSprite->SetSize(this->GetSize());
	}
	if (m_CaptionTextNode != nullptr)
	{
		m_CaptionTextNode->SetSize(this->GetSize());
	}
}

void Button::Init(Node* parent, std::string name, std::string caption, int x, int y, int width, int height)
{
	SetName(name);
	SetParent(parent);
	SetLocation(new Location(x, y));
	SetSize(new Size(width, height));

	Location* componentLocation = new Location(0, 0);

	Texture* buttonTexture = AssetManager::CreateTexture("Button.png");
	buttonTexture->SetHorizontalCount(1);
	buttonTexture->SetVerticalCount(5); //Possible states: Normal, Hover, Pressed, KeyboardFocus, Disabled

	//m_ButtonShape = new ShapeNode();
	//m_ButtonShape->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	//m_ButtonShape->SetComponentName("ToolWindowFramed");
	m_ButtonSprite = new SpriteNode();
	m_ButtonSprite->SetName("ButtonSprite");
	m_ButtonSprite->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_ButtonSprite->SetLocation(componentLocation);
	((SpriteNode*)m_ButtonSprite)->SetTexture(buttonTexture);
	((SpriteNode*)m_ButtonSprite)->SetTextureIndex(0);
	((SpriteNode*)m_ButtonSprite)->SetCornerSize(10);
	this->AddChild(m_ButtonSprite);

	m_CaptionTextNode = new TextNode();
	m_CaptionTextNode->SetName("CaptionTextNode");
	m_CaptionTextNode->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_CaptionTextNode->SetLocation(componentLocation);
	m_CaptionTextNode->SetText(caption);
	Color* textColor = AssetManager::CreateColor(255, 255, 255, 255);
	m_CaptionTextNode->SetTextColor(textColor);
	this->AddChild(m_CaptionTextNode);

	SetSubComponentSizes();
}

Button::Button()
{
	LogEngine::Log(LOG_TRACE, "Button", "Constructor called.");

	Init(nullptr, "Button", "Caption", DEFAULT_X, DEFAULT_Y, DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

Button::Button(Node* parent, std::string name, std::string caption, int x, int y, int width, int height)
{
	LogEngine::Log(LOG_TRACE, "Button", "Constructor called.");

	Init(parent, name, caption, x, y, width, height);
}


Button::~Button()
{
	LogEngine::Log(LOG_TRACE, "Button", "Destructor called.");

	delete m_ButtonSprite;
	delete m_CaptionTextNode;
}

std::string Button::GetCaption()
{
	return m_CaptionTextNode->GetText();
}

void Button::SetCaption(std::string value)
{
	m_CaptionTextNode->SetText(value);
}

void Button::SetSize(Size* value)
{
	CanvasNode::SetSize(value);
	SetSubComponentSizes();
}

void Button::ProcessState()
{
	if (!GetIsEnabled())
	{
		m_ButtonSprite->SetTextureIndex(4);
		return;
	}

	if (GetIsPressed())
	{
		m_ButtonSprite->SetTextureIndex(2);
		return;
	}

	if (GetIsHover())
	{
		m_ButtonSprite->SetTextureIndex(1);
		return;
	}

	/*if (GetIsKeyboardFocused())
	{
		m_ButtonSprite->SetTextureIndex(3);
		return;
	}*/

	m_ButtonSprite->SetTextureIndex(0);
}

void Button::Update()
{
	ProcessState();

	//Bubble up
	super::Update();
}

void Button::Draw()
{
	LogEngine::Log(LOG_DEBUG, "Button", "Draw() called on " + this->GetName());

	//Visible?
	if (GetIsVisible() == false) return;

	//if (GetIsEnabled())
	//{
	//	//Enabled
	//	m_ButtonSprite->SetTextureIndex(0);

	//	if (GetIsHover())
	//	{
	//		//OnHover
	//		m_ButtonSprite->SetTextureIndex(2);
	//	}
	//}
	//else
	//{
	//	//Disabled
	//	m_ButtonSprite->SetTextureIndex(1);
	//}

	//if (m_ButtonSprite != nullptr)
	//{
	//	m_ButtonSprite->Draw();
	//}
	//if (m_CaptionTextNode != nullptr)
	//{
	//	m_CaptionTextNode->Draw();
	//}

	//Don't bubble upwards
	super::Draw();
}