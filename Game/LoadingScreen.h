#pragma once

#include "Node.h"
#include "LogEngine.h"
#include "CanvasNode.h"

class LoadingScreen : public Node
{
private:
	typedef Node	super;
	Node*			m_Scene;
public:
	LoadingScreen();
	~LoadingScreen();
};