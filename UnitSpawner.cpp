#include "UnitSpawner.h"
#include "Game.h"
#include "Unit.h"
#include "UnitManager.h"

UnitSpawner::UnitSpawner()
{
	init();
}

bool UnitSpawner::init()
{
	mpDataManager = Game::getInstance()->getDataManager();
	if (mpDataManager = nullptr) 
	{
		return false;
	}
	mSpeedMin = mpDataManager->getFloat("SpeedMin");
	mSpeedMax = mpDataManager->getFloat("SpeedMax");
	mSpeedIncrease = mpDataManager->getFloat("SpeedIncrease");
	mSpawnChance = mpDataManager->getFloat("SpawnChance");
	mSpawnIncrease = mpDataManager->getFloat("SpawnIncrease");
	return true;
}

void UnitSpawner::update(float dt)
{
	float chance = rand() % 100;

	if (chance <= mSpawnChance)
	{
		spawnUnit();
	}
	mSpeedMin += mSpeedIncrease * (dt / 1000);
	mSpeedMax += mSpeedIncrease * (dt / 1000);

	mSpawnChance += mSpawnIncrease * (dt / 1000);
}

void UnitSpawner::spawnUnit()
{
	Unit* pUnit = Game::getInstance()->getUnitManager()->enableUnit();

	if (pUnit == nullptr) return;

	//random spawn position
	int randXPos = (rand() % (mSpawnAreaWidth + 1)) - mSpawnAreaWidth / 2;
	int randYPos = (rand() % (mSpawnAreaHeight + 1)) - mSpawnAreaHeight / 2;
	Vector2D spawnPoint = Vector2D(randXPos, randYPos);
	pUnit->setPosition(spawnPoint);

	//random velocity
	int randXDir = (rand() % 1001) - 500;
	int randYDir = (rand() % 1001) - 500;
	float speed = lerp(mSpeedMin, mSpeedMax, ((rand() % 101) / (float)100));
	pUnit->setVelocity(Vector2D(randXDir, randYDir), speed);

	int randColor = rand() % 2;
	if (randColor == 0) pUnit->swapAnimation();//TODO: change this to swap state entirely
}