#include "EventManager.h"


//Init static members
Node**	EventManager::m_SubscriberList;
int		EventManager::m_SubscriberCount;
Node*	EventManager::m_NodeHit;
Node*	EventManager::m_NodeHitPrev;
Node*	EventManager::m_NodeMouseButtonDown;
Node*	EventManager::m_NodeMouseButtonUp;
Node*	EventManager::m_NodeFocused;

EventManager::EventManager()
{}

EventManager::~EventManager()
{}

int EventManager::Init()
{
	m_SubscriberCount = 0;
	return 0;  //SUCCESS
}

void EventManager::Subscribe(Node* node)
{
	Node** newList = new Node*[m_SubscriberCount + 1];

	if (m_SubscriberCount != 0)
	{
		for (int i = 0; i < m_SubscriberCount; i++)
		{
			newList[i] = m_SubscriberList[i];
		}
	}
	delete m_SubscriberList;
	newList[m_SubscriberCount] = node;
	m_SubscriberList = newList;
	m_SubscriberCount++;
	
}

void EventManager::Broadcast(Message* msg)
{

	switch (msg->m_Type)
	{
	case MSG_UPDATE:
		BroadcastUpdate();
		break;
	case MSG_DRAW:
		BroadcastDraw();
		break;
	case MSG_MOUSEMOTION:
	case MSG_MOUSEBUTTONDOWN:
	case MSG_MOUSEBUTTONUP:
	case MSG_MOUSEWHEEL:
		BroadcastMouse(msg);
		break;
	default:
		//BroadcastObscure(msg);
		break;
	}
}

void EventManager::BroadcastUpdate()
{
	for (int i = 0; i < m_SubscriberCount; i++)
	{
		m_SubscriberList[i]->Update();
	}
}

//void EventManager::BroadcastDraw()
//{
//	for (int i = 0; i < m_SubscriberCount; i++)
//	{
//		CanvasNode* canvasNode = dynamic_cast<CanvasNode*>(m_SubscriberList[i]);
//		if (canvasNode != nullptr)
//		{
//			canvasNode->Draw();
//		}
//	}
//}

void EventManager::BroadcastDraw()
{
	Node* root = GameEngine::GetRootNode();

	BroadcastDrawSubNode(root);
	
}

void EventManager::BroadcastDrawSubNode(Node* node)
{
	node = node->GetFirstChild();

	while (node != nullptr)
	{
		CanvasNode* canvasNode = dynamic_cast<CanvasNode*>(node);
		if (canvasNode != nullptr)
		{
			if (canvasNode->GetIsVisible())
			{
				canvasNode->Draw();
				//If node is not visible children are hidden as well.
				BroadcastDrawSubNode(node);

			}
		}
		node = node->GetNextSibling();
	}
}



void EventManager::BroadcastMouse(Message* msg)
{
	m_NodeHit = nullptr;
	Node* root = GameEngine::GetRootNode();

	BroadcastMouseSubNode(root, msg);

	if (m_NodeHitPrev != m_NodeHit)
	{
		//Check if mouse being pressed on something
		//if (m_NodeMouseButtonDown == nullptr)
		{
			if (m_NodeHitPrev != nullptr)
			{
				((ControlNode*)m_NodeHitPrev)->OnMouseLeave(msg);
			}
			if (m_NodeHit != nullptr)
			{
				((ControlNode*)m_NodeHit)->OnMouseMove(msg);
			}
			m_NodeHitPrev = m_NodeHit;
		}
		//else if (m_NodeMouseButtonDown = m_NodeHit)
		{

		}
	}

	if (msg->m_Type == MSG_MOUSEBUTTONDOWN)
	{
		if (m_NodeHit != nullptr)
		{
			((ControlNode*)m_NodeHit)->OnMouseDown(msg);
		}
		m_NodeMouseButtonDown = m_NodeHit;
	}
	if (msg->m_Type == MSG_MOUSEBUTTONUP)
	{
		if (m_NodeHit != nullptr)
		{
			((ControlNode*)m_NodeHit)->OnMouseUp(msg);
		}
		m_NodeMouseButtonUp = m_NodeHit;
		
		
		if (m_NodeMouseButtonUp == m_NodeMouseButtonDown)
		{
			if (m_NodeMouseButtonDown != nullptr)
			{
				((ControlNode*)m_NodeMouseButtonDown)->OnMouseClick(msg);
			}
		}
		
		m_NodeMouseButtonDown = nullptr;
		m_NodeMouseButtonUp = nullptr;
	}
	

}

void EventManager::BroadcastMouseSubNode(Node* node, Message* msg)
{
	node = node->GetFirstChild();

	while (node != nullptr)
	{
		//if (msg->m_Type == MSG_MOUSEMOTION)
		{
			ControlNode* controlNode = dynamic_cast<ControlNode*>(node);
			if (controlNode != nullptr
			&& controlNode->GetIsVisible() == true
			&& controlNode->GetIsEnabled() == true)
			{
				SDL_Rect* rectHitBox = new SDL_Rect();
				rectHitBox->x = 0;
				rectHitBox->y = 0;
				rectHitBox->w = controlNode->GetSize()->GetWidth();
				rectHitBox->h = controlNode->GetSize()->GetHeight();
				//Perform Local to Global coord transformation
				RenderingEngine::ClientRectToScreenRect(node, rectHitBox);

				//Grab mouse coordinates from event
				int mouseX = msg->m_SDLEvent->motion.x;
				int mouseY = msg->m_SDLEvent->motion.y;

				//Check if mouse is outside
				if (mouseX >= rectHitBox->x
					&& mouseX <= rectHitBox->x + rectHitBox->w
					&& mouseY >= rectHitBox->y
					&& mouseY <= rectHitBox->y + rectHitBox->h)
				{
					m_NodeHit = controlNode;
				}

			}
		}
		BroadcastMouseSubNode(node, msg);
		node = node->GetNextSibling();
	}
}

void EventManager::BroadcastObscure(Message* msg)
{
	for (int i = 0; i < m_SubscriberCount; i++)
	{
		m_SubscriberList[i]->ProcessMessage(msg);
	}
}

void EventManager::GrabFocus(Node* node)
{
	//Defocus previous
	UnFocusTree(m_NodeFocused);
	//Make focused
	FocusTree(node);
	m_NodeFocused = node;
}

void EventManager::UnFocusTree(Node* node)
{
	while (node != nullptr)
	{
		ControlNode* controlNode = dynamic_cast<ControlNode*>(node);
		if (controlNode != nullptr)
		{
			controlNode->SetIsFocused(false);
		}
		node = node->GetParent();
	}
}

void EventManager::FocusTree(Node* node)
{
	while (node != nullptr)
	{
		ControlNode* controlNode = dynamic_cast<ControlNode*>(node);
		if (controlNode != nullptr)
		{
			controlNode->SetIsFocused(true);
		}
		node = node->GetParent();
	}
}
