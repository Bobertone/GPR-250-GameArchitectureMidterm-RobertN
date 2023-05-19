#pragma once
#include <Trackable.h>
#include "DataManager.h"
class UnitSpawner : public Trackable
{
public:
	UnitSpawner();
	~UnitSpawner() {};

	float minVel;
	float maxVel;

	bool init();
	void update(float dt);
	void spawnUnit();
private:
	DataManager* mpDataManager;
	float mSpeedMin;
	float mSpeedMax;
	float mSpeedIncrease;
	float mSpawnChance;
	float mSpawnIncrease;

	int mSpawnAreaWidth = 80;
	int mSpawnAreaHeight = 60;

};