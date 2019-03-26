#pragma once

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include <SDL_ttf.h>
#include "LogEngine.h"
#include "AssetManager.h"
#include "RenderingEngine.h"
#include "EventManager.h"
#include "Node.h"
#include "CanvasNode.h"
#include "ControlNode.h" //Remove these after I moved infoPane and Editor to different classes
#include "Color.h"
#include "Message.h"


//Static class, because we just want to use the namespace and there can need not to be any objects
class GameEngine
{
private:
	static std::string			m_SystemName;
	static Node*				m_RootNode;
	static Node*				m_RootScene;
	static Node*				m_WindowInfoPane;

	static bool					m_QuitLoop;

	//Performance Indicators
	static int					m_FrameCount;
	static int					m_LastFrameCount;
	static int					m_LastTime;
	static int					m_CurrentTime;
	static int					m_FrameTime;
	static int					m_FPS;
	

	//Hidden constructor / destructor
	GameEngine();
	~GameEngine();


	static void UpdateTickers();
public:
	static int Init(int windowX, int windowY, int windowWidth, int windowHeight);
	static void UnInit();
	static int StartLoop(Node* node);
	static void AddToRootScene(Node* node);
	//static void AddToRootNode(Node* value);
	//static void SendMessageToRootSiblings(Message* msg);
	
	static Node* GetRootNode();
	static bool IsRootNode(Node* node);
	static void AddToRootNode(Node* node);

	static int GetFPS();
	static int GetFrameCount();
	static int GetFrameTime();

	//static Node* ChangeScene(Node* newScene);
	//Changes the scene and continues the loop with that. Gets back the old scene
	//Everybody is notified who are added to the SceneTree or left the tree.
	//A ReourceManager csak csendben gyujtogeti az object-eket.
	//Az AssetManager csak megkrealja az TextureImage-eket es TextureAtlas-okat
	//A vegen a gameengine mindkettot megkeri, hogy kurja ki az object-eket... (garbage collection-t is csinalhat...)

};