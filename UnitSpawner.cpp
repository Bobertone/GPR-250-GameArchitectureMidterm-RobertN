#include "UnitSpawner.h"
#include "Game.h"
#include "GraphicsSystem.h"
#include "Unit.h"
#include "UnitManager.h"

UnitSpawner::UnitSpawner()
{
	init();
}

bool UnitSpawner::init()
{
	DataManager* pDataManager = Game::getInstance()->getDataManager();
	if (pDataManager == nullptr)
	{
		return false;
	}
	mSpeedMin = pDataManager->getFloat("SpeedMin");
	mSpeedMax = pDataManager->getFloat("SpeedMax");
	mSpeedIncrease = pDataManager->getFloat("SpeedIncrease");
	mSpawnChance = pDataManager->getFloat("SpawnChance");
	mSpawnIncrease = pDataManager->getFloat("SpawnIncrease");
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
	int randXPos = ((rand() % (mSpawnAreaWidth + 1)) - mSpawnAreaWidth / 2) + Game::getInstance()->getGraphicsSystem()->getWidth() / 2;
	int randYPos = ((rand() % (mSpawnAreaHeight + 1)) - mSpawnAreaHeight / 2) + Game::getInstance()->getGraphicsSystem()->getHeight() / 2;
	Vector2D spawnPoint = Vector2D(randXPos, randYPos);
	pUnit->setPosition(spawnPoint);

	//random velocity
	int randXDir = (rand() % 1001) - 500;
	int randYDir = (rand() % 1001) - 500;
	float speed = lerp(mSpeedMin, mSpeedMax, ((rand() % 101)));
	pUnit->setVelocity(Vector2D(randXDir, randYDir), speed);

	int randColor = rand() % 2;
	if (randColor == 0) pUnit->swapUnit();//TODO: change this to swap state entirely
}