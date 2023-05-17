#include "HUD.h"
HUD::HUD(GraphicsSystem& graphicsSystem)
{
	mGraphicsSystem = &graphicsSystem;
}
HUD::~HUD()
{
}
void HUD::startScreen()
{
	Vector2D loc1(300, 200);
	Vector2D loc2(125, 300);
	string titleText = "RJN Midterm";
	string instructionText = "Press Space to Start";
	mGraphicsSystem->writeText(loc1, mpFont, mWhite, titleText);
	mGraphicsSystem->writeText(loc2, mpFont, mWhite, instructionText);
}
void HUD::pauseScreen()
{
	Vector2D loc1(300, 200);
	Vector2D loc2(100, 300);
	Vector2D loc3(100, 400);
	string text1 = "Paused";
	string text2 = "Press Space to Resume";
	string text3 = " Press Escape to Exit";
	mGraphicsSystem->writeText(loc1, mpFont, mWhite, text1);
	mGraphicsSystem->writeText(loc2, mpFont, mWhite, text2);
	mGraphicsSystem->writeText(loc3, mpFont, mWhite, text3);
}
void HUD::gameOver()
{
	Vector2D loc1(300, 200);
	Vector2D loc2(125, 300);
	string text1 = "Game Over";
	string text2 = "Press Escape to Exit";
	mGraphicsSystem->writeText(loc1, mpFont, mWhite, text1);
	mGraphicsSystem->writeText(loc2, mpFont, mWhite, text2);
}
void HUD::score(int score)
{
	Vector2D loc(0, 0);
	string text = "Score: " + to_string(score);
	mGraphicsSystem->writeText(loc, mpFont, mWhite, text);
}
void HUD::fps(float fps)
{
	Vector2D loc(500, 0);
	string text = to_string(fps);
	mGraphicsSystem->writeText(loc, mpFont, mWhite, text);
}
void HUD::timer(int timer)
{
	Vector2D loc(500, 500);
	string text = "Time: " + to_string(timer);
	mGraphicsSystem->writeText(loc, mpFont, mWhite, text);
}