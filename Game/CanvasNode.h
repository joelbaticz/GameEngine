#pragma once

#include "Node.h"
#include "Location.h"
#include "Size.h"

//#include "SDL.h"
//#include "LogEngine.h"
//#include "GameEngine.h"
//#include "AssetManager.h"
//#include "RenderingEngine.h"

class CanvasNode: public Node
{
private:
	typedef Node	super;
	bool			m_IsVisible;
	//bool			m_ToBeShownInSceneTree;
	//bool			m_IsFreeFlowNode;
	Location*		m_Location;
	Size*			m_Size;
public:
	//Constructors, destructor
	CanvasNode();
	~CanvasNode();

	//Accessor methods
	bool GetIsVisible();
	void SetIsVisible(bool value);
	Location* GetLocation();
	void SetLocation(Location* location);
	Size* GetSize();
	void SetSize(Size* size);
	void BringToFront();

	//Overridable methods
	virtual void ProcessMessage(Message* msg);
	//virtual void Update();
	virtual void Draw();
};