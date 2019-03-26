#include "ToolWindow.h"
#include "AssetManager.h"

void ToolWindow::SetSubComponentSizes()
{
	Size* sizeFrame = this->GetSize();
	Size* sizeTitleBar = new Size(sizeFrame->GetWidth(), 20);
	Size* sizeBackground = new Size(sizeFrame->GetWidth() - 8, sizeFrame->GetHeight() - 24);
	Location* locationCloseButton = new Location(sizeFrame->GetWidth() - 20, 3);

	//Pass it on to our basic shapes
	if (m_WindowFrame != nullptr)
	{
		m_WindowFrame->SetSize(sizeFrame);
	}
	if (m_WindowTitleBar != nullptr)
	{
		m_WindowTitleBar->SetSize(sizeTitleBar);
	}
	if (m_TitleTextNode != nullptr)
	{
		m_TitleTextNode->SetSize(sizeTitleBar);
	}
	if (m_WindowBackground != nullptr)
	{
		m_WindowBackground->SetSize(sizeBackground);
	}
	if (m_CloseButton != nullptr)
	{
		m_CloseButton->SetLocation(locationCloseButton);
	}
}

void ToolWindow::Init(Node* parent, std::string name, std::string title, int x, int y, int width, int height)
{
	Location* locationFrame = new Location(0, 0);
	Location* locationTitleBar = new Location(0, 0);// Location(3, 3);
	Location* locationBackground = new Location(4, 20);// Location(3, 23);
	
	//Component
	SetName(name);
	SetParent(parent);
	SetLocation(new Location(x, y));
	CanvasNode::SetSize(new Size(width, height));

	//SubComponent - WindowFrame
	Texture* frameTexture = AssetManager::CreateTexture("ToolWindowFrame.png");
	frameTexture->SetHorizontalCount(1);
	frameTexture->SetVerticalCount(2); //Possible states: Active, Inactive

	m_WindowFrame = new SpriteNode();
	m_WindowFrame->SetName("ToolWindowFrame");
	m_WindowFrame->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_WindowFrame->SetLocation(locationFrame);
	((SpriteNode*)m_WindowFrame)->SetTexture(frameTexture);
	((SpriteNode*)m_WindowFrame)->SetTextureIndex(0);
	((SpriteNode*)m_WindowFrame)->SetCornerSize(10);
	this->AddChild(m_WindowFrame);

	//SubComponent - TitleBar
	Texture* titlebarTexture = AssetManager::CreateTexture("ToolWindowTitle.png");
	titlebarTexture->SetHorizontalCount(1);
	titlebarTexture->SetVerticalCount(2); //Possible states: Active, Inactive

										  //m_WindowTitleBar = new ShapeNode();
										  //m_WindowTitleBar->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
										  //m_WindowTitleBar->SetComponentName("ToolWindowFramed");
	m_WindowTitleBar = new SpriteNode();
	m_WindowTitleBar->SetName("ToolWindowTitleBar");
	m_WindowTitleBar->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_WindowTitleBar->SetLocation(locationTitleBar);
	((SpriteNode*)m_WindowTitleBar)->SetTexture(titlebarTexture);
	((SpriteNode*)m_WindowTitleBar)->SetTextureIndex(0);
	((SpriteNode*)m_WindowTitleBar)->SetCornerSize(10);
	this->AddChild(m_WindowTitleBar);


	//SubComponent - TitleText
	m_TitleTextNode = new TextNode();
	m_TitleTextNode->SetName("ToolWindowTitle");
	m_TitleTextNode->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_TitleTextNode->SetLocation(locationTitleBar);
	m_TitleTextNode->SetText(title);
	Color* textColor = AssetManager::CreateColor(255, 255, 255, 255);
	m_TitleTextNode->SetTextColor(textColor);
	this->AddChild(m_TitleTextNode);

	//SUBCOMPONENT - BACKGROUND
	Texture* backgroundTexture = AssetManager::CreateTexture("ToolWindowBackground.png");
	backgroundTexture->SetHorizontalCount(1);
	backgroundTexture->SetVerticalCount(2); //Possible states: Active, Inactive

	m_WindowBackground = new SpriteNode();
	m_WindowBackground->SetName("ToolWindowBackground");
	m_WindowBackground->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_WindowBackground->SetLocation(locationBackground);
	((SpriteNode*)m_WindowBackground)->SetTexture(backgroundTexture);
	((SpriteNode*)m_WindowBackground)->SetTextureIndex(0);
	((SpriteNode*)m_WindowBackground)->SetCornerSize(10);
	this->AddChild(m_WindowBackground);

	//Subcomponent - CloseButton
	m_CloseButton = new Button();
	m_CloseButton->SetName("ToolWindowCloseButton");
	m_CloseButton->SetParent(this);  //This is needed since the Screen coordinate lookup searches the parents
	m_CloseButton->SetLocation(locationTitleBar);
	m_CloseButton->SetSize(new Size(15, 15));
	m_CloseButton->SetCaption("x");
	this->AddChild(m_CloseButton);


	SetSubComponentSizes();
	ProcessState();
}

