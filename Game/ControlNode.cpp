#include "ControlNode.h"
#include "RenderingEngine.h"
#include "EventManager.h"

ControlNode::ControlNode()
{
	LogEngine::Log(LOG_TRACE, "ControlNode", "Constructor called.");

	SetName("ControlNode");
	m_IsEnabled = true;
	m_IsHover = false;
	m_IsPressed = false;
	
	//m_MinSize = nullptr;
	//m_MaxSize = nullptr;
	//m_Anchor = AnchorNone;
	//m_Margin = 0;

}

ControlNode::~ControlNode()
{
	LogEngine::Log(LOG_TRACE, "ControlNode", "Destructor called.");
}

bool ControlNode::GetIsEnabled()
{
	return m_IsEnabled;
}

void ControlNode::SetIsEnabled(bool value)
{
	m_IsEnabled = value;
}

bool ControlNode::GetIsHover()
{
	return m_IsHover;
}

void ControlNode::SetIsHover(bool value)
{
	m_IsHover = value;
}

bool ControlNode::GetIsPressed()
{
	return m_IsPressed;
}

void ControlNode::SetIsPressed(bool value)
{
	m_IsPressed = value;
}

bool ControlNode::GetIsFocused()
{
	return m_IsFocused;
}

void ControlNode::SetIsFocused(bool value)
{
	m_IsFocused = value;
}

