#include "Unit.h"
#include "Game.h"
#include "GraphicsSystem.h"
#include "GameEvent.h"
#include "EventSystem.h"

Unit::Unit(Vector2D loc, const std::vector<Animation>& animations) 
{
	mLoc = loc;
	mAnimations = animations;
	mCurrentAnimation = 0;
	mEnabled = false;
}

Unit::Unit(const std::vector<Animation>& animations)
{
	mLoc = Game::getInstance()->getGraphicsSystem()->getCenter();
	mAnimations = animations;
	mCurrentAnimation = 0;
	mEnabled = false;
}

Unit::~Unit()
{
}

void Unit::update(float dt)
{
	//Update Position
	mLoc += mVel * (dt/1000);
	//Update Animation
	mAnimations[mCurrentAnimation].update(dt);
	//Check if unit is off screen, disable if so
	if (mLoc.getX() > Game::getInstance()->getGraphicsSystem()->getWidth() || mLoc.getX() < 0 ||
		mLoc.getY() > Game::getInstance()->getGraphicsSystem()->getHeight() || mLoc.getY() < 0)
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
	Game::getInstance()->getGraphicsSystem()->drawCentered(mLoc, mAnimations[mCurrentAnimation].getCurrentSprite());
}

void Unit::swapAnimation()
{
	if ((int)mCurrentAnimation >= (int)mAnimations.size()-1)
	{
		mCurrentAnimation = 0;
	}
	else
	{
		mCurrentAnimation++;
	}
}

void Unit::swapUnit()
{
	swapAnimation();
	mIsRed = !mIsRed;
}

void Unit::setVelocity(Vector2D newDir, float newSpeed)
{
	Vector2D dir = newDir.getNormalizedVector();
	mVel = (dir * newSpeed);
}

void Unit::reset()
{
	mVel = mOrigin;
	mLoc = Game::getInstance()->getGraphicsSystem()->getCenter();

}