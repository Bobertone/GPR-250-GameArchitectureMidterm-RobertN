#pragma once
#include "GraphicsSystem.h"
#include "Font.h"
#include "Color.h"
#include <string>
using namespace std;

//HUD – displays score, total time elapsed, and FPS counter
class HUD
{
public:
	HUD();
	~HUD();
	void startScreen();
	void pauseScreen();
	void gameOver();
	void score(int score);
	void fps(float fps);
	void timer(int timer);
private:
	GraphicsSystem* mpGraphicsSystem;
	const string ASSET_PATH = "..\\..\\shared\\assets\\";
	const string FONT_FILENAME = "cour.ttf";
	const int FONT_SIZE = 50;
	Color mWhite = Color(255, 255, 255);
	Font* mpFont;
};