ToolWindow::ToolWindow()
{
	LogEngine::Log(LOG_TRACE, "ToolWindow", "Constructor called.");

	Init(nullptr, "ToolWindow", "ToolWindowTitle", DEFAULT_X, DEFAULT_Y, DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

ToolWindow::ToolWindow(Node* parent, std::string name, std::string title, int x, int y, int width, int height)
{
	LogEngine::Log(LOG_TRACE, "ToolWindow", "Constructor called.");

	Init(parent, name, title, x, y, width, height);
}

ToolWindow::~ToolWindow()
{
	LogEngine::Log(LOG_TRACE, "ToolWindow", "Destructor called.");

	delete m_WindowFrame;
	delete m_WindowTitleBar;
	delete m_TitleTextNode;
}

std::string ToolWindow::GetTitle()
{
	if (m_TitleTextNode != nullptr)
		return m_TitleTextNode->GetText();
	else
		return nullptr;
}

void ToolWindow::SetTitle(std::string value)
{
	if (m_TitleTextNode != nullptr)
		m_TitleTextNode->SetText(value);
}

void ToolWindow::SetSize(Size* value)
{
	CanvasNode::SetSize(value);
	SetSubComponentSizes();
}

void ToolWindow::ProcessState()
{
	if (GetIsFocused())
	{
		m_WindowFrame->SetTextureIndex(0);
		m_WindowTitleBar->SetTextureIndex(0);
		m_WindowBackground->SetTextureIndex(0);
		m_TitleTextNode->SetTextColor(AssetManager::CreateColor(255, 255, 255, 255));
		return;
	}

	m_WindowFrame->SetTextureIndex(1);
	m_WindowTitleBar->SetTextureIndex(1);
	m_WindowBackground->SetTextureIndex(1);
	m_TitleTextNode->SetTextColor(AssetManager::CreateColor(255, 80, 80, 80));
	return;
}

void ToolWindow::ProcessMessage(Message* msg)
{
	if (m_CloseButton != nullptr)
	{
		m_CloseButton->ProcessMessage(msg);
	}

	//Bubble up
	super::ProcessMessage(msg);
}

void ToolWindow::Update()
{
	ProcessState();

	//Bubble up
	super::Update();
}

void ToolWindow::Draw()
{
	LogEngine::Log(LOG_DEBUG, "ToolWindow", "Draw() called on " + this->GetName());

	if (GetIsVisible())
	{
		//if (m_WindowFrame != nullptr)
		//{
		//	m_WindowFrame->Draw();
		//}
		//if (m_WindowTitleBar != nullptr)
		//{
		//	m_WindowTitleBar->Draw();
		//}
		//if (m_TitleTextNode != nullptr)
		//{
		//	m_TitleTextNode->Draw();
		//}
		//if (m_CloseButton != nullptr)
		//{
		//	m_CloseButton->Draw();
		//}
	}

	//Don't bubble upwards
	super::Draw();
}




/*
void ToolWindow::OnMouseEnter(Message* msg)
{
	ProcessState();
}

void ToolWindow::OnMouseLeave(Message* msg)
{
	ProcessState();
}

void ToolWindow::OnMouseDown(Message* msg)
{
	ProcessState();
}

void ToolWindow::OnMouseUp(Message* msg)
{
	ProcessState();
}
*/
void ToolWindow::OnMouseClick(Message* msg)
{
	//m_CloseButton->SetIsVisible(false);

	//Bubble up
	super::OnMouseClick(msg);
}