#include "GraphicsSystem.h"
#include "InputSystem.h"

#include "UnitManager.h"
#include "GraphicsBufferManager.h"
#include "DataManager.h"

#include "Animation.h"
#include "Unit.h"
#include "UnitSpawner.h"
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

		mpInputSystem->update(deltaTime);

		if(!mIsPaused)
		{
			update(deltaTime);
		}
		
		draw(deltaTime);

		timer.sleepUntilElapsed(mLoopTime);
		
		deltaTime = pPerformanceTracker->getElapsedTime("loop");
		//cout << endl << "Time for loop:" << pPerformanceTracker->getElapsedTime("loop") << " ms" << endl;
		elapsedGameTime += pPerformanceTracker->getElapsedTime("loop");
	}
	delete pPerformanceTracker;
}

void Game::update(float dt)
{
	mpUnitManager->update(dt);
	mpUnitSpawner->update(dt);
	if(mPoints < 0)
	{
		mGameOver = true;
		mIsPaused = true;
	}
}

void Game::draw(float dt)
{
	mpGraphicsSystem->draw(Vector2D(0, 0), mpGraphicsBufferManager->getBuffer("Background"));
	mpUnitManager->draw();
	
	if(!mIsPaused)
	{
		mpHUD->fps(dt);
		mpHUD->score(mPoints);
		mpHUD->timer(elapsedGameTime / 1000);
	}else if(mGameStart)
	{
		mpHUD->startScreen();
	}
	else if (mGameOver)
	{
		mpHUD->gameOver();
	}
	else
	{
		mpHUD->pauseScreen();
	}
	
	mpGraphicsSystem->flip();
}

bool Game::init()
{
	const string SHARED_ASSETS_PATH = "..\\..\\shared\\assets\\";
	const string PRIVATE_ASSETS_PATH = "assets\\";
	const string SMURFS_FILENAME = "smurf_sprites.png";
	const string DEAN_FILENAME = "dean_sprites.png";
	const string BALLS_FILENAME = "glowing-balls.png";
	const string CONFIG_FILENAME = "config.txt";
	const string SOUNDFILES_FILENAME = "soundfiles.txt";
	const string NUMBERED_FILENAME = "smurf_sprites_numbered.png";

	//event listeners

	EventSystem::getInstance()->addListener((EventType)CLOSE_GAME, this);
	EventSystem::getInstance()->addListener((EventType)UNPAUSE_GAME, this);
	EventSystem::getInstance()->addListener((EventType)SWAP_UNIT, this);
	EventSystem::getInstance()->addListener((EventType)BLUE_ORB_DESTROYED, this);
	EventSystem::getInstance()->addListener((EventType)RED_ORB_DESTROYED, this);

	//init member objects
	mpGraphicsSystem = new GraphicsSystem();
	mpInputSystem = new InputSystem();
	mpInputTranslator = new InputTranslator();
	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpDataManager = new DataManager(PRIVATE_ASSETS_PATH + CONFIG_FILENAME);
	
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
	GraphicsBuffer* mpBackgroundBuffer = new GraphicsBuffer(Game::getInstance()->getGraphicsSystem()->getWidth(), Game::getInstance()->getGraphicsSystem()->getHeight(), mBlack);
	mpGraphicsBufferManager->addBuffer("SmurfSheet", mpSmurfSheetBuffer);
	mpGraphicsBufferManager->addBuffer("DeanSheet", mpDeanSheetBuffer);
	mpGraphicsBufferManager->addBuffer("Background", mpBackgroundBuffer);
	
	Animation mpSmurfAnim = Animation(mpGraphicsBufferManager->getBuffer("SmurfSheet"), 4, 4);
	Animation mpDeanAnim = Animation(mpGraphicsBufferManager->getBuffer("DeanSheet"), 4, 4);

	vector<Animation> mpAnimations = vector<Animation>();

	mpAnimations.push_back(mpSmurfAnim);
	mpAnimations.push_back(mpDeanAnim);

	mpUnitManager = new UnitManager(mpAnimations);
	mpUnitSpawner = new UnitSpawner();

	mIsRunning = true;

	return true;
}

void Game::cleanup()
{
	delete mpUnitSpawner;
	delete mpDataManager;
	delete mpHUD;
	delete mpInputTranslator;
	delete mpGraphicsBufferManager;
	delete mpUnitManager;
	delete mpInputSystem;
	delete mpGraphicsSystem;
}

void Game::handleEvent(const Event& theEvent)
{
	switch (theEvent.getType())
	{
	case GameEventType::CLOSE_GAME:
		if (mIsPaused)
		{
			mIsRunning = false;
		}
		else
		{
			mIsPaused = true;
		}
		break;
	case GameEventType::UNPAUSE_GAME:
		if (mGameStart) 
		{
			mGameStart = false;
		}
		if(mIsPaused)
		{
			mIsPaused = false;
		}
		break;

	case GameEventType::SWAP_UNIT:
		if (mpInputSystem->getMouseState(1))
		{
			Unit* theUnit = mpUnitManager->getUnitAtPosition(((GameEvent&)theEvent).getPosition());
			if (theUnit != nullptr)
			{
				theUnit->swapUnit();
			}
		}
		break;
	case GameEventType::RED_ORB_DESTROYED:
		mPoints -= mPointDecrease;
		break;
	case GameEventType::BLUE_ORB_DESTROYED:
		mPoints += mPointIncrease;
		break;
	default:
		break;
	}
}