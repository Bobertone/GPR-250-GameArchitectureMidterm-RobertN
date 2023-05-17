#pragma once
#include <Trackable.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class Font : public Trackable
{
private:
	////-DATA-
	//Allegro font
	ALLEGRO_FONT* mpFontType;
	//Font size
	int mSize;
public:
	////-FRIENDS-
	//Font is a friend class of GraphicsSystem
	friend class GraphicsSystem;

	////-FUNCTIONS-
	//Constructor / destructor
	Font(const std::string& filename, int size);
	~Font();
	//Accessors(size)
	int	getWidth() { return mSize; }
};

