#include "Node.h"
#include "GameEngine.h"
#include "EventManager.h"

void Node::Init(std::string name)
{
	m_Name = name;
	m_Parent = nullptr;
	m_FirstChild = nullptr;
	m_NextSibling = nullptr;
	EventManager::Subscribe(this);

	//Register at ResourceManager
}

Node::Node()
{
	LogEngine::Log(LOG_TRACE, "Node", "Creating node");

	Init("NodeName");
}

Node::Node(std::string name)
{
	LogEngine::Log(LOG_TRACE, "Node", "Creating node " + name);

	Init(name);
}

Node::~Node()
{
	LogEngine::Log(LOG_TRACE, "Node", "Destroying node");

	m_Parent = nullptr;

	//ACTUALLY CALLING DELETE ON CHILD NODES 
}

std::string Node::GetName()
{
	return m_Name;
}

void Node::SetName(std::string componentName)
{
	m_Name = componentName;
}

Node* Node::GetParent()
{
	if (GameEngine::IsRootNode(m_Parent))
	{
		//return nullptr;
	}

	return m_Parent;
}

Node* Node::SetParent(Node* value)
{
	Node* prevParent = m_Parent;
	
	if (GameEngine::IsRootNode(prevParent))
	{
		//prevParent = nullptr;
	}

	m_Parent = value;
	return prevParent;
}

Node* Node::GetFirstChild()
{
	return m_FirstChild;
}

void Node::SetFirstChild(Node* value)
{
	m_FirstChild = value;
}

Node* Node::GetNextSibling()
{
	return m_NextSibling;
}

void Node::SetNextSibling(Node* value)
{
	m_NextSibling = value;
}

Node* Node::GetTopmostNode()
{
	Node* result = this;

	while(true)
	{
		if (result->GetParent() == nullptr)
		{
			return result;
		}
		else
		{
			result = result->GetParent();
		}
	}
}

//Node* Node::GetTopmostNode()
//{
//	Node* node = this;
//	Node* parent;
//	//while((node = node->GetParent()) !=nullptr)
//	while (1)
//	{
//		parent = node->GetParent();
//		if (parent == nullptr)
//		{
//			return node;
//		}
//		node = parent;
//	}
//}

void Node::AddChild(Node* value)
{
	Node* node = this;

	if (node->GetFirstChild() == nullptr)
	{
		node->SetFirstChild(value);
		value->SetParent(this);
		return;
	}

	node = node->GetFirstChild();
	while(1)
	{
		if (node->GetNextSibling() != nullptr)
		{
			node = node->GetNextSibling();
		}
		else
		{
			node->SetNextSibling(value);
			value->SetParent(this);
			return;
		}
	}
}

void Node::ProcessMessage(Message* msg)
{
	LogEngine::Log(LOG_DEBUG, "Node", "ProcessMessage() called on " + this->GetName());

	switch(msg->m_Type)
	{
	case MSG_UPDATE:
		this->Update();
		//return;
		////Bubble Down Update
		//Node* node = this->GetFirstChild();
		//while (node != nullptr)
		//{
		//	node->Update();
		//	node = node->GetNextSibling();
		//}
		////Message was bubbled down
		//return;
	}

	////Bubble Down ProcessMessage
	/*Node* node = this->GetFirstChild();
	while (node != nullptr)
	{
		node->ProcessMessage(msg);
		node = node->GetNextSibling();
	}*/

	//Call Node.Draw:
	//Node::Draw();
	//Anything else calls CanvasNode
	//Draw(), this->Draw(), dynacast, cast...
}

void Node::Update()
{
	LogEngine::Log(LOG_DEBUG, "Node", "Update() called on " + this->GetName());

	//Bubble Down Update
	//Node* node = this->GetFirstChild();
	//while (node != nullptr)
	//{
	//	node->Update();
	//	node = node->GetNextSibling();
	//}
	////Message was bubbled down
	//return;
}
