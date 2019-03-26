#include "GameEngine.h"

#include "Label.h"
#include "ToolWindow.h"
#include "InfoPane.h"

//Init static members
//GameEngine*			GameEngine::m_Instance;
std::string			GameEngine::m_SystemName;
Node*				GameEngine::m_RootNode;
Node*				GameEngine::m_RootScene;
Node*				GameEngine::m_WindowInfoPane;
//CanvasNode*			GameEngine::m_WindowInfoPane;

bool				GameEngine::m_QuitLoop;
int					GameEngine::m_FrameCount;
int					GameEngine::m_LastFrameCount;
int					GameEngine::m_LastTime;
int					GameEngine::m_CurrentTime;
int					GameEngine::m_FrameTime;
int					GameEngine::m_FPS;



//Hidden Constructor - won't be called, since these are 
GameEngine::GameEngine()
{
	LogEngine::Log(LOG_TRACE, m_SystemName, "Constructor called.");
}

//Hidden Desctructor
GameEngine::~GameEngine()
{
	LogEngine::Log(LOG_TRACE, m_SystemName, "Destructor called.");
}

int GameEngine::Init(int windowX, int windowY, int windowWidth, int windowHeight)
{
	//Log GameEngine Init without LogEngine
	std::cout << "[TRACE] - GameEngine: Init() called." << std::endl;

	//Initialize members
	m_SystemName = "GameEngine";
	m_RootNode = nullptr;
	m_RootScene = nullptr;
	m_WindowInfoPane = nullptr;

	//LogEngine

	if (LogEngine::Init(LOG_TRACE | LOG_DEBUG | LOG_ERROR) != 0)
	{
		LogEngine::Log(LOG_ERROR, m_SystemName, SDL_GetError());
		return 1;
	}

	//RenderingEngine
	if (RenderingEngine::Init("Game", windowX, windowY, windowWidth, windowHeight) != 0)
	{
		LogEngine::Log(LOG_ERROR, m_SystemName, SDL_GetError());
		return 1;
	}

	//AssetManager (TTF is NEEDED)
	if (AssetManager::Init("res") != 0)
	{
		LogEngine::Log(LOG_ERROR, m_SystemName, SDL_GetError());
		return 1;
	}

	//MessageBus
	if (EventManager::Init() != 0)
	{
		LogEngine::Log(LOG_ERROR, m_SystemName, "Error init MessageBus");
		return 1;
	}

	//OptionsManager
	//OptionsManager::GetOption("MasterVolume");
	//AudioEngine


	//Create RootNode
	m_RootNode = new Node("RootNode");
	//Create RootScene
	m_RootScene = new Node("RootScene");
	AddToRootNode(m_RootScene);
	//m_RootNode = m_RootScene;

	//Create InfoPane (it adds itself already to RootNode)
	m_WindowInfoPane = new InfoPane();
	//((InfoPane*)m_WindowInfoPane)->SetIsShown(false);

	ToolWindow* m_WindowTest = new ToolWindow(nullptr, "TestWindow", "Test", 180, 120, 200, 200);
	AddToRootNode(m_WindowTest);

	for (int i = 0; i < 10; i++)
	{
		ToolWindow* m_WindowTestX = new ToolWindow(nullptr, "TestWindow", "Test", 380 + (i*20), 120 + (i * 20), 200, 200);
		AddToRootNode(m_WindowTestX);
	}

	Node* stuff = m_RootScene->GetParent();
	Node* stuff2 = m_WindowInfoPane->GetParent();
	Node* stuff3 = m_WindowInfoPane->GetFirstChild()->GetParent();
	Node* stuff4 = m_WindowInfoPane->GetFirstChild()->GetNextSibling()->GetParent();

	//ToolWindow tool;
	//tool.Draw();

	/*ToolWindow* windowInfoPane = new ToolWindow();
	windowInfoPane->SetComponentName("InfoPane");
	windowInfoPane->SetTitle("InfoPane");
	SDL_Rect* rectInfoPane = new SDL_Rect();
	rectInfoPane->x = 50;
	rectInfoPane->y = 25;
	rectInfoPane->w = 100;
	rectInfoPane->h = 200;
	windowInfoPane->SetRect(rectInfoPane);*/
	//m_SceneTree->AddChild(nodeInfoPane);
	//windowEditor->AddChild(nodeInfoPane);

	//m_SceneTree->AddChild(windowEditor);
	//m_SceneTree->AddChild(windowInfoPane);

	m_QuitLoop = false;

	//Log init was OK
	LogEngine::Log(LOG_TRACE, m_SystemName, "Init()...OK.");

	return 0;
}

void GameEngine::UnInit()
{
	LogEngine::Log(LOG_TRACE, m_SystemName, "UnInit() called.");

	//Destroy scene objects
	//m_CurrentScene->~Node();

	//Destroy textures in GPU
	//SDL_DestroyTexture(texBackground);

	RenderingEngine::UnInit();

	LogEngine::Log(LOG_TRACE, m_SystemName, "UnInit...OK.");

}