void ControlNode::ProcessMessage(Message* msg)
{
	bool isMessageConsumed = false;

	//Do not process, neighter children if not visible
	if (this->GetIsVisible() == false) return;
	//Do not process, neighter children if not enabled
	if (this->GetIsEnabled() == false) return;

	//if (msg->m_Type == MSG_MOUSEINPUT)
	{
		//CREATE HITBOX FOR CHECKING

		//Create Zero-based (local) coordinate hitbox
		SDL_Rect* rectHitBox = new SDL_Rect();
		rectHitBox->x = 0;
		rectHitBox->y = 0;
		rectHitBox->w = this->GetSize()->GetWidth();
		rectHitBox->h = this->GetSize()->GetHeight();
		//Perform Local to Global coord transformation
		RenderingEngine::ClientRectToScreenRect(this, rectHitBox);

		if (msg->m_SDLEvent->type == SDL_MOUSEMOTION)
		{
			//Grab mouse coordinates from event
			int mouseX = msg->m_SDLEvent->motion.x;
			int mouseY = msg->m_SDLEvent->motion.y;

			//Actual HitBox check
			if (m_IsHover)
			{
				//OnMouseEnter message was already sent
				//Check if mouse is outside
				if (mouseX < rectHitBox->x
					|| mouseX > rectHitBox->x + rectHitBox->w
					|| mouseY < rectHitBox->y
					|| mouseY > rectHitBox->y + rectHitBox->h)
				{
					//Mouse found to be outside of HitBox
					m_IsHover = false;

					//Create new message type with same data 
					Message* newMsg = new Message();
					newMsg->m_Type = MSG_MOUSELEAVE;
					newMsg->m_SDLEvent = msg->m_SDLEvent;
					this->OnMouseLeave(newMsg);
					delete newMsg;

					
				}
				else
				{
					//Do nothing (mouse is still inside the control, MouseEnter was already sent)
				}
			}
			else
			{
				//OnMouseEnter was not sent yet. Shall we send it?
				if (mouseX >= rectHitBox->x
					&& mouseX <= rectHitBox->x + rectHitBox->w
					&& mouseY >= rectHitBox->y
					&& mouseY <= rectHitBox->y + rectHitBox->h)
				{
					//HitBox test positive -> send OnMouseEnter
					m_IsHover = true;

					//Mouse found to be inside of HitBox
					//Create new message type with same data 
					Message* newMsg = new Message();
					newMsg->m_Type = MSG_MOUSEENTER;
					newMsg->m_SDLEvent = msg->m_SDLEvent;
					this->OnMouseEnter(newMsg);
					delete newMsg;

					
				}
				else
				{
					//Do nothing (mouse is still OUTSIDE of the control
				}
			}
		}
		else if (msg->m_SDLEvent->type == SDL_MOUSEBUTTONDOWN)
		{
			//Grab mouse coordinates from event
			int mouseX = msg->m_SDLEvent->motion.x;
			int mouseY = msg->m_SDLEvent->motion.y;

			//Actual HitBox check
			if (m_IsHover)
			{
				//Mouse is already atop of control
				if (!m_IsPressed)
				{
					//Pressed signal was not sent yet
					m_IsPressed = true;
					
					Message* newMsg = new Message();
					newMsg->m_Type = MSG_MOUSEBUTTONDOWN;
					newMsg->m_SDLEvent = msg->m_SDLEvent;
					this->OnMouseDown(newMsg);
					delete newMsg;

					
				}
				else
				{
					//Signal was already sent (do nothing)
				}
			}
			else
			{
					//Do nothing (mouse is outside of the control
			}
		}
		else if (msg->m_SDLEvent->type == SDL_MOUSEBUTTONUP)
		{
			//Grab mouse coordinates from event
			int mouseX = msg->m_SDLEvent->motion.x;
			int mouseY = msg->m_SDLEvent->motion.y;

			//Actual HitBox check
			if (m_IsHover)
			{
				//Mouse is already atop of control
				if (m_IsPressed)
				{
					//Pressed signal was already sent: send Up singal
					m_IsPressed = false;

					Message* newMsg = new Message();
					newMsg->m_Type = MSG_MOUSEBUTTONUP;
					newMsg->m_SDLEvent = msg->m_SDLEvent;
					this->OnMouseUp(newMsg);
					delete newMsg;

					//Actually that's a click

					Message* newMsg2 = new Message();
					newMsg2->m_Type = MSG_MOUSECLICK;
					newMsg2->m_SDLEvent = msg->m_SDLEvent;
					this->OnMouseClick(newMsg2);
					delete newMsg2;
				
				}
				else
				{
					//Signal was already sent (do nothing)
				}
			}
			else
			{
				//Mouse is outside of the control
				m_IsPressed = false;

				Message* newMsg = new Message();
				newMsg->m_Type = MSG_MOUSEBUTTONUP;
				newMsg->m_SDLEvent = msg->m_SDLEvent;
				this->OnMouseUp(newMsg);
				delete newMsg;
			}
		}
		delete rectHitBox;

		////Bubble Down
		//Node* node = this->GetFirstChild();
		//while (node != nullptr)
		//{
		//	if (dynamic_cast<ControlNode*>(node))
		//	{
		//		((ControlNode*)node)->Draw();
		//	}
		//	node = node->GetNextSibling();
		//}
		////Message was bubbled down
		//return;
	}

	////Bubble Down
	//Node* node = this->GetFirstChild();
	//while (node != nullptr)
	//{
	//	//if (dynamic_cast<ControlNode*>(node))
	//	//{
	//		//((ControlNode*)node)->Draw();
	//	//}
	//	node->ProcessMessage(msg);
	//	node = node->GetNextSibling();
	//}
	//Message was bubbled down
	//return;

	//Bubble up: Dispatch message to CanvasNode's ProcessMessage
	super::ProcessMessage(msg);
}

void ControlNode::OnMouseMove(Message* msg)
{
	if (!m_IsHover)
	{
		this->OnMouseEnter(msg);
	}
}

void ControlNode::OnMouseEnter(Message* msg)
{
	this->SetIsHover(true);
}

void ControlNode::OnMouseLeave(Message* msg)
{
	this->SetIsHover(false);
	this->SetIsPressed(false);
}

void ControlNode::OnMouseDown(Message* msg)
{
	this->BringToFront();
	EventManager::GrabFocus(this);
	this->SetIsPressed(true);
	this->SetIsFocused(true);
}

void ControlNode::OnMouseUp(Message* msg)
{
	this->SetIsPressed(false);
}

void ControlNode::OnMouseClick(Message* msg)
{
	this->SetIsFocused(true);
	
}

void ControlNode::Draw()
{
	LogEngine::Log(LOG_DEBUG, "ControlNode", "Draw() called on " + this->GetName());

	if (GetIsVisible())
	{
		//Color* fillColor = AssetManager::CreateColor(80, 0, 0, 80);
		//RenderingEngine::SetFillColor(fillColor);
		//RenderingEngine::DrawRectangle(this, 0, 0, this->GetSize()->GetWidth(), this->GetSize()->GetHeight());
	}

	//Don't bubble upwards
	super::Draw();
}

