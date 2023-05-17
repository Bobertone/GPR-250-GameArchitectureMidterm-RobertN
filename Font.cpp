#include "Font.h"

Font::Font(const std::string& filename, int size)
{
	mSize = size;
	mpFontType = al_load_ttf_font(filename.c_str(), mSize, 0);
}

Font::~Font()
{
	al_destroy_font(mpFontType);
}