int GameEngine::GetFrameCount()
{
	return m_FrameCount;
}

int GameEngine::GetFPS()
{
	return m_FPS;
}

int GameEngine::GetFrameTime()
{
	return m_FrameTime;
}

void GameEngine::UpdateTickers()
{

	std::string strFrameInfo = "";

	//Query ticker
	m_FrameCount++;
	m_CurrentTime = SDL_GetTicks();
	if (m_CurrentTime > m_LastTime + 1000)
	{
		m_FPS = m_FrameCount - m_LastFrameCount;
		m_FrameTime = (m_CurrentTime - m_LastTime) / m_FPS;

		strFrameInfo = "FrameNo.: " + std::to_string(m_FrameCount);
		strFrameInfo += ", FPS: " + std::to_string(m_FPS);
		strFrameInfo += ", FrameTime: " + std::to_string(m_FrameTime) + "[ms]";
		std::cout << strFrameInfo << std::endl;

		m_LastFrameCount = m_FrameCount;
		m_LastTime = m_CurrentTime;
	}
}

int GameEngine::StartLoop(Node* scene)
{
	LogEngine::Log(LOG_TRACE, m_SystemName, "StartLoop() called.");

	//We save CurrentGameScene so we can replace it easier later
	//*m_Scene = *scene;
	//*m_SceneTree->GetFirstChild() = *scene;
	//m_RootScene->AddChild(scene);
	AddToRootScene(scene);

	//Send message to current scene: enter scene tree
	//Message* msg = new Message();
	//msg->m_Sender = this;
	//msg->m_Type = MSG_ENTER_TREE;
	//scene->ProcessMessage(msg);

	LogEngine::SetFilterFlags(0);

	SDL_Event e;

	Message* msg = new Message();

	while (!m_QuitLoop)
	{
		RenderingEngine::BeginFrame();

		UpdateTickers();

		//HANDLE INPUTS
		//SEND INPUT MESSAGES TO SCENE -> THAT DUDE WILL BUBBLE IT DOWN TO IT'S CHILDREN

		//Query event queue - Process all events
		while (SDL_PollEvent(&e))
		{
			//Hande system wide events
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.scancode == SDL_SCANCODE_F9)
				{
					//Toggle visibility of InfoPane
					((InfoPane*)m_WindowInfoPane)->SetIsVisible(!((InfoPane*)m_WindowInfoPane)->GetIsVisible());
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					//Quit GameLoop
					m_QuitLoop = true;
				}
			}

			//Create message
			msg->m_Type = MSG_UNDEFINED;
			msg->m_SDLEvent = &e;
			
			if (e.type == SDL_MOUSEMOTION)
				msg->m_Type = MSG_MOUSEMOTION;
			if (e.type == SDL_MOUSEBUTTONDOWN)
				msg->m_Type = MSG_MOUSEBUTTONDOWN;
			if (e.type == SDL_MOUSEBUTTONUP)
				msg->m_Type = MSG_MOUSEBUTTONUP;
			if (e.type == SDL_MOUSEWHEEL)
				msg->m_Type = MSG_MOUSEWHEEL;

			EventManager::Broadcast(msg);
		}

		//SEND UPDATE TO SCENE
		msg->m_Type = MSG_UPDATE;
		//msg->m_SDLEvent = nullptr;
		EventManager::Broadcast(msg);

		//SEND DRAW TO SCENE
		msg->m_Type = MSG_DRAW;
		//msg->m_SDLEvent = nullptr;
		EventManager::Broadcast(msg);

		RenderingEngine::PresentFrame();
	}

	return 0;
}

void GameEngine::AddToRootScene(Node* node)
{
	m_RootScene->AddChild(node);
}

//void GameEngine::AddToRootNode(Node* value)
//{
//	Node* node = m_RootNode;
//
//	if (node == nullptr)
//	{
//		m_RootNode = value;
//		value->SetParent(nullptr);
//		return;
//	}
//
//	while (1)
//	{
//		if (node->GetNextSibling() != nullptr)
//		{
//			node = node->GetNextSibling();
//		}
//		else
//		{
//			node->SetNextSibling(value);
//			value->SetParent(nullptr);
//			return;
//		}
//	}
//}

//void GameEngine::SendMessageToRootSiblings(Message* msg)
//{
//	Node* node = m_RootNode;
//
//	while (node != nullptr)
//	{
//		node->ProcessMessage(msg);
//		node = node->GetNextSibling();
//	}
//}

Node* GameEngine::GetRootNode()
{
	return m_RootNode;
}

bool GameEngine::IsRootNode(Node* node)
{
	if (node == m_RootNode) return true;
	return false;
}

void GameEngine::AddToRootNode(Node* node)
{
	m_RootNode->AddChild(node);
	//node->SetParent(nullptr);
}