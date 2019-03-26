#pragma once

#include "PrimitiveNode.h"
#include "Color.h"
#include "Texture.h"

class SpriteNode : public PrimitiveNode
{
private:
	typedef PrimitiveNode	super;
	Texture*				m_Texture;
	int						m_CornerSize;
	int						m_TextureIndex;
	//SpriteLayout*			m_Layout;
	//Align*				m_Align;
public:
	//Constructors, destructor
	SpriteNode();
	~SpriteNode();

	//Accessor methods
	Texture* GetTexture();
	void SetTexture(Texture* value);

	int GetCornerSize();
	void SetCornerSize(int value);

	int GetTextureIndex();
	void SetTextureIndex(int textureIndex);

	//Overridable methods
	void Draw() override;
};