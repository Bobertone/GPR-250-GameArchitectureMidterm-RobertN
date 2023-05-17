#pragma once
#include <Trackable.h>
#include "Animation.h"
//Unit - A class to hold state information for a game entity – for now, it holds location info for an animation
class Unit : public Trackable
{
private:
	////-DATA-
	
	// location(x, y)
	Vector2D mLocation;
	int mCurrentAnimation;
	bool mIsDead;
	bool mEnabled = false;
	// animation(s)
	std::vector<Animation*> mpAnimations;
	Vector2D mOrigin = Vector2D(0, 0);
	float mSpeed;

public:
	////-FUNCTIONS-
	
	// constructor(s) / destructor
	Unit(Vector2D loc, std::vector<Animation*> animations);
	~Unit();

	// update – adjusts the state of the Unit – in this case at minimum will call animation’s update function
	void update(float dt);
	
	// draw – draw the current animation’s current sprite in the location of the unit
	void draw();
	
	// swapAnimation – switch to a new animation
	void swapAnimation();
	
	Animation* getAnimation() { return mpAnimations[mCurrentAnimation]; }
	Vector2D getPosition() { return mLocation; }
	void setPosition(Vector2D newPos) { mLocation = newPos; }

	bool isDead() { return mIsDead; }
	bool isEnabled() { return mEnabled; }
	void kill() { mIsDead = true; }
	void disable();

	void reset();

};