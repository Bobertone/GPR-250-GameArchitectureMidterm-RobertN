#include "Unit.h"
#include "Game.h"
#include "GraphicsSystem.h"
#include "GameEvent.h"
#include "EventSystem.h"

Unit::Unit(Vector2D loc, std::vector<Animation*> animations) 
{
	mLoc = loc;
	mpAnimations = animations;
	mCurrentAnimation = 0;
	mEnabled = false;
}

Unit::~Unit()
{
	for (unsigned int i = 0; i < mpAnimations.size(); i++)
	{
		delete mpAnimations[i];
	}
}

void Unit::update(float dt)
{
	//Update Position
	mLoc += mVel * (dt/1000);
	//Update Animation
	mpAnimations[mCurrentAnimation]->update(dt);
	//Check if unit is off screen, disable if so
	if (mLoc.getX() > DISP_WIDTH || mLoc.getX() < 0 || mLoc.getY() > DISP_HEIGHT || mLoc.getY() < 0)
	{
		if (mIsRed) 
		{
			EventSystem::getInstance()->fireEvent(GameEvent(RED_ORB_DESTROYED));
		}
		else
		{
			EventSystem::getInstance()->fireEvent(GameEvent(BLUE_ORB_DESTROYED));
		}
		disable();
	}
}

void Unit::draw()
{
	Game::getInstance()->getGraphicsSystem()->drawCentered(mLoc, mpAnimations[mCurrentAnimation]->getCurrentSprite());
}

void Unit::swapAnimation()
{
	if ((int)mCurrentAnimation >= (int)mpAnimations.size()-1)
	{
		mCurrentAnimation = 0;
	}
	else
	{
		mCurrentAnimation++;
	}
}

void Unit::setVelocity(Vector2D newDir, float newSpeed)
{
	Vector2D dir = newDir.getNormalizedVector();
	mVel = (dir * newSpeed);
}

void Unit::disable()
{
	mEnabled = false;
}

void Unit::reset()
{
	mVel = mOrigin;
	mLoc = mOrigin;

}
