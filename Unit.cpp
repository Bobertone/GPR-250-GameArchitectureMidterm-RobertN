#include "Unit.h"
#include "Game.h"
#include "GraphicsSystem.h"

Unit::Unit(Vector2D loc, std::vector<Animation*> animations) 
{
	mLocation = loc;
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
	mpAnimations[mCurrentAnimation]->update(dt);
}

void Unit::draw()
{
	Game::getInstance()->getGraphicsSystem()->drawCentered(mLocation, mpAnimations[mCurrentAnimation]->getCurrentSprite());
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

void Unit::disable()
{
	mEnabled = false;
}

void Unit::reset()
{
	mSpeed = 0;
	mLocation = mOrigin;

}
