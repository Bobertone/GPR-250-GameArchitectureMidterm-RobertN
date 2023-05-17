#include "GraphicsSystem.h"

GraphicsSystem::GraphicsSystem()
{
	mpDisplay = nullptr;
	mpBuffer = nullptr;
}

GraphicsSystem::~GraphicsSystem()
{
	cleanup();
}

bool GraphicsSystem::init(int width, int height)
{
	bool initSuccessful =
		al_init() &&
		al_init_image_addon() &&
		al_init_primitives_addon() &&
		al_init_font_addon() &&
		al_init_ttf_addon();

	mpDisplay = al_create_display(width, height);

	mpBuffer = new GraphicsBuffer(mpDisplay);

	return initSuccessful;

}

void GraphicsSystem::cleanup()
{
	delete mpBuffer;
	al_destroy_display(mpDisplay);
}

void GraphicsSystem::draw(const Vector2D& destLoc, Sprite* sourceImg, float scale)
{
	draw(mpBuffer, destLoc, sourceImg, scale);
}

void GraphicsSystem::draw(const Vector2D& destLoc, GraphicsBuffer* sourceBuff, float scale)
{
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	al_set_target_bitmap(mpBuffer->mpBitmap);

	al_draw_scaled_bitmap(
		sourceBuff->mpBitmap,
		0, 0,
		sourceBuff->getWidth(), sourceBuff->getHeight(),
		destLoc.getX(), destLoc.getY(),
		sourceBuff->getWidth() * scale, sourceBuff->getHeight() * scale,
		0);

	al_set_target_bitmap(pOldTarget);
}

void GraphicsSystem::draw(GraphicsBuffer* graphicsBuffer, const Vector2D& destLoc, Sprite* sourceImg, float scale)
{
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	al_set_target_bitmap(graphicsBuffer->mpBitmap);

	al_draw_scaled_bitmap(
		sourceImg->getBuffer()->mpBitmap,
		sourceImg->getSourceLoc().getX(), sourceImg->getSourceLoc().getY(),
		sourceImg->getWidth(), sourceImg->getHeight(),
		destLoc.getX(), destLoc.getY(),
		sourceImg->getWidth() * scale, sourceImg->getHeight() * scale,
		0);

	al_set_target_bitmap(pOldTarget);
}

void GraphicsSystem::drawCentered(const Vector2D& destLoc, Sprite* sourceImg, float scale)
{
	Vector2D halfSprite(sourceImg->getWidth()/2, sourceImg->getHeight()/2);
	Vector2D newDest(destLoc.getX() - halfSprite.getX(), destLoc.getY() - halfSprite.getY());
	draw(newDest, sourceImg, scale);
}

void GraphicsSystem::writeText(const Vector2D& targetLoc, Font* font, const Color& color, const std::string& text)
{
	al_draw_text(font->mpFontType, al_map_rgba(color.r, color.g, color.b, color.a), targetLoc.getX(), targetLoc.getY(), 0, text.c_str());
}

void GraphicsSystem::writeText(GraphicsBuffer* graphicsBuffer, const Vector2D& targetLoc, Font* font, const Color& color, const std::string& text)
{
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	al_set_target_bitmap(graphicsBuffer->mpBitmap);

	al_draw_text(font->mpFontType, al_map_rgba(color.r, color.g, color.b, color.a), targetLoc.getX(), targetLoc.getY(), 0, text.c_str());
	
	al_set_target_bitmap(pOldTarget);
}

void GraphicsSystem::saveBuffer(GraphicsBuffer* graphicsBuffer, const std::string filename)
{
	al_save_bitmap(filename.c_str(), graphicsBuffer->mpBitmap);
}
