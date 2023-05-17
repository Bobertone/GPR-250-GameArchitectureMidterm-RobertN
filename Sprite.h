#pragma once
#include <Trackable.h>
#include <Vector2D.h>
#include "GraphicsBuffer.h"
//A pointer to a specific part of a GraphicsBuffer
class Sprite : public Trackable
{
private:
	////-DATA-
	//Pointer to the GraphicsBuffer which contains the bitmap
	GraphicsBuffer* mpGraphicsBuffer;

	//Source loc(upper left - hand corner of where sprite begins)
	Vector2D mSourceLoc;

	//Width and height of sprite
	int mWidth;
	int mHeight;



public:
	////-FRIENDS-

	//Sprite is a friend class of GraphicsSystem
	//friend class GraphicsSystem;
	
	////-FUNCTIONS-
	
	//Constructor(s) / destructor
	Sprite(GraphicsBuffer* graphicsBuffer, Vector2D loc, int width, int height);
	Sprite(GraphicsBuffer* graphicsBuffer);
	~Sprite();
	
	//Accessors(source loc, height, width, GraphicsBuffer)
	Vector2D getSourceLoc() { return mSourceLoc; }
	int	getWidth() { return mWidth; }
	int getHeight() { return mHeight; }
	GraphicsBuffer* getBuffer() { return mpGraphicsBuffer; }
};

