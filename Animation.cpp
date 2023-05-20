#include "Animation.h"

Animation::Animation(GraphicsBuffer* spriteSheetBuffer, int rows, int columns)
{
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
		{
			Sprite frame(spriteSheetBuffer, 
				Vector2D(
					x * spriteSheetBuffer->getWidth()/ columns,
					y * spriteSheetBuffer->getHeight()/rows),
				spriteSheetBuffer->getWidth() / columns,
				spriteSheetBuffer->getHeight() / rows);

			mSprites.push_back(frame);
		}
	}

}

Animation::Animation(GraphicsBuffer* spriteSheetBuffer, int rows, int columns, int startingRow, int startingColumn, int endingRow, int endingColumn)
{
	for (int y = 0; y <= endingRow - startingRow; y++)
	{
		for (int x = 0; x < endingColumn - startingColumn; x++)
		{
			Sprite frame(spriteSheetBuffer,
				Vector2D(
					(x + startingColumn) * spriteSheetBuffer->getWidth() / columns,
					(y + startingRow) * spriteSheetBuffer->getHeight() / rows),
				spriteSheetBuffer->getWidth() / columns,
				spriteSheetBuffer->getHeight() / rows);

			mSprites.push_back(frame);
		}
	}

}

Animation::~Animation()
{
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

		if ((int)mCurrentSprite >= (int)mSprites.size()-1)
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
