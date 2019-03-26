#pragma once

#include "CanvasNode.h"
#include "Anchor.h"
#include "Margin.h"

class ControlNode : public CanvasNode
{
private:
	typedef CanvasNode	super;
	bool				m_IsEnabled;
	bool				m_IsHover;
	bool				m_IsPressed;
	bool				m_IsFocused;
	
	//bool				m_TabStop;
	//int				m_TabIndex;
	//Size*				m_MaxSize;
	//Size*				m_MinSize;
	//Anchor*			m_Anchor;
	//Margin*			m_Margin;
	//Padding*			m_Padding;
	//bool				m_IsAutoSize;
	//AutoSizeStyle*	m_AutoSizeStyle;
	
public:
	//Constructors, destructor
	ControlNode();
	~ControlNode();
		
	//Accessor methods
	bool GetIsEnabled();
	void SetIsEnabled(bool value);
	bool GetIsHover();
	void SetIsHover(bool value);
	bool GetIsPressed();
	void SetIsPressed(bool value);
	bool GetIsFocused();
	void SetIsFocused(bool value);

	//Overridable methods
	//virtual void Update(); //Called at every frame
	virtual void ProcessMessage(Message* msg);
	virtual void OnMouseMove(Message* msg);
	virtual void OnMouseEnter(Message* msg);
	virtual void OnMouseLeave(Message* msg);
	virtual void OnMouseDown(Message* msg);
	virtual void OnMouseUp(Message* msg);
	virtual void OnMouseClick(Message* msg);
	virtual void Draw() override;
};