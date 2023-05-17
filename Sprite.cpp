#include "Sprite.h"

Sprite::Sprite(GraphicsBuffer* graphicsBuffer, Vector2D loc, int width, int height)
{
	mpGraphicsBuffer = graphicsBuffer;
	mSourceLoc = loc;
	mWidth = width;
	mHeight = height;
}

Sprite::Sprite(GraphicsBuffer* graphicsBuffer)
{
	mpGraphicsBuffer = graphicsBuffer;
	mSourceLoc = Vector2D(0,0);
	mWidth = mpGraphicsBuffer->getWidth();
	mHeight = mpGraphicsBuffer->getHeight();
}


Sprite::~Sprite()
{
}
