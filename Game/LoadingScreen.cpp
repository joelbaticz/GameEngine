#include "LoadingScreen.h"

LoadingScreen::LoadingScreen(): super()
{
	LogEngine::Log(LOG_TRACE, "LoadingScreen", "Constructor called.");

	this->SetName("LoadingScreen");

	CanvasNode* background = new CanvasNode();
	background->SetName("Background");
	background->SetLocation(new Location(0, 0));
	background->SetSize(new Size(64, 48));

	
	Node* child2 = new Node("Child 2");

	CanvasNode* child3 = new CanvasNode();
	child3->SetName("Child3");
	child3->SetLocation(new Location(10, 10));
	child3->SetSize(new Size(50, 50));

	this->AddChild(background);
	this->AddChild(child2);
	this->AddChild(child3);

	//Create resources
	//ViewportSprite* background = new ViewportSprite();
	//background->SetTexture(backgroundTexture);

	//Build scene tree
	//m_Scene = background;
	//this->AddChild(backgroind);

	//ADD VIEWPORT TO SCENE???
}

LoadingScreen::~LoadingScreen()
{
	LogEngine::Log(LOG_TRACE, "LoadingScreen", "Destructor called.");

	//Will the super Node's destructor be called???

}


