#pragma once
#include <Trackable.h>
#include <vector>
#include <Vector2D.h>
#include "Animation.h"
#include "Unit.h"
using namespace std;

//A class to hold a “list” of all Units in the game
class Unit;

class UnitManager : public Trackable
{
private:
	////-DATA-

	// A collection of all the active Units
	std::vector<Unit*> mpActiveUnits;
	//The pool of Units
	std::vector<Unit*> mpUnitPool;

	Vector2D mOrigin = Vector2D(0, 0);

	int poolSize = 100;

public:

	////-FUNCTIONS-

	// Constructor / destructor
	UnitManager();
	~UnitManager();
	void initUnitManager(std::vector<Animation*> initAnims, int poolSize);

	//~UnitManager() { clear(); };
	//Clear - remove and delete all units
	void clear();

	// Some way of adding / deleting / getting units
	Unit* enableUnit();
	void disableUnit(Unit* unit);
	void disableUnit(unsigned int position);

	// Clear - remove and delete all units	;
	void moveDisabledUnitsToPool();

	//Unit* getUnit(unsigned int index);

	int getActiveUnitCount() { return mpActiveUnits.size(); }

	Unit* getUnitAtPosition(Vector2D mousePos);

	// update - update the units and delete the ones you were going to delete
	void update(float dt);

	// draw ~ draw the current animation’s current sprite in the location of the unit
	void draw();
};