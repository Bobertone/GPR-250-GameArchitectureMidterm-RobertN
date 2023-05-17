#pragma once
#include <Trackable.h>
#include "Color.h"
#include <allegro5/allegro.h>

//A class to hold a chunk of memory used to display something
class GraphicsBuffer : public Trackable
{	
private:
	////-DATA-

	//An Allegro bitmap
	ALLEGRO_BITMAP* mpBitmap;
	bool mOwnsBitmap;

public:
	////-FRIENDS-

	//Graphics Buffer is a friend class of GraphicsSystem
	friend class GraphicsSystem;

	////-FUNCTIONS-

	//Constructor(s) / destructor
	GraphicsBuffer(const std::string& filename);
	GraphicsBuffer(int width, int height, Color color);
	GraphicsBuffer(ALLEGRO_DISPLAY* mpDisplay);

	~GraphicsBuffer() /* { if (mOwnsBitmap)al_destroy_bitmap(mpBitmap); } */;

	//Accessors(height, width)
	int getHeight() { return al_get_bitmap_height(mpBitmap); }
	int getWidth() { return al_get_bitmap_width(mpBitmap); }

	void setBitmapColor(Color color);
	
	/*
	int spriteNum = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			pSmurf[spriteNum] = new Sprite(pSmurfSheetBuffer, Vector2D(i * SMURF_SIZE, j * SMURF_SIZE), SMURF_SIZE, SMURF_SIZE);
			pGraphicsSystem->draw(Vector2D(rand() % (DISP_WIDTH - SMURF_SIZE), rand() % (DISP_WIDTH - SMURF_SIZE)), pSmurf[spriteNum]);
			spriteNum++;
		}
	}	 
	*/	 
};		 
		 
