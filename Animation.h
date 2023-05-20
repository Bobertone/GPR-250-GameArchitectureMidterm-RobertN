#pragma once
#include <Trackable.h>
#include "Sprite.h"
#include <vector>
//Animation - A class to hold a list of Spritesand the timing information to switch between them
class Animation : public Trackable
{
private:
	////-DATA-
	
	// A “list” of Sprites (stl vector?)
	std::vector<Sprite> mSprites;

	// Timing info
	float mTimeBetweenSprites = 33.33f;
	float mTimeIncrement = 1;
	float elapsedTime = 0;

	// Data to keep track of which Sprite is current
	int mCurrentSprite = 0;

	// Data to indicate if animation should loop(start at beginning of list after reaching end) or not
	bool mShouldLoop = true;
	bool mPaused = false;

public:
	////-FUNCTIONS-
	
	// Constructor(s) / destructor
	// Some way of getting Sprite’s into Animation either through constructor or an addSprite function
	Animation(GraphicsBuffer* spriteSheetBuffer, int rows, int columns);
	Animation(GraphicsBuffer* spriteSheetBuffer, int rows, int columns, int startingRow, int startingColumn, int endingRow, int endingColumn);
	~Animation();
	
	// update – figure out what Sprite is “current”
	void update(float dt);

	// getCurrentSprite
	Sprite* getCurrentSprite() { return &mSprites[mCurrentSprite]; }

	// speed up / slow down – adjust timing to make animation faster or slower
	void changeAnimationSpeed(bool speedUp);

	void toggleAnimation() { mPaused = !mPaused; }
};

