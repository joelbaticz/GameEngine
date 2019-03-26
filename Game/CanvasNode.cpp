#include "CanvasNode.h"

CanvasNode::CanvasNode()
{
	LogEngine::Log(LOG_TRACE, "CanvasNode", "Constructor called.");

	SetName("CanvasNode");
	m_IsVisible = true;
	m_Location = new Location();
	m_Size = new Size();
}

CanvasNode::~CanvasNode()
{
	LogEngine::Log(LOG_TRACE, "CanvasNode", "Destructor called.");
}

bool CanvasNode::GetIsVisible()
{
	return m_IsVisible;
}

void CanvasNode::SetIsVisible(bool value)
{
	m_IsVisible = value;
	
	//Bubble Down???
	Node* node = this->GetFirstChild();
	while (node != nullptr)
	{
		if (dynamic_cast<CanvasNode*>(node)) ((CanvasNode*)node)->SetIsVisible(value);
		node = node->GetNextSibling();
	}
}

Location* CanvasNode::GetLocation()
{
	return m_Location;
}

void CanvasNode::SetLocation(Location* location)
{
	m_Location = location;
}

Size* CanvasNode::GetSize()
{
	return m_Size;
}

void CanvasNode::SetSize(Size* size)
{
	m_Size = size;
}

void CanvasNode::BringToFront()
{
	//Node* topmost = this->GetTopmostNode();
	Node* parent = this->GetParent();
	Node* lastsib = this;
	
	//Get the last sibling
	while (lastsib->GetNextSibling() != nullptr)
	{
		lastsib = lastsib->GetNextSibling();
	}

	if (lastsib != this)
	{
		//This is not the Front node

		//No more siblings -> Do swap

	
		//Search for previous child
		Node* prevsib = parent->GetFirstChild();
		while (prevsib->GetNextSibling() != this)
		{
			prevsib = prevsib->GetNextSibling();
		}

		lastsib->SetNextSibling(this);
		prevsib->SetNextSibling(this->GetNextSibling());
		this->SetNextSibling(nullptr);

		//Send Z-Order changed message (so the node can recalculate it's clienrect)

		//Tell parent too
		//Node* parent = this->GetParent();
	}
	if (parent != nullptr)
	{
		if (dynamic_cast<CanvasNode*>(this))
		{
			((CanvasNode*)parent)->BringToFront();
		}
	}
	
	
}

void CanvasNode::ProcessMessage(Message* msg)
{
	LogEngine::Log(LOG_DEBUG, "CanvasNode", "ProcessMessage() called on " + this->GetName());

	switch (msg->m_Type)
	{
	case MSG_DRAW:
		this->Draw();
		//return;
		////Bubble Down
		//Node* node = this->GetFirstChild();
		//while (node != nullptr)
		//{
		//	if (dynamic_cast<CanvasNode*>(node))
		//	{
		//		((CanvasNode*)node)->Draw();
		//	}
		//	node = node->GetNextSibling();
		//}
		////Message was bubbled down
		//return;
	}

	//Bubble up: Dispatch message to Node's ProcessMessage
	super::ProcessMessage(msg);
}

//void CanvasNode::Update()
//{
//	LogEngine::Log(LOG_DEBUG, "CanvasNode", "Update() called on " + this->GetName());
//
//	//Bubble up
//	super::Update();
//}

void CanvasNode::Draw()
{	
	LogEngine::Log(LOG_DEBUG, "CanvasNode", "Draw() called on " + this->GetName());

	if (m_IsVisible)
	{
		//Color* fillColor = AssetManager::CreateColor(80, 80, 0, 80);
		//RenderingEngine::SetFillColor(fillColor);
		//RenderingEngine::DrawRectangle(this, 0, 0, m_Size->GetWidth(), m_Size->GetHeight());
	}

	//Don't bubble upwards
	//super::Draw();

	//Bubble Down
	//Node* node = this->GetFirstChild();
	//while (node != nullptr)
	//{
	//	if (dynamic_cast<CanvasNode*>(node))
	//	{
	//		((CanvasNode*)node)->Draw();
	//	}
	//	node = node->GetNextSibling();
	//}
	////Message was bubbled down
	//return;

}
