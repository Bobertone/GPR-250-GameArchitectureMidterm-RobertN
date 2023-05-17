#include "GraphicsBuffer.h"

GraphicsBuffer::GraphicsBuffer(const std::string& filename)
{
	mpBitmap = al_load_bitmap(filename.c_str());
	mOwnsBitmap = true;
}

GraphicsBuffer::GraphicsBuffer(int width, int height, Color color)
{
	mpBitmap = al_create_bitmap(width, height);
	setBitmapColor(color);
	mOwnsBitmap = true;
}

GraphicsBuffer::GraphicsBuffer(ALLEGRO_DISPLAY* mpDisplay)
{
	mpBitmap = al_get_backbuffer(mpDisplay);
	mOwnsBitmap = false;
}

GraphicsBuffer::~GraphicsBuffer()
{
	if (mOwnsBitmap) {
		al_destroy_bitmap(mpBitmap);
	}

}

void GraphicsBuffer::setBitmapColor(Color color)
{
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	al_set_target_bitmap(mpBitmap);

	al_clear_to_color(al_map_rgba(color.r, color.g, color.b, color.a));

	al_set_target_bitmap(pOldTarget);
}
