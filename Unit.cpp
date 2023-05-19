#include "Unit.h"
#include "Game.h"
#include "GraphicsSystem.h"

Unit::Unit(Vector2D loc, std::vector<Animation*> animations) 
{
	mLoc = loc;
	mpAnimations = animations;
	mCurrentAnimation = 0;
	mIsDead = false;
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
	mVel = (newDir.normalize() * newSpeed);
	
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
