#pragma once
#include <Trackable.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <Vector2D.h>
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Font.h"
#include "Color.h"

//The class which creates and maintains the allegro display
class GraphicsSystem : public Trackable
{
private:
	////-DATA-
	//the allegro display
	ALLEGRO_DISPLAY* mpDisplay;

	GraphicsBuffer* mpBuffer;

public:

	////-FUNCTIONS-
	//Constructor/Destructor
	GraphicsSystem();
	~GraphicsSystem();

	//Init/Cleanup
	bool init(int width, int height);
	//call cleanup in destructor
	void cleanup();

	//Accessors (height, width, back buffer)
	int getHeight()	{ return al_get_display_height(mpDisplay); }
	int getWidth()	{ return al_get_display_width(mpDisplay);}
	Vector2D getCenter() { return Vector2D(getWidth()/2, getHeight()/2); }

	GraphicsBuffer* getBackbuffer() { return mpBuffer; }

	//Flip - call the al_flip function to display what is in the Back Buffer
	void flip() { al_flip_display(); }

	//Draw (dest loc, src loc, Sprite, scale /* default to 1.0 */ ) - draw to current backbuffer
	void draw(const Vector2D& destLoc, Sprite* sourceImg, float scale = 1);

	void draw(const Vector2D& destLoc, GraphicsBuffer* sourceBuff, float scale = 1);

	//Draw(target graphics buffer, dest loc, src loc, Sprite, scale /* default to 1.0 */) - draw to given GraphicsBuffer 
	void draw(GraphicsBuffer* graphicsBuffer, const Vector2D& destLoc, Sprite* sourceImg, float scale = 1);

	//Draw (dest loc, src loc, Sprite, scale /* default to 1.0 */ ) - draw to current backbuffer
	void drawCentered(const Vector2D& destLoc, Sprite* sourceImg, float scale = 1);

	//WriteText(target loc, Font, Color, text) – write to current backbuffer
	void writeText(const Vector2D& targetLoc, Font* font, const Color& color, const std::string &text);

	//WriteText(target graphics buffer, target loc, Font, Color, text) – write to given GraphicsBuffer
	void writeText(GraphicsBuffer* graphicsBuffer, const Vector2D& targetLoc, Font* font, const Color& color, const std::string &text);

	//SaveBuffer(buffer to save, filename) – save the contents of a GraphicsBuffer to a file
	void saveBuffer(GraphicsBuffer* graphicsBuffer, const std::string filename);

};

