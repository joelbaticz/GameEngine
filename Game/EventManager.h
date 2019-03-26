#pragma once

#include "GameEngine.h"


class EventManager
{
private:

	static Node**	m_SubscriberList;
	static int		m_SubscriberCount;

	static Node*	m_NodeHit;
	static Node*	m_NodeHitPrev;
	static Node*	m_NodeMouseButtonDown;
	static Node*	m_NodeMouseButtonUp;

	static Node*	m_NodeFocused;

	
	static void BroadcastUpdate();
	static void BroadcastDraw();
	static void BroadcastDrawSubNode(Node* node);
	static void BroadcastMouse(Message* msg);
	static void BroadcastMouseSubNode(Node* node, Message* msg);
	static void BroadcastObscure(Message* msg);

	static void UnFocusTree(Node* node);
	static void FocusTree(Node* node);

	EventManager();
	~EventManager();
public:
	static int Init();

	static void Subscribe(Node* node);
	static void Unsubscribe(Node* node);

	static void Broadcast(Message* msg);

	static void GrabFocus(Node* node);
	

};