#include "ShapeNode.h"
#include "AssetManager.h"

ShapeNode::ShapeNode()
{
	SetName("Shape");
	m_StrokeColor = AssetManager::GetDefaultPenColor();
	m_FillColor = AssetManager::GetDefaultFillColor();
	
	//We don't need this, since the CanvasNode will handle this!!!
	/*SDL_Rect* newRect = new SDL_Rect();
	newRect->x = 50;
	newRect->y = 50;
	newRect->w = 50;
	newRect->h = 50;
	SetRect(newRect);*/
}

ShapeNode::~ShapeNode()
{

}

Color* ShapeNode::GetStrokeColor()
{
	return m_StrokeColor;
}

void ShapeNode::SetStroketColor(Color* value)
{
	m_StrokeColor = value;
}

Color* ShapeNode::GetFillColor()
{
	return m_FillColor;
}

void ShapeNode::SetFillColor(Color* value)
{
	m_FillColor = value;
}

void ShapeNode::Draw()
{
	LogEngine::Log(LOG_DEBUG, "ShapeNode", "Draw() called on " + this->GetName());
	
	RenderingEngine::SetPenColor(m_StrokeColor);
	RenderingEngine::SetFillColor(m_FillColor);
	RenderingEngine::DrawRectangle(this, 0 , 0, this->GetSize()->GetWidth(), this->GetSize()->GetHeight());

	//Don't bubble upwards
	//super::Draw();
}
