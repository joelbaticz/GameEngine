#pragma once

#include "PrimitiveNode.h"
#include "Color.h"

class ShapeNode : public PrimitiveNode
{
private:
	typedef PrimitiveNode	super;
	Color*					m_StrokeColor;
	Color*					m_FillColor;
public:
	//Constructors, destructor
	ShapeNode();
	~ShapeNode();

	//Accessor methods
	Color* GetStrokeColor();
	void SetStroketColor(Color* color);

	Color* GetFillColor();
	void SetFillColor(Color* color);

	//Overridable methods
	void Draw() override;
};