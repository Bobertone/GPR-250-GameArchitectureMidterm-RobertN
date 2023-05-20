#include "UnitManager.h"
#include "Game.h"
#include "GraphicsSystem.h"

UnitManager::UnitManager(const vector<Animation>& orbAnimations)
{
	mpAnimations = orbAnimations;
	for (int i = 0; i < mPoolSize; i++)
	{
		mpUnitPool.push_back(new Unit(mpAnimations));
	}
}

UnitManager::~UnitManager()
{
	clear();
	// maybe a cleanup(); ?
}


void UnitManager::clear()
{
	for (unsigned int i = 0; i < mpUnitPool.size(); i++)
	{
		delete mpUnitPool[i];
	}
	for (unsigned int i = 0; i < mpActiveUnits.size(); i++)
	{
		delete mpActiveUnits[i];
	}
}

Unit* UnitManager::enableUnit()
{
	Unit* pTempUnit = mpUnitPool.at(0);
	if (pTempUnit == nullptr)
	{
		cout << "Unit Pool Empty" << endl;
		return nullptr;
	}
	mpUnitPool.erase(mpUnitPool.begin());
	mpActiveUnits.push_back(pTempUnit);

	pTempUnit->enable();

	return pTempUnit;
}

void UnitManager::disableUnit(Unit* theUnit)
{
	theUnit->disable();
}

void UnitManager::disableUnit(unsigned int position)
{
	mpActiveUnits[position]->disable();
}

void UnitManager::moveDisabledUnitsToPool()
{
	for (unsigned int i = 0; i < mpActiveUnits.size(); i++)
	{
		if (!mpActiveUnits[i]->isEnabled())
		{
			mpUnitPool.push_back(mpActiveUnits[i]);
			mpActiveUnits[i]->reset();
			mpActiveUnits.erase(mpActiveUnits.begin() + i);
			i--;
		}
	}
}

void UnitManager::update(float dt)
{
	for (unsigned int i = 0; i < mpActiveUnits.size(); i++)
	{
		mpActiveUnits[i]->update(dt);
	}
	moveDisabledUnitsToPool();
}

void UnitManager::draw()
{
	for (unsigned int i = 0; i < mpActiveUnits.size(); i++)
	{
		mpActiveUnits[i]->draw();
	}
}
/*
Unit* UnitManager::getUnit(unsigned int index)
{
	return mpActiveUnits.at(index);
}
*/
Unit* UnitManager::getUnitAtPosition(Vector2D mousePos)
{
	for (unsigned int i = 0; i < mpActiveUnits.size(); i++)
	{
		Vector2D unitPositon = mpActiveUnits[i]->getPosition();
		if((mousePos.getX() > unitPositon.getX() - (mpActiveUnits[i]->getAnimation()->getCurrentSprite()->getWidth()) / 2) &&
			(mousePos.getX() < unitPositon.getX() + (mpActiveUnits[i]->getAnimation()->getCurrentSprite()->getWidth()) / 2) &&
			(mousePos.getY() > unitPositon.getY() - (mpActiveUnits[i]->getAnimation()->getCurrentSprite()->getWidth()) / 2) &&
			(mousePos.getY() < unitPositon.getY() + (mpActiveUnits[i]->getAnimation()->getCurrentSprite()->getHeight())/2))
		{
			return mpActiveUnits[i];
		}
	}
	return nullptr;
}