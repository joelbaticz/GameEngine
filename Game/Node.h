#pragma once

#include <string>
#include "SDL.h"
#include "LogEngine.h"
//#include "GameEngine.h"
#include "Defaults.h"
#include "Message.h"

class Node
{
private:
	std::string m_Name;
	Node*		m_Parent;
	Node*		m_FirstChild;
	Node*		m_NextSibling;

	void Init(std::string name);
public:
	//Constructors, destructor
	Node();
	Node(std::string name);
	~Node();

	//Accessor methods
	std::string GetName();
	void SetName(std::string name);
	Node* GetParent();
	Node* SetParent(Node* value);
	Node* GetFirstChild();
	void SetFirstChild(Node* value);
	Node* GetNextSibling();
	void SetNextSibling(Node* value);
	//void RemoveChild(Node* child);
	Node* GetTopmostNode();
	void AddChild(Node* value);
	//Node* GetTopmostNode();
	


	//Overridable methods
	virtual void ProcessMessage(Message* msg);
	virtual void Update(); //Called at every frame
};