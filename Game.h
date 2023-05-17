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

	bool mIsRunning = false;
	float mLoopTime = 16.7f;

	static Game* mspGame;

	// Constructor/Destructor 
	Game() {};
	~Game();

public:
	////-FUNCTIONS-

	void doLoop();

	void input();
	void update(float dt);
	void draw();
	
	bool init();
	void cleanup();

	virtual void handleEvent(const Event& theEvent) override;

	void createSmurf(Vector2D pos);

	static void initInstance() { mspGame = new Game(); };
	static void cleanupInstance() { delete mspGame; mspGame = nullptr; };
	static Game* getInstance() { assert(mspGame != nullptr); return mspGame; };

	GraphicsSystem* getGraphicsSystem() { return mpGraphicsSystem; }

};