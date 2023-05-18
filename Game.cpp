#include "GraphicsSystem.h"
#include "InputSystem.h"

#include "UnitManager.h"
#include "GraphicsBufferManager.h"
#include "DataManager.h"

#include "Animation.h"
#include "Unit.h"
#include "HUD.h"

#include "EventSystem.h"
#include "GameEvent.h"

#include "Game.h"

#include "InputTranslator.h"

Game* Game::mspGame = nullptr;

Game::~Game()
{
	cleanup();
}

void Game::doLoop()
{
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;
	pPerformanceTracker->startTracking("loop");
	Timer timer;
	bool shouldContinue = true;
	float deltaTime = 0;

	while (mIsRunning)
	{
		pPerformanceTracker->clearTracker("loop");
		
		timer.start();

		update(deltaTime);
		draw(deltaTime);

		timer.sleepUntilElapsed(mLoopTime);
		
		deltaTime = pPerformanceTracker->getElapsedTime("loop");
		cout << endl << "Time for loop:" << pPerformanceTracker->getElapsedTime("loop") << " ms" << endl;
		elapsedGameTime += pPerformanceTracker->getElapsedTime("loop");
	}
	delete pPerformanceTracker;
}

void Game::update(float dt)
{
	mpUnitManager->update(dt);
	mpInputSystem->update(dt);
}

void Game::draw(float dt)
{
	mpGraphicsSystem->draw(Vector2D(0, 0), mpGraphicsBufferManager->getBuffer("Background"));
	mpUnitManager->draw();
	mpHUD->fps(dt);
	mpHUD->score(mPoints);
	mpHUD->timer(elapsedGameTime/1000);
	mpGraphicsSystem->flip();
}

bool Game::init()
{
	const string SHARED_ASSETS_PATH = "..\\..\\shared\\assets\\";
	const string PRIVATE_ASSETS_PATH = "\\assets\\config.txt";
	const string SMURFS_FILENAME = "smurf_sprites.png";
	const string DEAN_FILENAME = "dean_sprites.png";
	const string NUMBERED_FILENAME = "smurf_sprites_numbered.png";
	const string BACKGROUND_FILENAME = "Woods.png";

	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;

	//event listeners

	EventSystem::getInstance()->addListener((EventType)CLOSE_GAME, this);
	EventSystem::getInstance()->addListener((EventType)PLACE_SMURF, this);
	EventSystem::getInstance()->addListener((EventType)REMOVE_SMURF, this);
	EventSystem::getInstance()->addListener((EventType)TOGGLE_ANIMATION, this);
	EventSystem::getInstance()->addListener((EventType)SWAP_ANIMATION, this);

	//init member objects
	mpGraphicsSystem = new GraphicsSystem();
	mpInputSystem = new InputSystem();
	mpInputTranslator = new InputTranslator();
	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpUnitManager = new UnitManager();
	mpDataManager = new DataManager(PRIVATE_ASSETS_PATH);

	if (!mpGraphicsSystem->init(DISP_WIDTH, DISP_HEIGHT))
	{
		cout << "ERROR - Init failed\n";
		system("pause");
		return false;
	}

	if (!mpInputSystem->init())
	{
		cout << "ERROR - Init failed\n";
		system("pause");
		return false;
	}

	mpHUD = new HUD();

	GraphicsBuffer* mpSmurfSheetBuffer = new GraphicsBuffer(SHARED_ASSETS_PATH + SMURFS_FILENAME);
	GraphicsBuffer* mpDeanSheetBuffer = new GraphicsBuffer(SHARED_ASSETS_PATH + DEAN_FILENAME);
	GraphicsBuffer* mpBackgroundBuffer = new GraphicsBuffer(DISP_WIDTH, DISP_HEIGHT, mBlack);
	mpGraphicsBufferManager->addBuffer("SmurfSheet", mpSmurfSheetBuffer);
	mpGraphicsBufferManager->addBuffer("DeanSheet", mpDeanSheetBuffer);
	mpGraphicsBufferManager->addBuffer("Background", mpBackgroundBuffer);

	mIsRunning = true;

	return true;
}

void Game::cleanup()
{
	delete mpDataManager;
	delete mpHUD;
	delete mpInputTranslator;
	delete mpGraphicsBufferManager;
	delete mpUnitManager;
	delete mpInputSystem;
	delete mpGraphicsSystem;
}

//DO THIS + GameEvent.cpp
void Game::handleEvent(const Event& theEvent)
{
	switch (theEvent.getType())
	{
	case GameEventType::CLOSE_GAME:
		mIsRunning = false;
		break;
	case GameEventType::PLACE_SMURF:
		if (mpInputSystem->getMouseState(1))
		{
			createSmurf(((GameEvent&)theEvent).getPosition());
		}
		break;
	case GameEventType::REMOVE_SMURF:
		if (mpInputSystem->getMouseState(2))
		{
			Unit* theUnit = mpUnitManager->getUnitAtPosition(((GameEvent&)theEvent).getPosition());
			if (theUnit != nullptr)
			{
				//mpUnitManager->killUnit(theUnit);
			}
		}
		break;
	case GameEventType::TOGGLE_ANIMATION:
		//for (int i = 0; i < mpUnitManager->getUnitCount(); i++)
		//{
		//	mpUnitManager->getUnit(i)->getAnimation()->toggleAnimation();
		//}
		break;
	case GameEventType::SWAP_ANIMATION:
		if (mpInputSystem->getKeyState(KeyCode::ENTER))
		{
		//	mpUnitManager->getUnit(mpUnitManager->getUnitCount() - 1)->swapAnimation();
		}
		break;
	default:
		break;
	}
}

void Game::createSmurf(Vector2D pos)
{
	Animation* mpSmurfAnim = new Animation(mpGraphicsBufferManager->getBuffer("SmurfSheet"), 4, 4);
	Animation* mpDeanAnim = new Animation(mpGraphicsBufferManager->getBuffer("DeanSheet"), 4, 4);

	vector<Animation*> mpAnimations;

	mpAnimations.push_back(mpSmurfAnim);
	mpAnimations.push_back(mpDeanAnim);

	Unit* mpUnit = new Unit(pos, mpAnimations);
	//mpUnitManager->addUnits(mpUnit);
	
}