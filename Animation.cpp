#include "Animation.h"

Animation::Animation(GraphicsBuffer* spriteSheetBuffer, int rows, int columns)
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
		{
			Sprite* frame = new Sprite(spriteSheetBuffer, 
				Vector2D(
					x * spriteSheetBuffer->getWidth()/ columns,
					y * spriteSheetBuffer->getHeight()/rows),
				spriteSheetBuffer->getWidth() / columns,
				spriteSheetBuffer->getHeight() / rows);

			mpSprites.push_back(frame);
		}
	}

}

Animation::~Animation()
{
	for (unsigned int i = 0; i < mpSprites.size(); i++)
	{
		delete mpSprites[i];
	}
}

void Animation::update(float dt)
{
	if (mPaused) 
	{
		return;
	}
	elapsedTime += dt;
	if (elapsedTime >= mTimeBetweenSprites) 
	{
		elapsedTime = 0;

		if ((int)mCurrentSprite >= (int)mpSprites.size()-1)
		{
			if (mShouldLoop)
			{
				mCurrentSprite = 0;
			}
		}
		else
		{
			mCurrentSprite++;
		}
	}
}

void Animation::changeAnimationSpeed(bool speedUp)
{
	if (speedUp)
	{
		if (mTimeBetweenSprites > mTimeIncrement)
		{
			mTimeBetweenSprites -= mTimeIncrement;
		}
	}
	else
	{
		mTimeBetweenSprites += mTimeIncrement;
	}
}
