#include "UnitManager.h"

UnitManager::UnitManager()
{
	std::vector<Unit*> mpUnitPool(poolSize);
}

UnitManager::~UnitManager()
{
	clear();
	// maybe a cleanup(); ?
}

void UnitManager::initUnitManager(std::vector<Animation*> initAnims, int poolSize)
{
	mpUnitPool.reserve(poolSize);
	while (mpUnitPool.size() < poolSize)
	{
		mpUnitPool.push_back(new Unit(mOrigin, initAnims));
	}
};

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
	Unit* tempUnit = mpUnitPool.at(0);
	mpUnitPool.erase(mpUnitPool.begin());
	mpActiveUnits.push_back(tempUnit);
	return tempUnit;
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