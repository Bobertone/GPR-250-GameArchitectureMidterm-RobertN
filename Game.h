#pragma once
#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <Timer.h>
#include <Trackable.h>
#include <string>
#include <assert.h>
#include <EventListener.h>

using namespace std;

class GraphicsSystem;
class InputSystem;
class UnitManager;
class GraphicsBufferManager;
class InputTranslator;

//Game - The class which holds all systems and has the game loop
//Make this global in main
class Game : public EventListener
{
private:	 
	////-DATA-
	
	GraphicsSystem* mpGraphicsSystem = nullptr;
	InputSystem* mpInputSystem = nullptr;
	InputTranslator* mpInputTranslator = nullptr;
	
	GraphicsBufferManager* mpGraphicsBufferManager = nullptr;
	UnitManager* mpUnitManager = nullptr;
	DataManager* mpDataManager = nullptr;

	HUD* mpHUD = nullptr;

	bool mIsRunning = false;
	float mLoopTime = 16.7f;

	static Game* mspGame;

	// Constructor/Destructor 
	Game() {};
	~Game();
	float elapsedGameTime = 0;
	int mPoints = 10;
	int mPointIncrease = 1;
	int mPointDecrease = 5;

	Color mBlack = Color(0, 0, 0);
	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;

public:
	////-FUNCTIONS-

	void doLoop();

	void update(float dt);
	void draw(float dt);
	
	bool init();
	void cleanup();

	virtual void handleEvent(const Event& theEvent) override;

	void createSmurf(Vector2D pos);

	static void initInstance() { mspGame = new Game(); };
	static void cleanupInstance() { delete mspGame; mspGame = nullptr; };
	static Game* getInstance() { assert(mspGame != nullptr); return mspGame; };

	GraphicsSystem* getGraphicsSystem() { return mpGraphicsSystem; }
	DataManager* getDataManager() { return mpDataManager; }

};